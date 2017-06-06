project (uci_code_benchmarks)

# It's not great, I know.
file(GLOB uci_code_benchmarksfiles "*.cpp" "**/*.cpp" "../src/*.cpp" "../src/**/*.cpp")

# exclude src/main to avoid multiple main files.
list(REMOVE_ITEM uci_code_benchmarksfiles "${CMAKE_CURRENT_SOURCE_DIR}/../src/main.cpp")

add_executable(uci_code_benchmarks ${uci_code_benchmarksfiles})

target_link_libraries(uci_code_benchmarks benchmark -lpthread)