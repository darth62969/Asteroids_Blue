#include <mode.h>
#include <iostream>


mode::mode(std::string path)
{
	file = fileHandler(path);

	value a = file.findValue("maxLevel");
	switch(a.type)
	{
		case 1:
			maxlevel = a._int;
		default:
			std::cout << "Error: Return Type Not Int\n";
	}
	a = file.findValue("Object");
	switch(a.type)
	{
		case 0:
			if (string("Asteroid").compare(a.name))
			{
				objects = objects | 1;
			}
		default:
			std::cout << "Error: Return Type Not String\n";
	}
	


}