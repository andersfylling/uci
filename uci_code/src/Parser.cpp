// header file
#include "uci/Parser.h"

// cpp dependencies
#include <sstream>
#include <algorithm>

// local dependencies
#include "uci/events.h"


namespace uci {

/**
 * Constructor
 */
Parser::Parser() {
}

/**
 * Destructor
 */
Parser::~Parser() {
}


/**
 * Converts UCI terminal inputs to a std::map of arguments/parameters.
 *
 * @warning Currently this is written to handle multiple UCI commands in one string.
 *          This is only a missunderstanding on my part and will be fixed to deal with one string as one UCI command / input
 *          which is correct according to protocol.
 *
 * @return std::pair<uint8_t, arguments_t> An UCI command and the map with all the parameters / arguments related to that command.
 */
std::pair<uint8_t, arguments_t> Parser::parseInput(std::string input) {
  auto command = this->parseInputForCommand(input);
  if (command == ::uci::event::NO_MATCHING_COMMAND) {
    return std::pair<uint8_t, arguments_t>();
  }

  // get arguments
  auto arguments = this->parseInputForArguments(input);

  return std::pair<uint8_t, arguments_t>();
}

std::map<std::string, std::string> Parser::parseInputForArguments(std::string input) {
  std::stringstream request(input);

  // remove command, if it hasn't been removed already.
  // This assumes that if the first word is a match for a command, its a true command
  // and removes it.
  std::string command;
  if (this->parseInputForCommand(input) != ::uci::event::NO_MATCHING_COMMAND) {
    request >> command;
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);
  }

  // get arguments from argumentsStr.
  arguments_t arguments;
  std::string firstWord;
  request >> firstWord;

  const auto cmdEntry = this->commands.find(command);
  auto &vecHolder = cmdEntry->second;
  for (int i = 0; i < vecHolder.size(); i++) {
    auto &v = vecHolder.at(i);

    // if the first key in this vector doesn't equal the first word, ignore the rest and continue
    // to the next vector
    if (v.size() == 0 || v.front() != firstWord) {
      continue;
    }

    // add the key to the arguments map
    arguments.insert(std::pair<std::string, std::string>(firstWord, ""));

    // if the next word is not another key, it should be the value of this key.
    // this value is appended upon until the next key is met.
    std::string key = firstWord;
    std::string value = "";
    std::string nextWord;
    int j = 1;
    while (request >> nextWord) {
      //std::cout << request.str() << std::endl;

      if (j < v.size() && v.at(j) == nextWord) {
        // the next word is a key, store the existing value to the old key and clear it.
        j += 1;
        arguments[key] = value;
        value = "";
        key = nextWord;
        arguments.insert(std::pair<std::string, std::string>(key, ""));
        continue; // update the next word!
      }

      if (value == "") {
        value = nextWord;
      } else {
        value += " " + nextWord;
      }
    }

    arguments[key] = value;

    // finished
    break;
  }

  return arguments;
}


/**
 * Converts a UCI terminal input to a UCI command.
 * @note this should be a constexpr.
 */
uint8_t Parser::parseInputForCommand(std::string input) {
  std::string command = this->getFirstWord(input);

  // check if the command exists.
  // this is bad. find a way to store the uint8_t value or change it to a char, whatever it takes to reduce this mess.
  auto entry = this->commands.find(command);
  uint8_t event = 0;
  if (entry == this->commands.end()) {
    event = ::uci::event::NO_MATCHING_COMMAND;
  } else if (command == "uci") {
    event = ::uci::event::UCI;
  } else if (command == "debug") {
    event = ::uci::event::DEBUG;
  } else if (command == "isready") {
    event = ::uci::event::ISREADY;
  } else if (command == "setoption") {
    event = ::uci::event::SETOPTION;
  } else if (command == "register") {
    event = ::uci::event::REGISTER;
  } else if (command == "ucinewgame") {
    event = ::uci::event::UCINEWGAME;
  } else if (command == "position") {
    event = ::uci::event::POSITION;
  } else if (command == "go") {
    event = ::uci::event::GO;
  } else if (command == "stop") {
    event = ::uci::event::STOP;
  } else if (command == "ponderhit") {
    event = ::uci::event::PONDERHIT;
  } else if (command == "quit") {
    event = ::uci::event::QUIT;
  } else if (command == "black") {
    event = ::uci::event::BLACK;
  } else if (command == "white") {
    event = ::uci::event::WHITE;
  }

  return event;
}


/**
 * Loop the sentence until a space is hit, every char before that is returned as a std::string.
 *
 * @param sentence std::string Sentence where the first word is extract.
 * @return std::string the first word of the sentence.
 */
std::string Parser::getFirstWord(const std::string sentence) {
  return this->getFirstWord(0, sentence);
}


/**
 * Loop the sentence until a space is hit, every char before that is returned as a std::string.
 * This lets you however get the first word after X chars.
 *
 * @warning if the first char is a space, this returns "".
 *
 * @param index uint8_t The position where the loop should start. 0 -> X.
 * @param sentence std::string Sentence where the first word is extract.
 * @return std::string the first word of the sentence.
 */
std::string Parser::getFirstWord(const uint8_t index, const std::string sentence) {
  std::string word = "";
  int prog = index;

  const auto length = sentence.size();
  for (; prog < length && sentence[prog] != ' '; prog++) {
    word += sentence[prog];
  }

  return word;
}


}
