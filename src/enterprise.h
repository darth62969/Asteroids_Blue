#ifndef __ENTERPRISE_H__
#define __ENTERPRISE_H__

#include "headers.h"
#include "ship.h"

/**
 * DEPRECIATED
 * REMOVED FROM CORE
 */

//enterprise player = new enterprise();

class enterprise : public ship
{
	public: 
		/*constructor*/
		enterprise();

		/*actions*/
		void fire(mode * md);
		void resetShip();

		/*render*/
		void render();
/*
		std::vector<point> getBounds();
        std::vector<point> getPoints();
        std::vector<triangle> getTriangles();
        std::vector<point> getAtkPnts();
        
        //setters
	
		int getHealth();         
		void setHealth(int dmg);
		int getAction();
		void setAction(int act);*/

		int getBulletsFired(){return bulletsFired;};
		
	private:
		int endGameAnimeScale = 5;
		int bulletsFired = 0;




};

#endif
