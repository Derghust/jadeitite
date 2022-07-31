add_executable(sdl_template src/main.c)
target_include_directories(sdl_template PRIVATE ../../src/)
target_link_libraries(sdl_template PRIVATE jadeitite_sdl2)
target_compile_definitions(sdl_template PRIVATE JADEITITE_RENDERER_SDL2)
