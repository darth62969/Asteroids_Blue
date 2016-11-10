<<<<<<< HEAD
=======
#ifndef __ASTEROID_H_INCLUDED__
#define __ASTEROID_H_INCLUDED__

>>>>>>> 6f3f8e3cec2b25a9b0eaa7faac6c3067d7588bd2
#include "headers.h"
#include "structs.h"

class asteroid
{
	public:
        	asteroid createAsteroid();
		asteroid breakupAsteroid(asteroid a);

<<<<<<< HEAD
	private:
		//triangle * triptr;
		//triangle * nexttriptr;
		// point origin;
        	int numsides;
		int max_x;
	    	int max_y;
        	//asteroid createAsteroid(triangle a);
	    	asteroid tessilateAsteriod();	
=======
    private:
        float rotation;
        point translation;
        point origin;
        std::vector<point> astPnts;
        std::vector<triangle> astTris;
        bool clipped;
        int numsides;
	    int max_x;
	    int max_y;
        //asteroid createAsteroid(triangle a);
	    asteroid tessilateAsteriod();
	
>>>>>>> 6f3f8e3cec2b25a9b0eaa7faac6c3067d7588bd2
};
