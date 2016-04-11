#include <GLFW/glfw3.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>

using namespace std;

void sierpenski(int lv, double ax, double ay, double bx, double by, double cx, double cy) {
    if(lv) {
        glBegin(GL_TRIANGLES);
        switch(lv % 3) {
            case 0 : glColor3f(1.f, 0.f, 0.f); break;
            case 1 : glColor3f(0.f, 1.f, 0.f); break;
            case 2 : glColor3f(0.f, 0.f, 1.f); break;
        }
        glVertex3f((ax+bx)/2.f, (ay+by)/2.f, 0.f);
        glVertex3f((bx+cx)/2.f, (by+cy)/2.f, 0.f);
        glVertex3f((cx+ax)/2.f, (cy+ay)/2.f, 0.f);
        glEnd();
        sierpenski(lv-1, ax, ay, (ax+bx)/2.f, (ay+by)/2.f, (ax+cx)/2.f, (ay+cy)/2.f);
        sierpenski(lv-1, bx, by, (ax+bx)/2.f, (ay+by)/2.f, (bx+cx)/2.f, (by+cy)/2.f);
        sierpenski(lv-1, cx, cy, (cx+bx)/2.f, (cy+by)/2.f, (ax+cx)/2.f, (ay+cy)/2.f);
    }
    else {
        glBegin(GL_TRIANGLES);
        glColor3f(0.5f, 0.5f, 0.5f);
        glVertex3f(ax, ay, 0.f);
        glVertex3f(bx, by, 0.f);
        glVertex3f(cx, cy, 0.f);
        glEnd();
    }
}

int main(int argc, char** argv) {
    GLFWwindow* window;

    int level = 3;
    if(argc > 1) {
        level = atoi(argv[1]);
    }

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

        sierpenski(level, 0, 1, -1, -1, 1, -1);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        usleep(10000);
    }

    glfwTerminate();
    return 0;
}