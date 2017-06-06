include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories(${UCI_BENCHMARK_INCLUDE_DIR})
include_directories(${UCI_CATCH_INCLUDE_DIR})

add_subdirectory(src)           # source files
add_subdirectory(benchmarks)    # Our benchmarks
add_subdirectory(tests)         # Our tests