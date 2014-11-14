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

bool onTheSameSide(const Point2DH<GLdouble>& p1, const Point2DH<GLdouble>& p2, const Point2DH<GLdouble>& e)
{
    GLdouble temp = 0;
    GLdouble temp2 = 0;

    temp = e.getX() * (p1.getX() / p1.getZ()) + e.getY() * (p1.getY() / p1.getZ()) + e.getZ();
    temp2 = e.getX() * (p2.getX() / p2.getZ()) + e.getY() * (p2.getY() / p2.getZ()) + e.getZ();


    if ( (temp * temp2) > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}


#endif