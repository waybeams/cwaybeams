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

#include "arena.h"
#include "beam.h"
#include "log.h"
#include "renderer.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

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
  beam_rect_t b_rect;
  beam_color_t b_color;
  arena_t arena;
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

node_t *create_moving_box(app_services_t *s) {
  beam_rect_t *rect = &s->b_rect;
  return box(
      name("moving-box"),
      width(rect->w),
      height(rect->h)
      // color(s->b_color)
      // color(s->b_color),
    );
}

// node_t *create_content(app_services_t *s) {
//   app_model_t *m = &s->model;
// 
//   // Build a task view for each task record.
//   node_t **task_views = arena_malloc(&s->arena, sizeof(intptr_t) * m->task_count);
//   if (task_views == NULL) {
//     printf("arena_malloc failed\n");
//     return NULL;
//   }
// 
//   for (size_t i = 0; i < m->task_count; i++) {
//     task_views[i] = create_task_view(&m->tasks[i]);
//   }
// 
//   return vbox(
//       children(
//         label("Task List"),
//         vbox(
//           children_list(m->task_count, task_views)
//         )
//       )
//     );
// }

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
            create_moving_box(s)
            // create_content(s)
          )
        )
      )
    );
}

static bool direction = true;
static s32_t render(app_services_t *servies, beam_surface_t *surface,
    beam_signal_t *signals, node_t *root) {

  beam_rect_t *rect = &servies->b_rect;
  if (direction) {
    rect->w += 3;
  } else {
    rect->w -= 3;
  }
  if (rect->w < 10) {
    direction = true;
  }
  if (rect->w > 1024) {
    direction = false;
  }

  return beam_render(surface, signals, root);
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
    .b_rect = {
      x: 0,
      y: 0,
      w: 100,
      h: 100,
    },
    .b_color = {
      r: 0xff,
      g: 0x00,
      b: 0x00,
      a: 0xff,
    },
    .model = {
      .title = "TOODOO",
      .task_count = task_count,
      .tasks = tasks,
    },
  };

  // Initialize the arena allocator
  s8_t status = arena_init(&services.arena, ARENA_SIZE);
  node_set_arena(&services.arena);
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
    render(&services, surface, signals, node);

    // printf("Looping\n");
    // if (nanosleep(&req, &rem) == -1) {
    //   printf("nanosleep failed\n");
    //   if (errno == EINTR) {
    //     printf("Interrupted\n");
    //     req = rem;
    //     continue;
    //   }
    // }

    arena_reset(&services.arena);
  }

  printf("Main while loop exited\n");
  arena_free(&services.arena);
  beam_surface_free(surface);
  printf("Exiting\n");
  return 0;
}
