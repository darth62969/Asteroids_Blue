#ifndef __FIGHTER_H__
#define __FIGHTER_H__

#include "ship.h"

/**
 * DEPRECIATED
 * REMOVED FROM CORE
 */

class fighter : public ship
{
	public:
		fighter();
		void fire(mode * md);
		void doAction(mode * md);

	private:
		int cycle = 0;


};


#endif