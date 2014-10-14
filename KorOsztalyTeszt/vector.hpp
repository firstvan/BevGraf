#ifndef VECTOR_HPP
#define VECTOR_HPP

template<typename T>
class myVector{
	T x, y;
public:

	//inicializ�l�s 0-val;
	myVector() : x(0), y(0)
	{}

	//ir�nyvektor l�trehoz�sa
	myVector(T rhsx, T rhsy) : x(rhsx), y(rhsy)
	{}

	~myVector(){}
	
	//ir�nyvektor x �rt�k�nek visszaad�sa
	T getX(){
		return x;
	}

	//ir�nyvektor y �rt�k�nek visszaad�sa
	T getY(){
		return y;
	}

	//ir�nyvektor x �rt�k�nek be�ll�t�sa
	void setX(T rhs){
		x = rhs;
	}

	//ir�nyvektor y �rt�k�nek be�ll�t�sa
	void setY(T rhs){
		y = rhs;
	}

	//ir�nyvektor hossza (3sz�g �tfog�ja �ltal)
	double length(){
		return std::hypot(x, y);
	}

	//ir�nyvektor hossz n�gyzete
	double length2(){
		return x * x + y * y;
	}

	//ir�nyvektor szorz�sa skal�rral
	myVector<T> operator*(T a){
		return myVector<T>(x * a, y * a);
	}

	//ir�nyvektorok �sszead�sa
	myVector<T> operator+(myVector<T> rhs){
		return myVector<T>(x + rhs.getX(), y + rhs.getY());
	}

	//skal�rszorzat
	friend T multiply(myVector<T> a, myVector<T> b){
		return (a.getX() * b.getX()) + (a.getY() * b.getY());
	}

	//visszapattan�s defini�l�sa
	void snap(myVector<T> a){
		GLdouble c = 2 * multiply(a, *this) / multiply(a,a);
		x = -x + c * a.getX();
		y = -y + c * a.getY();
	}

};



#endif