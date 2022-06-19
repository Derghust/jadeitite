set(C_FILES ../../src/jadeitite_glut.c ../../src/jadeitite_math.c ../../src/jadeitite_string.c ../../src/jadeitite_memory.c)

add_executable(base_template src/main.c ${C_FILES})
target_include_directories(base_template PRIVATE ../../src/)
target_link_libraries(base_template PRIVATE GL GLU glut m)
