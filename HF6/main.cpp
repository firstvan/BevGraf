#include <GL/glut.h>
#include <iostream>
#include "myPoint2dh.hpp"

GLint winW = 800, winH = 800;	//ablakméret
GLint dragged = -1;				//egérkezelés
GLdouble draggedX = 0, draggedY = 0;	//erintő vektor mozgatása a p0 pont mozgatására



void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, winW, 0.0, winH);
    glShadeModel(GL_FLAT);
    glPointSize(5);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}



void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3d(0.4, 0.7, 0.5);

    glutSwapBuffers();

}
/*

GLint getActivePoint(, GLint size, GLint sens, GLint xMouse, GLint yMouse)
{
}

void processMouse(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
}

void processMouseMotion(GLint xMouse, GLint yMouse)
{


    glutPostRedisplay();
}*/

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("Varázs Szemüveg");

    init();

    glutDisplayFunc(display);
    /*glutMouseFunc(processMouse);
    glutMotionFunc(processMouseMotion);
    */

    glutMainLoop();



    return 0;
}
