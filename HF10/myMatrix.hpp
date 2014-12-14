#ifndef MYMATRIX_HPP
#define MYMATRIX_HPP

#include <vector>
#include <string>
#include <cmath>
#include "myPoint4D.hpp"

#define PI	3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679


template<typename T>
class myMatrix
{
    int n, m;

    void rs()
    {
        /*
        matrix.resize(n);
        for (int i = 0; i < n; i++)
        {
            matrix[i].resize(m);
        }*/

        matrix = new GLdouble*[n];
        for (int i = 0; i < n; i++)
        {
            matrix[i] = new GLdouble[m];
            for (int j = 0; j < m; j++)
            {
                if (i == j)
                {
                    matrix[i][j] = 1;
                }
                else
                    matrix[i][j] = 0;
            }
        }

    }

public:
    GLdouble alfa;
    //std::vector<std::vector<T>> matrix;
    GLdouble ** matrix;

    myMatrix() {}

    /*~myMatrix()
    {
        for (int i = 0; i < n; i++)
        {
            delete[] matrix[i];
        }

        delete[] matrix;
    }*/

    myMatrix(int r_nm)
    {
        n = r_nm;
        m = r_nm;

        rs();
    }

    myMatrix(int r_n, int r_m)
    {
        n = r_n;
        m = r_m;

        rs();
    }




    myMatrix(int r_n, int r_m, const T* vector)
    {

        n = r_n;
        m = r_m;

        rs();
        int k = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                matrix[i][j] = vector[k++];
            }
        }
    }

    myMatrix(std::string type, GLdouble v1 = 0)
    {
        n = 4;
        m = 4;

        rs();

        for (int i = 0; i < n; i++)
        {
            matrix[i][i] = 1.0;
        }

        if (type == "Rx")
        {
            alfa = v1;
            GLdouble tempRad = v1 * (PI / (double)180);
            matrix[1][1] = std::cos(tempRad);
            matrix[1][2] = -std::sin(tempRad);
            matrix[2][1] = std::sin(tempRad);
            matrix[2][2] = std::cos(tempRad);
        }
        else if (type == "Ry")
        {
            alfa = v1;
            GLdouble tempRad = v1 * (PI / (double)180);
            matrix[0][0] = std::cos(tempRad);
            matrix[0][2] = std::sin(tempRad);
            matrix[2][0] = -std::sin(tempRad);
            matrix[2][2] = std::cos(tempRad);
        }
        else if (type == "Vm")
        {
            matrix[2][2] = 0;
        }
        else if (type == "Vc")
        {
            matrix[2][2] = 0;
            matrix[3][2] = -1 * (1 / static_cast<GLdouble>(v1));
        }
        else if (type == "Ax")
        {
            double q = 1.0/2.0;
            GLdouble tempRad = v1 * (PI / (double)180);
            matrix[0][0] = q * std::cos(tempRad);
            matrix[0][1] = 1;
            matrix[1][0] = q * std::sin(tempRad);
            matrix[1][1] = 0;
            matrix[1][2] = 1;
            matrix[2][2] = 0;

        }



    }

    void initWindowToViewPort(const myPoint4D<T>& w1, const myPoint4D<T>& w2, const myPoint4D<T>& v1, const myPoint4D<T>& v2)
    {
        n = 4;
        m = 4;
        rs();
        for (int i = 0; i < n; i++)
        {
            matrix[i][i] = 1.0;
        }
        GLdouble t1 = w2.x - w1.x;
        GLdouble t2 = w2.y - w1.y;
        if (t1 != 0 && t2 != 0)
        {
            matrix[0][0] = (v2.x - v1.x) / t1;
            matrix[1][1] = (v2.y - v1.y) / t2;
            matrix[0][3] = v1.x - w1.x * matrix[0][0];
            matrix[1][3] = v1.y - w1.y * matrix[1][1];
        }
        else
            std::cout << "Division by zero" << std::endl;
    }

    void setDeg(std::string type, T value)
    {
        if (type == "Rx")
        {
            alfa = value;
            GLdouble tempRad = value * (PI / (double)180);
            matrix[1][1] = std::cos(tempRad);
            matrix[1][2] = -std::sin(tempRad);
            matrix[2][1] = std::sin(tempRad);
            matrix[2][2] = std::cos(tempRad);
        }
        else if (type == "Ry")
        {
            alfa = value;
            GLdouble tempRad = value * (PI / (double)180);
            matrix[0][0] = std::cos(tempRad);
            matrix[0][2] = std::sin(tempRad);
            matrix[2][0] = -std::sin(tempRad);
            matrix[2][2] = std::cos(tempRad);
        }
        else if (type == "Ax")
        {
            GLdouble tempRad = value *(PI / (double)180);
            double q = 1.0/2.0;
            matrix[0][0] = q * std::cos(tempRad);
            matrix[1][0] = q * std::sin(tempRad);
        }
    }

    void setS(T value)
    {
        matrix[3][2] = -1 * (1 / static_cast<GLdouble>(value));
    }

    void setElement(int r_n, int r_m, T value)
    {
        matrix[r_n][r_m] = value;
    }

    T getElement(int r_n, int r_m) const
    {
        return matrix[r_n][r_m];
    }

    int getN() const
    {
        return n;
    }

    int getM() const
    {
        return m;
    }

    myMatrix<T>& operator*=(T skalar)
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                matrix[j][i] *= skalar;
            }

        }
        return *this;
    }

    virtual void kiir() const
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                std::cout << matrix[i][j] << ", ";
            }
            std::cout << std::endl;
        }

    }

    //myMatrix<T> inverse()
    //{
    //    myMatrix<T> inv(n);
    //    inv.matrix[0][0] = matrix[1][1] * matrix[2][2] * matrix[3][3] -
    //                       matrix[1][1] * matrix[3][2] * matrix[2][3] -
    //                       matrix[1][2] * matrix[2][1] * matrix[3][3] +
    //                       matrix[1][2] * matrix[3][1] * matrix[2][3] +
    //                       matrix[1][3] * matrix[2][1] * matrix[3][2] -
    //                       matrix[1][3] * matrix[3][1] * matrix[2][2];

    //    inv.matrix[0][1] = -matrix[0][1] * matrix[2][2] * matrix[3][3] +
    //                       matrix[0][1] * matrix[3][2] * matrix[2][3] +
    //                       matrix[0][2] * matrix[2][1] * matrix[3][3] -
    //                       matrix[0][2] * matrix[3][1] * matrix[2][3] -
    //                       matrix[0][3] * matrix[2][1] * matrix[3][2] +
    //                       matrix[0][3] * matrix[3][1] * matrix[2][2];

    //    inv.matrix[0][2] = matrix[0][1] * matrix[1][2] * matrix[3][3] -
    //                       matrix[0][1] * matrix[3][2] * matrix[1][3] -
    //                       matrix[0][2] * matrix[1][1] * matrix[3][3] +
    //                       matrix[0][2] * matrix[3][1] * matrix[1][3] +
    //                       matrix[0][3] * matrix[1][1] * matrix[3][2] -
    //                       matrix[0][3] * matrix[3][1] * matrix[1][2];

    //    inv.matrix[0][3] = -matrix[0][1] * matrix[1][2] * matrix[2][3] +
    //                       matrix[0][1] * matrix[2][2] * matrix[1][3] +
    //                       matrix[0][2] * matrix[1][1] * matrix[2][3] -
    //                       matrix[0][2] * matrix[2][1] * matrix[1][3] -
    //                       matrix[0][3] * matrix[1][1] * matrix[2][2] +
    //                       matrix[0][3] * matrix[2][1] * matrix[1][2];

    //    inv.matrix[1][0] = -matrix[1][0] * matrix[2][2] * matrix[3][3] +
    //                       matrix[1][0] * matrix[3][2] * matrix[2][3] +
    //                       matrix[1][2] * matrix[2][0] * matrix[3][3] -
    //                       matrix[1][2] * matrix[3][0] * matrix[2][3] -
    //                       matrix[1][3] * matrix[2][0] * matrix[3][2] +
    //                       matrix[1][3] * matrix[3][0] * matrix[2][2];

    //    inv.matrix[1][1] = matrix[0][0] * matrix[2][2] * matrix[3][3] -
    //                       matrix[0][0] * matrix[3][2] * matrix[2][3] -
    //                       matrix[0][2] * matrix[2][0] * matrix[3][3] +
    //                       matrix[0][2] * matrix[3][0] * matrix[2][3] +
    //                       matrix[0][3] * matrix[2][0] * matrix[3][2] -
    //                       matrix[0][3] * matrix[3][0] * matrix[2][2];

    //    inv.matrix[1][2] = -matrix[0][0] * matrix[1][2] * matrix[3][3] +
    //                       matrix[0][0] * matrix[3][2] * matrix[1][3] +
    //                       matrix[0][2] * matrix[1][0] * matrix[3][3] -
    //                       matrix[0][2] * matrix[3][0] * matrix[1][3] -
    //                       matrix[0][3] * matrix[1][0] * matrix[3][2] +
    //                       matrix[0][3] * matrix[3][0] * matrix[1][2];

    //    inv.matrix[1][3] = matrix[0][0] * matrix[1][2] * matrix[2][3] -
    //                       matrix[0][0] * matrix[2][2] * matrix[1][3] -
    //                       matrix[0][2] * matrix[1][0] * matrix[2][3] +
    //                       matrix[0][2] * matrix[2][0] * matrix[1][3] +
    //                       matrix[0][3] * matrix[1][0] * matrix[2][2] -
    //                       matrix[0][3] * matrix[2][0] * matrix[1][2];

    //    inv.matrix[2][0] = matrix[1][0] * matrix[2][1] * matrix[3][3] -
    //                       matrix[1][0] * matrix[3][1] * matrix[2][3] -
    //                       matrix[1][1] * matrix[2][0] * matrix[3][3] +
    //                       matrix[1][1] * matrix[3][0] * matrix[2][3] +
    //                       matrix[1][3] * matrix[2][0] * matrix[3][1] -
    //                       matrix[1][3] * matrix[3][0] * matrix[2][1];

    //    inv.matrix[2][1] = -matrix[0][0] * matrix[2][1] * matrix[3][3] +
    //                       matrix[0][0] * matrix[3][1] * matrix[2][3] +
    //                       matrix[0][1] * matrix[2][0] * matrix[3][3] -
    //                       matrix[0][1] * matrix[3][0] * matrix[2][3] -
    //                       matrix[0][3] * matrix[2][0] * matrix[3][1] +
    //                       matrix[0][3] * matrix[3][0] * matrix[2][1];

    //    inv.matrix[2][2] = matrix[0][0] * matrix[1][1] * matrix[3][3] -
    //                       matrix[0][0] * matrix[3][1] * matrix[1][3] -
    //                       matrix[0][1] * matrix[1][0] * matrix[3][3] +
    //                       matrix[0][1] * matrix[3][0] * matrix[1][3] +
    //                       matrix[0][3] * matrix[1][0] * matrix[3][1] -
    //                       matrix[0][3] * matrix[3][0] * matrix[1][1];

    //    inv.matrix[2][3] = -matrix[0][0] * matrix[1][1] * matrix[2][3] +
    //                       matrix[0][0] * matrix[2][1] * matrix[1][3] +
    //                       matrix[0][1] * matrix[1][0] * matrix[2][3] -
    //                       matrix[0][1] * matrix[2][0] * matrix[1][3] -
    //                       matrix[0][3] * matrix[1][0] * matrix[2][1] +
    //                       matrix[0][3] * matrix[2][0] * matrix[1][1];

    //    inv.matrix[3][0] = -matrix[1][0] * matrix[2][1] * matrix[3][2] +
    //                       matrix[1][0] * matrix[3][1] * matrix[2][2] +
    //                       matrix[1][1] * matrix[2][0] * matrix[3][2] -
    //                       matrix[1][1] * matrix[3][0] * matrix[2][2] -
    //                       matrix[1][2] * matrix[2][0] * matrix[3][1] +
    //                       matrix[1][2] * matrix[3][0] * matrix[2][1];

    //    inv.matrix[3][1] = matrix[0][0] * matrix[2][1] * matrix[3][2] -
    //                       matrix[0][0] * matrix[3][1] * matrix[2][2] -
    //                       matrix[0][1] * matrix[2][0] * matrix[3][2] +
    //                       matrix[0][1] * matrix[3][0] * matrix[2][2] +
    //                       matrix[0][2] * matrix[2][0] * matrix[3][1] -
    //                       matrix[0][2] * matrix[3][0] * matrix[2][1];

    //    inv.matrix[3][2] = -matrix[0][0] * matrix[1][1] * matrix[3][2] +
    //                       matrix[0][0] * matrix[3][1] * matrix[1][2] +
    //                       matrix[0][1] * matrix[1][0] * matrix[3][2] -
    //                       matrix[0][1] * matrix[3][0] * matrix[1][2] -
    //                       matrix[0][2] * matrix[1][0] * matrix[3][1] +
    //                       matrix[0][2] * matrix[3][0] * matrix[1][1];

    //    inv.matrix[3][3] = matrix[0][0] * matrix[1][1] * matrix[2][2] -
    //                       matrix[0][0] * matrix[2][1] * matrix[1][2] -
    //                       matrix[0][1] * matrix[1][0] * matrix[2][2] +
    //                       matrix[0][1] * matrix[2][0] * matrix[1][2] +
    //                       matrix[0][2] * matrix[1][0] * matrix[2][1] -
    //                       matrix[0][2] * matrix[2][0] * matrix[1][1];

    //    T det = matrix[0][0] * inv.matrix[0][0] +
    //            matrix[1][0] * inv.matrix[0][1] +
    //            matrix[2][0] * inv.matrix[0][2] +
    //            matrix[3][0] * inv.matrix[0][3];

    //    det = 1.0f / det;

    //    inv *= det;
    //    return inv;
    //}


    myMatrix<T> operator*(const myMatrix<T>& rhs)
    {
        myMatrix<T> temp(n, rhs.getM());

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < rhs.getM(); j++)
            {
                double tDouble = 0;
                for (int k = 0; k < m; k++)
                {
                    tDouble += matrix[i][k] * rhs.getElement(k, j) ;
                }

                temp.matrix[i][j] = tDouble;
            }
        }

        return temp;
    }

};




#endif