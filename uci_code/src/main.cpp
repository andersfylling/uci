#include "uci/events.h"
#include "uci/Listener.h"

int main (int argc, char* argv[]) {
  // example of basic usage
  ::uci::Listener l;

  l.addListener(::uci::event::UCI, [](::uci::arguments_t args){
    // since the uci command doesn't have any args, args should be empty. always.
    std::cout << "An UCI command was sent to the engine" << std::endl;

    // when you start the program, try to type uci in your console and see what happens.
  });

  // lets add a listener for every command this repo doesn't know about.
  l.addListener(::uci::event::NO_MATCHING_COMMAND, [](::uci::arguments_t args){
    std::cerr << "UCI command does not exit!" << std::endl;
  });

  // and finally since this isn't a chess engine, we will add actions for "quit".
  l.addListener(::uci::event::QUIT, [&](::uci::arguments_t args){
    l.stopListening();
  });


  // Start listening for uci commands in another thread, and join threads.
  l.setupListener();

  // You can also just create the new thread and then join it later like this:
  //
  // l.initiateThread();
  //
  // // do some stuff here...
  //
  // l.joinListener(); // since the threads joins here, this will block the main thread.
  // But it's needed to get a clean exit code.
  //

  return 0;
}