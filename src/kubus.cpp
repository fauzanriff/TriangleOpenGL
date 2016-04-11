#include <GLFW/glfw3.h>
#include <GL/glut.h>
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

    float angelY=0.f, angelZ=0.f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */

        glClear(GL_COLOR_BUFFER_BIT);

        glRotatef(angleY, 0.0f, 1.0f, 0.0f); // Rotate around the y axis.
        glRotatef(angleZ, 0.0f, 0.0f, 1.0f); // Rotate around the z axis.

        glBegin(GL_QUADS);
        //front
        glColor3f(1.f, 0.f, 0.f); //red

        glVertex3f(-0.5f, 0.5f, 0.f);
        glVertex3f(0.5, 0.5f, 0.f);
        glVertex3f(0.5f, -0.5f, 0.f);
        glVertex3f(-0.5f, -0.5f, 0.f);

        glEnd();

        glBegin(GL_QUADS);
        //back
        glColor3f(0.f, 0.f, 1.f); //blue

        glVertex3f(-0.5f, 0.5f, 1.f);
        glVertex3f(0.5, 0.5f, 1.f);
        glVertex3f(0.5f, -0.5f, 1.f);
        glVertex3f(-0.5f, -0.5f, 1.f);

        glEnd();

        glBegin(GL_QUADS);
        //top
        glColor3f(0.f, 1.f, 0.f); //green

        glVertex3f(-0.5f, 0.5f, 0.f);
        glVertex3f(0.5f, 0.5f, 0.f);
        glVertex3f(-0.5f, 0.5f, 1.f);
        glVertex3f(0.5f, 0.5f, 1.f);

        glEnd();

        glBegin(GL_QUADS);
        //bottom
        glColor3f(1.f, 1.f, 0.f); //purple

        glVertex3f(-0.5f, -0.5f, 0.f);
        glVertex3f(0.5f, -0.5f, 0.f);
        glVertex3f(-0.5f, -0.5f, 1.f);
        glVertex3f(0.5f, -0.5f, 0.f);

        glEnd();

        glBegin(GL_QUADS);
        //right
        glColor3f(0.f, 0.f, 1.f); //blue

        glVertex3f(-0.5f, 0.5f, 0.f);
        glVertex3f(-0.5f, -0.5f, 0.f);
        glVertex3f(-0.5f, 0.5f, 1.f);
        glVertex3f(-0.5f, -0.5f, 1.f);

        glEnd();

        glBegin(GL_QUADS);
        //left
        glColor3f(0.f, 0.f, 1.f); //blue

        glVertex3f(0.5f, 0.5f, 0.f);
        glVertex3f(0.5f, -0.5f, 0.f);
        glVertex3f(0.5f, 0.5f, 1.f);
        glVertex3f(0.5f, -0.5f, 1.f);

        glEnd();

        //Change Angle
        angelY += 2.f;
        angleZ += 3.f;

        if(angleY >= 360.0f)
            angleY = 0.0f;
        if(angleZ >= 360.0f)
            angleZ = 0.0f;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        usleep(1000);
    }

    glfwTerminate();
    return 0;
}