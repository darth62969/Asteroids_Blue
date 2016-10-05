#ifndef __STRUCTS_H_INCLUDED__
#define __STRUCTS_H_INCLUDED__

#include "stucts.h"


class asteroid.h
{
    public:
        asteroid asteroid::createAsteroid();
        asteroid asteroid::createAsteroid(triangle a);

    private:
        triangle * triptr;
        triangle * nexttriptr;
        point * origin;
        int numsides;
}

#endif