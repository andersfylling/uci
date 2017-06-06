include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories(${CHESS_ANN_BENCHMARK_INCLUDE_DIR})
include_directories(${CHESS_ANN_CATCH_INCLUDE_DIR})

add_subdirectory(src)           # source files
add_subdirectory(benchmarks)    # Our benchmarks
add_subdirectory(tests)         # Our tests