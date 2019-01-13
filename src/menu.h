#include <vector>
#include <string>
#include "structs.h"

struct menu
{
	std::vector<menuItem> menuOpt;
	std::string name;
		
};


struct menuItem
{
	std::string name;
	value v;
};