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

#ifndef SHIPTEST
struct ship
{
    triangle body;
    float rotation;
    point aLocation;
};


struct bullet
{
    float theta;
    point location;
    point translation;
    
};
#endif
#endif
