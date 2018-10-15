#ifndef _MODE_H_
#define _MODE_H_

#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
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
		void generateObjects();

		

	private:
		fileHander file;
		char* name;
		map<std::string, value> constants;
		int maxlevel;
		vector<condition> winConditions;
		short objects;


};

#endif