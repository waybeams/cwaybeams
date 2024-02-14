//
// Created by lukebayes on 5/13/21.
//
#include "beam.h"
#include "renderer/glfw.h"
#include "log.h"
#include "node_visitor.h"
#include <stdio.h>
#include <stdlib.h>

#include <GLFW/glfw3.h>

#define DEFAULT_WIDTH 1024
#define DEFAULT_HEIGHT 768

beam_surface_t *beam_create_surface(beam_surface_type t) {
  beam_surface_t *s = calloc(1, sizeof(beam_surface_t));
  if (s == NULL) {
    log_err("failed to allocate beam_surface_t");
    return NULL;
  }

  s->type = t;
  return s;
}

s32_t beam_window_should_close(beam_surface_t *s) {
  if (s == NULL) {
    return -1;
  }

  glfw_context_t *c = s->platform;
  if (c->main_window == NULL) {
    return -1;
  }

  return glfwWindowShouldClose(c->main_window);
}

static void render_window(UNUSED beam_surface_t *s, UNUSED node_t *node) {
  if (s == NULL) {
    return;
  }
  // log_info("render_window with: %s", get_name(node));
  glfw_context_t *c = s->platform;
  if (c->main_window == NULL) {
    // This is the first window we've encountered.
    GLFWwindow *window;
    s32_t w = get_width(node);
    s32_t h = get_height(node);
    if (0 == w) {
      w = DEFAULT_WIDTH;
    }
    if (0 == h) {
      h = DEFAULT_HEIGHT;
    }

    log_info("Creating window at %d x %d", w, h);

    window = glfwCreateWindow(w, h, "Hello World", NULL, NULL);
    if (window == NULL) {
      log_err("failed to create main window");
      return;
    }

    log_info("main window created!");
    c->main_window = window;

    glfwMakeContextCurrent(window);
  }
}

static visit_status_t visit_handler(node_t *node, void *userdata) {
  beam_surface_t *s = userdata;
  s32_t status = BeamSuccess;
  // log_info("visit node: %s", get_name(node));
  switch (node->type) {
    case BeamTypeWindow:
      render_window(s, node);
  }
  return status;
}

static s32_t glfw_process_tree(beam_surface_t *t, node_t *node) {
  s32_t status = BeamSuccess;
  // log_info("glfw_process_tree with: %d", t->type);

  breadth_first(node, visit_handler, t);

  return status;
}

static glfw_context_t *glfw_context_new() {
  glfw_context_t *c = calloc(1, sizeof(glfw_context_t));
  if (c == NULL) {
    log_err("failed to allocate glfw_context_t");
    return NULL;
  }
  c->init_status = -1;
  return c;
}

void beam_surface_free(beam_surface_t *s) {
  if (s == NULL) {
    return;
  }

  if (s->platform != NULL) {
    glfw_context_t *c = s->platform;
    if (c->main_window != NULL) {
      log_info("terminating GLFW now");
      glfwTerminate();
    }
    free(s->platform);
  }

  free(s);
}

s32_t beam_render(beam_surface_t *surface, beam_signal_t *signals,
                 node_t *node) {
  if (signals != NULL) {
    // beam_signal_t *s = *signals;
    // log_info("and signals: %d", s->type);
  }

  if (surface != NULL) {
    // log_info("beam_render with: %d", surface->type);
  }

  if (node != NULL) {
    // log_info("and node: %d", node->type);
  }

  if (surface->platform == NULL) {
    glfw_context_t *c = glfw_context_new();
    if (c == NULL) {
      log_err("glfw context failed to allocate");
      return BeamAllocationFailure;
    }
    surface->platform = c;
  }

  glfw_context_t *gc = surface->platform;

  s32_t status = BeamSuccess;

  if (gc->init_status == -1) {
    status = glfwInit();
    if (!status) {
      log_err("glfw failed to initialize");
      return status;
    }
    log_info("glfw initialized");
    gc->init_status = status;
  }

  glfw_process_tree(surface, node);

  // Undefined symbol...
  // glClear(GL_COLOR_BUFFER_BIT);

  glfw_context_t *c = surface->platform;
  glfwSwapBuffers(c->main_window);
  glfwPollEvents();

  return BeamSuccess;
}
