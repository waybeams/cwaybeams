#include "beam.h"
#include "log.h"
#include "node.h"
#include "node_visitor.h"
#include "renderer.h"
#include "renderer/sdl2.h"
#include <SDL2/SDL.h>
#include <stdio.h>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#define SDL_WIN_FLAGS ( \
    SDL_WINDOW_SHOWN | \
    SDL_WINDOW_RESIZABLE | \
    SDL_WINDOW_ALLOW_HIGHDPI)

static visit_status_t window_visitor(node_t *node, void *payload) {
  sdl2_context_t *p = (sdl2_context_t *)payload;

  if (node->type != BeamTypeWindow) {
    return VISIT_SUCCESS;
  }

  s32_t width = get_width(node);
  if (width == 0) {
    width = SCREEN_WIDTH;
  }

  s32_t height = get_height(node);
  if (height == 0) {
    height = SCREEN_HEIGHT;
  }
  char *title = get_title(node);
  if (strlen(title) == 0) {
    title = "Default Title";
  }

  size_t index = p->window_index++;
  SDL_Window *window = p->windows[index];
  SDL_Surface *surface = p->surfaces[index];

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    log_info("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  } else if (window == NULL) {
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WIN_FLAGS);

    if (window == NULL) {
      log_info("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      return VISIT_FAILURE;
    }

    // Get window surface
    surface = SDL_GetWindowSurface(window);
  }

  // Fill the surface
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0x16, 0x16, 0x16));

  // Update the surface
  SDL_UpdateWindowSurface(window);

  return VISIT_SUCCESS;
}

beam_signal_t *beam_signals_gather(beam_surface_t *s) {
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
  // log_info("beam_signals_gather with type: %d", s->type);
  return NULL;
}

beam_surface_t *beam_create_surface(beam_surface_type t) {
  beam_surface_t *s = calloc(sizeof(beam_surface_t), 1);
  if (s == NULL) {
    log_info("failed to allocate beam_surface_t");
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
    for (size_t i = 0; i < p->window_count; i++) {
      SDL_DestroyWindow(p->windows[i]);
    }
  }

  // Quit SDL subsystems
  SDL_Quit();

  free(p);
  free(s);
}

s32_t beam_render(beam_surface_t *surface, beam_signal_t *signals,
                 node_t *root) {
  if (signals == NULL) {
    // beam_signal_t *s = *signals;
    // log_info("and signals: %d", s->type);
  }

  if (surface == NULL) {
    log_info("SURFACE is null\n");
    return -1;
  }

  sdl2_context_t *p = surface->platform;
  if (p == NULL) {
    log_info("PLATFORM IS NULL\n");
    return -1;
  }

  if (root != NULL) {
    p->window_count = get_child_count(root);
  
    if (p->windows == NULL && p->window_count > 0) {
      p->windows = (SDL_Window**)malloc(p->window_count * sizeof(SDL_Window *));
      p->surfaces = (SDL_Surface**)malloc(p->window_count * sizeof(SDL_Surface *));

      each_child(root, window_visitor, p);
    }
  }

  // // Fill the surface
  // SDL_FillRect(p->surface, NULL, SDL_MapRGB(p->surface->format, 0x16, 0x16, 0x16));

  // // Update the surface
  // SDL_UpdateWindowSurface(p->window);

  return BeamSuccess;
}
