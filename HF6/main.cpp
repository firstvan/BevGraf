#include <GL/glut.h>
#include <iostream>
#include "myPoint2dh.hpp"
#include "myPolygon.hpp"
#include "myStar.hpp"

GLint winW = 1280, winH = 720;	//ablakméret
GLint dragged = -1;				//egérkezelés
GLdouble draggedX = 0, draggedY = 0;	//erintő vektor mozgatása a p0 pont mozgatására
std::vector<Point2DH<GLdouble>> faPontok = {Point2DH<GLdouble>(950, 50), Point2DH<GLdouble>(950, 350), Point2DH<GLdouble>(1000, 350), Point2DH<GLdouble>(1000, 50)};
myPoligon<GLdouble> fa(faPontok);

std::vector<Point2DH<GLdouble>> faKoronaPontok = { Point2DH<GLdouble>(950, 350), Point2DH<GLdouble>(1000, 350), Point2DH<GLdouble>(1100, 450), Point2DH<GLdouble>(1050, 500), Point2DH<GLdouble>(975, 510),Point2DH<GLdouble>(900, 475), Point2DH<GLdouble>(850, 400) };
myPoligon<GLdouble> faKorona(faKoronaPontok);

std::vector<Point2DH<GLdouble>> hegyPontok = { Point2DH<GLdouble>(50, 50), Point2DH<GLdouble>(300, 378), Point2DH<GLdouble>(580, 251), Point2DH<GLdouble>(925, 575), Point2DH<GLdouble>(1100, 50) };
myPoligon<GLdouble> hegy(hegyPontok);

std::vector<Point2DH<GLdouble>> bokorPontok = { Point2DH<GLdouble>(700, 50), Point2DH<GLdouble>(800, 50), Point2DH<GLdouble>(850, 75), Point2DH<GLdouble>(840, 125), Point2DH<GLdouble>(750, 175),Point2DH<GLdouble>(660, 125), Point2DH<GLdouble>(650, 75) };
myPoligon<GLdouble> bokor(bokorPontok);


myStar csillag(Point2DH<GLdouble>(300, 600), 30, 100,8, 30);

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

    glColor3d(0.0, 0.0, 0.0);

    fa.draw();
    faKorona.draw();
    hegy.draw();
    bokor.draw();
    csillag.draw();

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
