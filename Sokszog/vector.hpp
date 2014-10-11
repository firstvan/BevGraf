#ifndef VECTOR_HPP
#define VECTOR_HPP

template<typename T>
class myVector{
	T x, y;
public:

	myVector() : x(0), y(0)
	{}

	myVector(T rhsx, T rhsy) : x(rhsx), y(rhsy)
	{}

	~myVector(){}
	
	T getX(){
		return x;
	}

	T getY(){
		return y;
	}

	void setX(T rhs){
		x = rhs;
	}

	void setY(T rhs){
		y = rhs;
	}

	double length(){
		return std::hypot(x, y);
	}


	double length2(){
		return x * x + y * y;
	}

	myVector<T> operator*(T a){
		return myVector<T>(x * a, y * a);
	}

	myVector<T> operator+(myVector<T> rhs){
		return myVector<T>(x + rhs.getX(), y + rhs.getY());
	}

	friend T multiply(myVector<T>& a, myVector<T>& b){
		return (a.getX() * b.getX() + a.getY() * b.getY());
	}

	friend myVector<T> snap(myVector<T> &a, myVector<T> &b){
		GLdouble c = 2 * (multiply(a, b) / multiply(a,a));
		myVector tx (a * -1);
		myVector ty (b * c);

		return myVector<T>(tx + ty);
	}

};



#endif