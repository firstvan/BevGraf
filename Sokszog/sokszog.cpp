#include <GL/glut.h>
#include "point.hpp"
#include <math.h>
#include <vector>

#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406

GLdouble winW = 800.0, winH = 800.0;

GLint keyStates[256];

myPoint center(winW/2, winH/2);
GLfloat delta = 0.01;
GLdouble r = 100;
GLint sokszam = 4;
std::vector<myPoint> nPont;

GLdouble degToRad(GLint deg){	//fok átváltása radiánba
	return deg * (PI / 180);
}


void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_POINT_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winW, 0.0, winH);

}

void keyPressed(unsigned char key, int x, int y) {
	keyStates[key] = 1;
}

void keyUp(unsigned char key, int x, int y) {
	keyStates[key] = 0;
}

	
void keyOperations(){ 
	if (keyStates['a'])
	{
		sokszam++;
	}


	glutPostRedisplay();
}

void kor(){
	
	GLdouble lepeskoz = degToRad(1);
	glColor3f(0.0, 0.0, 1.0);
	glLineWidth(1);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++){
		GLdouble x = center.getX() + r * cos(i * lepeskoz);
		GLdouble y = center.getY() + r * sin(i * lepeskoz);
		glVertex2d(x, y);
	}

	glEnd();

}

void sokSzog(){
	
}

void display(void)
{

	keyOperations();
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0, 0.4, 0.2);
	glBegin(GL_POINTS);
	glVertex2f(center.getX(), center.getY());
	glEnd();

	kor();
	sokSzog();

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowPosition(50, 100);

	glutInitWindowSize(winW, winH);

	glutCreateWindow("multiple key press");

	init();

	glutDisplayFunc(display);

	glutKeyboardFunc(keyPressed);

	glutKeyboardUpFunc(keyUp);

	glutMainLoop();

	return 0;
}


