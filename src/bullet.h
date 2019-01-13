#ifndef __BULLET_H__
#define __BULLET_H__

#include "headers.h"
#include "object.h"
#include "structs.h"

class bullet : public object
{
	public:
		explicit bullet();
		explicit bullet(std::vector<point> pnts, int dmg, double vel);
		explicit bullet(const bullet& other, point loc);

		void doAction(mode * md);
		void render();
		bullet* fireBullet(double x, double y, double angle);
		std::shared_ptr<bullet> fireBullet2(double x, double y, double angle);
		
		std::vector<point> getBounds();
		int getDamage();
		point getLocation();
		bullet* clone() const {return new bullet(*this);};

	private:
		int damage;
	//	point location;
	//	double velocity;
		
};

#endif