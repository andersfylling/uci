# settings
cmake_minimum_required(VERSION 3.6)
project(uci LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

# Setup paths
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Paths.cmake")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

# Third party libraries in lib
add_subdirectory(external)

# Our source code
add_subdirectory(uci_code)