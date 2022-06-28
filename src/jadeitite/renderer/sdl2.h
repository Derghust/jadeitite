#ifndef JADEITITE_SDL2_H
#define JADEITITE_SDL2_H

#include "jadeitite/renderer/window.h"
#include "jadeitite/datatypes.h"
#include "callbacks.h"

#include <SDL2/SDL.h>

//======================================
//         SDL2 static variables
//======================================

static SDL_Window *s_sdl_window;
static SDL_Renderer *s_sdl_renderer;

//======================================
//            SDL2 engine
//======================================

u8 window_run(callbacks_t p_callbacks, winProp_t p_winProp);
u8 window_init(int p_argc, char *p_argv[], winProp_t p_winProp);
void window_resize(int p_width, int p_height);

#endif //JADEITITE_SDL2_H
