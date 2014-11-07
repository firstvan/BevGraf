﻿#include <GL/glut.h>
#include <iostream>
#include "point.hpp"
#include "myMatrix.hpp"
#include "myStar.hpp"


GLint winW = 720, winH = 720;

typedef myPoint<GLdouble> MYPOINT;
typedef myMatrix<GLdouble> MYMATRIX;

MYPOINT center(360, 360);

int s = 6;

myStar smallStar(center, 50, 150, s);
myStar bigStar(center, 150, 200, s, 20);

MYMATRIX e1('E', -1 * center.getX(), -1 * center.getY());
MYMATRIX f1('F', 1);
MYMATRIX f2('F', -1);
MYMATRIX sk('S', 0.99, 0.99);
MYMATRIX sn('S', 1.005, 1.005);
MYMATRIX e2('E', center.getX(), center.getY());

MYMATRIX transform1 = e2 * sn * f1 * e1;


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


    /*  std::cout << "*******************************************\n";
      transform1.kiir();
      std::cout << "*******************************************\n";*/

    glColor3d(0.0, 0.0, 0.0);
    center.display();

    glColor3d(1.0, 0.0, 0.0);
    //smallStar.drawCircle();
    smallStar.draw();

    glColor3d(1.0, 0.0, 1.0);
    //bigStar.drawCircle();
    //bigStar.draw();


    glutSwapBuffers();

}

void update(int n)
{
    for (int i = 0; i < s; i++)
    {
        GLdouble temp[3] = { smallStar.getElement(1, i).getX(), smallStar.getElement(1, i).getY(), 1 };

        MYMATRIX m(3, 1, temp);
        MYMATRIX res1(3, 1, '0', 0);
        res1 = transform1 * m;
        smallStar.setElement(1, i, res1.getElement(0, 0), res1.getElement(1, 0));

        temp[0] = smallStar.getElement(2, i).getX();
        temp[1] = smallStar.getElement(2, i).getY();
        temp[2] = 1;
        std::cout << temp[0] << ", " << temp[1] << ", " << temp[2] << "\n";
        MYMATRIX m1(3, 1, temp);
        MYMATRIX res2(3, 1, '0', 0);
        res2 = transform1 * m1;

        smallStar.setElement(2, i, res2.getElement(0, 0), res2.getElement(1, 0));
        /*std::cout << "-----------------------------------\n";
        m.kiir();
        std::cout << "-----------------------------------\n";
        m1.kiir();
        std::cout << "-----------------------------------\n";*/
    }


    glutPostRedisplay();
    glutTimerFunc(20, update, 0);
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("Csillagok");

    init();

    glutDisplayFunc(display);

    glutTimerFunc(10, update, 0);

    glutMainLoop();



    return 0;
}
