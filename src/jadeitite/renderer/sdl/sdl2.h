#ifndef JADEITITE_SDL2_H
#define JADEITITE_SDL2_H

#include "jadeitite/renderer/window.h"
#include "jadeitite/renderer/callbacks.h"
#include "jadeitite/datatypes.h"

#include <SDL2/SDL.h>

//======================================
//         SDL2 static variables
//======================================

static SDL_Window *s_sdl_window;
static SDL_Renderer *s_sdl_renderer;

//======================================
//            SDL2 engine
//======================================

u8 window_close(void);
u8 window_run(callbacks_t p_callbacks, winProp_t p_winProp);
u8 window_init(int p_argc, char *p_argv[], winProp_t p_winProp);
void window_resize(int p_width, int p_height);

//======================================
//           SDL2 rendering
//======================================

/**
 * Clear window
 */
static inline void render_begin(void) {
  SDL_RenderClear(s_sdl_renderer);
}

/**
 * Swap render buffer
 */
static inline void render_end(void) {
  SDL_RenderPresent(s_sdl_renderer);
}

#endif //JADEITITE_SDL2_H
