set(CMAKE_C_STANDARD 99)

add_executable(basic src/main.c)
target_link_libraries(basic PRIVATE jadeitite_shared)
