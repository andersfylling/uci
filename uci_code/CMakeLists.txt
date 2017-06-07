add_subdirectory(src) # source files

# Externals
if ("${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}/uci_code")
    include_directories(${UCI_BENCHMARK_INCLUDE_DIR})
    include_directories(${UCI_CATCH_INCLUDE_DIR})

    add_subdirectory(benchmarks)    # Our benchmarks
    add_subdirectory(tests)         # Our tests
endif()