#ifndef STRUCTS
#define STRUCTS

#include <vector>

struct point{
    GLfloat x, y, z, w;
}

struct triangle{
    point a, b, c;    
}

struct asteriod{
    float rotation;
    point translation;
    vector <points> astPnts;
    bool clipped;
}


struct ship{
    triangle body;
    GLfloat rotation;
}

struct bullet{
    point p;
    point pTranslation;
}

#endif
