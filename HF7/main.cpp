#include <GL/glut.h>
#include <math.h>
#include "point.hpp"
#include <vector>
#include <iostream>
#include "Slider.hpp"

GLsizei winWidth = 1280, winHeight = 720;

std::vector<myPoint<GLdouble>> points;
GLdouble e1, e2, e3, e4, e5;
myPoint<GLdouble> temp;
GLdouble t0 = 0.33;
GLint dragged = -1;

myPoint<GLdouble> str(280, 50);
myPoint<GLdouble> end(1000, 50);

mySlider<GLdouble> sldr(str, end, 0.0, 100.0);

GLint Round( GLfloat n )
{
    return (GLint)( n + 0.5 );
}

GLint faktorial(GLint n)
{
    GLint temp = 1;
    for (int i = 1; i <=n ; i++)
    {
        temp *= i;
    }

    return temp;
}

void init( )
{
    glClearColor( 1.0, 1.0, 1.0, 0.0 );
    glMatrixMode( GL_PROJECTION );
    gluOrtho2D( 0.0, winWidth, 0.0, winHeight );
    glShadeModel( GL_FLAT );
    glEnable( GL_POINT_SMOOTH );
    glEnable( GL_LINE_SMOOTH );
    glPointSize(5);
    glLineWidth(3);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    e1 = faktorial(4) / static_cast<GLdouble>(faktorial(0) * faktorial(4));
    e2 = faktorial(4) / static_cast<GLdouble>(faktorial(1) * faktorial(3));
    e3 = faktorial(4) / static_cast<GLdouble>(faktorial(2) * faktorial(2));
    e4 = faktorial(4) / static_cast<GLdouble>(faktorial(3) * faktorial(1));
    e5 = faktorial(4) / static_cast<GLdouble>(faktorial(4) * faktorial(0));
}


myPoint<GLdouble> Bemstein(GLdouble t)
{
    GLdouble tempx,tempy;

    tempx = e1 * pow((1-t),4) * points[0].getX() + e2 * t * pow((1 - t), 3) * points[1].getX() + e3 * t * t * pow((1 - t),2) * points[2].getX() + e4 * t * t * t * (1-t) * points[3].getX() + e5 * pow(t,4) * points[0].getX();
    tempy = e1 * pow((1-t),4) * points[0].getY() + e2 * t * pow((1 - t), 3) * points[1].getY() + e3 * t * t * pow((1 - t),2) * points[2].getY() + e4 * t * t * t * (1-t) * points[3].getY() + e5 * pow(t,4) * points[0].getY();


    return myPoint<GLdouble>(tempx, tempy);

}


void display()
{

    glPointSize(5);
    glLineWidth(3);

    glClear(GL_COLOR_BUFFER_BIT);


    if (points.size() > 3)
    {
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 4; i++)
        {
            glVertex2d(points[i].getX(), points[i].getY());
        }
        glEnd();

        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_LINE_LOOP);
        for (GLdouble t = 0.0; t < 1.0; t +=0.0001)
        {
            temp = Bemstein(t);
            glVertex2d(temp.getX(), temp.getY());
        }
        glEnd();
    }

    if (points.size() > 7)
    {
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINE_STRIP);
        for (int i = 4; i < 8; i++)
        {
            glVertex2d(points[i].getX(), points[i].getY());
        }
        glEnd();


        std::vector<myPoint<GLdouble>> a;

        a.emplace_back(points[0]);
        for (size_t i = 4; i < 8; i++)
        {
            a.emplace_back(points[i]);
        }
        a.emplace_back(points[0]);


        std::vector<myPoint<GLdouble>> b;
        glColor3d(0.0, 0.0, 1.0);
        glBegin(GL_LINE_STRIP);
        for (GLdouble t = 0.0; t < 1.0; t += 0.001)
        {
            b = a;
            for (int j = 5; j >= 0; j--)
            {
                for (int i = 0; i < j; i++)
                {
                    b[i].setX((1 - t) * b[i].getX() + t * b[i + 1].getX());
                    b[i].setY((1 - t) * b[i].getY() + t * b[i + 1].getY());
                }
            }
            glVertex2d(b[0].getX(), b[0].getY());
        }
        glEnd();

        glColor3d(1.0, 0.0, 0.0);
        for (int j = 5; j >= 0; j--)
        {
            glBegin(GL_LINE_STRIP);
            for (int i = 0; i < j; i++)
            {
                a[i].setX((1 - t0) * a[i].getX() + t0 * a[i + 1].getX());
                a[i].setY((1 - t0) * a[i].getY() + t0 * a[i + 1].getY());
                glVertex2d(a[i].getX(), a[i].getY());
            }
            glEnd();
        }

        glColor3d(0.0, 0.0, 1.0);
        glBegin(GL_POINTS);
        glVertex2d(a[0].getX(), a[0].getY());
        glEnd();

    }


    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_POINTS);
    for (auto p : points)
        glVertex2d(p.getX(), p.getY());
    glEnd();

    sldr.draw();

    glutSwapBuffers( );
}

/*
 *  Ket pont tavolsaganak negyzetet adja vissza.
 */
GLfloat dist2( myPoint<GLdouble> P1, myPoint<GLdouble> P2 )
{
    GLdouble t1 = P1.getX() - P2.getX();
    GLdouble t2 = P1.getY() - P2.getY();
    return t1 * t1 + t2 * t2;
}

GLint getActivePoint1(std::vector<myPoint<GLdouble>> p, GLint size, GLint sens, GLint x, GLint y )
{
    GLint i, s = sens * sens;
    myPoint<GLdouble> P( x, y );

    for ( i = 0; i < size; i++ )
        if (dist2(p[i], P) < s)
        {
            return i;
        }
    return -1;
}


void processMouse( GLint button, GLint action, GLint xMouse , GLint yMouse )
{
    GLint i;
    if ( button == GLUT_LEFT_BUTTON && action == GLUT_DOWN )
        if (points.size() < 8)
        {
            if (points.size() == 2)
            {
                points.emplace_back(myPoint<GLdouble>(xMouse, winHeight - yMouse));
                double tempx = points[0].getX() + (-1 * (points[1].getX() - points[0].getX()));
                double tempy = points[0].getY() + (-1 * (points[1].getY() - points[0].getY()));
                points.emplace_back(myPoint<GLdouble>(tempx,tempy));
                tempx = 4 / static_cast<GLdouble>(5) * (points[0].getX() - points[3].getX()) + points[0].getX();
                tempy = 4 / static_cast<GLdouble>(5) * (points[0].getY() - points[3].getY()) + points[0].getY();
                points.emplace_back(myPoint<GLdouble>(tempx,tempy));
            }
            else if (points.size() == 6)
            {
                points.emplace_back(myPoint<GLdouble>(xMouse, winHeight - yMouse));
                double tempx = points[0].getX() + (-1 * (points[4].getX() - points[0].getX()));
                double tempy = points[0].getY() + (-1 * (points[4].getY() - points[0].getY()));
                points.emplace_back(myPoint<GLdouble>(tempx,tempy));
            }
            else
            {
                points.emplace_back(myPoint<GLdouble>(xMouse, winHeight - yMouse));
            }
        }
        else if (sldr.dis2Click(xMouse, winHeight - yMouse) < 64)
        {
            dragged = 10;
        }
        else if ( ( i = getActivePoint1( points, points.size(), 8, xMouse, winHeight - yMouse ) ) != -1 )
            dragged = i;
    if ( button == GLUT_LEFT_BUTTON && action == GLUT_UP  )
        dragged = -1;
}

void processMouseActiveMotion( GLint xMouse, GLint yMouse )
{
    if ( dragged >= 0 )
    {
        if (dragged == 10)
        {
            sldr.setClickX(xMouse);
            t0 = sldr.getValue() / 100;
        }
        else if (dragged != 3 && dragged != 4 && dragged != 7)
        {
            points[dragged].setX(xMouse);
            points[dragged].setY(winHeight - yMouse);

            if (dragged == 0 || dragged == 1)
            {
                points[3].setX(points[0].getX() + (-1 * (points[1].getX()-points[0].getX())));
                points[3].setY(points[0].getY() + (-1 * (points[1].getY()-points[0].getY())));

                GLdouble tempx = 4 / static_cast<GLdouble>(5) * (points[0].getX() - points[3].getX()) + points[0].getX();
                GLdouble tempy = 4 / static_cast<GLdouble>(5) * (points[0].getY() - points[3].getY()) + points[0].getY();

                points[4].setX(tempx);
                points[4].setY(tempy);

                points[7].setX(points[0].getX() + (-1 * (points[4].getX()-points[0].getX())));
                points[7].setY(points[0].getY() + (-1 * (points[4].getY()-points[0].getY())));

            }


            //points[dragged].setX(xMouse);
            //points[dragged].setY(winHeight - yMouse);
        }

        glutPostRedisplay( );
    }
}

int main( int argc, char** argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize( winWidth, winHeight );
    glutInitWindowPosition( 100,100 );
    glutCreateWindow( "Bezier Curves" );
    init( );
    glutDisplayFunc( display );
    glutMouseFunc( processMouse );
    glutMotionFunc( processMouseActiveMotion );
    glutMainLoop( );
    return 0;
}
