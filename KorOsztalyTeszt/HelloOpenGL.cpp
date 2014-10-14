#include <GL/glut.h>					// (or others, depending on the system in use)
#include "myCircle.hpp"					

typedef myCircle<GLdouble> MyCircle;

MyCircle circle1(200, 150, 50);


void init (void)
{
    glClearColor (0.0, 1.0, 1.0, 0.0);	// Set display-window color to white.

    glMatrixMode (GL_PROJECTION);		// Set projection parameters.
    gluOrtho2D (0.0, 400.0, 0.0, 300.0);
}

void lineSegment (void)
{
    glClear (GL_COLOR_BUFFER_BIT);  // Clear display window.

    glColor3f (1.0, 0.4, 0.2);      

	circle1.draw();

    glFlush ( );     // Process all OpenGL routines as quickly as possible.
}

int main (int argc, char** argv)
{
    glutInit (&argc, argv);                         // Initialize GLUT.
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);   // Set display mode.
    glutInitWindowPosition (50, 100);   // Set top-left display-window position.
    glutInitWindowSize (400, 300);      // Set display-window width and height.
    glutCreateWindow ("An Example OpenGL Program"); // Create display window.

    init ( );                            // Execute initialization procedure.
    glutDisplayFunc (lineSegment);       // Send graphics to display window.
    glutMainLoop ( );                    // Display everything and wait.
    return 0;
}