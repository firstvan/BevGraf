#ifndef MYPOLYGON_HPP
#define MYPOLYGON_HPP
#include <vector>
#include "myPoint2dh.hpp"

template<typename T>
class myPoligon
{
    std::vector<Point2DH<T>> values;
    int size;


public:
    myPoligon<T>() {}

    myPoligon<T>(const std::vector<Point2DH<T>> rhs)
    {
        values = rhs;
        size = rhs.size();
    }

    Point2DH<T>& operator[](int i)
    {
        return values[i];
    }

    const Point2DH<T>& operator[](int i) const
    {
        return values[i];
    }

    void draw()
    {
        glBegin(GL_LINE_LOOP);

        for (int i = 0; i < size; i++)
        {
            glVertex2d(values[i].getX(), values[i].getY());
        }
        glEnd();
    }


};








#endif