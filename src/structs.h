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
/*
struct asteriod
{
    float rotation;
    point translation;
    std::vector<point> astPnts;
    std::vector<triangle> astTris;
    bool clipped;
};
*/
struct ship
{
    triangle body;
    float rotation;
};

struct bullet
{
    float theta;
    point location;
    point translation;
    
};

#endif
