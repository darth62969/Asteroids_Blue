#ifndef _MODE_H_
#define _MODE_H_

#include "headers.h"
#include "globals.h"
#include "object.h"
#include "asteroid.h"
#include "ship.h"
#include <vector>

class mode
{
	public:
		mode();							// Default Asteroids Mode;
		virtual int step(); 			// Increments mode, runs checkes for level clear and moves objects if needed. 
										// returns 1 if mode won 2 if lost;
		virtual void generateLevel();	// Generates objects and places them onScreen;
		virtual void init();			// 

		virtual std::vector<object*> getOnScreen(); 
		void addToOnScreen(object* obj);


	protected:
		std::vector<object*> onScreen;	// collection of objects for the mode that are displayed onScreen;
		int level = 1;					// current level, default 1;
		int stp = 0;					// current step, used to keep track of frames;
		int maxLevel;					// Maximum level posible in mode, SET THIS!!;


				

};

#endif