#ifndef MY_POINT_4D
#define MY_POINT_4D


template <typename T> class myMatrix;
template<typename T>
class myPoint4D
{
public:
    T x, y, z, t;

    myPoint4D(): x(0), y(0), z(0), t(1) {}

    myPoint4D(T rx, T ry, T rz=0): x(rx), y(ry), z(rz), t(1) {}

    void norma()
    {
        x = x / static_cast<GLdouble>(t);
        y = y / static_cast<GLdouble>(t);
        z = z / static_cast<GLdouble>(t);
        t = 1;
    }

    void print()
    {
        std::cout << x << ", " << y << ", " << z << ", " << t << std::endl;
    }

    inline void trans(const myMatrix<T>& m)
    {
        GLdouble temp=0;
        T oX = x;
        T oY = y;
        T oZ = z;
        T oT = t;

        x = oX * m.matrix[0][0] + oY * m.matrix[0][1]+ oZ * m.matrix[0][2]+oT * m.matrix[0][3];
        y = oX * m.matrix[1][0] + oY * m.matrix[1][1]+ oZ * m.matrix[1][2]+oT * m.matrix[1][3];
        z = oX * m.matrix[2][0] + oY * m.matrix[2][1]+ oZ * m.matrix[2][2]+oT * m.matrix[2][3];
        t = oX * m.matrix[3][0] + oY * m.matrix[3][1]+ oZ * m.matrix[3][2]+oT * m.matrix[3][3];


    }


    myPoint4D<GLdouble> operator-(const myPoint4D<GLdouble>& rhs)
    {
        myPoint4D<GLdouble> temp;

        temp.x = x - rhs.x;
        temp.y = y - rhs.y;
        temp.z = z - rhs.z;

        return temp;
    }
};

#endif