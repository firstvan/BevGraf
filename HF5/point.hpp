#ifndef POINTS_HPP
#define POINTS_HPP

#include <GL/glut.h>
#include <math.h>


template<typename T>
class myPoint
{
    T x, y;

public:
    //pont inicializálása
    myPoint() : x(0), y(0) {}

    //pont létrehozása x,y pontban
    myPoint(T rhsX, T rhsY) : x(rhsX), y(rhsY)
    {}

    //másoló konstruktor
    myPoint(myPoint& rhs)
    {
        x = rhs.getX();
        y = rhs.getY();
    }


    //x visszatérítése
    T getX() const
    {
        return x;
    }

    //y visszatérítése
    T getY() const
    {
        return y;
    }

    //x beállítása
    void setX(const T& rhsx)
    {
        x = rhsx;
    }

    //y beállytása
    void setY(const T& rhsy)
    {
        y = rhsy;
    }

    //x növelése paraméterrel
    void addX(T val)
    {
        x += val;
    }

    //y növelése paraméterrel
    void addY(T val)
    {
        y += val;
    }

    //pont kirajzolása
    void display() const
    {
        glBegin(GL_POINTS);
        glVertex2d(x, y);
        glEnd();
    }

    //x y növelése paraméterrel
    void add(T rhsX, T rhsY)
    {
        x += rhsX;
        y += rhsY;
    }

    //x y csökkentése paraméterrel
    void sub(T rhsX, T rhsY)
    {
        x -= rhsX;
        y -= rhsY;
    }

    // pontok egyenlõség vizsgálata
    bool operator==(myPoint& rhs) const
    {
        if (this->getX() == rhs.getX() && this->getY() == rhs.getY())
            return true;
        return false;
    }

    //pont számmal való szorzása
    myPoint operator*(const double rhs) const
    {
        return myPoint(rhs*this->getX(), rhs*this->getY());
    }

    //pontok összeadása
    myPoint operator+(const myPoint& rhs)
    {
        return myPoint(this->getX() + rhs.getX(), this->getY() + rhs.getY());
    }

    //pont távolsága négyzete a paraméterben meghatározott két pont által határolt egyenesnek
    double lineDistance2(const myPoint& a1, const myPoint& a2)
    {
        GLdouble x = a1.getY() - a2.getY();
        GLdouble y = a2.getX() - a1.getX();
        GLdouble c = (a1.getY() - a2.getY()) * a1.getX() + (a2.getX() - a1.getX()) * a1.getY();

        return pow(fabs(x * this->getX() + y * this->getY() - c), 2) / (x * x + y * y);
    }

    //pont távolsága 2pont által határole egyeneseknek
    double lineDistance(const myPoint& a1, const myPoint& a2)
    {
        GLdouble x = a1.getY() - a2.getY();
        GLdouble y = a2.getX() - a1.getX();
        GLdouble c = (a1.getY() - a2.getY()) * a1.getX() + (a2.getX() - a1.getX()) * a1.getY();

        return abs(x * this->getX() + y * this->getY() - c) / sqrt(x * x + y * y);
    }

    //két pont távolság négyzete
    double pointDis2(const myPoint & p)
    {
        GLdouble retX = x - p.getX();
        GLdouble retY = y - p.getY();
        return (retX * retX + retY * retY);
    }

    double pointDis2(T x1, T y1)
    {
        GLdouble retX = x - x1;
        GLdouble retY = y - y1;
        return (retX * retX + retY * retY);
    }

};



#endif