#ifndef STRUCTS_H
#define STRUCTS_H

class point{

private: 
struct point
{
	double x
	double y
	double z
}

public:
point(double x, double y, double z);
void structs::setX(double x);
void structs::setY(double y);
void structs::setZ(double z);
void structs::set(double x, double y, double z);
double structs::getX();
double structs::getY();
double structs::getZ();
double[3] structs::get();



}
class triangle {

private:
struct triangle{
	point a;
	point b;
	point c;
}

public:
triangle();
void setA(point a);
void setB(point a);
void setC(point a);
void set(point a, point b, point c);
point getA();
point getB();
point getC();
point[3] triangle::get();

}

class triangleArray
{
public:
	triangle triangleArray::at(int idx); // gets triangle at index
	triangle 
	

}


#include "structs.cpp"

#endif
