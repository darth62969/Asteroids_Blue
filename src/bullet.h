#ifndef __BULLETS__
#define __BULLETS__

#include <vector>
#include "structs.h"
#include "object.h"

class bullet : public object
{
	public:
		explicit bullet();
		explicit bullet(std::vector<point> pnts, int dmg, double vel);
		void doAction();
		void render();
		bullet* fireBullet(double x, double y, double angle);
		
		vector<point> getBounds();
		int getDamage();
		point getLocation();

	private:
		int damage;
		point location;
		object* clone() const {return new bullet(*this);};
};

#endif