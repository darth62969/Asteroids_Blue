#include "fileHandler.h"
#include <iostream>
#include <unistd.h>
#include <stdio.h>

fileHandler::fileHandler(std::string in)
{
	char buff[FILENAME_MAX];
	getcwd(buff, FILENAME_MAX);
	string CurrentDirectory(buff);
	std::cout << in << ' '<< CurrentDirectory << endl;
	file.open(in.c_str(), std::fstream::in);
	std::cout << file.good() << endl;
	if(file)
	{
		std::string temp;
		getline(file,temp);
		std::string line[3];
		line[0]=temp.substr(0, temp.find_first_of(' '));
		line[1]=temp.substr(temp.find_first_of(' ')+1, temp.find_last_of(' '));
		line[2]=temp.substr(temp.find_last_of(' '));

		if (line[0].compare("Mode")==0)
		{
			type=0;
			std::cout << "found type Mode\n";
		} 
		if (line[0].compare("Ship")!=0)
		{
			type=1;
			std::cout << "found type Ship\n";
		} 

		
	}
}
int fileHandler::executeNext()
{
	switch(type)
	{
		case 0:
			std::string temp;
			stk.push(file.tellg());
			getline(file,temp);
			std::cout << temp  << std::endl;
			if (temp.size()<=1)
			{
				stk.pop();
				executeNext();
			}
			std::queue<std::string> que;
			int thing;
			while(true)
			{
				que.push(temp.substr(0, temp.find_first_of(" ")));
				std::cout << que.back() << std::endl;
				thing = temp.find_first_of(" ");
				temp=temp.substr(thing+1);
				if(thing==std::string::npos) break;
				

			}
			
			
			if (que.front().compare(0, 5,"Object")==0)
			{
				std::cout << "found Object\n";
				instructionSet.push(0);
				que.pop();
				std::cout << que.front().c_str() << std::endl << 
					que.front().compare(0,8, "Asteroid") << std::endl;

				if (que.front().compare(0, 8, "Asteroid")==0)
				{
					std::cout << "found Asteroid\n";
					instructionSet.push(0);
					que.pop();
				}
			}

			
	while(!instructionSet.empty())
	{
		std::string temp;
		getline(file, temp);
		std::queue<std::string> que;
		int thing;
		while(true)
		{
			que.push(temp.substr(0, temp.find_first_of(" ")));
			std::cout << que.back() << std::endl;
			thing = temp.find_first_of(" ");
			temp=temp.substr(thing+1);
			if(thing==std::string::npos) break;
		}
		switch(instructionSet.front())
		{
			instructionSet.pop();
			case 0:
				switch (instructionSet.front())
				{
					instructionSet.pop();
					case 0:
						if (que.front().compare(1,8,"Generate"))
						{
							que.pop();
							int Generate =std::stoi(que.front(), nullptr, 10);
							for(int i =0; i < Generate ; i++)
							{
								std::cout << "Asteroid" << std::endl;
								asteroid a = asteroid();
								asteroidBelt.push_back(a);
							}
							if(!file.eof())
							{
								std::cout << "Not End Of File\n";
								instructionSet.push(0);
								instructionSet.push(0);
							}
							
						}
						std::cout << instructionSet.empty();
				}

		}
	}

			
			

	}




	return 0; 					// Return 0 if Successfull;


	return -1; 					// Return -1 if Failed;

	return 1 ; 					// return 1 if done;
}

/*
int main(int argc, char** argv)
{
	fileHandler file = fileHandler("Normal.mode");
}*/