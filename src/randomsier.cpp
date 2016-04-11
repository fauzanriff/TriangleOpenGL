#include <GLFW/glfw3.h> 
#include <unistd.h>
#include <math.h>	
#include <cstdlib>

int main(int argc, char** argv){
    GLFWwindow* window;
	int numSteps = 5;

    if (argc > 1){
    	numSteps = atoi(argv[1]);
    }

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Sierpinski Triangle", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    // glClearColor(1.f, 1.f, 1.f, 0.0f);

    float ax = -0.9f;
  	float ay = -0.9f;
  	float bx = 0.9f;
  	float by = -0.9f;
  	float cx = 0.f;
  	float cy = 0.9f;

  	//initial coordinates for the point px
  	float px = ax;
  	float py = ay;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
	  //do the process numSteps times
	  for(int n = 0; n < numSteps; n++)
	  {
	    //draw the pixel
	    glBegin(GL_POINTS);
	    glColor3f(1.f, 0.f, 0.f);
        glVertex2f(px, py);
        glEnd();

	    //pick a random number 0, 1 or 2
	    switch(abs(rand() % 3))
	    {
	      //depending on the number, choose another new coordinate for point p
	      case 0:
	        px = (px + ax) / 2.0;
	        py = (py + ay) / 2.0;
	        break;
	      case 1:
	        px = (px + bx) / 2.0;
	        py = (py + by) / 2.0;
	        break;
	      case 2:
	        px = (px + cx) / 2.0;
	        py = (py + cy) / 2.0;
	        break;
    	}
  		}

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

  		/* Poll for and process events */
        glfwPollEvents();
        usleep(1000);

    }

    glfwTerminate();
	return 0;
}