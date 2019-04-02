#ifndef __endless_H__
#define __endless_H__

#include "mode.h"
#include "headers.h"


typedef class object;


class endless : public mode
{
	public:
		endless();							// Default Asteroids Mode;
		int step(); 			// Increments mode, runs checkes for level clear and moves objects if needed. 
										// returns 1 if mode won 2 if lost;
		void generateLevel();	// Generates objects and places them onScreen;
		void init();			// 

		//std::vector<object *> getOnScreen(); 
		//std::vector<std::shared_ptr<object>> getOnScreen2(); 
		//void addToOnScreen(object * obj);
		//void addToOnScreen(std::shared_ptr<object> obj);

		void drawLevel();
		void drawObjects();
		void drawScore();
		void drawAll();

		std::string getName();

		void keyboardFunc(char key, int x, int y);
		void mouseFunc(int button, int state, int x, int y);
		void passiveMouseFunc(int x, int y);

		object * player;
		std::mt19937_64 generator;

	protected:
		//std::vector<object *> onScreen;	// collection of objects for the mode that are displayed onScreen;
		//std::vector<std::shared_ptr<object>> onScreen2;	// collection of objects for the mode that are displayed onScreen;
		int level = 1;					// current level, default 1;
		int stp = 0;					// current step, used to keep track of frames;
		int maxLevel;					// Maximum level posible in mode, SET THIS!!;
		int bulletsHit = 0;
		//std::string name;

	private:
//		int bulletsHit = 0;
		int numAsteroids;


				

};

#endif