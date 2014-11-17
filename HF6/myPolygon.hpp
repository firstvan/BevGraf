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

    void draw(bool filled = false)
    {
        if (filled)
            glBegin(GL_POLYGON);
        else
            glBegin(GL_LINE_LOOP);

        for (int i = 0; i < size; i++)
        {
            glVertex2d(values[i].getX(), values[i].getY());
        }
        glEnd();
    }

    void drawWithPoints()
    {
        glBegin(GL_LINE_LOOP);

        for (int i = 0; i < size; i++)
        {
            glVertex2d(values[i].getX(), values[i].getY());
        }
        glEnd();


        glBegin(GL_POINTS);

        for (int i = 0; i < size; i++)
        {
            glVertex2d(values[i].getX(), values[i].getY());
        }
        glEnd();
    }

    void setValues(const std::vector<Point2DH<T>>& a)
    {
        values.clear();
        values = a;
        size = a.size();
    }

    int getSize() const
    {
        return size;
    }

    myPoligon<T> cutWith(const myPoligon& cutter)
    {
        myPoligon<T> temp = (*this);
        int n = cutter.getSize();

        //A vágó poligon pontjain megyek végig
        for (int i = 0; i < n; i++)
        {
            std::vector<Point2DH<GLdouble>> tempPoly;

            int next = i + 1;

            if (next == n)
            {
                next = 0;
            }

            Point2DH<GLdouble> cutterSide = metszIlleszt(cutter[i], cutter[next]);

            int next1 = next + 1;

            if (next1 == n)
            {
                next1 = 0;
            }

            Point2DH<GLdouble> compPoint = cutter[next1];
            // a vágandó felületen megyek végig
            int m = temp.getSize();
            for (int j = 0; j < m; j++)
            {
                int next2 = j + 1;

                if (next2 == m)
                {
                    next2 = 0;
                }

                if (onTheSameSide(temp[j], compPoint, cutterSide))
                {
                    if (onTheSameSide(temp[next2], compPoint, cutterSide))
                    {
                        tempPoly.emplace_back(temp[next2]);
                    }
                    else
                    {
                        Point2DH<GLdouble> a = metszIlleszt(cutterSide, metszIlleszt(temp[j], temp[next2]));
                        a.norm();
                        tempPoly.emplace_back(a);
                    }
                }
                else
                {
                    if (onTheSameSide(temp[next2], compPoint, cutterSide))
                    {
                        Point2DH<GLdouble> a = metszIlleszt(cutterSide, metszIlleszt(temp[j], temp[next2]));
                        a.norm();
                        tempPoly.emplace_back(a);
                        tempPoly.emplace_back(temp[next2]);
                    }
                }
            }
            temp.setValues(tempPoly);

        }


        return temp;
    }


    /* std::vector<Point2DH<T>> vagas(const myPoligon<T>& rhs)
     {
         //rhs a szemüveg amivel vágunk
         std::vector<Point2DH<T>> a = values; //ezzel fogok majd visszatérni
         int n = rhs.getSize();

         // végigmegyünk a szemüveglencse élein
         for (int i = 0; i < n; i++)
         {
             int next = i + 1;

             if (next == n)
             {
                 next = 0;
             }

             Point2DH<GLdouble> tempOldal = metszIlleszt(rhs[i], rhs[next]);


             Point2DH<GLdouble> pont = a[a.size()-1];
             std::vector<Point2DH<GLdouble>> temp;

             for (int j = 0; j < a.size(); j++)
             {

                 int nextP = j + 1;

                 if (nextP == a.size())
                 {
                     nextP = 0;
                 }

                 Point2DH<GLdouble> tempEL = metszIlleszt(a[j], a[nextP]);

                 if (onTheSameSide(rhs[i], pont, tempEL) && onTheSameSide(rhs[next], pont, tempEL))
                 {
                     temp.emplace_back(rhs[next]);
                 }
                 else if (onTheSameSide(rhs[i], pont, tempEL) == true && onTheSameSide(rhs[next], pont, tempEL) == false)
                 {
                     Point2DH<T> a = metszIlleszt(tempEL, tempOldal);
                     temp.emplace_back(a);
                 }
                 else if (onTheSameSide(rhs[i], pont, tempEL) == false && onTheSameSide(rhs[next], pont, tempEL) == true)
                 {
                     Point2DH<T> a = metszIlleszt(tempEL, tempOldal);
                     temp.emplace_back(a);
                     temp.emplace_back(rhs[next]);
                 }

                 pont = a[j];
             }


         }


         return a;
     }*/
};








#endif