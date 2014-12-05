#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <math.h>
#include <vector>
#include <iostream>
#include "myMatrix.hpp"
#include "myPoint4D.hpp"


typedef myPoint4D<GLdouble> POINT4D;
typedef myMatrix<GLdouble> MATRIX;

GLsizei winWidth = 1280, winHeight = 720;
bool dragged = false;
GLdouble step = 0.5;

POINT4D w1(-20, -20);
POINT4D w2(20, 20);

POINT4D v1(200, 0);
POINT4D v2(720, 720);

MATRIX temp(4, 1);
MATRIX temp1(4, 1);
MATRIX temp2(4, 1);
MATRIX temp3(4, 1);
MATRIX temp4(4, 1);

MATRIX vw;
MATRIX a("Ax", 225);

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
    //a.kiir();
}

GLdouble f(const GLdouble& x, const GLdouble& y)
{
    return sin(sqrt(x*x + y*y)+p);
}



void display()
{

    glClear(GL_COLOR_BUFFER_BIT);



    glColor3f(0.0, 0.0, 0.0);

    for (GLdouble x = -20; x < 20; x += step)
    {
        for (GLdouble y = -20; y < 20; y += step)
        {

            //			Első pont
            temp.matrix[0][0] = x;
            temp.matrix[1][0] = y;
            temp.matrix[2][0] = f(x, y);
            temp.matrix[3][0] = 1;

            temp1 =  vw * a * temp;

            temp1.matrix[0][0] /= temp1.matrix[3][0];
            temp1.matrix[1][0] /= temp1.matrix[3][0];

            glVertex2d(temp1.matrix[0][0], temp1.matrix[1][0]);

            //			Második pont
            temp.matrix[0][0] = x;
            temp.matrix[1][0] = y+step;
            temp.matrix[2][0] = f(x, y+step);
            temp.matrix[3][0] = 1;

            temp2 = vw * a * temp;

            temp2.matrix[0][0] /= temp1.matrix[3][0];
            temp2.matrix[1][0] /= temp1.matrix[3][0];

            //			Harmadik pont
            temp.matrix[0][0] = x + step;
            temp.matrix[1][0] = y+step;
            temp.matrix[2][0] = f(x+step, y+step);
            temp.matrix[3][0] = 1;

            temp3 = vw * a * temp;

            temp3.matrix[0][0] /= temp1.matrix[3][0];
            temp3.matrix[1][0] /= temp1.matrix[3][0];


            //			Negyedik pont
            temp.matrix[0][0] = x + step;
            temp.matrix[1][0] = y;
            temp.matrix[2][0] = f(x+step, y);
            temp.matrix[3][0] = 1;

            temp4 = vw * a * temp;

            temp4.matrix[0][0] /= temp1.matrix[3][0];
            temp4.matrix[1][0] /= temp1.matrix[3][0];
            glColor3f(1.0, 0.0, 0.0);

            glBegin(GL_POLYGON);

            glVertex2d(temp1.matrix[0][0], temp1.matrix[1][0]);
            glVertex2d(temp2.matrix[0][0], temp2.matrix[1][0]);
            glVertex2d(temp3.matrix[0][0], temp3.matrix[1][0]);
            glVertex2d(temp4.matrix[0][0], temp4.matrix[1][0]);

            glEnd();

            glColor3f(0.0, 0.0, 0.0);
            glBegin(GL_LINE_LOOP);

            glVertex2d(temp1.matrix[0][0], temp1.matrix[1][0]);
            glVertex2d(temp2.matrix[0][0], temp2.matrix[1][0]);
            glVertex2d(temp3.matrix[0][0], temp3.matrix[1][0]);
            glVertex2d(temp4.matrix[0][0], temp4.matrix[1][0]);

            glEnd();

        }
    }

    glutSwapBuffers();
}


void update(int n)
{
    p -= 0.1;

    glutPostRedisplay();
    glutTimerFunc(100, update, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("f(sqrt(x*x+y*y))");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(100, update, 0);
    glutMainLoop();
    return 0;
}
