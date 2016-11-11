
#ifndef __ASTEROID_H_INCLUDED__
#define __ASTEROID_H_INCLUDED__

#include "structs.h"

class asteroid
{
	public:
        explicit asteroid();
		std::vector<asteroid> breakupAsteroid();
		std::vector<point> getPoints();
		std::vector<triangle> getTess();

	private:
	    float rotation;
        point translation;
    	std::vector<point> astPnts;
    	std::vector<triangle> astTris;
    	bool clipped;
        int numsides;
        //asteroid createAsteroid(triangle a);
		//triangle * triptr;
		//triangle * nexttriptr;
		// point origin;

	    void tessilateAsteriod();	



};
#endif
