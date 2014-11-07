#include <GL/glut.h>
#include <iostream>
#include "point.hpp"
#include "myMatrix.hpp"

GLint winW = 720, winH = 720;

typedef myPoint<GLdouble> MYPOINT;
typedef myMatrix<GLdouble> MYMATRIX;




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



}


int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("Csillagok");

    init();

    glutDisplayFunc(display);

    glutMainLoop();



    return 0;
}
