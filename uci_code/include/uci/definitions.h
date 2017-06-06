#pragma once

#include <iostream>
#include <map>
#include <functional>

namespace uci {

// Holds the keys and associated values per UCI input.
typedef std::map<std::string, std::string> arguments_t;

// The lambda type which is used to add a function listener to an event.
typedef std::function<void(arguments_t)> callback_t;
}
