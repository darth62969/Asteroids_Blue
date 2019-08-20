#ifndef _FILE_HANDLER_H_
#define _FILE_HANDLER_H_

#include <fstream>
#include <string>
#include <stack>
#include <queue>
#include "asteroid.h"
#include "ship.h"
#include "bullet.h"
#include "structs.h"
#include "globals.h"

/**
 * DEPRECIATED
 * Orginal intention was to develop a scripting language.
 * Now Dynamic Libraries are the main.
 */

class fileHandler
{
	public:
		explicit fileHandler(std::string in);
		explicit fileHandler();
		
		int executeNext();

		value findValue(std::string key);
		int setAfterValue(std::string Key);

		int readFile(std::string in);

	private:
		std::fstream file;
		std::stack<int> stk;
		std::queue<int> instructionSet;
		int type;

		std::queue<std::string> breakLine(std::string line);





};

#endif