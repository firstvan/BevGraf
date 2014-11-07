#ifndef MYSTAR_HPP
#define MYSTAR_HPP

#define PI	3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679

#include "point.hpp"

class myStar
{
    myPoint<GLdouble> center;
    int r1, r2;
    int splt;
    std::vector<myPoint<GLdouble>> points1;
    std::vector<myPoint<GLdouble>> points2;
    GLdouble rotate;

public:

    myStar(const myPoint<GLdouble>& c, int rr1, int rr2, int rsplit, int rrotate = 0)
    {
        center = c;
        r1 = rr1;
        r2 = rr2;
        splt = rsplit;
        rotate = degToRad(rrotate);
        split();
    }

    void draw()
    {
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < splt; i++)
        {
            glVertex2d(points1[i].getX(), points1[i].getY());
            glVertex2d(points2[i].getX(), points2[i].getY());
        }
        glEnd();
    }

    void inline drawCircle()
    {
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 360; i++)
        {
            GLdouble x = center.getX() + r1 * cos(i * degToRad(1));
            GLdouble y = center.getY() + r1 * sin(i * degToRad(1));
            glVertex2d(x, y);
        }
        glEnd();

        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 360; i++)
        {
            GLdouble x = center.getX() + r2 * cos(i * degToRad(1));
            GLdouble y = center.getY() + r2 * sin(i * degToRad(1));
            glVertex2d(x, y);
        }
        glEnd();
    }

    void inline split()
    {
        points1.clear();
        points2.clear();

        GLdouble tempSzog = degToRad(360) / static_cast<GLdouble>(splt);
        for (int i = 0; i < splt; i++)
        {
            points1.push_back(myPoint<GLdouble>(center.getX() + r1 * cos((i * tempSzog) + rotate), center.getY() + r1 * sin((i * tempSzog) + rotate) ));
        }


        GLdouble temp2 = tempSzog / static_cast<GLdouble>(2);
        temp2 += rotate;

        for (int i = 0; i < splt; i++)
        {
            points2.push_back(myPoint<GLdouble>(center.getX() + r2 * cos((i * tempSzog) + temp2), center.getY() + r2 * sin((i * tempSzog) + temp2 ) ));
        }
    }

    GLdouble static degToRad(GLint a)
    {
        return  a * (PI / (double)180);
    }

    void setElement(int which, int element, GLdouble valueX, GLdouble valueY)
    {
        if (which == 1)
        {
            points1[element].setX(valueX);
            points1[element].setY(valueY);
        }
        else
        {
            points2[element].setX(valueX);
            points2[element].setY(valueY);
        }
    }

    myPoint<GLdouble> getElement(int which, int element)
    {
        if (which == 1)
        {
            return points1[element];
        }
        else
        {
            return points2[element];
        }
    }
};


#endif MYSTAR_HPP