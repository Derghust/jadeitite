set(CMAKE_C_STANDARD 99)

add_executable(basic src/main.c)
target_include_directories(basic PRIVATE ../../src/)
target_link_libraries(basic PRIVATE m ${PACKAGE_SDL})
