#include <GL/glut.h>
#include <iostream>
#include "point.hpp"
#include "myMatrix.hpp"
#include "myStar.hpp"


GLint winW = 720, winH = 720;
GLint fok = 0;
typedef myPoint<GLdouble> MYPOINT;
typedef myMatrix<GLdouble> MYMATRIX;

MYPOINT center(360, 360);

int s = 6;

myStar smallStar(center, 30, 100, s);
myStar bigStar(center, 100, 130, s, 20);

//Tranzformációs mátrixok inicializásása 'E' eltolás, 'F' elforgatás alfa fokkal, 'S' skálázás
MYMATRIX e1('E', -1 * center.getX(), -1 * center.getY());
MYMATRIX f1('F', 1.0);
MYMATRIX f2('F', -1.0);
MYMATRIX sk('S', 0.995, 0.995);
MYMATRIX sn('S', 1.005, 1.005);
MYMATRIX e2('E', center.getX(), center.getY());

//Végbemenő tranzformációs mátrixok, fontos a mátrix szorzás betartlása !! AxB*BxC
MYMATRIX transform1 = e2 * sn * f1 * e1;
MYMATRIX transform2 = e2 * sn * f2 * e1;


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
    glLineWidth(2);

}



void display()
{
    glClear(GL_COLOR_BUFFER_BIT);



    glColor3d(0.0, 0.0, 0.0);
    center.display();

    glColor3d(1.0, 0.0, 0.0);
    smallStar.draw();

    glColor3d(0.0, 0.0, 1.0);
    bigStar.draw();


    glutSwapBuffers();

}

void update(int n)
{
    if (fok == 90)
    {
        transform1 = e2 * sk * f1 * e1;
        transform2 = e2 * sk * f2 * e1;
    }

    if (fok == 180)
    {
        transform1 = e2 * sn * f1 * e1;
        transform2 = e2 * sn * f2 * e1;
        fok = 0;
    }

    //kiscsillag pontjaira a tranzformáció
    for (int i = 0; i < s; i++)
    {
        GLdouble temp[3] = { smallStar.getElement(1, i).getX(), smallStar.getElement(1, i).getY(), 1 };

        MYMATRIX m(3, 1, temp);
        m = transform1 * m;
        smallStar.setElement(1, i, m.getElement(0, 0), m.getElement(1, 0));

        //kiscsillag homogén kordinátában
        temp[0] = smallStar.getElement(2, i).getX();
        temp[1] = smallStar.getElement(2, i).getY();
        temp[2] = 1;

        MYMATRIX m1(3, 1, temp);
        m1 = transform1 * m1;

        smallStar.setElement(2, i, m1.getElement(0, 0), m1.getElement(1, 0));
    }

    //nagycsillag pontjaira a tranzformáció
    for (int i = 0; i < s; i++)
    {
        GLdouble temp[3] = { bigStar.getElement(1, i).getX(), bigStar.getElement(1, i).getY(), 1 };

        MYMATRIX m(3, 1, temp);
        m = transform2 * m;
        bigStar.setElement(1, i, m.getElement(0, 0), m.getElement(1, 0));

        temp[0] = bigStar.getElement(2, i).getX();
        temp[1] = bigStar.getElement(2, i).getY();
        temp[2] = 1;

        MYMATRIX m1(3, 1, temp);
        m1 = transform2 * m1;

        bigStar.setElement(2, i, m1.getElement(0, 0), m1.getElement(1, 0));
    }




    fok++;

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
