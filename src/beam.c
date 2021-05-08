#include "beam.h"
#include <stdlib.h>
#include <stdio.h>

beam_surface_t *beam_create_surface(beam_surface_type t) {
  beam_surface_t *s = calloc(sizeof(beam_surface_t), 1);
  s->type = t;
  return s;
}

void render(beam_surface_t *s, node_t *node) {
  printf("render with: %d\n", s->type);
  printf("and node: %d\n", node->type);
}