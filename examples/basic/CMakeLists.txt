set(CMAKE_C_STANDARD 99)

add_executable(jadeitite_gl src/main.c)
target_include_directories(jadeitite_gl PRIVATE ../../src)
target_link_libraries(jadeitite_gl PRIVATE jadeitite_shared)

add_executable(jadeitite_asset src/prepare.c)
target_include_directories(jadeitite_asset PRIVATE ../../src ../../vendors)
