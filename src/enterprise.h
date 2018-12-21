#ifndef __ENTERPRISE_H__
#define __ENTERPRISE_H__

#include "object.h"
#include "ship.h"


class enterprise : public ship
{
	public: 
		/*constructor*/
		enterprise();

		/*actions*/
		void fire();
		void resetShip();

		/*render*/
		void render();
		
	private:
		int endGameAnimeScale = 5;




};

#endif
