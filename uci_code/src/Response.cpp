#include "uci/Response.h"

namespace uci {

/**
 * Sends a std::string to the UCI GUI.
 */
void send(std::string res) {
  std::cout << res << std::endl;
}

/**
 * Sends a UCI response based on a UCI command and a std::map as arguments_t.
 */
void send(std::string command, ::uci::arguments_t args) {
  std::string res = command;

  for (auto &entry : args) {
    res += entry.first + ' ' + entry.second;
  }

  send(res);
}

}