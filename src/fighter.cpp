#include "fighter.h"
#include "globals.h"

fighter::fighter()
{
	layer lyr;
	std::vector<point> temp;

	lyr.pnts.push_back(point{ 3,  0, 0 ,1});
	lyr.pnts.push_back(point{ 0,  1, 0 ,1});
	lyr.pnts.push_back(point{-2,  3, 0 ,1});
	lyr.pnts.push_back(point{-2, -3, 0 ,1});
	lyr.pnts.push_back(point{ 0, -1, 0 ,1});
	
	tessellate(&lyr);
	
	lyrs.push_back(lyr);

	atkpnts.push_back(point{ 3,  0, 0, 1});

	temp.push_back(point { 3, -1, 0, 1});
	temp.push_back(point { 3,  1, 0, 1});
	temp.push_back(point { 1,  2, 0, 1});
	temp.push_back(point {-3,  2, 0, 1});
	temp.push_back(point {-3, -2, 0, 1});
	temp.push_back(point { 1, -2, 0, 1});

	blt = bullet(temp, 10, 2);

	actionSet = 2;
	health = 20;
	cycle = 25;
}

void fighter::fire(mode * md)
{
	std::vector<point> temp=getAtkPnts();
	for (int i = 0; i < temp.size(); i++)
	{	
		temp[i].x+=sin(location.angle);
		temp[i].y+=cos(location.angle);
		bullet * shot = blt.fireBullet(temp[i].x, temp[i].y, location.angle);
		md->addToOnScreen(shot);
	}
}

void fighter::doAction(mode * md)
{
	cycle++;

	point pnt = player.getAtkPnts()[0];
	double bearing =(atan2f(pnt.y-this->getAtkPnts()[0].y, pnt.x-this->getAtkPnts()[0].x));
	this->setRotation(bearing);

	switch(cycle/50)
	{
		case 0:
			location.x++;
			break;
		case 1:
			location.x--;
			break;
	}
	switch(cycle%50)
	{
		case 0:
			location.y-=10;
			break;

	}
	if (cycle >= 100)
	{
		cycle = 0;
	}
	switch(rand()%70)
	{
		case 0: 
		fire(md);
		break;
	}
}