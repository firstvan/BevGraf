#ifndef POINTS_HPP
#define POINTS_HPP

#include <GL/glut.h>

class myPoint{
	GLdouble x, y;

public:
	//pont inicializálása
	myPoint() : x(0), y(0){}

	//pont létrehozása x,y pontban
	myPoint(GLdouble rhsX, GLdouble rhsY) : x(rhsX), y(rhsY)
	{}

	//másoló konstruktor
	myPoint(myPoint& rhs){
		x = rhs.getX();
		y = rhs.getY();
	}

	//másoló értékadás
	/*myPoint& operator=(const myPoint& rhs){
	if (this != &rhs)
	{
	this->setX(rhs.getX());
	this->setY(rhs.getY());
	}

	}*/

	//x visszatérítése
	GLdouble getX() const{
		return x;
	}

	//y visszatérítése
	GLdouble getY() const{
		return y;
	}

	//x beállítása
	void setX(GLdouble& rhsx){
		x = rhsx;
	}

	//y beállytása
	void setY(GLdouble& rhsy){
		y = rhsy;
	}

	//pont kirajzolása
	void display() const{
		glBegin(GL_POINTS);
		glVertex2d(x, y);
		glEnd();
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



};



#endif