#ifndef __BULLETS__
#define __BULLETS__

#include <vector>
#include "structs.h"

class bullet
{
	public:
		explicit bullet();
		explicit bullet(std::vector<point> pnts, int dmg, double vel);
		bullet createBullet(int x, int y, double rot);
		void increment();
		void drawBullet();
		
		int getDamage();
		point getLocation();



	private:
		int damage;
		
		point location;

		std::vector<point> bltPnts;
		std::vector<triangle> bltTris;

		void tesselate();

};

#endif