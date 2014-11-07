#ifndef MYMATRIX_HPP
#define MYMATRIX_HPP

#include <vector>
#include <math.h>

#define PI	3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679


template<typename T>
class myMatrix
{
    int n, m;
    std::vector<std::vector<T>> matrix;

    void rs()
    {
        matrix.resize(n);
        for (int i = 0; i < n; i++)
        {
            matrix[i].resize(m);
        }
    }

public:

    myMatrix() {}

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


    myMatrix(int r_n, int r_m, std::vector<std::vector<T>> rhs_matrix)
    {
        n = r_n;
        m = r_m;

        rs();

        matrix = rhs_matrix;

    }

    myMatrix(int r_n,int r_m, const T* vector)
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

    myMatrix(char type, GLdouble v1, GLdouble v2 = 0)
    {
        n = 3;
        m = 3;

        rs();

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (i == j)
                    matrix[i][j] = 1;
                else
                    matrix[i][j] = 0;
            }
        }

        switch (type)
        {
        case 'E':
            matrix[0][2] = v1;
            matrix[1][2] = v2;
            break;
        case 'S':
            matrix[0][0] = v1;
            matrix[1][1] = v2;
            break;
        case 'F':
            GLdouble tempRad = v1 * ( PI / (double)180);
            matrix[0][0] = cos(tempRad);
            matrix[0][1] = -sin(tempRad);
            matrix[1][0] = sin(tempRad);
            matrix[1][1] = cos(tempRad);
            break;

        }
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
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
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

    myMatrix<T> inverse()
    {
        myMatrix<T> inv(n);
        inv.matrix[0][0] = matrix[1][1] * matrix[2][2] * matrix[3][3] -
                           matrix[1][1] * matrix[3][2] * matrix[2][3] -
                           matrix[1][2] * matrix[2][1] * matrix[3][3] +
                           matrix[1][2] * matrix[3][1] * matrix[2][3] +
                           matrix[1][3] * matrix[2][1] * matrix[3][2] -
                           matrix[1][3] * matrix[3][1] * matrix[2][2];

        inv.matrix[0][1] = -matrix[0][1] * matrix[2][2] * matrix[3][3] +
                           matrix[0][1] * matrix[3][2] * matrix[2][3] +
                           matrix[0][2] * matrix[2][1] * matrix[3][3] -
                           matrix[0][2] * matrix[3][1] * matrix[2][3] -
                           matrix[0][3] * matrix[2][1] * matrix[3][2] +
                           matrix[0][3] * matrix[3][1] * matrix[2][2];

        inv.matrix[0][2] = matrix[0][1] * matrix[1][2] * matrix[3][3] -
                           matrix[0][1] * matrix[3][2] * matrix[1][3] -
                           matrix[0][2] * matrix[1][1] * matrix[3][3] +
                           matrix[0][2] * matrix[3][1] * matrix[1][3] +
                           matrix[0][3] * matrix[1][1] * matrix[3][2] -
                           matrix[0][3] * matrix[3][1] * matrix[1][2];

        inv.matrix[0][3] = -matrix[0][1] * matrix[1][2] * matrix[2][3] +
                           matrix[0][1] * matrix[2][2] * matrix[1][3] +
                           matrix[0][2] * matrix[1][1] * matrix[2][3] -
                           matrix[0][2] * matrix[2][1] * matrix[1][3] -
                           matrix[0][3] * matrix[1][1] * matrix[2][2] +
                           matrix[0][3] * matrix[2][1] * matrix[1][2];

        inv.matrix[1][0] = -matrix[1][0] * matrix[2][2] * matrix[3][3] +
                           matrix[1][0] * matrix[3][2] * matrix[2][3] +
                           matrix[1][2] * matrix[2][0] * matrix[3][3] -
                           matrix[1][2] * matrix[3][0] * matrix[2][3] -
                           matrix[1][3] * matrix[2][0] * matrix[3][2] +
                           matrix[1][3] * matrix[3][0] * matrix[2][2];

        inv.matrix[1][1] = matrix[0][0] * matrix[2][2] * matrix[3][3] -
                           matrix[0][0] * matrix[3][2] * matrix[2][3] -
                           matrix[0][2] * matrix[2][0] * matrix[3][3] +
                           matrix[0][2] * matrix[3][0] * matrix[2][3] +
                           matrix[0][3] * matrix[2][0] * matrix[3][2] -
                           matrix[0][3] * matrix[3][0] * matrix[2][2];

        inv.matrix[1][2] = -matrix[0][0] * matrix[1][2] * matrix[3][3] +
                           matrix[0][0] * matrix[3][2] * matrix[1][3] +
                           matrix[0][2] * matrix[1][0] * matrix[3][3] -
                           matrix[0][2] * matrix[3][0] * matrix[1][3] -
                           matrix[0][3] * matrix[1][0] * matrix[3][2] +
                           matrix[0][3] * matrix[3][0] * matrix[1][2];

        inv.matrix[1][3] = matrix[0][0] * matrix[1][2] * matrix[2][3] -
                           matrix[0][0] * matrix[2][2] * matrix[1][3] -
                           matrix[0][2] * matrix[1][0] * matrix[2][3] +
                           matrix[0][2] * matrix[2][0] * matrix[1][3] +
                           matrix[0][3] * matrix[1][0] * matrix[2][2] -
                           matrix[0][3] * matrix[2][0] * matrix[1][2];

        inv.matrix[2][0] = matrix[1][0] * matrix[2][1] * matrix[3][3] -
                           matrix[1][0] * matrix[3][1] * matrix[2][3] -
                           matrix[1][1] * matrix[2][0] * matrix[3][3] +
                           matrix[1][1] * matrix[3][0] * matrix[2][3] +
                           matrix[1][3] * matrix[2][0] * matrix[3][1] -
                           matrix[1][3] * matrix[3][0] * matrix[2][1];

        inv.matrix[2][1] = -matrix[0][0] * matrix[2][1] * matrix[3][3] +
                           matrix[0][0] * matrix[3][1] * matrix[2][3] +
                           matrix[0][1] * matrix[2][0] * matrix[3][3] -
                           matrix[0][1] * matrix[3][0] * matrix[2][3] -
                           matrix[0][3] * matrix[2][0] * matrix[3][1] +
                           matrix[0][3] * matrix[3][0] * matrix[2][1];

        inv.matrix[2][2] = matrix[0][0] * matrix[1][1] * matrix[3][3] -
                           matrix[0][0] * matrix[3][1] * matrix[1][3] -
                           matrix[0][1] * matrix[1][0] * matrix[3][3] +
                           matrix[0][1] * matrix[3][0] * matrix[1][3] +
                           matrix[0][3] * matrix[1][0] * matrix[3][1] -
                           matrix[0][3] * matrix[3][0] * matrix[1][1];

        inv.matrix[2][3] = -matrix[0][0] * matrix[1][1] * matrix[2][3] +
                           matrix[0][0] * matrix[2][1] * matrix[1][3] +
                           matrix[0][1] * matrix[1][0] * matrix[2][3] -
                           matrix[0][1] * matrix[2][0] * matrix[1][3] -
                           matrix[0][3] * matrix[1][0] * matrix[2][1] +
                           matrix[0][3] * matrix[2][0] * matrix[1][1];

        inv.matrix[3][0] = -matrix[1][0] * matrix[2][1] * matrix[3][2] +
                           matrix[1][0] * matrix[3][1] * matrix[2][2] +
                           matrix[1][1] * matrix[2][0] * matrix[3][2] -
                           matrix[1][1] * matrix[3][0] * matrix[2][2] -
                           matrix[1][2] * matrix[2][0] * matrix[3][1] +
                           matrix[1][2] * matrix[3][0] * matrix[2][1];

        inv.matrix[3][1] = matrix[0][0] * matrix[2][1] * matrix[3][2] -
                           matrix[0][0] * matrix[3][1] * matrix[2][2] -
                           matrix[0][1] * matrix[2][0] * matrix[3][2] +
                           matrix[0][1] * matrix[3][0] * matrix[2][2] +
                           matrix[0][2] * matrix[2][0] * matrix[3][1] -
                           matrix[0][2] * matrix[3][0] * matrix[2][1];

        inv.matrix[3][2] = -matrix[0][0] * matrix[1][1] * matrix[3][2] +
                           matrix[0][0] * matrix[3][1] * matrix[1][2] +
                           matrix[0][1] * matrix[1][0] * matrix[3][2] -
                           matrix[0][1] * matrix[3][0] * matrix[1][2] -
                           matrix[0][2] * matrix[1][0] * matrix[3][1] +
                           matrix[0][2] * matrix[3][0] * matrix[1][1];

        inv.matrix[3][3] = matrix[0][0] * matrix[1][1] * matrix[2][2] -
                           matrix[0][0] * matrix[2][1] * matrix[1][2] -
                           matrix[0][1] * matrix[1][0] * matrix[2][2] +
                           matrix[0][1] * matrix[2][0] * matrix[1][2] +
                           matrix[0][2] * matrix[1][0] * matrix[2][1] -
                           matrix[0][2] * matrix[2][0] * matrix[1][1];

        T det = matrix[0][0] * inv.matrix[0][0] +
                matrix[1][0] * inv.matrix[0][1] +
                matrix[2][0] * inv.matrix[0][2] +
                matrix[3][0] * inv.matrix[0][3];

        det = 1.0f / det;

        inv *= det;
        return inv;
    }


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

                temp.setElement(i, j, tDouble);
            }
        }

        return temp;
    }

};




#endif