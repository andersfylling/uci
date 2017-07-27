#pragma once

#include <vector>
#include <map>
#include "./definitions.h" // in cpp files use "uci/definitions.h"

namespace uci {
class Parser {
 private:
  const std::map<std::string, std::vector<std::vector<std::string>>> commands = { // I'll fix this later
      {"uci", {
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
      {"black", {
            {}
        }},
      {"white", {
            {}
        }}
  };

 public:
  Parser();
  ~Parser();

  uint8_t                                 parseInputForCommand(std::string input);
  ::uci::arguments_t                      parseInputForArguments(std::string input);
  std::pair<uint8_t, ::uci::arguments_t>  parseInput(std::string input);

  // extract the first word from a sentence
  std::string getFirstWord(const std::string sentence);

  // extract the first word after position
  std::string getFirstWord(const uint8_t index, const std::string sentence);
};

}
