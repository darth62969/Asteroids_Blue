#include "mode.h"
#include <iostream>

mode::mode()
{
	maxLevel=1;
}

int mode::step()
{
	for (int i = 0; i<onScreen.size(); i++)
	{
		
	}

	return 0;
}

void mode::generateLevel()
{
	for (int i=0; i<50; i++)
	{
		onScreen.push_back(new asteroid());
	}
}

void mode::init()
{

}

std::vector<object*> mode::getOnScreen()
{
	return onScreen;
}

void mode::addToOnScreen(object * obj)
{
	onScreen.push_back(obj);
}