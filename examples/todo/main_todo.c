/**
 * This is currently an aspirational application definition that isbeing used
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
#include <beam.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct {
  char *label;
  bool is_done;
}task_t;

typedef struct {
  char *title;
  int task_count;
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
  node_t *task_views[m->task_count];
  for (int i = 0; i < m->task_count; i++) {
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
      children(
          window(
              name("main-window"),
              title(s->model.title),
              width(800),
              height(600),
              children(
                  create_content(s)
              )
          )
      )
  );
}

int main(void) {
  printf("Starting\n");

  int task_count = 8;
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
        .title = "Main Page",
        .task_count = task_count,
        .tasks = tasks
      }
  };

  // Events *events;
  int status = 0;
  do {
    // printf("Looping\n");
    // events = gather_events();
    node_t *node = create_projection(&services);
    // status = render(node, events);
    free_node(node);
    usleep(10);
  } while(status < 10000);

  printf("Exiting\n");
  return 0;
}
