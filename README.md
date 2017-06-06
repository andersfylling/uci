# uci - Universal Chess Interface
See description: http://wbec-ridderkerk.nl/html/UCIProtocol.html
In case the website is down, see the description here: https://github.com/sciencefyll/uci/blob/master/description.md

## Features

- [x] Isolated code. Everything exists within the `uci` namespace.
- [x] Events or UCI commands has their own `event` namespace.
- [x] Threaded, as required.
- [x] Unit testing.
- [ ] CMakeList.txt that supports using this repo as a git-submodule.
- [ ] Benchmarks.

### GUI to ENGINE

- [x] Commands or event types.
- [x] Error command or error event type on unknown UCI commands.
- [x] String parser to convert UCI input to an std::map.
- [x] Typedefs for easier usage.
- [ ] Utilities to parse strings to int / float / etc.

### ENGINE to GUI

- [x] Nothing.
