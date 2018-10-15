#include "fileHandler.h"
#include <iostream>
#include <exception>
#include <unistd.h>
#include <stdio.h>
#include <regex>

fileHandler::fileHandler(std::string in)
{
	char buff[FILENAME_MAX];
	getcwd(buff, FILENAME_MAX);
	string CurrentDirectory(buff);
	std::cout << in << ' '<< CurrentDirectory << endl;

	readlink("/proc/self/exe", buff, FILENAME_MAX);
	std::cout << buff << endl;

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

		if (line[0].compare(0,4, "Mode")==0)
		{
			type=0;
			//std::cout << "found type Mode\n";
		} 
		if (line[0].compare(0,4, "Ship")==0)
		{
			type=1;
			//std::cout << "found type Ship\n";
		} 

		
	}
}
int fileHandler::executeNext()
{
//	std::cout << "executing next\n" << "type is " << type << std::endl;
	switch(type)
	{
		case 0:
			std::string temp;
			stk.push(file.tellg());
			getline(file,temp);
//			std::cout << temp  << std::endl;
			if (temp.size()<=1)
			{
				stk.pop();
				executeNext();
				return 1;
			}
			std::queue<std::string> que;
			int thing;
			while(true)
			{
				que.push(temp.substr(0, temp.find_first_of(" ")));
//				std::cout << que.back() << std::endl;
				thing = temp.find_first_of(" ");
				temp=temp.substr(thing+1);
				if(thing==std::string::npos) break;
				

			}
			
			
			if (que.front().compare(0, 6,"Object")==0)
			{
				//std::cout << "found Object\n";
				instructionSet.push(0);
				que.pop();
				//std::cout << que.front().c_str() << std::endl << 
				//	que.front().compare(0,8, "Asteroid") << std::endl;

				if (que.front().compare(0, 8, "Asteroid")==0)
				{
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
			if(temp.at(0)=='\t') temp=temp.substr(1);
			que.push(temp.substr(0, temp.find_first_of(" ")));
			thing = temp.find_first_of(" ");
			temp=temp.substr(thing+1);
			if(thing==std::string::npos) break;
		}
		cout << instructionSet.empty() << endl;
		switch(instructionSet.front())
		{
			instructionSet.pop();
			case 0:
				switch (instructionSet.front())
				{
					instructionSet.pop();
					case 0:
				
						string a = que.front();
				
						if (a.compare("Number")==0)
						{
							cout<<  que.front() << endl;
							que.pop();
							int Generate =std::stoi(que.front(), nullptr, 10);
							for(int i =0; i < Generate ; i++)
							{
								//std::cout << "Asteroid" << std::endl;
								asteroid a = asteroid();
								asteroidBelt.push_back(a);
							}
						}
						if(!file.eof())
						{
				
							instructionSet.push(0);
							instructionSet.push(0);
						}
							
				
				
				}

		}
		break;
	}

			
			

	}




	return 0; 					// Return 0 if Successfull;


	return -1; 					// Return -1 if Failed;

	return 1 ; 					// return 1 if done;
}

value fileHandler::findValue(string key)
{
	stk.push(file.tellg());
	file.seekg(0);
	value rtv;
	std::string line;
	std::smatch matcher;
	std::regex num ("[0-9]");
	std::regex dot ("[\.]");
	std::regex alpha("[a-z]");
	std::regex ALPHA("[A-Z]");

	while (file.good())
	{
		getline(file, line);
		std::queue<std::string> que = breakLine(line);
		switch(que.front().compare(key))
		{
			que.pop();
			case 0:
				std::string a = que.front();
				if(!std::regex_search(a, matcher, alpha) && !std::regex_search(a, matcher, ALPHA))
				{
					if(std::regex_search(a, matcher, num))
					{
						if(std::regex_search(a, matcher, dot))
						{
							rtv.type = 2;
							rtv._double = stod(a);
						}
						else
						{
							rtv.type = 1;
							rtv._int = stoi(a);
						}
					}
				}
				else
				{
					rtv.type = 0;
					rtv.name = (char*)a.c_str();
				}
				file.setstate(ios::eofbit);
				break;
		}

	}
	file.seekg(stk.top());
	stk.pop();
	return rtv;
}

int setAfterValue(std:string key)
{
	stk.push(file.tellg());
	file.seekg(0);
	std::string line;
	bool found = false;

	while (file.good())
	{
		getline(file, line);
		std::queue<std::string> que = breakLine(line);
		switch(que.front().compare(key))
		{
			que.pop();
			case 0:
				file.setstate(ios::eofbit);
				found =true;
				break;
		}

	}
	file.setstate(ios::clear);
	if(!found)
	{
		file.seekg(stk.top());
		stk.pop();
		return -1;
	}
	return 0;
}

std::queue<std::string> fileHandler::breakLine(std::string line)
{
	std::queue<std::string> que;
	int thing;
	while(true)
	{
		if(line.at(0)=='\t') line=line.substr(1);
		que.push(line.substr(0, line.find_first_of(" ")));
		thing = line.find_first_of(" ");
		line=line.substr(thing+1);
		if(thing==std::string::npos) break;
	}
}

/*
int main(int argc, char** argv)
{
	fileHandler file = fileHandler("Normal.mode");
}*/