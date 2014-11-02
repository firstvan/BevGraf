#include <GL/glut.h>
#include <iostream>
#include "point.hpp"
#include "Slider.hpp"
#include "myCircle.hpp"

typedef myPoint<GLdouble> MYPOINT;

GLint winW = 800, winH = 800;
GLint dragged;
GLdouble draggedX = 0, draggedY = 0;
GLint size = 3;

MYPOINT irany(200, 250);

MYPOINT points[3] = {
	MYPOINT(200, 200),
	MYPOINT(350, 325),
	MYPOINT(450, 200),
};

void init(){
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winW, 0.0, winH);
	glShadeModel(GL_FLAT);
	glPointSize(5);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2d(points[0].getX(), points[0].getY());
	glVertex2d(irany.getX(), irany.getY());
	glEnd();

	glColor3d(0.0, 0.0, 1.0);
	irany.display();


	glColor3d(0.0, 0.0, 0.0);
	for (int i = 0; i < 3; i++)
	{
		points[i].display();
	}

	

	glutSwapBuffers();
}


GLint getActivePoint(MYPOINT * p, GLint size, GLint sens, GLint xMouse, GLint yMouse){
	GLint  i, s = sens * sens;
	for (i = 0; i < size; i++){
		if (p[i].pointDis2(xMouse, yMouse) < s)
		{
			if (i == 0)
			{
				draggedX = irany.getX() - p[0].getX();
				draggedY = irany.getY() - p[0].getY();
			}
			return i;
		}
	}

	return -1;
}

void processMouse(GLint button, GLint action, GLint xMouse, GLint yMouse){
	GLint i;
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
		if (irany.pointDis2(xMouse, winH - yMouse))
		{
			dragged = 10;
		}

		if ((i = getActivePoint(points, size, 8, xMouse, winH - yMouse)) != -1)
			dragged = i;


	}

	if (button == GLUT_LEFT_BUTTON && action == GLUT_UP){
		dragged = -1;
	}
}

void processMouseMotion(GLint xMouse, GLint yMouse){
	if (dragged != 10)
	{
		points[dragged].setX(static_cast<GLdouble>(xMouse));
		points[dragged].setY(static_cast<GLdouble>(winH - yMouse));

		if (dragged == 0)
		{
			irany.setX(points[0].getX() + draggedX);
			irany.setY(points[0].getY() + draggedY);
		}
	}
	else
	{
		irany.setX(static_cast<GLdouble>(xMouse));
		irany.setY(static_cast<GLdouble>(winH - yMouse));
	}

	glutPostRedisplay();
}

int main(int argc, char ** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(winW, winH);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Hermite");

	init();

	glutDisplayFunc(display);
	glutMouseFunc(processMouse);
	glutMotionFunc(processMouseMotion);
	
	glutMainLoop();



	return 0;
}
