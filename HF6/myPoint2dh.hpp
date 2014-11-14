#ifndef MYPOINT2DH_HPP
#define MYPOINT2DH_HPP


template<typename T>
class Point2DH
{
    T x, y, z;

public:

    Point2DH<T>()
    {}

    Point2DH<T>(T rhsx, T rhsy, T rhsz = 1)
    {
        x = rhsx;
        y = rhsy;
        z = rhsz;
    }

    void setX(T rhs)
    {
        x = rhs;
    }

    void setY(T rhs)
    {
        y = rhs;
    }

    void setZ(T rhs)
    {
        z = rhs;
    }

    T getX() const
    {
        return x;
    }

    T getY() const
    {
        return y;
    }

    T getZ() const
    {
        return z;
    }

    void print()
    {
        std::cout << x << ", " << y << ", " << z << std::endl;
    }

    void norm()
    {
        x /= z;
        y /= z;
        z /= z;
    }

    Point2DH<T> operator*(const Point2DH& rhs) const
    {
        Point2DH<T> temp;

        temp.setX(x * rhs.getX());
        temp.setX(y * rhs.getY());
        temp.setX(z * rhs.getZ());

        return temp;
    }
};


Point2DH<GLdouble> metszIlleszt(const Point2DH<GLdouble>& a, const Point2DH<GLdouble>& b)
{
    Point2DH<GLdouble> temp;
    temp.setX( (a.getY() * b.getZ()) - (b.getY() * a.getZ()) );
    temp.setY( -1 * ( (a.getX() * b.getZ()) - (b.getX() * a.getZ()) ) );
    temp.setZ( (a.getX() * b.getY()) - (b.getX() * a.getY()) );

    return temp;
}

bool onTheSameSide(const Point2DH<GLdouble>& p1, const Point2DH<GLdouble>& p2, GLdouble a, GLdouble b, GLdouble c)
{
    Point2DH<GLdouble> pT = p1 * p2;
    GLdouble temp = 0;

    temp = a * (pT.getX() / pT.getZ()) + b * (pT.getY() / pT.getZ()) + c;

    std::cout << "a= " << temp << std::endl;

    if (temp > 0)
    {
        return true;
    }
    else if (temp < 0)
    {
        return false;
    }
}


#endif