#include <GL/glut.h>
#include "point.hpp"
#include <math.h>
#include <vector>
#include <iostream>

#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406

GLint winW = 1200, winH = 800;

GLint keyStates[256];

myPoint<GLdouble> p1Center(winW/4 , winH/2);
myPoint<GLdouble> p2Center(3 * winW/4 , winH/2);
GLdouble delta = 0.01;
GLdouble r = 50;
GLint p1h = 4;							//p1 Health
GLint p2h = 4;							//p2 Health
std::vector<myPoint<GLdouble>> p1a;		//player one angle
std::vector<myPoint<GLdouble>> p2a;		//player two angle
myPoint<GLdouble> player1(winW / 2, winH);
myPoint<GLdouble> player2(winW / 2, 0);


GLdouble degToRad(GLdouble deg){	//fok átváltása radiánba
	return deg * (PI / 180);
}


void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_POINT_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winW, 0.0, winH);

	for (int i = 0; i < p1h; i++)
	{
		GLdouble pointDist = degToRad(360 / (double) p1h);
		GLdouble tempx = p1Center.getX() + r * cos(i * pointDist);
		GLdouble tempy = p1Center.getY() + r * sin(i * pointDist);

		p1a.push_back(myPoint<GLdouble>(tempx, tempy));
	}

	for (int i = 0; i < p2h; i++)
	{
		GLdouble pointDist = degToRad(360 / (double) p2h);
		GLdouble tempx = p2Center.getX() + r * cos(i * pointDist);
		GLdouble tempy = p2Center.getY() + r * sin(i * pointDist);

		p2a.push_back(myPoint<GLdouble>(tempx, tempy));
	}
}

void keyPressed(unsigned char key, int x, int y) {
	keyStates[key] = 1;
}

void keyUp(unsigned char key, int x, int y) {
	keyStates[key] = 0;
}

	
void keyOperations(){ 
	//player one control
	if (keyStates['w'])
	{
		if (player1.getY() != winH && (player1.getX() == 0 || player1.getX() == winW))
			player1.incY();
	}

	if (keyStates['a'])
	{
		if (player1.getX() != 0 && (player1.getY() == 0 || player1.getY() == winH))
			player1.decX();
	}

	if (keyStates['s'])
	{
		if (player1.getY() != 0 && (player1.getX() == 0 || player1.getX() == winW))
			player1.decY();
	}

	if (keyStates['d'])
	{
		if (player1.getX() != winW && (player1.getY() == 0 || player1.getY() == winH))
			player1.incX();
	}
	//end player one control

	//player two control
	if (keyStates['i'])
	{
		if (player2.getY() != winH && (player2.getX() == 0 || player2.getX() == winW))
			player2.incY();
	}

	if (keyStates['j'])
	{
		if (player2.getX() != 0 && (player2.getY() == 0 || player2.getY() == winH))
			player2.decX();
	}

	if (keyStates['k'])
	{
		if (player2.getY() != 0 && (player2.getX() == 0 || player2.getX() == winW))
			player2.decY();
	}

	if (keyStates['l'])
	{
		if (player2.getX() != winW && (player2.getY() == 0 || player2.getY() == winH))
			player2.incX();
	}
	//end player two control


	glutPostRedisplay();
}


//elsõ játékos körének létrehozása
void circleForPlayers(){
	
	GLdouble lepeskoz = degToRad(1);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++){
		GLdouble x = p1Center.getX() + r * cos(i * lepeskoz);
		GLdouble y = p1Center.getY() + r * sin(i * lepeskoz);
		glVertex2d(x, y);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++){
		GLdouble x = p2Center.getX() + r * cos(i * lepeskoz);
		GLdouble y = p2Center.getY() + r * sin(i * lepeskoz);
		glVertex2d(x, y);
	}

	glEnd();

}

//draw polygon
void playersDiagonal(){
	
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	for (int i = 0; i < p1h; i++)
		for (int j = i + 1; j < p1h; j++){
		glVertex2d(p1a.at(i).getX(), p1a.at(i).getY());
		glVertex2d(p1a.at(j).getX(), p1a.at(j).getY());
		}
	glEnd();
	
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	for (int i = 0; i < p2h; i++)
		for (int j = i + 1; j < p2h; j++){
		glVertex2d(p2a.at(i).getX(), p2a.at(i).getY());
		glVertex2d(p2a.at(j).getX(), p2a.at(j).getY());
		}
	glEnd();


}

void playersLine(){
	glPointSize(10);

	//display player one point
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POINTS);
		glVertex2d(player1.getX(), player1.getY());
	glEnd();

	//display player two point
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
		glVertex2d(player2.getX(), player2.getY());
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex2d(player1.getX(), player1.getY());
		glVertex2d(player2.getX(), player2.getY());
	glEnd();
}

void display(void)
{

	keyOperations();
	glClear(GL_COLOR_BUFFER_BIT);

	circleForPlayers();
	playersDiagonal();

	playersLine();

	glutSwapBuffers();
}

/*játékból majd kivenni
void keyboard(unsigned char key, int x, int y) {
	p1a.clear();
	p2a.clear();
	switch (key) {
	case 'p':
		p1h++;
		break;
	case 'o':
		p2h++;
		break;
	};

	for (int i = 0; i < p1h; i++)
	{
		GLdouble pointDist = degToRad(360 / (double)p1h);
		GLdouble tempx = p1Center.getX() + r * cos(i * pointDist);
		GLdouble tempy = p1Center.getY() + r * sin(i * pointDist);

		p1a.push_back(myPoint<GLdouble>(tempx, tempy));
	}

	for (int i = 0; i < p2h; i++)
	{
		GLdouble pointDist = degToRad(360 / (double)p2h);
		GLdouble tempx = p2Center.getX() + r * cos(i * pointDist);
		GLdouble tempy = p2Center.getY() + r * sin(i * pointDist);

		p2a.push_back(myPoint<GLdouble>(tempx, tempy));
	}
}
*/


int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowPosition(25, 25);
	
	glutInitWindowSize(winW, winH);

	glutCreateWindow("multiple key press");

	init();

	glutDisplayFunc(display);

	glutKeyboardFunc(keyPressed);

	glutKeyboardUpFunc(keyUp);
	
	glutMainLoop();

	return 0;
}


