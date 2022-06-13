AUX_SOURCE_DIRECTORY(../../src C_FILES)

add_executable(base_template src/main.c ${C_FILES})
target_include_directories(base_template PRIVATE ../../src/)
target_link_libraries(base_template PRIVATE GL GLU glut m)
