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
<<<<<<< HEAD
    vector<point> astPnts;
    vector<triangle> astTris;
=======
    std::vector<point> astPnts;
    std::vector<triangle> astTris;
>>>>>>> 6f3f8e3cec2b25a9b0eaa7faac6c3067d7588bd2
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
