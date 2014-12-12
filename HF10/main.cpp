#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <cmath>
#include <vector>
#include <iostream>
#include "myMatrix.hpp"
#include "myPoint4D.hpp"

#define PI	3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679

GLsizei winWidth = 1280, winHeight = 720;
GLdouble lepeskoz = 0.1;
myPoint4D<GLdouble> center(0, 0, 0);
GLdouble r = 1.0;

double s = 2.0;
myPoint4D<GLdouble> centerPoint(0, 0, s);

myMatrix<GLdouble> VC("Vc", s);
myMatrix<GLdouble> WV;

myPoint4D<GLdouble> w1(-2.0, -2.0);
myPoint4D<GLdouble> w2(2.0, 2.0);

myPoint4D<GLdouble> v1(20.0, 20.0);
myPoint4D<GLdouble> v2(800, 800);

myMatrix<GLdouble> RX("Rx", 80);
myMatrix<GLdouble> RY("Ry", 40);

myMatrix<GLdouble> trans;

myPoint4D<GLdouble> temp1;
myPoint4D<GLdouble> temp2;
myPoint4D<GLdouble> temp3;
myPoint4D<GLdouble> temp4;

myPoint4D<GLdouble> vectorialMultiply(const myPoint4D<GLdouble> a, myPoint4D<GLdouble> b)
{
    myPoint4D<GLdouble> temp;
    temp.x = (a.y * b.z) - (b.y * a.z);
    temp.y = -1 * ((a.x * b.z) - (b.x * a.z));
    temp.z = (a.x * b.y) - (b.x * a.y);

    return temp;

}


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

    WV.initWindowToViewPort(w1, w2, v1, v2);

    trans = WV * VC * RX * RY;

}

void display()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);


    for (GLdouble teta = 0.0; teta < 2 * PI; teta += lepeskoz)
    {
        for (GLdouble fi = 0.0; fi < PI; fi += lepeskoz)
        {
            temp1.x = center.x + r * cos(teta) * sin(fi);
            temp1.y = center.y + r * sin(teta) * sin(fi);
            temp1.z = center.z + r * cos(fi);

            temp1.trans(trans);
            temp1.norma();


            temp2.x = center.x + r * cos(teta) * sin(fi + lepeskoz);
            temp2.y = center.y + r * sin(teta) * sin(fi + lepeskoz);
            temp2.z = center.z + r * cos(fi + lepeskoz);

            temp2.trans(trans);
            temp2.norma();

            temp3.x = center.x + r * cos(teta + lepeskoz) * sin(fi + lepeskoz);
            temp3.y = center.y + r * sin(teta + lepeskoz) * sin(fi + lepeskoz);
            temp3.z = center.z + r * cos(fi + lepeskoz);

            temp3.trans(trans);
            temp3.norma();

            temp4.x = center.x + r * cos(teta + lepeskoz) * sin(fi);
            temp4.y = center.y + r * sin(teta + lepeskoz) * sin(fi);
            temp4.z = center.z + r * cos(fi);

            temp4.trans(trans);
            temp4.norma();

            myPoint4D<GLdouble> normalVec;
            normalVec = vectorialMultiply(temp2-temp1, temp3-temp1);





            glBegin(GL_LINE_LOOP);

            glVertex2d(temp1.x, temp1.y);
            glVertex2d(temp2.x, temp2.y);
            glVertex2d(temp3.x, temp3.y);
            glVertex2d(temp4.x, temp4.y);

            glEnd();
        }
    }




    glutSwapBuffers();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Gömb");
    init();

    glutDisplayFunc(display);
//	glutKeyboardFunc(keyPressed);
//	glutKeyboardUpFunc(keyUp);
//	glutTimerFunc(50, update, 0);
    glutMainLoop();
    return 0;
}

