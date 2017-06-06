
// CPP dependencies
#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <thread>
#include <mutex>

// local dependencies
#include "uci/definitions.h"
#include "uci/events.h"
#include "uci/Parser.h"
#include "uci/Listener.h"


namespace uci {

/**
 * Constructor
 */
Listener::Listener()
    : runListener(false),
      lastID(2),
      strict(false)
{
}

/**
 * Constructor
 *
 * @param strict bool Whether or not unknown commands should be ignored. strict(True) will ignore unknown commands.
 */
Listener::Listener(bool strict)
    : runListener(false),
      lastID(2),
      strict(strict)
{
}

/**
 * Destructor
 */
Listener::~Listener() {
}

/**
 * Add a new listener to be triggered at a given UCI event / command.
 *
 * @param event uint8_t Use uci::event::? for UCI commands and uci::event::error in case a UCI error takes place.
 * @param func std::function<void(std::map<std::string, std::string>)> The callback function / lambda to handle the incoming UCI event
 * @return int Listener ID. This can be used later to remove and change listeners dynamically.
 */
int Listener::addListener(const uint8_t event,
                          const std::function<void(std::map<std::string, std::string>)> &func) {
  const int id = this->lastID += 1;

  // check if event key already exists, if not create it.
  if (this->events.count(event) == 0) {
    this->events.insert(
        std::pair<const uint8_t, std::map<const int, const std::function<void(std::map<std::string, std::string>)>>>(
            event, std::map<const int, const std::function<void(std::map<std::string, std::string>)>>()
        )
    );
  }

  this->events[event].insert(std::pair<const int, const std::function<void(std::map<std::string, std::string>)>>(id,
                                                                                                                 func));
  this->eventIDs.insert(std::pair<const int, const uint8_t>(id, event));

  return id;
}

/**
 * Initiates the UCI listener in a new thread.
 * Note that this requires you to join the thread later so the program can exit correctly.
 *
 * @see Listener::joinListener() to do join the thread.
 * @return bool False, always..
 */
bool Listener::initiateListener() {

  this->runListener = true;

  this->listener = std::thread([&] {
    std::string line;
    while (this->runListener && std::getline(std::cin, line)) {
      if (line == "") {
        continue;
      }

      auto event = this->parser.parseInputForCommand(line);

      // if strict mode is on and the command is unknown, it will be ignored.
      if (this->strict && event == uci::event::NO_MATCHING_COMMAND) {
        continue;
      }


      // Get the args and fire all bond listeners.
      auto args = this->parser.parseInputForArguments(line);
      this->fireEvent(event, args);
    }
  });

  return false;
}

/**
 * Joins the thread to the main thread.
 * This makes sure there are no loose threads in the end when the program exits.
 *
 * @return bool True the thread joined.
 */
bool Listener::joinListener() {
  if (this->listener.joinable()) {
    this->listener.join();
    return true;
  }
  return false;
}

/**
 * Joins the listener thread and stops the listener thread.
 *
 * @warning Not completed. Only tells the listener on next run to stop.
 * @return bool True if the listener has joined threads and is set to stop at next run / loop round.
 */
bool Listener::joinListenerAndStop() {
  this->runListener = false;
  bool joined = this->joinListener();

  return joined && !this->runListener;
}

/**
 * Setup the listener thread and join it to the main thread.
 *
 * @return bool True if successfull.
 */
bool Listener::setupListener() {
  this->initiateListener();
  return this->joinListener();
}

/**
 * Triggers an UCI event.
 * Every listener binded to this event is fired / called without arguments.
 */
void Listener::fireEvent(const uint8_t event) {
  this->fireEvent(event, std::map<std::string, std::string>());
}

/**
 * Triggers an UCI event.
 * Every listener binded to this event is fired / called with arguments.
 *
 * @param args arguments_t A map to hold UCI parameters.
 */
void Listener::fireEvent(const uint8_t event, const arguments_t args) {
  auto entry = this->events.find(event);

  if (entry == this->events.end()) {
    return;
  }

  for (auto &observerEntry : entry->second) {
    auto &observer = observerEntry.second;
    observer(args);
  }
}

/**
 * Checks whether or not a listener exists base on ID.
 *
 * @multithreadingSupport false
 * @param int listenerID
 * @return True if listener with listenerID exists
 */
bool Listener::hasListener(const int listenerID) {
  return this->eventIDs.count(listenerID) > 0;
}

/**
 * Checks whether or not a listener exists base on ID.
 * Then calls the callback during mutex lock of both events and eventIDs.
 *
 * @multithreadingSupport true
 * @param int listenerID
 * @return True if listener with listenerID exists
 */
void Listener::hasListener(int listenerID, std::function<void(bool exists)> lockedCallback) {
  static std::mutex m;
  {
    std::lock_guard<std::mutex> e(m);
  };

  {
    std::lock(this->eventIDsMutex, this->eventsMutex);
    std::lock_guard<std::mutex> es(this->eventsMutex, std::adopt_lock);
    std::lock_guard<std::mutex> eis(this->eventIDsMutex, std::adopt_lock);

    {
      std::lock_guard<std::mutex> e(m);
    }

    // ok
    bool exist = this->hasListener(listenerID);
    lockedCallback(exist);
  }

}

/**
 * Makes sure a listenerID (+ it's listener) does not exist in the system afterwards.
 *
 * @multithreadingSupport false
 * @param listenerID
 * @return true if the listener has been removed or does not exist.
 */
bool Listener::removeListener(const int listenerID) {
  if (!this->hasListener(listenerID)) {
    return true;
  }

  // find and remove function
  auto eventID = this->eventIDs.find(listenerID)->second;
  auto &eventEntry = this->events.find(eventID)->second;
  eventEntry.erase(eventEntry.find(listenerID));

  // then remove the listenerID
  this->eventIDs.erase(this->eventIDs.find(listenerID));

  return !this->hasListener(listenerID);
}

/**
 * Makes sure a listenerID (+ it's listener) does not exist in the system afterwards.
 *
 * @multithreadingSupport true
 * @param listenerID
 * @return true if the listener has been removed or does not exist.
 */
void Listener::removeListenerThread(int listenerID) {
  this->hasListener(listenerID, [&](bool exists) {
    this->removeListener(listenerID);
  });
}

/**
 * Stops the listener thread.
 *
 * @warning Not completed. Only tells the listener on next run to stop.
 */
void Listener::stopListening() {
  this->runListener = false;
}
}