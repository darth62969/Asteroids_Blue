#include "mode.h"
#include <iostream>


mode::mode(std::string path)
{
	file = fileHandler(path);

	value a = file.findValue("MaxLevel");
	switch(a.type)
	{
		case 1:
			maxlevel = a._int;
			std::cout << "Value: type = " << a.type << " name = "
				<< a.name << " _int = " << a._int << std::endl;
			break;
		default:
			std::cout << "Error: Return Type Not Int\n";
			std::cout << "Value: type = " << a.type << " name = "
				<< a.name << " _int = " << a._int << std::endl;
			break;
	}
	
	file.setAfterValue("MaxLevel");

	a = file.findValue("Object");
	
	switch(a.type)
	{
		case 0:
			if (string("Asteroid").compare(a.name))
			{
				objects = objects | 1;
			}
			break;
		default:
			std::cout << "Error: Return Type Not String\n";
			break;
	}


}
void mode::generateLevel()
{

}

void mode::generateObjects()
{

}

bool mode::checkWinConditions()
{
	/* 
	 * 
	 * getState(what, )
	 * 
	 * 
	 */
}