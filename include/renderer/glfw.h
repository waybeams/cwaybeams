//
// Created by lukebayes on 5/13/21.
//

#ifndef CWAYBEAMS_GLFW_H
#define CWAYBEAMS_GLFW_H

#include <GLFW/glfw3.h>

typedef struct glfw_context_t {
  int init_status;
  GLFWwindow *main_window;
}glfw_context_t;

#endif //CWAYBEAMS_GLFW_H
