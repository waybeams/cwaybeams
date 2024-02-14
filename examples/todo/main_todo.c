/**
 * This is currently an aspirational application definition that is being used
 * to provide clarity for next steps.
 *
 * An application (or game) developer would describe their application data
 * and services. These entities would be instantiated, configured and prepared.
 *
 * They would then provide a series of functions that transform those data into
 * UI controls. These functions can start out coarse and be refined over time.
 *
 * Whatever information your transformations require, would be attached to
 * your own application service locator. Views could be declared in their own
 * files or all in a giant single file, however you wish.
 *
 * The application developer would need to execute their transformation
 * functions and then provide the resulting tree to a concrete or magical
 * renderer of their choosing.
 */
// NOTE(lbayes): Required for time.h to provide nanosleep
#define _POSIX_C_SOURCE 199309L

#include "renderer.h"
#include "arena.h"
#include "beam.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <errno.h>

// Malloc block for the arena allocator.
#define ARENA_SIZE (512 * 1024)

typedef struct {
  char *label;
  bool is_done;
}task_t;

typedef struct {
  char *title;
  u32_t task_count;
  task_t *tasks;
}app_model_t;

typedef struct app_services_t  {
  app_model_t model;
}app_services_t;

node_t *create_task_view(task_t *t) {
  return hbox(
      children(
        label(t->label)
        // checkbox(t->is_done),
        )
      );
}

node_t *create_content(app_services_t *s) {
  app_model_t *m = &s->model;

  // Build a task view for each task record.
  node_t **task_views = arena_malloc(sizeof(intptr_t) * m->task_count);
  if (task_views == NULL) {
    printf("arena_malloc failed\n");
    return NULL;
  }

  for (size_t i = 0; i < m->task_count; i++) {
    task_views[i] = create_task_view(&m->tasks[i]);
  }

  return vbox(
      children(
        label("Task List"),
        vbox(
          children_list(m->task_count, task_views)
        )
      )
    );
}

/**
 * Transform the provided data into a concrete projection / user interface.
 * @param app_services_t *s
 * @return
 */
node_t* create_projection(app_services_t *s) {
  return app(
      name("main-app"),
      children(
        window(
          name("main-window"),
          title(s->model.title),
          width(1280),
          height(720),
          children(
            create_content(s)
          )
        )
      )
    );
}

int main(void) {
  printf("Starting\n");

  u32_t task_count = 8;
  task_t tasks[8] = {
    {.label = "one", .is_done = false},
    {.label = "two", .is_done = false},
    {.label = "three", .is_done = false},
    {.label = "four", .is_done = false},
    {.label = "five", .is_done = false},
    {.label = "six", .is_done = false},
    {.label = "seven", .is_done = false}
  };

  app_services_t services = {
    .model = {
      .title = "TOODOO",
      .task_count = task_count,
      .tasks = tasks,
    },
  };

  // Initialize the arena allocator
  s8_t status = arena_init(ARENA_SIZE);
  if (status != 0) {
    printf("arena_init failed\n");
    return -1;
  }

  beam_surface_t *surface = beam_create_surface(BeamSurfaceSDL3);
  // beam_surface_t *surface = beam_create_surface(BeamSurfaceGlfw);
  if (surface == NULL) {
    printf("beam_create_surface failed\n");
    return -1;
  }

  // struct timespec req, rem = {0};
  // req.tv_sec = 2;
  // req.tv_nsec = 1000000000 / 60;

  while (!beam_window_should_close(surface)) {
    beam_signal_t *signals = beam_signals_gather(surface);
    node_t *node = create_projection(&services);
    beam_render(surface, signals, node);

    // printf("Looping\n");
    // if (nanosleep(&req, &rem) == -1) {
    //   printf("nanosleep failed\n");
    //   if (errno == EINTR) {
    //     printf("Interrupted\n");
    //     req = rem;
    //     continue;
    //   }
    // }

    arena_reset();
  }

  printf("Main while loop exited\n");
  arena_free();
  beam_surface_free(surface);
  printf("Exiting\n");
  return 0;
}
