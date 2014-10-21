#include <GL/glut.h>
#include <iostream>
#include "myCircle.hpp"		
#include "Slider.hpp"

GLint winW = 400, winH = 300;
GLint dragged = -1;
typedef myCircle<GLdouble> MyCircle;

MyCircle circle1(200, 150, 50);
myPoint<GLint> p1(50, 50);
myPoint<GLint> p2(200, 50);
mySlider<GLint> a(p1, p2, 5);

myPoint<GLint> p11(250, 50);
myPoint<GLint> p21(250, 250);
mySlider<GLint> a1(p11, p21, 0);

mySlider<GLint> clkPoints[] = { a, a1 };


void init (void)
{
    glClearColor (0.0, 1.0, 1.0, 0.0);	// Set display-window color to white.

    glMatrixMode (GL_PROJECTION);		// Set projection parameters.
    gluOrtho2D (0.0, winW, 0.0, winH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
}

void lineSegment (void)
{
    glClear (GL_COLOR_BUFFER_BIT);  // Clear display window.

    glColor3f (1.0, 0.4, 0.2);      
	glPointSize(5);


	
	clkPoints[0].draw();
	clkPoints[1].draw();
	


    glFlush ( );     // Process all OpenGL routines as quickly as possible.
}

GLint getActivePoint(mySlider<GLint> *p, GLint size, GLint sens, GLint xMouse, GLint yMouse){
	GLint  i, s = sens * sens;
	for (i = 0; i < size; i++){
		if (p[i].dis2Click(xMouse, yMouse) < s)
			return i;
	}

	return -1;
}


void processMouse(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
	GLint i;
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
		if ((i = getActivePoint(clkPoints, 2, 8, xMouse, winH - yMouse)) != -1)
			dragged = i;
	}

	if (button == GLUT_LEFT_BUTTON && action == GLUT_UP){
			dragged = -1;
	}
}

void processMouseMovement(GLint xMouse, GLint yMouse){
	if (dragged > -1){
		clkPoints[dragged].setClickX(xMouse);
		clkPoints[dragged].setClickY(winH - yMouse);
		
		glutPostRedisplay();
	}
}

int main (int argc, char** argv)
{
    glutInit (&argc, argv);                         // Initialize GLUT.
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);   // Set display mode.
    glutInitWindowPosition (50, 100);   // Set top-left display-window position.
    glutInitWindowSize (winW, winH);      // Set display-window width and height.
    glutCreateWindow ("An Example OpenGL Program"); // Create display window.

    init ( );                            // Execute initialization procedure.
    glutDisplayFunc (lineSegment);       // Send graphics to display window.
	glutMouseFunc(processMouse);
	glutMotionFunc(processMouseMovement);
    glutMainLoop ( );                    // Display everything and wait.
    return 0;
}