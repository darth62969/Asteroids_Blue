#ifndef _MODE_H_
#define _MODE_H_

#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include "asteroid.h"
#include "ship.h"
#include "bullet.h"
#include "structs.h"
#include "globals.h"
#include "FileHandler.h"

/* | r | r | S | A |
 * 
 */

class mode
{
	public:
		explicit mode(std::string path);
		void generateLevel();
		void generateObjects();
		bool checkWinConditions();
		

		

	private:
		fileHandler file;
		char* name;
		map<std::string, value> constants;
		int maxlevel;
		int curLevel;
		vector<condition> winConditions;
		short objects;


};

#endif