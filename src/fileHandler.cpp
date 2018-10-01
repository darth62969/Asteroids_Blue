#include "fileHandler.h"

fileHandler::fileHandler(std::string in)
{
	file.open(in.c_str(), std::fstream::in);
	if(file)
	{
		std::string temp;
		getline(file,temp);
		std::string line[3];
		line[0]=temp.substr(0, temp.find_first_of(' '));
		line[1]=temp.substr(temp.find_first_of(' '), temp.find_last_of(' '));
		line[2]=temp.substr(temp.find_last_of(' '), temp.end);

		if (line[0].compare("Mode")) type=0;
		if (line[0].compare("Ship")) type=1;
		
	}
}