#include <GL/glut.h>
#include <iostream>
#include "point.hpp"
#include "Slider.hpp"
#include "myCircle.hpp"
#include "matrix.hpp"

typedef myPoint<GLdouble> MYPOINT;

GLint winW = 800, winH = 800;	//ablakméret
GLint dragged = -1;				//egérkezelés
GLdouble draggedX = 0, draggedY = 0;	//erintő vektor mozgatása a p0 pont mozgatására
GLint size = 5;					//pontok mérete
MYPOINT irany(200, 200);		//érintő végső pontja
MYPOINT points[] = {			//pontok
	MYPOINT(100, 100),
	MYPOINT(200, 250),
	MYPOINT(300, 200),
	MYPOINT(600, 300),
	MYPOINT(700, 600) };
MYPOINT r1(irany.getX() - points[0].getX(), irany.getY() - points[0].getY());		//érintő vektora
Matrix<4, 3, GLdouble> G;		//első 3 geometriai pontot tartalmazó mátrix, amely 90 fokos elforgatással van, elsődleges cél a könnyebb feltölthetőség	
Matrix<4, 3, GLdouble> G1;		//második 3 g.pont...
GLdouble tParams[3] = { -1.0, 0.0, 1.0 };	//paraméterek
Matrix<4, 4, GLdouble> N;		//segédmátrix
Matrix<4, 4, GLdouble> M;		
Matrix<1, 4, GLdouble> T;		//t-k vektora csak itt is leforgatás
Matrix<1, 3, GLdouble> Q;
MYPOINT sp1(50, 50);		//slider kezdőpontja
MYPOINT sp2(700, 50);		//slider végpontja
mySlider<GLdouble> sl1(sp1, sp2, (-2.0), 2.0, 4 );		//slider

//M mátrix újraszámolása megváltozott paraméterekhez
void gUjraszamol()
{
	N.setElement(0, 0, tParams[0] * tParams[0] * tParams[0]);
	N.setElement(1, 0, tParams[0] * tParams[0]);
	N.setElement(2, 0, tParams[0]);
	N.setElement(3, 0, 1.0);

	N.setElement(0, 1, tParams[1] * tParams[1] * tParams[1]);
	N.setElement(1, 1, tParams[1] * tParams[1]);
	N.setElement(2, 1, tParams[1]);
	N.setElement(3, 1, 1.0);

	N.setElement(0, 2, tParams[2] * tParams[2] * tParams[2]);
	N.setElement(1, 2, tParams[2] * tParams[2]);
	N.setElement(2, 2, tParams[2]);
	N.setElement(3, 2, 1.0);

	N.setElement(0, 3, 3.0 * tParams[0] * tParams[0]);
	N.setElement(1, 3, 2.0 * tParams[0]);
	N.setElement(2, 3, 1.0);
	N.setElement(3, 3, 0.0);


	M = N.inverse();
}


//a második 3 pont érintőjének újraszámolásához
void erinto()
{
	T.setElement(0, 0, 3.0 * tParams[2] * tParams[2]);
	T.setElement(1, 0, 2.0 * tParams[2]);
	T.setElement(2, 0, 1.0);
	T.setElement(3, 0, 0.0);

	Q = G * M * T;
	G1.setElement(0, 3, Q.getElement(0, 0));
	G1.setElement(1, 3, Q.getElement(1, 0));

}


void init(){
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winW, 0.0, winH);
	glShadeModel(GL_FLAT);
	glPointSize(5);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//init g és g1 mátrix	
	gUjraszamol();

	G.setElement(2, 0, 1.0);
	G.setElement(2, 1, 1.0);
	G.setElement(2, 2, 1.0);
	G.setElement(2, 3, 1.0);
	G1.setElement(2, 0, 1.0);
	G1.setElement(2, 1, 1.0);
	G1.setElement(2, 2, 1.0);
	G1.setElement(2, 3, 1.0);


	G.setElement(0, 0, points[0].getX());
	G.setElement(1, 0, points[0].getY());
	G.setElement(0, 1, points[1].getX());
	G.setElement(1, 1, points[1].getY());
	G.setElement(0, 2, points[2].getX());
	G.setElement(1, 2, points[2].getY());
	G.setElement(0, 3, r1.getX());
	G.setElement(1, 3, r1.getY());

	G1.setElement(0, 0, points[2].getX());
	G1.setElement(1, 0, points[2].getY());
	G1.setElement(0, 1, points[3].getX());
	G1.setElement(1, 1, points[3].getY());
	G1.setElement(0, 2, points[4].getX());
	G1.setElement(1, 2, points[4].getY());
	erinto();

}



void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	
	
	glBegin(GL_LINE_STRIP);

	// görbe kirajzoltatása
	Matrix<4, 3, GLdouble > C = G * M;
	for (GLdouble t = tParams[0]; t <= tParams[2]; t += 0.01)
	{
		T.setElement(0, 0, (t * t * t));
		T.setElement(1, 0, (t * t));
		T.setElement(2, 0, (t));
		T.setElement(3, 0, 1.0);

		Q = C * T;

		glVertex2d(Q.getElement(0, 0), Q.getElement(1, 0));
	}

	C = G1 * M;
	for (GLdouble t = tParams[0]; t <= tParams[2]; t += 0.01)
	{
		T.setElement(0, 0, (t * t * t));
		T.setElement(1, 0, (t * t));
		T.setElement(2, 0, (t));
		T.setElement(3, 0, 1.0);

		Q = C * T;

		glVertex2d(Q.getElement(0, 0), Q.getElement(1, 0));
	}


	glVertex2d(points[4].getX(), points[4].getY());
	glEnd();


	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2d(points[0].getX(), points[0].getY());
	glVertex2d(irany.getX(), irany.getY());
	glEnd();

	glColor3d(0.0, 0.0, 1.0);
	irany.display();


	glColor3d(0.0, 0.0, 0.0);
	for (int i = 0; i < size; i++)
	{
		points[i].display();
	}

	sl1.draw();
	
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
		if (irany.pointDis2(xMouse, winH - yMouse) < 8*8)
		{
			dragged = 10;
		}
		
		if (sl1.dis2Click(xMouse, winH - yMouse, 0) < 8*8)
		{
			dragged = 11;
		}

		if (sl1.dis2Click(xMouse, winH - yMouse, 1) < 8*8)
		{
			dragged = 12;
		}

		if (sl1.dis2Click(xMouse, winH - yMouse, 2) < 8*8)
		{
			dragged = 13;
		}

		if ((i = getActivePoint(points, size, 8, xMouse, winH - yMouse)) != -1)
			dragged = i;


	}

	if (button == GLUT_LEFT_BUTTON && action == GLUT_UP){
		dragged = -1;
	}
}

void processMouseMotion(GLint xMouse, GLint yMouse){
		switch (dragged){
		case 0:
			points[dragged].setX(static_cast<GLdouble>(xMouse));
			points[dragged].setY(static_cast<GLdouble>(winH - yMouse));
			G.setElement(0, dragged, points[dragged].getX());
			G.setElement(1, dragged, points[dragged].getY());
			irany.setX(points[0].getX() + draggedX);
			irany.setY(points[0].getY() + draggedY);
			erinto();
			break;
		case 1:
			points[dragged].setX(static_cast<GLdouble>(xMouse));
			points[dragged].setY(static_cast<GLdouble>(winH - yMouse));
			G.setElement(0, dragged, points[dragged].getX());
			G.setElement(1, dragged, points[dragged].getY());
			erinto();
			break;
		case 2:
			points[dragged].setX(static_cast<GLdouble>(xMouse));
			points[dragged].setY(static_cast<GLdouble>(winH - yMouse));
			G.setElement(0, dragged, points[dragged].getX());
			G.setElement(1, dragged, points[dragged].getY());
			G1.setElement(0, 0, points[dragged].getX());
			G1.setElement(1, 0, points[dragged].getY());
			erinto();
			break;
		case 3:
		case 4:
			points[dragged].setX(static_cast<GLdouble>(xMouse));
			points[dragged].setY(static_cast<GLdouble>(winH - yMouse));
			G1.setElement(0, dragged - 2, points[dragged].getX());
			G1.setElement(1, dragged - 2, points[dragged].getY());
			erinto();
			break;
		case 10:
			irany.setX(static_cast<GLdouble>(xMouse));
			irany.setY(static_cast<GLdouble>(winH - yMouse));

			G.setElement(0, 3, irany.getX() - points[0].getX());
			G.setElement(1, 3, irany.getY() - points[0].getY());
			erinto();

			break;
		case 11:
			sl1.setClickX(0, xMouse);
			tParams[0] = sl1.getValue(0);
			gUjraszamol();
			erinto();
			break;
		case 12:
			sl1.setClickX(1, xMouse);
			tParams[1] = sl1.getValue(1);
			gUjraszamol();
			erinto();
			break;
		case 13:
			sl1.setClickX(2, xMouse);
			tParams[2] = sl1.getValue(2);
			gUjraszamol();
			erinto();
			break;

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
