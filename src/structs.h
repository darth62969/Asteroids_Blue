#ifndef STRUCTS
#define STRUCTS

#include <vector>

struct point
{
    float x, y, z, w;
}

struct triangle
{
    point a, b, c;    
}

struct asteriod
{
    float rotation;
    point translation;
    vector<point> astPnts;
    vector<triangle> astTris;
    bool clipped;
}

struct ship
{
    triangle body;
    float rotation;
}

struct bullet
{
    point location;
    point translation;
}

#endif
