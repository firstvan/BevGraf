#include <GL/glut.h>
#include <GL/freeglut_ext.h>	//glutLeaveMainLoop() miatt kell!
#include "point.hpp"
#include "vector.hpp"
#include <math.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406
//Ablak m�rete
GLint winW = 700.0, winH = 500.0;
//t�bb billenty� haszn�lat�hoz
GLint keyStates[256];
GLdouble delta = 0.01;
//Labd�k mozgat� vectora
myVector<GLdouble> p1Next(1, 1);
myVector<GLdouble> p2Next(-1, -1);
//labd�k k�z�ppontjai
myPoint<GLdouble> p1Center(winW/4 , winH/2);
myPoint<GLdouble> p2Center(3 * winW/4 , winH/2);
GLdouble r = 50;
//Soksz�gek sz�ma
GLint p1h = 7;							//p1 Health
GLint p2h = 7;							//p2 Health
std::vector<myPoint<GLdouble>> p1a;		//player one angle
std::vector<myPoint<GLdouble>> p2a;		//player two angle
//J�t�kosok pontjai
myPoint<GLdouble> player1(winW / 2, winH - 1);
myPoint<GLdouble> player2(winW / 2, 0);
//J�t�kosok �ltal meghat�rozott vektor
myVector<GLdouble> playerWall(player1.getX() - player2.getX(), player1.getY() - player2.getY());
//keret 4 pontja
myPoint<GLdouble> LD(1.0, 0.0);
myPoint<GLdouble> LU(1.0, static_cast<GLdouble>(winH - 1));
myPoint<GLdouble> RD(static_cast<GLdouble>(winW), 1.0);
myPoint<GLdouble> RU(static_cast<GLdouble>(winW), static_cast<GLdouble>(winH - 1));
//keret oldalai
myVector<GLdouble> left(LU.getX() - LD.getX(), LU.getY() - LD.getY());
myVector<GLdouble> right(RU.getX() - RD.getX(), RU.getY() - RD.getY());
myVector<GLdouble> top(RU.getX() - LU.getX(), RU.getY() - LU.getY());
myVector<GLdouble> bottom(RD.getX() - LD.getX(), RD.getY() - LD.getY());
//Soksz�geket n�vel� pontok
myPoint<GLdouble> food1((winW / 2) + 50, 50);
myPoint<GLdouble> food2((winW / 2) - 50, winH - 50);

//fok �tv�lt�sa radi�nn�
GLdouble degToRad(GLdouble deg)
{
    return deg * (PI / 180);
}


void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_POINT_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, winW, 0.0, winH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


}

void keyPressed(unsigned char key, int x, int y)
{
    keyStates[key] = 1;
}

void keyUp(unsigned char key, int x, int y)
{
    keyStates[key] = 0;
}


void keyOperations()
{
    //Els� j�t�kos ir�nyit�sa: w, a, s, d
    if (keyStates['w'])
    {
        if (player1.getY() < winH - 1 && (player1.getX() <= 1 || player1.getX() >= winW - 1))
            player1.add(0, delta);
    }

    if (keyStates['a'])
    {
        if (player1.getX() > 1 && (player1.getY() <= 1 || player1.getY() >= winH - 1))
            player1.sub(delta, 0);
    }

    if (keyStates['s'])
    {
        if (player1.getY() > 1 && (player1.getX() <= 1 || player1.getX() >= winW - 1))
            player1.sub(0, delta);
    }

    if (keyStates['d'])
    {
        if (player1.getX() < winW - 1 && (player1.getY() <= 1|| player1.getY() >= winH - 1))
            player1.add(delta, 0);
    }

    //M�sodik j�t�kos ir�ny�t�sa: i, j, k, l
    if (keyStates['i'])
    {
        if (player2.getY() < winH - 1&& (player2.getX() <= 1 || player2.getX() >= winW - 1))
            player2.add(0, delta);
    }

    if (keyStates['j'])
    {
        if (player2.getX() > 1 && (player2.getY() <= 1 || player2.getY() >= winH - 1))
            player2.sub(delta, 0);
    }

    if (keyStates['k'])
    {
        if (player2.getY() > 1 && (player2.getX() <= 1 || player2.getX() >= winW - 1))
            player2.sub(0, delta);
    }

    if (keyStates['l'])
    {
        if (player2.getX() < winW-1 && (player2.getY() <= 1 || player2.getY() >= winH - 1))
            player2.add(delta, 0);
    }

    //Pontok mozgat�sa ut�ni �ltaluk meghat�rozott ir�nyvektorok �jrasz�mol�sa
    playerWall.setX(player1.getX() - player2.getX());
    playerWall.setY(player1.getY() - player2.getY());

    glutPostRedisplay();
}


//J�t�kosok k�reinek kirajzoltat�sa
void circleForPlayers()
{

    GLdouble lepeskoz = degToRad(1);
    glColor3f(0.0, 0.0, 0.0);

    //Player green
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++)
    {
        GLdouble x = p1Center.getX() + r * cos(i * lepeskoz);
        GLdouble y = p1Center.getY() + r * sin(i * lepeskoz);
        glVertex2d(x, y);
    }
    glEnd();

    //Player blue
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++)
    {
        GLdouble x = p2Center.getX() + r * cos(i * lepeskoz);
        GLdouble y = p2Center.getY() + r * sin(i * lepeskoz);
        glVertex2d(x, y);
    }

    glEnd();

}

//soksz�gek kirajzoltat�sa
void playersDiagonal()
{

    //Els� j�t�kos soksz�geit meghat�roz� vektor ki�rit�se majd felt�lteni a megfelel� pontokkal (mozg�s miatt kell mindig kirajzoltatni)
    p1a.clear();
    for (int i = 0; i < p1h; i++)
    {
        GLdouble pointDist = degToRad(360) / (double)p1h;
        GLdouble tempx = p1Center.getX() + r * cos(i * pointDist);
        GLdouble tempy = p1Center.getY() + r * sin(i * pointDist);

        p1a.push_back(myPoint<GLdouble>(tempx, tempy));
    }

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    for (int i = 0; i < p1h; i++)
        for (int j = i + 1; j < p1h; j++)
        {
            glVertex2d(p1a.at(i).getX(), p1a.at(i).getY());
            glVertex2d(p1a.at(j).getX(), p1a.at(j).getY());
        }
    glEnd();


    //M�sodik j�t�kos soksz�geit meghat�roz� vektor ki�rit�se majd felt�lteni a megfelel� pontokkal (mozg�s miatt kell mindig kirajzoltatni)
    p2a.clear();
    for (int i = 0; i < p2h; i++)
    {
        GLdouble pointDist = degToRad(360 / (double)p2h);
        GLdouble tempx = p2Center.getX() + r * cos(i * pointDist);
        GLdouble tempy = p2Center.getY() + r * sin(i * pointDist);

        p2a.push_back(myPoint<GLdouble>(tempx, tempy));
    }

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    for (int i = 0; i < p2h; i++)
        for (int j = i + 1; j < p2h; j++)
        {
            glVertex2d(p2a.at(i).getX(), p2a.at(i).getY());
            glVertex2d(p2a.at(j).getX(), p2a.at(j).getY());
        }
    glEnd();
}

void playersLine()
{
    glPointSize(10);

    //Els� j�t�kos ponj�nak megjelen�t�se
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2d(player1.getX(), player1.getY());
    glEnd();

    //M�sodik j�t�kos pontjainak kirajzoltat�sa
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    glVertex2d(player2.getX(), player2.getY());
    glEnd();

    //K�t j�t�kos �ltal meghat�rozott fal kirajzoltat�sa
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2d(player1.getX(), player1.getY());
    glVertex2d(player2.getX(), player2.getY());
    glEnd();
}

void foods()
{
    glPointSize(5);

    //Kaj�k kirajzoltat�sa
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2d(food1.getX(), food1.getY());
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    glVertex2d(food2.getX(), food2.getY());
    glEnd();
}

//keret megrajzol�sa
void frame()
{
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2d(LD.getX(), LD.getY());
    glVertex2d(LU.getX(), LU.getY());
    glVertex2d(RU.getX(), RU.getY());
    glVertex2d(RD.getX(), RD.getY());
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
    frame();

    glutSwapBuffers();
}


void update(int n)
{
    //Els� j�t�kos k�r�nek pattan�sai:
    p1Center.addX(p1Next.getX());
    p1Center.addY(p1Next.getY());

    //J�t�kosfalr�l
    if (p1Center.lineDistance2(player1, player2) < r * r)
    {
        p1Next.snap(playerWall);
    }

    //Fels�falr�l
    if (p1Center.lineDistance2(LU, RU) < r * r)
    {
        p1Next.snap(top);
    }

    //Talajr�l
    if (p1Center.lineDistance2(LD, RD) < r * r)
    {
        p1Next.snap(bottom);
    }

    //Jobb falr�l
    if (p1Center.lineDistance2(RU, RD) < r * r)
    {
        p1Next.snap(right);
    }

    //Bal falr�l
    if (p1Center.lineDistance2(LU, LD) < r * r)
    {
        p1Next.snap(left);
    }

    //M�sodik j�t�kos k�r�nek pattan�sai az el�bbiek szerint
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


    //Kaj�k pontjainak meghat�roz�sa tov�bb� a kaj�k megev�s�nek felt�telei
    GLint tempW = winW - r;
    GLint tempH = winH - r;
    if (p1Center.pointDis2(food1) < r * r)
    {
        p1h++;
        GLdouble tempx = rand() % tempW + r;
        food1.setX(tempx);
        GLdouble tempy = rand() % tempH + r;
        food1.setY(tempy);
    }

    if (p1Center.pointDis2(food2) < r * r)
    {
        p1h--;
        GLdouble tempx = rand() % tempW + r;
        food2.setY(tempx);
        GLdouble tempy = rand() % tempH + r;
        food2.setY(tempy);
    }

    if (p2Center.pointDis2(food2) < r * r)
    {
        p2h++;
        GLdouble tempx = rand() % tempW + r;
        food2.setX(tempx);
        GLdouble tempy = rand() % tempH + r;
        food2.setY(tempy);
    }

    if (p2Center.pointDis2(food1) < r * r)
    {
        p2h--;
        GLdouble tempx = rand() % tempW + r;
        food1.setX(tempx);
        GLdouble tempy = rand() % tempH + r;
        food1.setY(tempy);
    }

    //Nyertes Kiirat�sa
    if (p1h == 20 || p2h == 2)
    {
        std::cout << "zold nyert" << std::endl;
        glutLeaveMainLoop();

    }

    if (p2h == 20 || p1h == 2)
    {
        std::cout << "kek nyert" << std::endl;
        glutLeaveMainLoop();
    }

    glutPostRedisplay();
    glutTimerFunc(10, update, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);	//glutLeaveMainLoop() miatt.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(25, 25);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("Ball games");

    init();

    srand(time(NULL));

    glutDisplayFunc(display);

    glutKeyboardFunc(keyPressed);

    glutKeyboardUpFunc(keyUp);

    glutTimerFunc(10, update, 0);

    glutMainLoop();

    while (true);	//eredm�ny miatt kell, hogy l�that� legyen
    return 0;
}


