
#ifndef __ASTEROID_H_INCLUDED__
#define __ASTEROID_H_INCLUDED__

#include "structs.h"

class asteroid
{
	public:
        explicit asteroid();
		std::vector<asteroid> breakupAsteroid();


	private:
	    float rotation;
        point translation;
    	std::vector<point> astPnts;
    	std::vector<triangle> astTris;
    	bool clipped;
        int numsides;
		int max_x;
	    int max_y;
        //asteroid createAsteroid(triangle a);
		//triangle * triptr;
		//triangle * nexttriptr;
		// point origin;

	    asteroid tessilateAsteriod();	



};
#endif
