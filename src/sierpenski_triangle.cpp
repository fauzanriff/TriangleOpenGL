#include <GLFW/glfw3.h>
#include <unistd.h>

using namespace std;

int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Tugas Grafika", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */

        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.f, 0.f);
        glVertex3f(-a, 0.f, 0.f);
        glVertex3f(-0.5f, 1.f, 0.f);
        glVertex3f(0.f, 0.f, 0.f);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(1.f, 0.f, 0.f);
        glVertex3f(0.5f, 1.f, 0.f);
        glVertex3f(0.f, 0.f, 0.f);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(-0.5f, -1.f, 0.f);
        glVertex3f(0.f, 0.f, 0.f);
        glVertex3f(0.5f, -1.f, 0.f);
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        usleep(1000);
    }

    glfwTerminate();
    return 0;
}