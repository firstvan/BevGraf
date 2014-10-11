#include <GL/glut.h>
#include "point.hpp"
#include "vector.hpp"
#include <math.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406

GLint winW = 700.0, winH = 500.0;
GLint keyStates[256];
myVector<GLdouble> p1Next(1, 1);
myVector<GLdouble> p2Next(-1, 1);
myPoint<GLdouble> p1Center(winW/4 , winH/2); // elsõ játékos körének középpontja
myPoint<GLdouble> p2Center(3 * winW/4 , winH/2);
GLdouble delta = 0.01;
GLdouble r = 50;
GLint p1h = 7;							//p1 Health
GLint p2h = 7;							//p2 Health
std::vector<myPoint<GLdouble>> p1a;		//player one angle
std::vector<myPoint<GLdouble>> p2a;		//player two angle
myPoint<GLdouble> player1(winW / 2, winH);
myPoint<GLdouble> player2(winW / 2, 0);
myVector<GLdouble> playerWall(player1.getX() - player2.getX(), player1.getY() - player2.getY());
myPoint<GLdouble> LD(0.0, 0.0);
myPoint<GLdouble> LU(0.0, static_cast<GLdouble>(winH));
myPoint<GLdouble> RD(static_cast<GLdouble>(winW), 0.0);
myPoint<GLdouble> RU(static_cast<GLdouble>(winW), static_cast<GLdouble>(winH));
myVector<GLdouble> left(LU.getX() - LD.getX(), LU.getY() - LD.getY());
myVector<GLdouble> right(RU.getX() - RD.getX(), RU.getY() - RD.getY());
myVector<GLdouble> top(RU.getX() - LU.getX(), RU.getY() - LU.getY());
myVector<GLdouble> bottom(RD.getX() - LD.getX(), RD.getY() - LD.getY());
myPoint<GLdouble> food1((winW / 2) + 50, 50);
myPoint<GLdouble> food2((winW / 2) - 50, winH - 50);

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

	//first player control
	if (keyStates['w']){
		if (player1.getY() < winH && (player1.getX() <= 0 || player1.getX() >= winW))
			player1.add(0, delta);
	}

	if (keyStates['a']){
		if (player1.getX() > 0 && (player1.getY() <= 0 || player1.getY() >= winH))
			player1.sub(delta, 0);
	}

	if (keyStates['s']){
		if (player1.getY() > 0 && (player1.getX() <= 0 || player1.getX() >= winW))
			player1.sub(0, delta);
	}

	if (keyStates['d']){
		if (player1.getX() < winW && (player1.getY() <= 0|| player1.getY() >= winH))
			player1.add(delta, 0);
	}

	//second player control
	if (keyStates['i']){
		if (player2.getY() < winH && (player2.getX() <= 0 || player2.getX() >= winW))
			player2.add(0, delta);
	}

	if (keyStates['j']){
		if (player2.getX() > 0 && (player2.getY() <= 0 || player2.getY() >= winH))
			player2.sub(delta, 0);
	}

	if (keyStates['k']){
		if (player2.getY() > 0 && (player2.getX() <= 0 || player2.getX() >= winW))
			player2.sub(0, delta);
	}

	if (keyStates['l']){
		if (player2.getX() < winW && (player2.getY() <= 0 || player2.getY() >= winH))
			player2.add(delta, 0);
	}

	playerWall.setX(player1.getX() - player2.getX());
	playerWall.setY(player1.getY() - player2.getY());
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
	p1a.clear();
	for (int i = 0; i < p1h; i++)
	{
		GLdouble pointDist = degToRad(360 / (double)p1h);
		GLdouble tempx = p1Center.getX() + r * cos(i * pointDist);
		GLdouble tempy = p1Center.getY() + r * sin(i * pointDist);

		p1a.push_back(myPoint<GLdouble>(tempx, tempy));
	}

	p2a.clear();
	for (int i = 0; i < p2h; i++)
	{
		GLdouble pointDist = degToRad(360 / (double)p2h);
		GLdouble tempx = p2Center.getX() + r * cos(i * pointDist);
		GLdouble tempy = p2Center.getY() + r * sin(i * pointDist);

		p2a.push_back(myPoint<GLdouble>(tempx, tempy));
	}

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

void foods(){
	glPointSize(5);

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POINTS);
		glVertex2d(food1.getX(), food1.getY());
	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
		glVertex2d(food2.getX(), food2.getY());
	glEnd();
}

void display(void)
{

	keyOperations();
	glClear(GL_COLOR_BUFFER_BIT);

	circleForPlayers();
	playersDiagonal();
	playersLine();
	foods();

	glutSwapBuffers();
}


void update(int n){
	p1Center.addX(p1Next.getX());
	p1Center.addY(p1Next.getY());
	

	if (p1Center.lineDistance2(player1, player2) < r * r)
	{
		p1Next.snap(playerWall);
	}

	if (p1Center.lineDistance2(LU, RU) < r * r)
	{
		p1Next.snap(top);
	}
	
	if (p1Center.lineDistance2(LD, RD) < r * r)
	{
		p1Next.snap(bottom);
	}

	if (p1Center.lineDistance2(RU, RD) < r * r)
	{
		p1Next.snap(right);
	}

	if (p1Center.lineDistance2(LU, LD) < r * r)
	{
		p1Next.snap(left);
	}

	p2Center.addX(p2Next.getX());
	p2Center.addY(p2Next.getY());
	

	if (p2Center.lineDistance2(player1, player2) < r * r)
	{
		p2Next.snap(playerWall);
	}

	if (p2Center.lineDistance2(LU, RU) < r * r)
	{
		p2Next.snap(top);
	}
	
	if (p2Center.lineDistance2(LD, RD) < r * r)
	{
		p2Next.snap(bottom);
	}

	if (p2Center.lineDistance2(RU, RD) < r * r)
	{
		p2Next.snap(right);
	}

	if (p2Center.lineDistance2(LU, LD) < r * r)
	{
		p2Next.snap(left);
	}


	//foods
	if (p1Center.pointDis2(food1) < r * r){
		p1h++;
		
		GLdouble tempx = rand() % winW - 50 + r;
		food1.setX(tempx);
		
		GLdouble tempy = rand() % winH - 50 + r;
		food1.setY(tempy);
	}

	if (p1Center.pointDis2(food2) < r * r){
		p1h--;

		GLdouble tempx = rand() % winW - 50 + r;
		food2.setY(tempx);

		GLdouble tempy = rand() % winH - 50 + r;
		food2.setY(tempy);
	}

	if (p2Center.pointDis2(food2) < r * r){
		p2h++;

		GLdouble tempx = rand() % winW - 50 + r;
		food2.setX(tempx);

		GLdouble tempy = rand() % winH - 50 + r;
		food2.setY(tempy);
	}

	if (p2Center.pointDis2(food1) < r * r){
		p2h--;

		GLdouble tempx = rand() % winW - 50 + r;
		food1.setX(tempx);

		GLdouble tempy = rand() % winH - 50 + r;
		food1.setY(tempy);


	}


	glutPostRedisplay();

	glutTimerFunc(10, update, 0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(25, 25);
	glutInitWindowSize(winW, winH);
	glutCreateWindow("multiple key press");

	init();

	srand(time(NULL));

	glutDisplayFunc(display);

	glutKeyboardFunc(keyPressed);

	glutKeyboardUpFunc(keyUp);
	
	glutTimerFunc(10, update, 0);

	glutMainLoop();

	return 0;
}


