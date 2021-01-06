#include <dom.h>
#include <stdio.h>

#define GL_COLOR_BUFFER_BIT 0x00004000
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <GL/gl.h>

Node* uiControl(char *title) {
  return vbox(
    name(title),
    width(800),
    height(600),
    children(
      box(name("child-1")),
      box(name("child-2")),
      box(name("child-3"))
    )
  );
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Scale with high dpi screens */
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, true);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1024, 768, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    double lastTime = glfwGetTime();
    int nbFrames = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        Node *root = uiControl("root");
        // printNode(root);

        /*
         * On 12/29/2020, was able to generate (and free) about 25k simple trees
         * within a 16ms frame budget.
        int count = 25000;
        // unsigned int ids[count];
        for (int i = 0; i < count; i++) {
          Node *elem = uiControl("abcd");
          // ids[i] = elem->id;
          freeNode(elem);
        }
        */

        // Measure speed
        double currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
            // printf and reset timer
            printf("%f ms/frame\n", (1000.0 / (double)nbFrames));
            nbFrames = 0;
            lastTime += 1.0;
        }

        /* Render here */
        // Cannot find declaration for...
        // glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        freeNode(root);
    }

    glfwTerminate();
    return 0;
}

