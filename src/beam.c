#include "beam.h"
#include "log.h"
#include "shared.h"
#include <stdio.h>
#include <stdlib.h>

/*
beam_surface_t *beam_create_surface(beam_surface_type t) {
  beam_surface_t *s = calloc(sizeof(beam_surface_t), 1);
  s->type = t;
  return s;
}

void beam_render(beam_surface_t *surface, beam_signal_t **signals, node_t
*node) {
  beam_signal_t *s = *signals;
  printf("beam_render with: %d\n", surface->type);
  printf("and node: %d\n", node->type);
  printf("and signals: %d\n", s->type);
}
*/

beam_signal_t *beam_signals_gather(UNUSED beam_surface_t *s) {
  // log_info("beam_signals_gather with type: %d", s->type);
  return NULL;
}

attr_t *name(char *value) {
  return new_char_attr(BeamAttrKeysName, value);
}

attr_t *text(char *value) {
  return new_char_attr(BeamAttrKeysText, value);
}

attr_t *title(char *value) {
  return new_char_attr(BeamAttrKeysTitle, value);
}

attr_t *label(char *value) {
  return new_char_attr(BeamAttrKeysLabel, value);
}

attr_t *layout(beam_layout_t value) {
  return new_u32_attr(BeamAttrKeysLayout, value);
}

attr_t *width(s32_t value) {
  return new_s32_attr(BeamAttrKeysWidth, value);
}

attr_t *height(s32_t value) {
  return new_s32_attr(BeamAttrKeysHeight, value);
}

attr_t *x(s32_t value) {
  return new_s32_attr(BeamAttrKeysX, value);
}

attr_t *y(s32_t value) {
  return new_s32_attr(BeamAttrKeysY, value);
}

attr_t *z(s32_t value) {
  return new_s32_attr(BeamAttrKeysZ, value);
}

attr_t *handler(void *value) {
  return new_ext_ptr_attr(BeamAttrKeysHandler, value);
}

char *get_name(node_t *node) {
  return get_char_attr_from_node(node, BeamAttrKeysName, DEFAULT_CHAR);
}

char *get_text(node_t *node) {
  return get_char_attr_from_node(node, BeamAttrKeysText, DEFAULT_CHAR);
}

char *get_label(node_t *node) {
  return get_char_attr_from_node(node, BeamAttrKeysLabel, DEFAULT_CHAR);
}

beam_layout_t get_layout(node_t *node) {
  return get_u32_attr_from_node(node, BeamAttrKeysLayout, LayoutDefault);
}

s32_t get_width(node_t *node) {
  return get_s32_attr_from_node(node, BeamAttrKeysWidth, DEFAULT_ZERO);
}

s32_t get_height(node_t *node) {
  return get_s32_attr_from_node(node, BeamAttrKeysHeight, DEFAULT_ZERO);
}

s32_t get_x(node_t *node) {
  return get_s32_attr_from_node(node, BeamAttrKeysX, DEFAULT_ZERO);
}

s32_t get_y(node_t *node) {
  return get_s32_attr_from_node(node, BeamAttrKeysY, DEFAULT_ZERO);
}

s32_t get_z(node_t *node) {
  return get_s32_attr_from_node(node, BeamAttrKeysZ, DEFAULT_ZERO);
}
