#include <GL/glut.h>
#include <math.h>
#include <iostream>

#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406


typedef struct POINT2D{
	GLdouble x;
	GLdouble y;
} Point2D;

GLdouble winW = 800.0, winH = 800.0;

Point2D center;
Point2D bigPointer;
Point2D smallPointer;
GLdouble smallPointLen = 3 / (double)4;
GLint hour = 0;
GLdouble rotSmall, rotBig;
GLdouble r = 300.0;
Point2D points[12];
Point2D smallPoints[12];
GLint resz = 10;

void pointInit(Point2D& a, GLdouble a1, GLdouble a2){
	a.x = a1;
	a.y = a2;
}

GLdouble degToRad(GLint deg){
	return deg * (PI / 180);
}

void init(){
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winW, 0.0, winH);
	glShadeModel(GL_FLAT);
	glPointSize(5.0);
	glEnable(GL_POINT_SMOOTH);
	rotBig = degToRad(90.0);
	rotSmall = degToRad(0.0);

	GLdouble temp = r * cos(rotBig);
	GLdouble temp1 = r * sin(rotSmall);


	pointInit(center, winW / 2, winH / 2);
	pointInit(bigPointer, center.x+ temp, center.y + temp1);

	temp = smallPointLen * cos(degToRad(0));
	temp1 = smallPointLen * r * sin(degToRad(0));
	pointInit(smallPointer, center.x + temp, center.y + temp1);
	
	GLdouble pontKoz = degToRad(360 / (double)12);
	for (int i = 0; i < 12; i++){
		smallPoints[i].x = center.x + smallPointLen * r * cos(i * pontKoz);
		smallPoints[i].y = center.y + smallPointLen * r * sin(i * pontKoz);
	}
}



void kor(){

	GLdouble lepeskoz = degToRad(1);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++){
		GLdouble x = center.x + r * cos(i * lepeskoz);
		GLdouble y = center.y + r * sin(i * lepeskoz);
		glVertex2d(x, y);
	}

	glEnd();
}

void pointsDraw(){
	GLdouble pontKoz = degToRad(360 / (double)12);

	glColor3f(1.0, 0.0, 0.0);
		
	glBegin(GL_POINTS);
	glVertex2d(center.x, center.y);
	
	for (int i = 0; i < 12; i++){
		points[i].x = center.x + r * cos(i * pontKoz + degToRad(90));
		points[i].y = center.y + r * sin(i * pontKoz + degToRad(90));
		glVertex2d(points[i].x, points[i].y);
	}
	glEnd();
}

void mutatok(){

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
		glVertex2d(center.x, center.y);
		glVertex2d(bigPointer.x, bigPointer.y);
		glVertex2d(center.x, center.y);
		glVertex2d(smallPointer.x, smallPointer.y);
	glEnd();
}

void mutatoKoz(){
	
	glColor3f(0.0, 1.0, 1.0);
	glLineWidth(1);
	glBegin(GL_LINES);
	for (int i = 1; i <= resz; i++){
		GLdouble tempX = smallPointer.x + i * ((3 / (double)4) * r / (double)resz) * cos(rotSmall);
		GLdouble tempY = smallPointer.y + i * ((3 / (double)4) * r / (double)resz) * sin(rotSmall);
		glVertex2d(tempX, tempY);

		GLdouble temp1X = bigPointer.x - i * (r / (double)resz) * cos(rotBig);
		GLdouble temp1Y = bigPointer.y - i * (r / (double)resz) * sin(rotBig);
		glVertex2d(temp1X, temp1Y);
	}
	glEnd();
}

void display(){

	glClear(GL_COLOR_BUFFER_BIT);

	kor();

	pointsDraw();

	mutatok();

	mutatoKoz();

	glutSwapBuffers();
}

void update(int n){
	
	rotBig -= degToRad(1);
	rotSmall -= degToRad(1) / 12;

	if (rotBig < degToRad(-270.0))
	{
		rotBig = degToRad(90);
		std::cout << "meghívja" << std::endl;
		hour--;
		if (hour < 0)
			hour = 11;

		smallPointer.x = smallPoints[hour].x;
		smallPointer.y = smallPoints[hour].y;
		
	}else{
		smallPointer.x = center.x + smallPointLen * r * cos(rotSmall);
		smallPointer.y = center.y + smallPointLen * r * sin(rotSmall);
	}


	bigPointer.x = center.x + r * cos(rotBig);
	bigPointer.y = center.y + r * sin(rotBig);
	
	

	glutPostRedisplay();
	glutTimerFunc(1, update, 0);
}



int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(winW, winH);
	glutInitWindowPosition(50, 10);
	glutCreateWindow("Óra");

	init();
	glutDisplayFunc(display);
	glutTimerFunc(1, update, 0);
	glutMainLoop();
	return 0;
}