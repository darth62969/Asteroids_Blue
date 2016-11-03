#ifndef STRUCTS
#define STRUCTS

#include "headers.h"

struct point
{
    float x, y, z, w;
};

struct triangle
{
    point a, b, c;    
};

struct asteriod
{
    float rotation;
    point translation;
    std::vector<point> astPnts;
    std::vector<triangle> astTris;
    bool clipped;
};

struct ship
{
    triangle body;
    float rotation;
};

struct bullet
{
    point location;
    point translation;
};

#endif
