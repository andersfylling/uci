#pragma once

#include <cstdint>

namespace uci {

// Different commands created by the UCI protocol
namespace event {

// errors, this isn't really a UCI protocol command, but used within this project.
static const uint8_t NO_MATCHING_COMMAND = 0;

// commands issued by the UCI protocol
static const uint8_t TEST = 5;
static const uint8_t UCI = 10;
static const uint8_t DEBUG = 20;
static const uint8_t ISREADY = 30;
static const uint8_t SETOPTION = 40;
static const uint8_t REGISTER = 50;
static const uint8_t UCINEWGAME = 60;
static const uint8_t POSITION = 70;
static const uint8_t GO = 80;
static const uint8_t STOP = 90;
static const uint8_t PONDERHIT = 100;
static const uint8_t QUIT = 110;

}
}
