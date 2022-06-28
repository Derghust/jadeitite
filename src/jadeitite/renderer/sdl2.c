#include "sdl2.h"

#include "jadeitite/log.h"
#include "jadeitite/datatypes.h"
#include <SDL2/SDL.h>

u8 window_init(int p_argc, char *p_argv[], winProp_t p_winProp) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    LOG_FATAL("Failed to initialize sdl video [error=%s]", SDL_GetError());
    return RS_FAILED;
  }

  s_sdl_window = SDL_CreateWindow(
    p_winProp.label,
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    p_winProp.width,
    p_winProp.height,
    0
    );
  if (s_sdl_window == NULL) {
    LOG_FATAL("Failed to create sdl window [error=%s]", SDL_GetError());
    return RS_FAILED;
  }

  return RS_OK;
}
