# Settings
project (uci_code_src)

# Files to be compiled.
file(GLOB uci_code_srcfiles "*.cpp" "**/*.cpp")
add_executable(uci_code_src ${uci_code_srcfiles})

# Make this folder linkable for parent folder.
target_link_libraries(uci_code_src -lpthread)