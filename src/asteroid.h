#ifndef __STRUCTS_H_INCLUDED__
#define __STRUCTS_H_INCLUDED__

#include "headers.h"

class asteroid
{
    public:
        asteroid createAsteroid();
	    asteroid breakupAsteroid(asteroid a);

    private:
        //triangle * triptr;
        //triangle * nexttriptr;
       // point origin;
        int numsides;
	    int max_x;
	    int max_y;
        //asteroid createAsteroid(triangle a);
	    asteroid tessilateAsteriod();
	
};

#endif
