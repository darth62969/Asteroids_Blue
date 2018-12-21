#ifndef __FIGHTER_H__
#define __FIGHTER_H__

#include "ship.h"

class fighter : public ship
{
	public:
		fighter();
		void fire();
		void doAction();

	private:
		int cycle = 0;


};


#endif