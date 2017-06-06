project (uci_code_tests)

# It's not great, I know.
file(GLOB uci_code_testsfiles "*.cpp" "**/*.cpp" "../src/*.cpp" "../src/**/*.cpp")

# exclude src/main to avoid multiple main files.
list(REMOVE_ITEM uci_code_testsfiles "${CMAKE_CURRENT_SOURCE_DIR}/../src/main.cpp")

add_executable(uci_code_tests  ${uci_code_testsfiles})

target_link_libraries(uci_code_tests -lpthread)