#ifndef MY_CIRCLE_HPP
#define MY_CIRCLE_HPP

#include "point.hpp"
#include <vector>
#include <cmath>
#include <iostream>


#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406


template<typename T>
class myCircle{
	myPoint<T> center;
	std::vector<myPoint<T>> nPoints;
	T r;
	int splt = 0;

public:
	
	//initialized with 0
	myCircle() : center.setX(0), center.setY(0), r(1)
	{}

	//initialized with myPoints
	myCircle(const myPoint<T> rhs, T r){
		center = rhs;
		this.r = r
	}

	//initialized with myPoints and split n
	myCircle(const myPoint<T> rhs, T r, GLint n){
		center = rhs;
		this->r = r
		this->split(n);
	}

	//initialized with Tx,Ty
	myCircle(T x, T y ,T r){
		center.setX(x);
		center.setY(y);
		this->r = r;
	}

	//initialized with Tx,Ty
	myCircle(T x, T y ,T r, GLint n){
		center.setX(x);
		center.setY(y);
		this->r = r;
		this->split(n);
	}


	void setR(const T& rhs){
		r = rhs;
	}

	//draw the circle
	void inline draw(){
		glBegin(GL_LINE_LOOP);
			for (int i = 0; i < 360; i++){
				GLdouble x = center.getX() + r * cos(i * degToRad(1));
				GLdouble y = center.getY() + r * sin(i * degToRad(1));
				glVertex2d(x, y);
			}
		glEnd();
	}

	//draw the center point
	void inline drawCenter(){
		glBegin(GL_POINTS);
			glVertex2d(center.getX(), center.getY());
		glEnd();
	}

	void inline drawSplitted(){
		glBegin(GL_LINE_LOOP);

		for(auto vec : nPoints){
			glVertex2d(vec.getX(), vec.getY());
		}

		glEnd();
	}

	//split the circle to n equals part
	void inline split(GLint n){
		nPoints.clear();
		splt = n;
		for (int i = 0; i < n; i++){
			nPoints.push_back(myPoint<GLdouble>(center.getX() + r*cos(i* degToRad(360 / (double)n)), center.getY() + r*sin(i* degToRad(360 / (double)n))));
		}
	}

	//draw split points
	void inline drawSplit(){
		glBegin(GL_POINTS);
			for (auto i : nPoints){
				glVertex2d(i.getX(), i.getY());
			}
		glEnd();
	}

	//draw all diagonals
	void inline drawDiagonals(){
		glBegin(GL_LINES);
		for (int i = 0; i < nPoints.size(); i++)
			for (int j = i + 1; j < nPoints.size(); j++){
				glVertex2d(nPoints.at(i).getX(), nPoints.at(i).getY());
				glVertex2d(nPoints.at(j).getX(), nPoints.at(j).getY());
			}
		glEnd();
	}

	GLdouble static degToRad(GLint a){
		return PI * a / 180;
	}

	void inline drawEvolvent(){
		glPointSize(1);
		glBegin(GL_POINTS);
		std::cout << splt << std::endl;
		for (int j = 0; j < splt; j++)
		{
			GLdouble rotate = j * degToRad(360 / (double)splt);

			for (int i = 0; i < 50; i++){
				GLdouble tempRad = degToRad(i);
				GLdouble tempX = center.getX() + r * (cos(tempRad + rotate) + tempRad * sin(tempRad + rotate));
				GLdouble tempY = center.getY() + r * (sin(tempRad + rotate) - tempRad * cos(tempRad + rotate));
				glVertex2d(tempX, tempY);
			}
		}
		glEnd();
	}

};


#endif