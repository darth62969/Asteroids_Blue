#ifndef STRUCTS
#define STRUCTS

struct point
{
    float x, y, z, w, angle ;
};

struct triangle
{
    point a, b, c;
};

struct value
{
	int type;
	char* name;
	int _int;
	double _double;
	short fail;
};
struct condition
{
	int condition;
	value a;
	value b;
	
	
};

struct color
{
	double red;
	double green;
	double blue;
	double alpha;
};

#endif
