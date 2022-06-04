add_executable(base_template src/main.c)
target_include_directories(base_template PRIVATE ${PROJECT_SOURCE_DIR}/src/main)
target_link_libraries(base_template PRIVATE GL GLU glut m)
