add_executable(base_template src/main.c)
target_include_directories(base_template PRIVATE ../../src/)
target_link_libraries(base_template PRIVATE jadeitite)
