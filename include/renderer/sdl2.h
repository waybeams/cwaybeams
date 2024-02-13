//
// Created by lukebayes on 2/2/2024
//

#ifndef __sdl2_h__
#define __sdl2_h__

#include <SDL2/SDL.h>

typedef struct sdl2_context_t {
  SDL_Window **windows;
  SDL_Surface **surfaces;
  size_t window_count;
  size_t window_index;
}sdl2_context_t;

#endif // __sdl2_h__


