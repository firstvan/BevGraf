#include "vector.hpp"
#include "point.hpp"
#include <vector>
#include <math.h>

template<typename T>
class mySlider{
	myPoint<T> p1;
	myPoint<T> p2;
	T part;
	myPoint<T> clicks[3];
	std::vector<myPoint<T>> points;
	GLint current = 0;
	T start = 0, end = 0, interval = 0;
	T value[3];
	


public:

	mySlider<T>()
	{
		p1 = new myPoint();
		p2 = new myPoint();
		part = 0;
		click = new myPoint();
	}

	mySlider<T>(myPoint<T> rp1, myPoint<T> rp2, T strt, T nd, T pr = 0){
		p1 = rp1;
		p2 = rp2;
		part = pr;
		start = strt;
		end = nd;
		interval = end - start;

		GLdouble x = static_cast<GLdouble>(sqrt(p1.pointDis2(p2)) / part);

		if (rp2.getY() - rp1.getY() == 0){
			for (int i = 1; i < part; i++){
				points.push_back(myPoint<T>(static_cast<T>(p1.getX() + i * x), p1.getY()));
			}
		}
		else if (rp2.getX() - rp1.getX() == 0){
			for (int i = 1; i < part; i++){
				points.push_back(myPoint<T>(p1.getX(), static_cast<T>(p1.getY() + i * x)));
			}
		}

		clicks[0] = myPoint<T>(p1.getX() + x, p1.getY());
		clicks[1] = myPoint<T>(p1.getX() + 2 * x, p1.getY());
		clicks[2] = myPoint<T>(p1.getX() + 3 * x, p1.getY());

		value[0] = -1;
		value[1] = 0;
		value[2] = 1;

	}

	myPoint<T> getClick(int w) const{
		return clicks[w];
	}

	GLint getCurrentPosition(int w){
		return current + start;
	}

	T getValue(int w){
		return value[w];
	}

	void setClickX(int w, T rhs){
		if (rhs > p1.getX() && p2.getX() > rhs)
		{
			clicks[w].setX(rhs);
			double x = (static_cast<double>(clicks[w].getX() - p1.getX()) / ((p2.getX() - p1.getX()) / static_cast<double>(interval))) + start;
			value[w] = x;
		}
	}
	


	void inline draw(){
		
		if (part > 1){
			glPointSize(10);
			glColor3d(0.0, 0.0, 0.0);
			glBegin(GL_POINTS);
			for (int i = 0; i < part-1; i++){
				glVertex2d(points[i].getX(), points[i].getY());
			}
			glEnd();
			
		}
		
		glPointSize(10);
		glColor3d(0.0, 0.0, 0.0);
		glBegin(GL_POINTS);
			glVertex2d(p1.getX(), p1.getY());
			glVertex2d(p2.getX(), p2.getY());
		glEnd();

		glBegin(GL_LINES);
			glVertex2d(p1.getX(),p1.getY());
			glVertex2d(p2.getX(), p2.getY());
		glEnd();

		glColor3f(0.0, 0.0, 1.0);
		glPointSize(5);
		glBegin(GL_POINTS);
		for (int i = 0; i < 3; i++)
		{
			glVertex2d(clicks[i].getX(), clicks[i].getY());
		}
		glEnd();
	}

	GLdouble dis2Click(T a1, T a2, int w){
		return (a1 - clicks[w].getX()) * (a1 - clicks[w].getX()) + (a2 - clicks[w].getY()) * (a2 - clicks[w].getY());
	}
};