#ifndef MY_CIRCLE_HPP
#define MY_CIRCLE_HPP

#include "point.hpp"

#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406

template<typename T>
class myCircle{
	myPoint<T> center;
	std::vector<myPoint> felosztas;
	T r;

public:
	
	//initialized with 0
	myCircle() : center.setX(0), center.setY(0), r(1)
	{}

	//initialized with myPoints
	myCircle(const myPoint<T> rhs, T r){
		center = rhs;
		this.r = r
	}

	//initialized with Tx,Ty
	myCircle(const T x, const T y , const T r){
		center.setX(x);
		center.setY(y);
		this.r = r;
	}

	void inline draw(){
		glBegin(GL_LINE_LOOP);
			for (int i = 0; i < 360; i++){
				GLdouble x = center.getX() + i * cos(degToRad(1));
				GLdouble y = center.getY() + i * sin(degToRad(1));
				glVector2d(x, y);
			}
		glEnd();
	}

	GLdouble inline friend degToRad(GLint a){
		return PI * a / 180;
	}

};


#endif