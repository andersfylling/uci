# External project files
# These are ignored if this is used as a external / sub module
if (${CMAKE_CURRENT_SOURCE_DIR} EQUAL ${CMAKE_SOURCE_DIR})
    set(UCI_BENCHMARK_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/benchmark/include")
    set(UCI_CATCH_INCLUDE_DIR     "${CMAKE_CURRENT_SOURCE_DIR}/external/Catch/include")
endif()

# Main project files
set(UCI_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/include")
set(UCI_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")