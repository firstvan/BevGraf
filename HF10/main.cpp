#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <cmath>
#include <vector>
#include <iostream>
#include "myMatrix.hpp"
#include "myPoint4D.hpp"
#include <algorithm>
#include <functional>
#include <array>
#include <iostream>

#define PI	3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679

GLsizei winWidth = 1280, winHeight = 720;
GLdouble lepeskoz = PI / 15;
myPoint4D<GLdouble> center(0, 0, 0);
GLdouble r = 1.0;

double s = 2.0;
myPoint4D<GLdouble> centerPoint(0, 0, s);
myPoint4D<GLdouble> f(1280, 1000, 1000);

myMatrix<GLdouble> VC("Vc", s);
myMatrix<GLdouble> WV;

myPoint4D<GLdouble> w1(-2.0, -2.0);
myPoint4D<GLdouble> w2(2.0, 2.0);

myPoint4D<GLdouble> v1(100.0, 20.0);
myPoint4D<GLdouble> v2(800.0, 720.0);

myMatrix<GLdouble> RX("Rx", 0);//25
myMatrix<GLdouble> RY("Ry", 0);//20

myMatrix<GLdouble> trans;

myPoint4D<GLdouble> temp1;
myPoint4D<GLdouble> temp2;
myPoint4D<GLdouble> temp3;
myPoint4D<GLdouble> temp4;

struct SIDE
{
    myPoint4D<GLdouble> x1;
    myPoint4D<GLdouble> x2;
    myPoint4D<GLdouble> x3;
    myPoint4D<GLdouble> x4;

    myPoint4D<GLdouble> norma;
    myPoint4D<GLdouble> S;

};


struct
{
    bool operator()(SIDE a, SIDE b)
    {
        return ((a.x1.z + a.x2.z + a.x3.z + a.x4.z) / 4) < ((b.x1.z + b.x2.z + b.x3.z + b.x4.z) / 4);
    }
} custom;


std::vector<SIDE> points;

myPoint4D<GLdouble> vectorialMultiply(const myPoint4D<GLdouble> a, myPoint4D<GLdouble> b)
{
    myPoint4D<GLdouble> temp;
    temp.x = ((a.y * b.z) - (b.y * a.z));
    temp.y = (-1 * (a.x * b.z) + (b.x * a.z));
    temp.z = ((a.x * b.y) - (b.x * a.y));

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


    glPointSize(3);

    WV.initWindowToViewPort(w1, w2, v1, v2);

    trans = WV * VC * RX * RY;

    for (GLdouble fi = 0.0; fi < PI; fi += lepeskoz)
    {
        for (GLdouble tetha = 0.0; tetha < 2 * PI; tetha += lepeskoz)
        {
            SIDE  tempSide;

            temp1.x = center.x + r * cos(tetha) * sin(fi);
            temp1.y = center.y + r * sin(tetha) * sin(fi);
            temp1.z = center.z + r * cos(fi);

            tempSide.x1 = temp1;

            temp2.x = center.x + r * cos(tetha) * sin(fi + lepeskoz);
            temp2.y = center.y + r * sin(tetha) * sin(fi + lepeskoz);
            temp2.z = center.z + r * cos(fi + lepeskoz);

            tempSide.x2 = temp2;

            temp3.x = center.x + r * cos(tetha + lepeskoz) * sin(fi + lepeskoz);
            temp3.y = center.y + r * sin(tetha + lepeskoz) * sin(fi + lepeskoz);
            temp3.z = center.z + r * cos(fi + lepeskoz);

            tempSide.x3 = temp3;

            temp4.x = center.x + r * cos(tetha + lepeskoz) * sin(fi);
            temp4.y = center.y + r * sin(tetha + lepeskoz) * sin(fi);
            temp4.z = center.z + r * cos(fi);

            tempSide.x4 = temp4;

            if (fi < PI/2)
                tempSide.norma = vectorialMultiply(temp1 - temp2, temp1 - temp3);
            else
                tempSide.norma = vectorialMultiply(temp4 - temp1, temp1 - temp3);


            //tempSide.norma.doUnitVector();

            points.emplace_back(tempSide);
        }
    }

    std::sort(points.begin(), points.end(), custom);

    f.doUnitVector();

}

void display()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);



    int i = 0;
    for (auto a : points)
    {

        temp1 = a.x1;
        temp2 = a.x2;
        temp3 = a.x3;
        temp4 = a.x4;

        temp1.trans(trans);
        temp1.norma();
        temp2.trans(trans);
        temp2.norma();
        temp3.trans(trans);
        temp3.norma();
        temp4.trans(trans);
        temp4.norma();

        //centerPoint.trans(trans);
        myPoint4D<GLdouble> S;
        S.x = -1 * temp1.x;
        S.y = -1 * temp1.y;
        S.z = -1 * temp1.z + centerPoint.z;
        S.doUnitVector();

        a.norma.trans(trans);
        a.norma.norma();
        a.norma.doUnitVector();

        double alfa = a.norma.x * S.x + a.norma.y * S.y + a.norma.z * S.z;

        //if (alfa > 0)
        //{

        double comp = a.norma.x * f.x + a.norma.y * f.y + a.norma.z * f.z;

        comp = (comp + 1) / double(2);

        glColor3f(comp, comp, comp);
        glBegin(GL_POLYGON);

        glVertex2d(temp1.x, temp1.y);
        glVertex2d(temp2.x, temp2.y);
        glVertex2d(temp3.x, temp3.y);
        glVertex2d(temp4.x, temp4.y);

        glEnd();

        /*glColor3f(1.0, 0.0, 1.0);
        a.norma.trans(trans);
        a.norma.norma();
        glBegin(GL_LINES);
        glVertex2d(a.norma.x, a.norma.y);
        glVertex2d(S.x, S.y);
        glEnd();*/


        //}
    }




    glutSwapBuffers();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("G�mb");
    init();

    glutDisplayFunc(display);
//	glutKeyboardFunc(keyPressed);
//	glutKeyboardUpFunc(keyUp);
//	glutTimerFunc(50, update, 0);
    glutMainLoop();
    return 0;
}

