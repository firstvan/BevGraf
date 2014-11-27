#include <GL/glut.h>
#include "point.hpp"
#include "Slider.hpp"
#include "myCircle.hpp"



typedef mySlider<GLint> Slider;
typedef myPoint<GLint> Point;

GLint winW = 800, winH = 800;
GLint dragged;
myCircle<GLdouble> circle(400, 400, 0, 1);
GLint size = 3;
GLdouble tenpi = 180 * 10;
Slider sliders[] =
{
    Slider(Point(100, 150), Point(700, 150), 1, 60, 59),
    Slider(Point(100, 100),Point(700, 100), 0, 1800),
    Slider(Point(100, 50), Point(700, 50), 0, 100)
};

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, winW, 0.0, winH);
    glShadeModel(GL_FLAT);
    glPointSize(10);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 1.0, 1.0);
    circle.draw();
    //circle.drawSplitted();
    circle.drawEvolvent();


    for (int i = 0; i < size; i++)
    {
        glColor3f(1.0, 0.5, 0.0);
        sliders[i].draw();
    }

    glutSwapBuffers();
}

GLint getActivePoint(Slider *p, GLint size, GLint sens, GLint xMouse, GLint yMouse)
{
    GLint  i, s = sens * sens;
    for (i = 0; i < size; i++)
    {
        if (p[i].dis2Click(xMouse, yMouse) < s)
            return i;
    }

    return -1;
}

void processMouse(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
    GLint i;
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
    {
        if ((i = getActivePoint(sliders, size, 8, xMouse, winH - yMouse)) != -1)
            dragged = i;
    }

    if (button == GLUT_LEFT_BUTTON && action == GLUT_UP)
    {
        dragged = -1;
    }
}

void processMouseMotion(GLint xMouse, GLint yMouse)
{
    if (dragged > -1)
    {
        sliders[dragged].setClickX(xMouse);
        sliders[dragged].setClickY(winH - yMouse);
        if (dragged == 2)
        {
            GLint temp = sliders[dragged].getValue();
            circle.setR(temp);
        }

        if (dragged == 1)
        {
            GLint temp = sliders[dragged].getValue();
            circle.setT(temp);
        }


        if (dragged == 0)
        {
            GLint temp = sliders[dragged].getCurrentPosition();
            circle.split(temp);
        }

        glutPostRedisplay();
    }
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winW, winH);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("3.HF");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(processMouse);
    glutMotionFunc(processMouseMotion);
    glutMainLoop();



    return 0;
}
