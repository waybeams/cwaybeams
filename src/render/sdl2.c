#include "beam.h"
#include "node.h"
#include "render/sdl2.h"
#include <SDL2/SDL.h>
#include <stdio.h>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#define SDL_WIN_FLAGS ( \
    SDL_WINDOW_SHOWN | \
    SDL_WINDOW_RESIZABLE | \
    SDL_WINDOW_ALLOW_HIGHDPI)

beam_signal_t *beam_signals_gather(beam_surface_t *s) {
  // TODO(lbayes): Return a stream of beam signals allocated on the arena
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
      case SDL_KEYDOWN:
        SDL_Log("User just pressed down a key!");
        break;  
      case SDL_WINDOWEVENT:
        if (e.window.event == SDL_WINDOWEVENT_CLOSE) {
          SDL_Log("User closed the window!");
          s->should_close = true;
        }
        break;
      default:
        break;
    }
  }
  // printf("beam_signals_gather with type: %d", s->type);
  return NULL;
}

beam_surface_t *beam_create_surface(beam_surface_type t) {
  beam_surface_t *s = calloc(sizeof(beam_surface_t), 1);
  if (s == NULL) {
    printf("failed to allocate beam_surface_t");
    return NULL;
  }

  s->platform = calloc(sizeof(sdl2_context_t), 1);
  s->type = t;
  return s;
}

s32_t beam_window_should_close(beam_surface_t *s) {
  if (s != NULL && s->should_close) {
    return 1;
  }

  return 0;
}

void beam_surface_free(beam_surface_t *s) {
  sdl2_context_t *p = s->platform;

  if (p != NULL) {
    // Destroy window
    SDL_DestroyWindow(p->window);
  }

  // Quit SDL subsystems
  SDL_Quit();

  free(p);
  free(s);
}

s32_t beam_render(beam_surface_t *surface, beam_signal_t *signals,
                 node_t *root) {
  if (signals != NULL) {
    // beam_signal_t *s = *signals;
    // log_info("and signals: %d", s->type);
  }

  if (surface != NULL) {
    // log_info("beam_render with: %d", surface->type);
  }

  if (root != NULL) {
    printf("root: %d", root->type);

  }

  sdl2_context_t *p = surface->platform;

  if (p == NULL) {
    printf("PLATFORM IS NULL\n");
    return -1;
  }

  if (p->window == NULL) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
      p->window = SDL_CreateWindow("SDL2 Hello World", SDL_WINDOWPOS_UNDEFINED,
          SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WIN_FLAGS);
      // Get window surface
      p->surface = SDL_GetWindowSurface(p->window);
      if (p->window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      }
    }
  }

  // Fill the surface
  SDL_FillRect(p->surface, NULL, SDL_MapRGB(p->surface->format, 0x16, 0x16, 0x16));

  // Update the surface
  SDL_UpdateWindowSurface(p->window);

  return BeamSuccess;
}
