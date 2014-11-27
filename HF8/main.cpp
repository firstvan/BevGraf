#include <GL/glut.h>
#include <math.h>
//#include "point.hpp"
#include <vector>
#include <iostream>
#include "myMatrix.hpp"
#include "myPoint4D.hpp"
#include "myCube.h"

typedef myMatrix<GLdouble> Matrix;
typedef myPoint4D<GLdouble> POINT4D;

GLsizei winWidth = 1280, winHeight = 720;
bool dragged = false;
GLint originalx, originaly;

POINT4D A(-1, -1);
POINT4D B(1, 1);

POINT4D C(50, 50);
POINT4D D(500, 500);

POINT4D A1(-1, -1);
POINT4D B1(1, 1);

POINT4D C1(750, 50);
POINT4D D1(1200, 500);

std::vector<POINT4D> cubePoints;
std::vector<POINT4D> cubePoints2;
myCube<GLdouble> cube;
myCube<GLdouble> cube2;

GLdouble dX = 20, dY = 50;

Matrix W("E");
Matrix WR("E");
Matrix W2("E");
Matrix VM("Vm");
Matrix VC("Vc", 1.5);
Matrix RX("Rx", dX);
Matrix RY("Ry", dY);
Matrix VMW;
Matrix VCW;

Matrix temp;

Matrix seged(4, 1);
Matrix seged2(4, 1);




void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, winWidth, 0.0, winHeight);
    glShadeModel(GL_FLAT);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glPointSize(5);
    glLineWidth(3);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    cubePoints.emplace_back(POINT4D(0.5, 0.5, 0.5));
    cubePoints.emplace_back(POINT4D(-0.5, 0.5, 0.5));
    cubePoints.emplace_back(POINT4D(-0.5, -0.5, 0.5));
    cubePoints.emplace_back(POINT4D(0.5, -0.5, 0.5));
    cubePoints.emplace_back(POINT4D(0.5, 0.5, -0.5));
    cubePoints.emplace_back(POINT4D(-0.5, 0.5, -0.5));
    cubePoints.emplace_back(POINT4D(-0.5, -0.5, -0.5));
    cubePoints.emplace_back(POINT4D(0.5, -0.5, -0.5));

    cubePoints2 = cubePoints;

    W.initWindowToViewPort(A, B, C, D);

    VMW = W * VM;

    temp = RX * RY;

    Matrix seged(4, 1);
    Matrix seged2(4, 1);

    seged.setElement(3, 0, 1);

    for (int i = 0; i < 8; i++)
    {
        seged.setElement(0, 0, cubePoints[i].x);
        seged.setElement(1, 0, cubePoints[i].y);
        seged.setElement(2, 0, cubePoints[i].z);
        seged2 = temp * seged;

        cubePoints[i].x = seged2.getElement(0, 0);
        cubePoints[i].y = seged2.getElement(1, 0);
        cubePoints[i].z = seged2.getElement(2, 0);
        cubePoints[i].t = seged2.getElement(3, 0);

    }



    W2.initWindowToViewPort(A1, B1, C1, D1);

    VCW = W2 * VC;

    temp = RX * RY;

    seged.setElement(3, 0, 1);

    for (int i = 0; i < 8; i++)
    {
        seged.setElement(0, 0, cubePoints2[i].x);
        seged.setElement(1, 0, cubePoints2[i].y);
        seged.setElement(2, 0, cubePoints2[i].z);
        seged2 = temp * seged;

        cubePoints2[i].x = seged2.getElement(0, 0);
        cubePoints2[i].y = seged2.getElement(1, 0);
        cubePoints2[i].z = seged2.getElement(2, 0);
        cubePoints2[i].t = seged2.getElement(3, 0);
    }

}




void display()
{

    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(5);
    glLineWidth(3);

    cube.data = cubePoints;



    for (int i = 0; i < 8; i++)
    {
        seged.setElement(0, 0, cube.data[i].x);
        seged.setElement(1, 0, cube.data[i].y);
        seged.setElement(2, 0, cube.data[i].z);
        seged.setElement(3, 0, 1);

        seged2 = VMW * seged;

        cube.data[i].x = seged2.getElement(0, 0);
        cube.data[i].y = seged2.getElement(1, 0);
        cube.data[i].z = seged2.getElement(2, 0);
        cube.data[i].t = seged2.getElement(3, 0);

        cube.data[i].norma();

    }

    cube2.data = cubePoints2;



    for (int i = 0; i < 8; i++)
    {
        seged.setElement(0, 0, cube2.data[i].x);
        seged.setElement(1, 0, cube2.data[i].y);
        seged.setElement(2, 0, cube2.data[i].z);
        seged.setElement(3, 0, 1);

        seged2 = VCW * seged;

        cube2.data[i].x = seged2.getElement(0, 0);
        cube2.data[i].y = seged2.getElement(1, 0);
        cube2.data[i].z = seged2.getElement(2, 0);
        cube2.data[i].t = seged2.getElement(3, 0);

        cube2.data[i].norma();

    }

    glColor3f(0.0, 1.0, 0.0);

    cube.draw();

    glColor3f(1.0, 0.0, 0.0);

    cube2.draw();

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2d(600, 0);
    glVertex2d(600, 720);
    glEnd();

    glutSwapBuffers();
}

void processMouse(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
    {
        originalx = xMouse;
        originaly = winHeight - yMouse;
        dragged = true;
    }
    if (button == GLUT_LEFT_BUTTON && action == GLUT_UP)
    {
        dragged = false;
    }
}

void processMouseActiveMotion(GLint xMouse, GLint yMouse)
{

    if (dragged)
    {
        GLdouble degx = (xMouse - originalx) / static_cast<GLdouble>(100);
        GLdouble degy = (winHeight - yMouse - originaly) / static_cast<GLdouble>(100);

        RX.setDeg("Rx", degy);
        RY.setDeg("Ry", degx);

        temp = RX * RY;

        seged.setElement(3, 0, 1);


        for (int i = 0; i < 8; i++)
        {

            seged.setElement(0, 0, cubePoints[i].x);
            seged.setElement(1, 0, cubePoints[i].y);
            seged.setElement(2, 0, cubePoints[i].z);

            seged2 = temp * seged;

            cubePoints[i].x = seged2.getElement(0, 0);
            cubePoints[i].y = seged2.getElement(1, 0);
            cubePoints[i].z = seged2.getElement(2, 0);
            cubePoints[i].t = seged2.getElement(3, 0);
        }


        seged.setElement(3, 0, 1);

        for (int i = 0; i < 8; i++)
        {
            seged.setElement(0, 0, cubePoints2[i].x);
            seged.setElement(1, 0, cubePoints2[i].y);
            seged.setElement(2, 0, cubePoints2[i].z);
            seged2 = temp * seged;

            cubePoints2[i].x = seged2.getElement(0, 0);
            cubePoints2[i].y = seged2.getElement(1, 0);
            cubePoints2[i].z = seged2.getElement(2, 0);
            cubePoints2[i].t = seged2.getElement(3, 0);

            cubePoints2[i].norma();

        }

    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Perpendicular and central projection");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(processMouse);
    glutMotionFunc(processMouseActiveMotion);
    glutMainLoop();
    return 0;
}
