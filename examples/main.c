// #include <dom.h>

#define GL_COLOR_BUFFER_BIT 0x00004000
#define GLFW_INCLUDE_NONE
#include <GL/gl.h>
#include <GLFW/glfw3.h>

/*
Element* uiControl(char *title) {
  return vbox(
    name(title),
    width(800),
    height(600),
    children(
      box(name("child-1")),
      box(name("child-2")),
      box(name("child-3")),
      hbox(name("child-4"),
        children(
          box(name("child-4-1")),
          box(name("child-4-2")),
          box(name("child-4-3")),
          box(name("child-4-4")),
          box(name("child-4-5"))
        )
      ),
      box(name("child-5")),
      box(name("child-6")),
      box(name("child-7")),
      box(name("child-8"))
    )
  );
}
*/

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1024, 768, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Element *root = uiControl("root-node");
    // printElement(root);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        // Cannot find declaration for...
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    // freeElement(root);
    glfwTerminate();
    return 0;
}

