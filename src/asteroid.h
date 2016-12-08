/* 
 * Asteroid Class Header for Asteroids: RETURN OF METEOR
 * 
 * Made by:
 * Jonathan Oakes
 * Braeden Brettin
 * Ted Dorfeuille 
 * Chris Le
 * Emily Herron
 * 
 * for the Class:
 * Intro to Computer Graphics (CSC315)
 * 
 * At:
 * Mercer Univercity  
 */

#ifndef __ASTEROID_H_INCLUDED__
#define __ASTEROID_H_INCLUDED__

#include "structs.h"
#include <vector>

class asteroid
{
	public:
        explicit asteroid();
		explicit asteroid(triangle a, point location, point offset, int num, float Orotation);
		point getCenter();
		std::vector<asteroid> breakupAsteroid();
		std::vector<point> getPoints();
		std::vector<point> getRealPoints();
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
		void createAsteroid(triangle a, point center, point offset, int num);
	   	void tessellateAsteriod();
		void sortPoints();
		void clear();
};
#endif

