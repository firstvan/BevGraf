#ifndef POINTS_HPP
#define POINTS_HPP

#include <GL/glut.h>
#include <math.h>
#include "vector.hpp"

template<typename T>
class myPoint{
	T x, y;

public:
	//pont inicializálása
	myPoint() : x(0), y(0){}

	//pont létrehozása x,y pontban
	myPoint(T rhsX, T rhsY) : x(rhsX), y(rhsY)
	{}

	//másoló konstruktor
	myPoint(myPoint& rhs){
		x = rhs.getX();
		y = rhs.getY();
	}


	//x visszatérítése
	T getX() const{
		return x;
	}

	//y visszatérítése
	T getY() const{
		return y;
	}

	//x beállítása
	void setX(T& rhsx){
		x = rhsx;
	}

	//y beállytása
	void setY(T& rhsy){
		y = rhsy;
	}

	void change( myVector<T> rhs){
		x += rhs.getX();
		y += rhs.getY();
	}

	//pont kirajzolása
	void display() const{
		glBegin(GL_POINTS);
		glVertex2d(x, y);
		glEnd();
	}

	void incX(){
		x++;
	}

	void incY(){
		y++;
	}

	void decX(){
		x--;
	}

	void decY(){
		y--;
	}

	void add(T rhsX, T rhsY){
		x += rhsX;
		y += rhsY;
	}

	void sub(T rhsX, T rhsY){
		x -= rhsX;
		y -= rhsY;
	}

	// pontok egyenlõség vizsgálata
	bool operator==(myPoint& rhs) const{
		if (this->getX() == rhs.getX() && this->getY() == rhs.getY())
			return true;
		return false;
	}

	//pont számmal való szorzása
	myPoint operator*(const double rhs) const{
		return myPoint(rhs*this->getX(), rhs*this->getY());
	}

	//pontok összeadása
	myPoint operator+(const myPoint& rhs){
		return myPoint(this->getX() + rhs.getX(), this->getY() + rhs.getY());
	}

	double lineDistance2(const myPoint& a1, const myPoint& a2){
		GLdouble x = a1.getY() - a2.getY();
		GLdouble y = a2.getX() - a1.getX();
		GLdouble c = x * a1.getX() + y * a1.getY();

		return pow(fabs(x * this->getX() + y * this->getY() - c), 2) / (pow(x, 2) + pow(y, 2));
	}


	double lineDistance(const myPoint& a1, const myPoint& a2){
		GLdouble x = a1.getY() - a2.getY();
		GLdouble y = a2.getX() - a1.getX();
		GLdouble c = (a1.getY() - a2.getY()) * a1.getX() + (a2.getX() - a1.getX()) * a1.getY();

		return abs(x * this->getX() + y * this->getY() - c) / sqrt(x * x + y * y);
	}


};



#endif