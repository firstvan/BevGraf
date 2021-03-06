#include "vector.hpp"
#include "point.hpp"
#include <vector>
#include <math.h>

template<typename T>
class mySlider{
	myPoint<T> p1;
	myPoint<T> p2;
	T part;
	myPoint<T> click;
	std::vector<myPoint<T>> points;
	GLint current = 0;
	GLint start = 0, end = 0 , length = 0;


public:

	mySlider<T>()
	{
		p1 = new myPoint();
		p2 = new myPoint();
		part = 0;
		click = new myPoint();
	}

	mySlider<T>(myPoint<T> rp1, myPoint<T> rp2, T pr = 0){
			p1 = rp1;
			p2 = rp2;
			part = pr;
			click = p1;
			T x = sqrt(p1.pointDis2(p2)) / part;

			if (rp2.getY() - rp1.getY() == 0){
				for (int i = 1; i < part; i++){
					points.push_back(myPoint<T>(p1.getX() + i * x, p1.getY()));
				}
			}
			else if (rp2.getX() - rp1.getX() == 0){
				for (int i = 1; i < part; i++){
					points.push_back(myPoint<T>(p1.getX() , p1.getY() + i * x));
				}
			}
			
	}

	mySlider<T>(myPoint<T> rp1, myPoint<T> rp2, T start, T end, T pr){
		p1 = rp1;
		p2 = rp2;
		part = pr;
		click = p1;
		this.start = start;
		this.end = end;
		length = end - start;

		T x = sqrt(p1.pointDis2(p2)) / part;

		if (rp2.getY() - rp1.getY() == 0){
			for (int i = 1; i < part; i++){
				points.push_back(myPoint<T>(p1.getX() + i * x, p1.getY()));
			}
		}
		else if (rp2.getX() - rp1.getX() == 0){
			for (int i = 1; i < part; i++){
				points.push_back(myPoint<T>(p1.getX(), p1.getY() + i * x));
			}
		}

	}



	myPoint<T> getClick() const{
		return click;
	}

	GLint getCurrentPosition(){
		return current;
	}

	void setClickX(T rhs){
		if (rhs > p1.getX() && rhs < p2.getX())
		{
			if (part == 0){
				click.setX(rhs);
			}
			else{
				GLdouble mind = abs(p1.getX() - rhs);
				GLint elem = -1;

				if (mind > abs(p2.getX() - rhs)){
					mind = abs(p2.getX() - rhs);
					elem = part + 1;
				}

				for (int i = 0; i < part - 1; i++){
					if (mind > abs(points[i].getX() - rhs)){
						mind = abs(points[i].getX() - rhs);
						elem = i;
					}
				}

				if (elem == -1)
				{
					T temp = p1.getX();
					click.setX(temp);
					current = 0;
				}
				else if (elem == part + 1){
					T temp = p2.getX();
					click.setX(temp);
					elem = part;
				}
				else{
					T temp = points[elem].getX();
					click.setX(temp);
					current = elem + 1;
				}
			}
		}
	}
	
	void setClickY(T rhs){
		if (rhs > p1.getY() && rhs < p2.getY())
		{
			if (part == 0){
				click.setY(rhs);
			}
			else{
				GLdouble mind = abs(p1.getY() - rhs);
				GLint elem = -1;

				if (mind > abs(p2.getY() - rhs)){
					mind = abs(p2.getY() - rhs);
					elem = part + 1;
				}

				for (int i = 0; i < part - 1; i++){
					if (mind > abs(points[i].getY() - rhs)){
						mind = abs(points[i].getY() - rhs);
						elem = i;
					}
				}

				if (elem == -1)
				{
					T temp = p1.getY();
					click.setY(temp);
					current = 0;
				}
				else if (elem == part + 1){
					T temp = p2.getY();
					click.setY(temp);
					elem = part;
				}
				else{
					T temp = points[elem].getY();
					click.setY(temp);
					current = elem + 1;
				}
			}
		}
	}

	void inline draw(){
		
		if (part > 1){
			glPointSize(3);
			glBegin(GL_POINTS);
			for (int i = 0; i < part-1; i++){
				glVertex2d(points[i].getX(), points[i].getY());
			}
			glEnd();
			
		}
		
		glPointSize(3);
		glBegin(GL_POINTS);
			glVertex2d(p1.getX(), p1.getY());
			glVertex2d(p2.getX(), p2.getY());
		glEnd();

		glPointSize(10);
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_POINTS);
			glVertex2d(click.getX(), click.getY());
		glEnd();
		
		glBegin(GL_LINES);
			glVertex2d(p1.getX(),p1.getY());
			glVertex2d(p2.getX(), p2.getY());
		glEnd();
	}

	GLdouble dis2Click(T a1, T a2){
		return (a1 - click.getX()) * (a1 - click.getX()) + (a2 - click.getY()) * (a2 - click.getY());
	}
};