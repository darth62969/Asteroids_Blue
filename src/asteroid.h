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

#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include "headers.h"
#include "object.h"
#include "prototypes.h"
//#include "globals.h"
#include "windowProperties.h"


class asteroid : public object
{
	public:
        asteroid();
		asteroid(triangle a, point location, point offset, int num, float Orotation);

		point getCenter();
		std::vector<point> getBounds();
		std::vector<point> getPoints();
		//std::vector<point> getRealPoints();
		//std::vector<triangle> getTess();
		std::vector<triangle> getTess2();
		float getRotation();

		std::vector<object *> breakupAsteroid();
		std::vector<std::shared_ptr<object>> breakupAsteroid2();
		//void incrementLocation(mode * );
		void render() override;
		void doAction(mode * md) override;
		

	private:
		point center;
	    	float rotation;
		point translation;
	    	std::vector<point> astPnts;
	    	std::vector<triangle> astTris;
	    	bool clipped;
		int numsides;
		std::vector<asteroid *> getInfluencers(mode * md);
		std::vector<std::shared_ptr<asteroid>> getInfluencers2(mode * md);
		//float getVectorLength(point a, point b);
		//float getVectorLength(asteroid b);*/
		void createAsteroid(triangle a, point center, point offset, int num);
	   	void tessellateAsteriod();
		void sortPoints();
		void clear();
		//asteroid clipAsteroid();
	//	const double ASTERIOD_WEIGHT = 0.4;
	//	const double GRAVITY_POTENTIAL = 1;
};

#endif
