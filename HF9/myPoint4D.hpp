#ifndef MY_POINT_4D
#define MY_POINT_4D


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
};

#endif