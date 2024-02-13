#ifndef __beam_renderer_h__
#define __beam_renderer_h__

#include "beam.h"
#include "node.h"

/**
 * This is the interface that one must implement in order to get a rendering
 * surface up and running.
 */

typedef enum beam_surface_type {
  BeamSurfaceGlfw = 1,
  BeamSurfaceGles,
  BeamSurfaceDirectX,
  BeamSurfaceMetal,
  BeamSurfaceVulkan,
  BeamSurfaceSDL3
} beam_surface_type;

typedef struct beam_surface_t {
  beam_surface_type type;
  bool should_close;
  void *platform;
} beam_surface_t;

beam_surface_t *beam_create_surface(beam_surface_type t);
int beam_render(beam_surface_t *s, beam_signal_t *signals, node_t *node);

beam_signal_t *beam_signals_gather(beam_surface_t *s);
int beam_window_should_close(beam_surface_t *s);

void beam_surface_free(beam_surface_t *s);



#endif // __beam_renderer_h__
