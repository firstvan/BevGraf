#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <cmath>
#include <vector>
#include <iostream>
#include "myMatrix.hpp"
#include "myPoint4D.hpp"


typedef myPoint4D<GLdouble> POINT4D;
typedef myMatrix<GLdouble> MATRIX;

GLsizei winWidth = 1280, winHeight = 720;
GLdouble step = 0.5;
GLint keyStates[256];
GLdouble alfa = 225;


POINT4D w1(-20, -20);
POINT4D w2(20, 20);

POINT4D v1(200, 0);
POINT4D v2(720, 720);

MATRIX vw;
MATRIX a("Ax", alfa);


POINT4D t1;
POINT4D t2;
POINT4D t3;
POINT4D t4;

MATRIX WVA(4, 4);

GLdouble p=0.0;

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, winWidth, 0.0, winHeight);
    glShadeModel(GL_FLAT);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    vw.initWindowToViewPort(w1, w2, v1, v2);

    WVA = vw * a;
}

GLdouble f(const GLdouble& x, const GLdouble& y)
{
    return std::sin(std::sqrt(x*x + y*y)+p);
}


void keyOperations();

void display()
{

    glClear(GL_COLOR_BUFFER_BIT);
    keyOperations();
    glColor3f(0.0, 0.0, 0.0);

    for (GLdouble x = -20; x < 20; x += step)
    {
        for (GLdouble y = -20; y < 20; y += step)
        {

            t1.x = x;
            t1.y = y;
            t1.z = f(x, y);

            t1.trans(WVA);
            t1.norma();

            t2.x = x;
            t2.y = y+step;
            t2.z = f(x, t2.y);

            t2.trans(WVA);
            t2.norma();

            t3.x = x+step;
            t3.y = y+step;
            t3.z = f(t3.x, t3.y);

            t3.trans(WVA);
            t3.norma();

            t4.x = x+step;
            t4.y = y;
            t4.z = f(t4.x, y);

            t4.trans(WVA);
            t4.norma();

            glColor3f(1.0, 0.0, 0.0);

            glBegin(GL_POLYGON);

            glVertex2d(t1.x, t1.y);
            glVertex2d(t2.x, t2.y);
            glVertex2d(t3.x, t3.y);
            glVertex2d(t4.x, t4.y);

            glEnd();

            glColor3f(0.0, 0.0, 0.0);
            glBegin(GL_LINE_LOOP);

            glVertex2d(t1.x, t1.y);
            glVertex2d(t2.x, t2.y);
            glVertex2d(t3.x, t3.y);
            glVertex2d(t4.x, t4.y);

            glEnd();

        }
    }
    std::cout << alfa << std::endl;
    glutSwapBuffers();
}


void update(int n)
{
    p -= 0.1;

    glutPostRedisplay();
    glutTimerFunc(10, update, 0);
}

void keyPressed(unsigned char key, int x, int y)
{
    keyStates[key] = 1;
}

void keyUp(unsigned char key, int x, int y)
{
    keyStates[key] = 0;
}


void keyOperations()
{
    if (keyStates['w'])
    {

        if (alfa <= 360)
            alfa++;
    }
    if (keyStates['s'])
    {
        if (alfa >= 180)
            alfa--;
    }

    a.setDeg("Ax", alfa);
    WVA = vw * a;

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("f(sqrt(x*x+y*y))");
    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);
    glutTimerFunc(10, update, 0);
    glutMainLoop();
    return 0;
}
