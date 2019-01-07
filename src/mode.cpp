#include "mode.h"
#include "asteroid.h"
#include "bullet.h"
#include "enterprise.h"
#include "render.h"

std::uniform_real_distribution<double> xlocdist(WORLD_COORDINATE_MIN_X, WORLD_COORDINATE_MAX_X);
std::uniform_real_distribution<double> ylocdist(WORLD_COORDINATE_MIN_Y, WORLD_COORDINATE_MAX_Y);

mode::mode()
{
	maxLevel=1;
	init();
	generateLevel();
	player = new enterprise();
	name = "Normal";
}

int mode::step()
{
	numAsteroids=0;
	for (int i = 0; i<onScreen.size(); i++)
	{
		onScreen[i]->doAction(this);
		if(dynamic_cast<asteroid *>(onScreen[i]))
			numAsteroids++;
	}
	switch(numAsteroids)
	{
		case 0:
			gamestate = 3;
			break;
	}

	std::cout << "Checking for Collisions" << std::endl << std::endl;
	
	for (int i = 0; i<onScreen.size(); i++)
	{
		
		object * o1 = onScreen[i];
		for(int j = i+1; j<onScreen.size(); j++)
		{
			object * o2 = onScreen[j];
			std::cout << "Checking collisions for objects " << i << " and " << j << std::endl;
			if(o1->collides(o2))
			{
				std::cout << "somthing collided\n";
				if(dynamic_cast<asteroid *>(o1))
				{
					std::vector<object *> temp =
						dynamic_cast<asteroid *>(o1)->breakupAsteroid();
					for (object * o : temp)
						onScreen.push_back(o);
					//delete(static_cast<asteroid*>(onScreen[i]));
					onScreen.erase(onScreen.begin()+i);
				}
				if(dynamic_cast<asteroid *>(o2))
				{
					std::vector<object *> temp =
						dynamic_cast<asteroid *>(o2)->breakupAsteroid();
					for (object * o : temp)
						onScreen.push_back(o);
					//delete(static_cast<asteroid*>(onScreen[j]));
					onScreen.erase(onScreen.begin()+j);
				}
				if(dynamic_cast<bullet * >(o2))
				{
					//delete (static_cast<bullet * >(onScreen[j]));
					onScreen.erase(onScreen.begin()+j);
					bulletsHit++;
				}
				if(dynamic_cast<bullet * >(o1))
				{
					//delete (static_cast<bullet * >(onScreen[i]));
					onScreen.erase(onScreen.begin()+i);
					bulletsHit++;
				}
			}
		}
	}
	for(int i = 0; i < onScreen.size(); i++)
	{
		object * o = onScreen[i];
		if (!render::insideOctogon(o->getLocation()))
		{
			if (dynamic_cast<bullet * > (o))
			{
				//delete(onScreen[i]);
				onScreen.erase(onScreen.begin()+i);
			}
			if (dynamic_cast<bullet * > (o))
			{
				o->setLocation(-(o->getLocation().x), -(o->getLocation().y));
			}
		}
	}


	return 0;
}

void mode::generateLevel()
{
	for (object * o : onScreen)
	{
		delete(o);
	}

	onScreen.clear();

	for (int i=0; i<50; i++)
	{
		onScreen.push_back(new asteroid());
		point loc;
		loc.x = INT32_MAX;
		loc.y = INT32_MAX;
		while(!render::insideOctogon(loc))
		{
		// Keep generateing points till the asteroid is not withing range of the ship
			do
			{
				loc.x = xlocdist(generator);
				loc.y = ylocdist(generator);
			}
			while(getVectorLength(loc, point{0, 0, 0, 1})<100);

			// Check the new asteroid for it's vecinity to other asteriods.
			bool nv = false;
			for (int i = 0; i < onScreen.size(); i++)
			{
				// If it is withing range of an asteroid set location back to (0,0)
				// This causes it to try again, till it finds a position that works.
				if(getVectorLength(loc, onScreen[i]->getLocation())<50)
				{
					loc.x = INT32_MAX;
					loc.y = INT32_MAX;
				}
			}
		}
		onScreen.back()->setLocation(loc.x, loc.y);
	}
}

void mode::init()
{
	render::initOctogon();
}

std::vector<object*> mode::getOnScreen()
{
	return onScreen;
}

void mode::addToOnScreen(object * obj)
{
	onScreen.push_back(obj);
}

void mode::drawLevel()
{
	render::drawOctogon();
}

void mode::drawObjects()
{
	for(object * o : onScreen)
	{
		o->render();
	}
	player->render();
	
}

void mode::drawScore()
{
	render::setFont(GLUT_BITMAP_HELVETICA_12);

	double hitRatio;
	switch (bulletsHit)
	{
		default:
			hitRatio = (double)bulletsHit/(double)dynamic_cast<enterprise*>(player)->getBulletsFired()*100.0;
			break;
		case 0:
			hitRatio = 0;
			break;
	}
	char mode[50];
	sprintf(mode, "Game Mode: %s", "Normal");
	char bulletsFiredStr[50];	
	sprintf(bulletsFiredStr, "Bullets Fired: %3d", dynamic_cast<enterprise*>(player)->getBulletsFired());
	char astsOnScr1[50];
	sprintf(astsOnScr1, "Asteroids Left: %d", numAsteroids ); 
	char astsHit[50];
	sprintf(astsHit, "Asteroids Hit: %4d", bulletsHit);
	char hrStr[50];
	sprintf(hrStr, "Hit Ratio:  %5.2f %%", hitRatio);
	char health[50];
	sprintf(health, "Health: %%%d", dynamic_cast<enterprise*>(player)->getHealth() );

	glColor3f(0.2, 0.5, 0.0);
	
	//Draw the strings, left side
	render::drawString(-280, -230, bulletsFiredStr);
	render::drawString(-280, -270, astsOnScr1);
	
	// draw the strings, right side.
	render::drawString(180, -230, astsHit);
	render::drawString(180, -215, mode);
	render::drawString(180, -270, hrStr);
	
	render::drawString(-280, 265, health);
}

void mode::drawAll()
{
	drawLevel();
	drawObjects();
	drawScore();
}

std::string mode::getName()
{
	return name;
}

void mode::mouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		switch(gamestate)
		{
			case 1:
				dynamic_cast<enterprise *>(player)->fire(this);
				break;
		}
    }
}
void mode::passiveMouseFunc(int x, int y)
{
	point pnt = dynamic_cast<ship *>(player)->getAtkPnts()[0];
	double bearing =(atan2f(pnt.y-y, pnt.x-x));
	player->setRotation(bearing);
}
