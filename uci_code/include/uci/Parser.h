#pragma once

#include <vector>
#include <map>
#include "./definitions.h" // in cpp files use "uci_protocol/definitions.h"

namespace uci {
class Parser {
 private:
  const std::map<std::string, std::vector<std::vector<std::string>>> commands = { // I'll fix this later
      {"uci_protocol", {
          {}
      }},
      {"debug", {
          {"on"},
          {"off"}
      }},
      {"isready", {
          {}
      }},
      {"setoption", {
          {"name", "value"}
      }},
      {"register", {
          {"later"},
          {"name", "code"}
      }},
      {"ucinewgame", {
          {}
      }},
      {"position", {
          {"fen", "moves"},
          {"startpos", "moves"}
      }},
      {"go", {
          {"searchmoves"},
          {"ponder"},
          {"wtime"},
          {"btime"},
          {"winc"},
          {"binc"},
          {"movestogo"},
          {"depth"},
          {"nodes"},
          {"mate"},
          {"movetime"},
          {"infinite"}
      }},
      {"stop", {
          {}
      }},
      {"ponderhit", {
          {}
      }},
      {"quit", {
          {}
      }},
  };

 public:
  Parser();
  ~Parser();

  uint8_t parseInputForCommand(std::string input);
  arguments_t parseInputForArguments(std::string input);
  std::pair<uint8_t, arguments_t> parseInput(std::string input);
};

}
