#ifndef POINTS_HPP
#define POINTS_HPP

#include <GL/glut.h>

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