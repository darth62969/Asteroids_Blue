#ifndef __ASTEROID_H_INCLUDED__
#define __ASTEROID_H_INCLUDED__

#include "structs.h"

class asteroid
{
	public:
        explicit asteroid();
		explicit asteroid(triangle a, point location, point offset, int num);
		point getCenter();
		std::vector<asteroid> breakupAsteroid();
		std::vector<point> getPoints();
		std::vector<triangle> getTess();
		float getRotation();
		void incrementLocation();

	private:
		point center;
	    float rotation;
        point translation;
    	std::vector<point> astPnts;
    	std::vector<triangle> astTris;
    	bool clipped;
        int numsides;
        void createAsteroid(triangle a, point center, point offset, int num);
		//triangle * triptr;
		//triangle * nexttriptr;
		// point origin;
	    void tessilateAsteriod();
		void sortPoints();
		void clear();
};
#endif
