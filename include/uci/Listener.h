#pragma once

#include <map>
#include <functional>
#include <thread>
#include <mutex>
#include "./Parser.h" // in cpp files use "uci/Parser.h"
#include "./definitions.h" // in cpp files use "uci/Definitions.h"

namespace uci {
class Listener {
 private:
  std::map<const uint8_t, std::map<const int, const callback_t>> events; // (eventID, (listenerID, eventHandler))
  std::map<const int, const uint8_t> eventIDs; //(listenerID, eventID)
  int lastID;
  std::thread listener;
  bool runListener;
  Parser parser;

  std::mutex eventsMutex;
  std::mutex eventIDsMutex;

 public:
  Listener();
  ~Listener();

  bool initiateListener();
  bool joinListener();
  bool setupListener();

  int addListener(const uint8_t event, const callback_t &func);
  bool hasListener(int listenerID);
  void hasListener(int listenerID, std::function<void(bool exists)> lockedCallback);
  bool removeListener(int listenerID);
  void fireEvent(const uint8_t event);
  void fireEvent(const uint8_t event, const arguments_t arguments);

  void stopListening();

  void removeListenerThread(int listenerID);
  bool joinListenerAndStop();
};
}
}
