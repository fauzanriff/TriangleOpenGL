#define degreesToRadians(x) x*(3.141592f/180.0f)
#define GLM_FORCE_RADIANS


#include <bits/stdc++.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unistd.h>

using namespace std;

const int fps = 30;
const int mini_size = 10;
const float space = 1;
const glm::vec3 world_size(30, 30, 30);
const glm::vec3 view_size(1, 1, 1);
const glm::vec3 offset(-0, -0, 0); 

set< float > st;
struct rec {
    glm::vec4 pos[4];
    glm::vec3 color;
    rec() {}
    rec(glm::vec3 off, glm::vec3 a, glm::vec3 b, glm::vec3 col) : color(col) {
        pos[0] = glm::vec4(off + a*0.005f + b*0.005f, 1);
        pos[1] = glm::vec4(off + a*0.985f + b*0.005f, 1);
        pos[2] = glm::vec4(off + a*0.985f + b*0.985f, 1);
        pos[3] = glm::vec4(off + a*0.005f + b*0.985f, 1);
    }
    void set_vertex(glm::vec3 off, glm::vec3 a, glm::vec3 b) {
        pos[0] = glm::vec4(off + a*0.005f + b*0.005f, 1);
        pos[1] = glm::vec4(off + a*0.985f + b*0.005f, 1);
        pos[2] = glm::vec4(off + a*0.985f + b*0.985f, 1);
        pos[3] = glm::vec4(off + a*0.005f + b*0.985f, 1);
    }
    void render() {
        glBegin(GL_QUADS);
        glColor3f(color.x, color.y, color.z);
        for(int i = 0; i<4; i++) {
            float xx = (float)pos[i].x/world_size.x*view_size.x + offset.x, 
                yy = (float)pos[i].y/world_size.y*view_size.y + offset.y,
                zz = (float)pos[i].z/world_size.z*view_size.z + offset.z;
            glVertex3f(xx, yy, zz);
        }
        glEnd();
    }

    void render1() {
        glBegin(GL_QUADS);
        glColor3f(color.x, color.y, color.z);
        for(int i = 0; i<4; i++) {
            glVertex3f(pos[i].x, pos[i].y, pos[i].z);
        }
        glEnd();
    }
    void transform(glm::mat4 trans) {
        for(int i = 0; i<4; i++)
            pos[i] = trans * pos[i];
    }
    void calibrate() {
        for(int i = 0; i<4; i++) {
            int tmp = (int(pos[i].x)*2+ mini_size)/(mini_size*2);
            pos[i].x = tmp*mini_size;
            tmp = (int(pos[i].y)*2+ mini_size)/(mini_size*2);
            pos[i].y = tmp*mini_size;
            tmp = (int(pos[i].z)*2+ mini_size)/(mini_size*2);
            pos[i].z = tmp*mini_size;
        }
    }
};

rec sisi[55];

void reset_rubik() {
    int dx, dy;
    dx = dy = 0;
    for(int i = 0; i<9; i++) {
        sisi[i].set_vertex(glm::vec3(dx, dy, 0), glm::vec3(mini_size, 0, 0), glm::vec3(0, mini_size, 0));
        sisi[i].color = glm::vec3(0, 0, 1); // BLUE
        dx += mini_size;
        if(dx >= 3*mini_size) {
            dy += mini_size;
            dx = 0;
        }
    }
    dx = dy = 0;
    for(int i = 0; i<9; i++) {
        sisi[i+9].set_vertex(glm::vec3(dx, 0, dy), glm::vec3(mini_size, 0, 0), glm::vec3(0, 0, mini_size));
        sisi[i+9].color = glm::vec3(1, 0, 0); // RED
        dx += mini_size;
        if(dx >= 3*mini_size) {
            dy += mini_size;
            dx = 0;
        }
    }
    dx = dy = 0;
    for(int i = 0; i<9; i++) {
        sisi[i+18].set_vertex(glm::vec3(0, dx, dy), glm::vec3(0, mini_size, 0), glm::vec3(0, 0, mini_size));
        sisi[i+18].color = glm::vec3(1, 1, 1); // WHITE
        dx += mini_size;
        if(dx >= 3*mini_size) {
            dy += mini_size;
            dx = 0;
        }
    }
    dx = dy = 3*mini_size;
    for(int i = 0; i<9; i++) {
        sisi[i+27].set_vertex(glm::vec3(dx, dy, 3*mini_size), glm::vec3(-mini_size, 0, 0), glm::vec3(0, -mini_size, 0));
        sisi[i+27].color = glm::vec3(100.0f/255.0f, 211.0f/255.0f, 23.0f/255.0f); //
        dx -= mini_size;
        if(dx <= 0) {
            dy -= mini_size;
            dx = 3*mini_size;
        }
    }
    dx = dy = 3*mini_size;
    for(int i = 0; i<9; i++) {
        sisi[i+36].set_vertex(glm::vec3(dx, 3*mini_size, dy), glm::vec3(-mini_size, 0, 0), glm::vec3(0, 0, -mini_size));
        sisi[i+36].color = glm::vec3(1, 143/255.0f, 0); // ORANGE
        dx -= mini_size;
        if(dx <= 0) {
            dy -= mini_size;
            dx = 3*mini_size;
        }
    }
    dx = dy = 3*mini_size;
    for(int i = 0; i<9; i++) {
        sisi[i+45].set_vertex(glm::vec3(3*mini_size, dx, dy), glm::vec3(0, -mini_size, 0), glm::vec3(0, 0, -mini_size));
        sisi[i+45].color = glm::vec3(1, 234.0f/255.0f, 0); // YELLOW
        dx -= mini_size;
        if(dx <= 0) {
            dy -= mini_size;
            dx = 3*mini_size;
        }
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void draw_rubik();

GLFWwindow* window;
int main(void) {
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "Tugas Grafika", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    // rec r1(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0));
    reset_rubik();
    glm::mat4 trans0;
    trans0 = glm::translate(trans0, glm::vec3(-world_size.x/2, -world_size.y/2, -world_size.z/2));
    for(int i = 0; i<54; i++)
        sisi[i].transform(trans0);
    
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        draw_rubik();
    }
    glfwTerminate();
    return 0;
}

void draw_rubik() {
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glPushMatrix();
    glRotatef(-25.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(45.0f, 0.0f, .1f, 0.0f);
    for(int i = 0; i<54; i++) {
        sisi[i].render();
    }

    glPopMatrix();
    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
    usleep(30000LL);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(action == GLFW_PRESS){
        if (key == GLFW_KEY_W){
            //Button Pos Left To Top           
            glm::mat4 trans;
            trans = glm::rotate(trans, degreesToRadians(90/fps), glm::vec3(1.0, 0.0, 0.0));
            for(int j = 0; j<fps; j++) {
                for(int i = 0; i<54; i++) {
                    bool ok = true;
                    for(int k = 0; k<4; k++)
                        if(sisi[i].pos[k].x >= -mini_size/2)
                            ok = false;
                    if(ok)
                        sisi[i].transform(trans);
                }
                draw_rubik();
            }
        }
        if (key == GLFW_KEY_E){
            //Button Pos Center To Top
            glm::mat4 trans;
            trans = glm::rotate(trans, degreesToRadians(90/fps), glm::vec3(1.0, 0.0, 0.0));
            for(int j = 0; j<fps; j++) {
                for(int i = 0; i<54; i++) {
                    bool ok = true;
                    for(int k = 0; k<4; k++)
                        if(sisi[i].pos[k].x <= -mini_size/2 || sisi[i].pos[k].x >= mini_size/2)
                            ok = false;
                    if(ok)
                        sisi[i].transform(trans);
                }
                draw_rubik();
            }
        }
        if (key == GLFW_KEY_R){
            //Button Pos Right To Top
            glm::mat4 trans;
            trans = glm::rotate(trans, degreesToRadians(90/fps), glm::vec3(1.0, 0.0, 0.0));
            for(int j = 0; j<fps; j++) {
                for(int i = 0; i<54; i++) {
                    bool ok = true;
                    for(int k = 0; k<4; k++)
                        if(sisi[i].pos[k].x <= mini_size/2)
                            ok = false;
                    if(ok)
                        sisi[i].transform(trans);
                }
                draw_rubik();
            }
        }
        if (key == GLFW_KEY_S){
            //Button Pos Left To Bottom
            glm::mat4 trans;
            trans = glm::rotate(trans, degreesToRadians(-90/fps), glm::vec3(1.0, 0.0, 0.0));
            for(int j = 0; j<fps; j++) {
                for(int i = 0; i<54; i++) {
                    bool ok = true;
                    for(int k = 0; k<4; k++)
                        if(sisi[i].pos[k].x >= -mini_size/2)
                            ok = false;
                    if(ok)
                        sisi[i].transform(trans);
                }
                draw_rubik();
            }
        }
        if (key == GLFW_KEY_D){
            //Button Pos Center To Bottom
            glm::mat4 trans;
            trans = glm::rotate(trans, degreesToRadians(-90/fps), glm::vec3(1.0, 0.0, 0.0));
            for(int j = 0; j<fps; j++) {
                for(int i = 0; i<54; i++) {
                    bool ok = true;
                    for(int k = 0; k<4; k++)
                        if(sisi[i].pos[k].x <= -mini_size/2 || sisi[i].pos[k].x >= mini_size/2)
                            ok = false;
                    if(ok)
                        sisi[i].transform(trans);
                }
                draw_rubik();
            }
        }
        if (key == GLFW_KEY_F){
            //Button Pos Right To Bottom
            glm::mat4 trans;
            trans = glm::rotate(trans, degreesToRadians(-90/fps), glm::vec3(1.0, 0.0, 0.0));
            for(int j = 0; j<fps; j++) {
                for(int i = 0; i<54; i++) {
                    bool ok = true;
                    for(int k = 0; k<4; k++)
                        if(sisi[i].pos[k].x <= mini_size/2)
                            ok = false;
                    if(ok)
                        sisi[i].transform(trans);
                }
                draw_rubik();
            }
        }
        if (key == GLFW_KEY_Q){
            //Button Pos Top To Left
            glm::mat4 trans;
            trans = glm::rotate(trans, degreesToRadians(90/fps), glm::vec3(0.0, 1.0, 0.0));
            for(int j = 0; j<fps; j++) {
                for(int i = 0; i<54; i++) {
                    bool ok = true;
                    for(int k = 0; k<4; k++)
                        if(sisi[i].pos[k].y <= mini_size/2)
                            ok = false;
                    if(ok)
                        sisi[i].transform(trans);
                }
                draw_rubik();
            }
        }
        if (key == GLFW_KEY_A){
            //Button Pos Center To Left
            glm::mat4 trans;
            trans = glm::rotate(trans, degreesToRadians(90/fps), glm::vec3(0.0, 1.0, 0.0));
            for(int j = 0; j<fps; j++) {
                for(int i = 0; i<54; i++) {
                    bool ok = true;
                    for(int k = 0; k<4; k++)
                        if(sisi[i].pos[k].y >= mini_size/2 || sisi[i].pos[k].y <= -mini_size/2)
                            ok = false;
                    if(ok)
                        sisi[i].transform(trans);
                }
                draw_rubik();
            }
        }
        if (key == GLFW_KEY_Z){
            //Button Pos Bottom To Left
            glm::mat4 trans;
            trans = glm::rotate(trans, degreesToRadians(90/fps), glm::vec3(0.0, 1.0, 0.0));
            for(int j = 0; j<fps; j++) {
                for(int i = 0; i<54; i++) {
                    bool ok = true;
                    for(int k = 0; k<4; k++)
                        if(sisi[i].pos[k].y >= -mini_size/2)
                            ok = false;
                    if(ok)
                        sisi[i].transform(trans);
                }
                draw_rubik();
            }
        }
        if (key == GLFW_KEY_T){
            //Button Pos Top To Right
            glm::mat4 trans;
            trans = glm::rotate(trans, degreesToRadians(-90/fps), glm::vec3(0.0, 1.0, 0.0));
            for(int j = 0; j<fps; j++) {
                for(int i = 0; i<54; i++) {
                    bool ok = true;
                    for(int k = 0; k<4; k++)
                        if(sisi[i].pos[k].y <= mini_size/2)
                            ok = false;
                    if(ok)
                        sisi[i].transform(trans);
                }
                draw_rubik();
            }
        }
        if (key == GLFW_KEY_G){
            //Button Pos Center To Right
            glm::mat4 trans;
            trans = glm::rotate(trans, degreesToRadians(-90/fps), glm::vec3(0.0, 1.0, 0.0));
            for(int j = 0; j<fps; j++) {
                for(int i = 0; i<54; i++) {
                    bool ok = true;
                    for(int k = 0; k<4; k++)
                        if(sisi[i].pos[k].y >= mini_size/2 || sisi[i].pos[k].y <= -mini_size/2)
                            ok = false;
                    if(ok)
                        sisi[i].transform(trans);
                }
                draw_rubik();
            }
        }
        if (key == GLFW_KEY_B){
            //Button Pos Bottom To Right
            glm::mat4 trans;
            trans = glm::rotate(trans, degreesToRadians(-90/fps), glm::vec3(0.0, 1.0, 0.0));
            for(int j = 0; j<fps; j++) {
                for(int i = 0; i<54; i++) {
                    bool ok = true;
                    for(int k = 0; k<4; k++)
                        if(sisi[i].pos[k].y >= -mini_size/2)
                            ok = false;
                    if(ok)
                        sisi[i].transform(trans);
                }
                draw_rubik();
            }
        }
        if (key == GLFW_KEY_Y){
            //Button Pos Back To Left
            glm::mat4 trans;
            trans = glm::rotate(trans, degreesToRadians(90/fps), glm::vec3(0.0, 0.0, 1.0));
            for(int j = 0; j<fps; j++) {
                for(int i = 0; i<54; i++) {
                    bool ok = true;
                    for(int k = 0; k<4; k++)
                        if(sisi[i].pos[k].z <= mini_size/2)
                            ok = false;
                    if(ok)
                        sisi[i].transform(trans);
                }
                draw_rubik();
            }
        }
        if (key == GLFW_KEY_H){
            //Button Pos Middle To Left
            glm::mat4 trans;
            trans = glm::rotate(trans, degreesToRadians(90/fps), glm::vec3(0.0, 0.0, 1.0));
            for(int j = 0; j<fps; j++) {
                for(int i = 0; i<54; i++) {
                    bool ok = true;
                    for(int k = 0; k<4; k++)
                        if(sisi[i].pos[k].z >= mini_size/2 || sisi[i].pos[k].z <= -mini_size/2)
                            ok = false;
                    if(ok)
                        sisi[i].transform(trans);
                }
                draw_rubik();
            }
        }
        if (key == GLFW_KEY_N){
            //Button Pos Front To Left
            glm::mat4 trans;
            trans = glm::rotate(trans, degreesToRadians(90/fps), glm::vec3(0.0, 0.0, 1.0));
            for(int j = 0; j<fps; j++) {
                for(int i = 0; i<54; i++) {
                    bool ok = true;
                    for(int k = 0; k<4; k++)
                        if(sisi[i].pos[k].z >= -mini_size/2)
                            ok = false;
                    if(ok)
                        sisi[i].transform(trans);
                }
                draw_rubik();
            }
        }
        if (key == GLFW_KEY_U){
            //Button Pos Back To Right
            glm::mat4 trans;
            trans = glm::rotate(trans, degreesToRadians(-90/fps), glm::vec3(0.0, 0.0, 1.0));
            for(int j = 0; j<fps; j++) {
                for(int i = 0; i<54; i++) {
                    bool ok = true;
                    for(int k = 0; k<4; k++)
                        if(sisi[i].pos[k].z <= mini_size/2)
                            ok = false;
                    if(ok)
                        sisi[i].transform(trans);
                }
                draw_rubik();
            }
        }
        if (key == GLFW_KEY_J){
            //Button Pos Middle To Right
            glm::mat4 trans;
            trans = glm::rotate(trans, degreesToRadians(-90/fps), glm::vec3(0.0, 0.0, 1.0));
            for(int j = 0; j<fps; j++) {
                for(int i = 0; i<54; i++) {
                    bool ok = true;
                    for(int k = 0; k<4; k++)
                        if(sisi[i].pos[k].z >= mini_size/2 || sisi[i].pos[k].z <= -mini_size/2)
                            ok = false;
                    if(ok)
                        sisi[i].transform(trans);
                }
                draw_rubik();
            }
        }
        if (key == GLFW_KEY_M){
            //Button Pos Front To Right
            glm::mat4 trans;
            trans = glm::rotate(trans, degreesToRadians(-90/fps), glm::vec3(0.0, 0.0, 1.0));
            for(int j = 0; j<fps; j++) {
                for(int i = 0; i<54; i++) {
                    bool ok = true;
                    for(int k = 0; k<4; k++)
                        if(sisi[i].pos[k].z >= -mini_size/2)
                            ok = false;
                    if(ok)
                        sisi[i].transform(trans);
                }
                draw_rubik();
            }
        }
        if (key == GLFW_KEY_UP){
            //Button Rubick To Top
            glm::mat4 trans;
            trans = glm::rotate(trans, degreesToRadians(90/fps), glm::vec3(1.0, 0.0, 0.0));
            for(int j = 0; j<fps; j++) {
                for(int i = 0; i<54; i++) {
                    sisi[i].transform(trans);
                }
                draw_rubik();
            }
        }
        if (key == GLFW_KEY_DOWN){
            //Button Rubick To Bottom
            glm::mat4 trans;
            trans = glm::rotate(trans, degreesToRadians(-90/fps), glm::vec3(1.0, 0.0, 0.0));
            for(int j = 0; j<fps; j++) {
                for(int i = 0; i<54; i++) {
                    sisi[i].transform(trans);
                }
                draw_rubik();
            }
        }
        if (key == GLFW_KEY_LEFT){
            //Button Rubick To Left
            glm::mat4 trans;
            trans = glm::rotate(trans, degreesToRadians(90/fps), glm::vec3(0.0, 1.0, 0.0));
            for(int j = 0; j<fps; j++) {
                for(int i = 0; i<54; i++) {
                    sisi[i].transform(trans);
                }
                draw_rubik();
            }
        }
        if (key == GLFW_KEY_RIGHT){
            //Button Rubick To Right
            glm::mat4 trans;
            trans = glm::rotate(trans, degreesToRadians(-90/fps), glm::vec3(0.0, 1.0, 0.0));
            for(int j = 0; j<fps; j++) {
                for(int i = 0; i<54; i++) {
                    sisi[i].transform(trans);
                }
                draw_rubik();
            }
        }
        if(key == GLFW_KEY_SPACE) {
            reset_rubik();
            glm::mat4 trans0;
            trans0 = glm::translate(trans0, glm::vec3(-world_size.x/2, -world_size.y/2, -world_size.z/2));
            for(int i = 0; i<54; i++)
                sisi[i].transform(trans0);   
            draw_rubik();
        }
    }   
}