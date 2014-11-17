#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "myPoint2dh.hpp"
#include "myPolygon.hpp"
#include "myStar.hpp"

//tesselacio
#ifndef WIN32
typedef GLvoid(*CallBack)(...);
#else
typedef GLvoid(_stdcall *CallBack)();
#endif

GLUtesselator *tess; // A tesszelaciohoz szukseges mutato

GLint winW = 1280, winH = 720;	//ablakméret
GLint dragged = -1;				//egérkezelés
GLint dragged2 = -1;
std::vector<GLdouble> draggedX, draggedY;	//erintő vektor mozgatása a p0 pont mozgatására
std::vector<GLdouble> draggedX2, draggedY2;	//erintő vektor mozgatása a p0 pont mozgatására
bool move = false;
std::vector<Point2DH<GLdouble>> faPontok = {Point2DH<GLdouble>(950, 50), Point2DH<GLdouble>(950, 350), Point2DH<GLdouble>(1000, 350), Point2DH<GLdouble>(1000, 50)};
myPoligon<GLdouble> fa(faPontok);

std::vector<Point2DH<GLdouble>> faKoronaPontok = { Point2DH<GLdouble>(950, 350), Point2DH<GLdouble>(1000, 350), Point2DH<GLdouble>(1100, 450), Point2DH<GLdouble>(1050, 500),Point2DH<GLdouble>(900, 475), Point2DH<GLdouble>(850, 400) };
myPoligon<GLdouble> faKorona(faKoronaPontok);

std::vector<Point2DH<GLdouble>> hegyPontok = { Point2DH<GLdouble>(50, 50), Point2DH<GLdouble>(300, 378), Point2DH<GLdouble>(580, 251), Point2DH<GLdouble>(925, 575), Point2DH<GLdouble>(1100, 50) };
myPoligon<GLdouble> hegy(hegyPontok);

std::vector<Point2DH<GLdouble>> bokorPontok = { Point2DH<GLdouble>(700, 50), Point2DH<GLdouble>(800, 50), Point2DH<GLdouble>(840, 125),Point2DH<GLdouble>(700, 175), Point2DH<GLdouble>(650, 75) };
myPoligon<GLdouble> bokor(bokorPontok);

myStar csillag(Point2DH<GLdouble>(300, 600), 20, 100,8, 30);
myPoligon<GLdouble> nap(csillag.getPoints());


std::vector<Point2DH<GLdouble>> lencse1pontok = { Point2DH<GLdouble>(500, 175), Point2DH<GLdouble>(475, 225), Point2DH<GLdouble>(500, 250), Point2DH<GLdouble>(670, 250), Point2DH<GLdouble>(670, 200) };
std::vector<Point2DH<GLdouble>> lencse2pontok = { Point2DH<GLdouble>(300, 150), Point2DH<GLdouble>(320, 275), Point2DH<GLdouble>(410, 250), Point2DH<GLdouble>(430, 225) };
myPoligon<GLdouble> lencse1(lencse1pontok);
myPoligon<GLdouble> lencse2(lencse2pontok);

//std::vector<Point2DH<GLdouble>> temp1;
//myPoligon<GLdouble> t(temp1);

//std::vector<myPoligon<GLdouble>> bg;

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

    draggedX.resize(lencse1.getSize());
    draggedY.resize(lencse1.getSize());
    draggedX2.resize(lencse2.getSize());
    draggedY2.resize(lencse2.getSize());


}

void updateTess(void)
{
    tess = gluNewTess();
    gluTessCallback(tess, GLU_TESS_VERTEX, (CallBack)glVertex3dv);
    gluTessCallback(tess, GLU_TESS_BEGIN, (CallBack)glBegin);
    gluTessCallback(tess, GLU_TESS_END, (CallBack)glEnd);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3d(0.0, 0.0, 0.0);

    fa.draw();
    faKorona.draw();
    hegy.draw();
    bokor.draw();
    nap.draw();

    lencse1.drawWithPoints();
    lencse2.drawWithPoints();

    glBegin(GL_LINES);
    glVertex2d(lencse1[1].getX(), lencse1[1].getY());
    glVertex2d(lencse2[3].getX(), lencse2[3].getY());
    glEnd();
    myPoligon<GLdouble> t = hegy.cutWith(lencse1);
//hegy vágása
    int s = t.getSize();
    GLdouble ** polygon1 = new GLdouble*[s];
    for (int i = 0; i < s; i++)
    {
        polygon1[i] = new GLdouble[3];
    }
    for (int i = 0; i < s; i++)
    {
        polygon1[i][0] = t[i].getX();
        polygon1[i][1] = t[i].getY();
        polygon1[i][2] = 0;
    }

    updateTess();
    glColor3d(0.596, 0.984, 0.596);

    gluTessBeginPolygon(tess, NULL);
    for (int i = 0; i < s; i++)
        gluTessVertex(tess, polygon1[i], polygon1[i]); // A poligont alkoto csucsokat rendre felsoroljuk.
    gluTessEndPolygon(tess);

    t = bokor.cutWith(lencse1);
    glColor3d(0.0, 0.39, 0.0);
    t.draw(true);

    t = faKorona.cutWith(lencse1);
    glColor3d(0.0, 0.39, 0.0);
    t.draw(true);

    t = fa.cutWith(lencse1);
    glColor3d(0.55, 0.27, 0.075);
    t.draw(true);

    t = nap.cutWith(lencse1);
    s = t.getSize();
    polygon1 = new GLdouble*[s];
    for (int i = 0; i < s; i++)
    {
        polygon1[i] = new GLdouble[3];
    }
    for (int i = 0; i < s; i++)
    {
        polygon1[i][0] = t[i].getX();
        polygon1[i][1] = t[i].getY();
        polygon1[i][2] = 0;
    }

    updateTess();
    glColor3d(1.0, 0.84, 0.0);

    gluTessBeginPolygon(tess, NULL);
    for (int i = 0; i < s; i++)
        gluTessVertex(tess, polygon1[i], polygon1[i]); // A poligont alkoto csucsokat rendre felsoroljuk.
    gluTessEndPolygon(tess);


    t = hegy.cutWith(lencse2);
    s = t.getSize();
    polygon1 = new GLdouble*[s];
    for (int i = 0; i < s; i++)
    {
        polygon1[i] = new GLdouble[3];
    }
    for (int i = 0; i < s; i++)
    {
        polygon1[i][0] = t[i].getX();
        polygon1[i][1] = t[i].getY();
        polygon1[i][2] = 0;
    }

    updateTess();
    glColor3d(0.596, 0.984, 0.596);

    gluTessBeginPolygon(tess, NULL);
    for (int i = 0; i < s; i++)
        gluTessVertex(tess, polygon1[i], polygon1[i]); // A poligont alkoto csucsokat rendre felsoroljuk.
    gluTessEndPolygon(tess);

    t = bokor.cutWith(lencse2);
    glColor3d(0.0, 0.39, 0.0);
    t.draw(true);

    t = faKorona.cutWith(lencse2);
    glColor3d(0.0, 0.39, 0.0);
    t.draw(true);

    t = fa.cutWith(lencse2);
    glColor3d(0.55, 0.27, 0.075);
    t.draw(true);

    t = nap.cutWith(lencse2);
    s = t.getSize();
    polygon1 = new GLdouble*[s];
    for (int i = 0; i < s; i++)
    {
        polygon1[i] = new GLdouble[3];
    }
    for (int i = 0; i < s; i++)
    {
        polygon1[i][0] = t[i].getX();
        polygon1[i][1] = t[i].getY();
        polygon1[i][2] = 0;
    }

    updateTess();
    glColor3d(1.0, 0.84, 0.0);

    gluTessBeginPolygon(tess, NULL);
    for (int i = 0; i < s; i++)
        gluTessVertex(tess, polygon1[i], polygon1[i]); // A poligont alkoto csucsokat rendre felsoroljuk.
    gluTessEndPolygon(tess);

    glutSwapBuffers();


}

GLint getActivePoint(myPoligon<GLdouble> p, GLint size, GLint sens, GLint xMouse, GLint yMouse)
{
    GLint  i, s = sens * sens;
    for (i = 0; i < size; i++)
    {
        if (p[i].pointDis2(xMouse, yMouse) < s)
        {
            return i;
        }
    }

    return -1;
}

GLint getActivePoint2(myPoligon<GLdouble> p, GLint size, GLint sens, GLint xMouse, GLint yMouse)
{
    GLint  i, s = sens * sens;
    for (i = 0; i < size; i++)
    {
        if (p[i].pointDis2(xMouse, yMouse) < s)
        {
            for (size_t j = 0; j < lencse1pontok.size(); j++)
            {
                draggedX[j] = lencse1[j].getX() - p[i].getX();
                draggedY[j] = lencse1[j].getY() - p[i].getY();
            }

            for (int j = 0; j < lencse2.getSize(); j++)
            {
                draggedX2[j] = lencse2[j].getX() - p[i].getX();
                draggedY2[j] = lencse2[j].getY() - p[i].getY();
            }

            return i;
        }
    }

    return -1;
}

void processMouse(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
    int i;
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
    {
        if ((i = getActivePoint(lencse1, lencse1.getSize(), 8, xMouse, winH - yMouse)) != -1)
            dragged = i;

        if ((i = getActivePoint(lencse2, lencse2.getSize(), 8, xMouse, winH - yMouse)) != -1)
            dragged2 = i;

    }

    if (button == GLUT_LEFT_BUTTON && action == GLUT_UP)
    {
        dragged = -1;
        dragged2 = -1;
    }

    if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN)
    {
        if((i = getActivePoint2(lencse1, lencse1.getSize(), 8, xMouse, winH - yMouse)) != -1)
            move = true;

        if((i = getActivePoint2(lencse2, lencse2.getSize(), 8, xMouse, winH - yMouse)) != -1)
            move = true;
    }

    if (button == GLUT_RIGHT_BUTTON && action == GLUT_UP)
    {
        move = false;
    }

}


void processMouseMotion(GLint xMouse, GLint yMouse)
{
    if (dragged > -1)
    {
        lencse1[dragged].setX(xMouse);
        lencse1[dragged].setY(winH - yMouse);

    }

    if (dragged2 > -1)
    {
        lencse2[dragged2].setX(xMouse);
        lencse2[dragged2].setY(winH - yMouse);

    }

    if (move)
    {
        for (int i = 0; i < lencse1.getSize(); i++)
        {
            lencse1[i].setX(xMouse + draggedX[i]);
            lencse1[i].setY(winH - yMouse + draggedY[i]);
        }

        for (int i = 0; i < lencse2.getSize(); i++)
        {
            lencse2[i].setX(xMouse + draggedX2[i]);
            lencse2[i].setY(winH - yMouse + draggedY2[i]);
        }

    }

    glutPostRedisplay();
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("Varázs Szemüveg");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(processMouse);
    glutMotionFunc(processMouseMotion);


    glutMainLoop();



    return 0;
}
