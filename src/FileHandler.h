#ifndef _FILE_HANDLER_H_
#define _FILE_HANDLER_H_

#include <fstream>
#include <string>
#include <stack>
#include "asteroid.h"
#include "ship.h"
#include "bullet.h"
#include "structs.h"


class fileHandler
{
	public:
		explicit fileHandler(std::string in);
		int executeNext();
		int readFile(std::string in);
	private:
		std::fstream file;
		std::stack<int>  stk;
		int type;





};

#endif