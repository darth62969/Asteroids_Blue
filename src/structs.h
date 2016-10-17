#ifndef STRUCTS_H
#define STRUCTS_H

struct asteriod{
    float rotation;
    float translation;
    vector <points> astPnts;
    bool clipped;
}

struct point{
    GLfloat x, y, z, w;
}

struct triangle{
    point a, b, c;    
}

struct ship{
    triangle body;
    vector<bullet> bullets;
    GLfloat rotation;
}

struct bullet{
    point p;
    point pTranslation;
}
#endif
