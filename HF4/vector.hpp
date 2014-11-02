#ifndef VECTOR_HPP
#define VECTOR_HPP

template<typename T>
class myVector{
	T x, y;
public:

	//inicializálás 0-val;
	myVector() : x(0), y(0)
	{}

	//irányvektor létrehozása
	myVector(T rhsx, T rhsy) : x(rhsx), y(rhsy)
	{}

	~myVector(){}
	
	//irányvektor x értékének visszaadása
	T getX(){
		return x;
	}

	//irányvektor y értékének visszaadása
	T getY(){
		return y;
	}

	//irányvektor x értékének beállítása
	void setX(T rhs){
		x = rhs;
	}

	//irányvektor y értékének beállítása
	void setY(T rhs){
		y = rhs;
	}

	//irányvektor hossza (3szög átfogója által)
	double length(){
		return std::hypot(x, y);
	}

	//irányvektor hossz négyzete
	double length2(){
		return x * x + y * y;
	}

	//irányvektor szorzása skalárral
	myVector<T> operator*(T a){
		return myVector<T>(x * a, y * a);
	}

	//irányvektorok összeadása
	myVector<T> operator+(myVector<T> rhs){
		return myVector<T>(x + rhs.getX(), y + rhs.getY());
	}

	//skalárszorzat
	friend T multiply(myVector<T> a, myVector<T> b){
		return (a.getX() * b.getX()) + (a.getY() * b.getY());
	}

	//visszapattanás definiálása
	void snap(myVector<T> a){
		GLdouble c = 2 * multiply(a, *this) / multiply(a,a);
		x = -x + c * a.getX();
		y = -y + c * a.getY();
	}

};



#endif