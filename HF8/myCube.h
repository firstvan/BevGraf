#ifndef MY_CUBE
#define MY_CUBE

#include "myPoint4D.hpp"
#include <vector>

template<typename T>
class myCube
{
public:
    std::vector<myPoint4D<T>> data;

    myCube()
    {
        data.resize(8);
    }

    myCube(const std::vector<myPoint4D<T>>& a) : data(a) {}

    void draw()
    {
        glBegin(GL_LINE_LOOP);
        for (int i = 4; i < 8; i++)
        {
            glVertex2d(data[i].x, data[i].y);
        }
        glEnd();

        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 4; i++)
        {
            glVertex2d(data[i].x, data[i].y);
        }
        glEnd();


        glBegin(GL_LINES);

        glVertex2d(data[0].x, data[0].y);
        glVertex2d(data[4].x, data[4].y);

        glVertex2d(data[1].x, data[1].y);
        glVertex2d(data[5].x, data[5].y);

        glVertex2d(data[2].x, data[2].y);
        glVertex2d(data[6].x, data[6].y);

        glVertex2d(data[3].x, data[3].y);
        glVertex2d(data[7].x, data[7].y);
        glEnd();

        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_POINTS);
        for (int i = 0; i < 8; i++)
        {
            glVertex2d(data[i].x, data[i].y);
        }
        glEnd();

    }

};

#endif