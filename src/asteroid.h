#ifndef __ASTEROID_H_INCLUDED__
#define __ASTEROID_H_INCLUDED__

#include "structs.h"

class asteroid
{
	public:
        	explicit asteroid();
		point getCenter();
		std::vector<asteroid> breakupAsteroid();
		std::vector<point> getPoints();
		std::vector<triangle> getTess();
		float getRotation();
		void incrementLocation();
		void setPoints(std::vector<point> v);

	private:
		point center;
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
		void sortPoints();
};
#endif
