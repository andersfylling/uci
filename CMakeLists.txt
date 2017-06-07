# settings
cmake_minimum_required(VERSION 3.6)
project(uci LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

# Third party libraries in lib
# These are ignored if this is used as a external / sub module
if (${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    # External project file headers
    set(UCI_BENCHMARK_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/benchmark/include")
    set(UCI_CATCH_INCLUDE_DIR     "${CMAKE_CURRENT_SOURCE_DIR}/external/Catch/include")

    add_subdirectory(external)
endif()

# Header files
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# Our source code
add_subdirectory(uci_code)