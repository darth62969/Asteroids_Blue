#include <algorithm>
#include "mode.h"
#include "asteroid.h"
#include "bullet.h"
#include "enterprise.h"
#include "render.h"


//std::uniform_real_distribution<double> xlocdist(WORLD_COORDINATE_MIN_X, WORLD_COORDINATE_MAX_X);
//std::uniform_real_distribution<double> ylocdist(WORLD_COORDINATE_MIN_Y, WORLD_COORDINATE_MAX_Y);
//std::uniform_real_distribution<double> spddist(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED);
/*
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
	for (int i = 0; i<onScreen2.size(); i++)
	{
		onScreen2[i]->doAction(this);
		if(std::dynamic_pointer_cast<asteroid>(onScreen2[i]))
			numAsteroids++;
	}
	switch(numAsteroids)
	{
		case 0:
			gamestate = 3;
			break;
	}

	//std::cout << "Checking for Collisions" << std::endl << std::endl;
	std::vector<int> t_int;
	for (int i = 0; i<onScreen2.size(); i++)
	{
		
		std::shared_ptr<object> o1 = onScreen2[i];
		if (o1->collides(player)&&std::dynamic_pointer_cast<asteroid>(o1))
		{
			dynamic_cast<enterprise*>(player)->damageHealth(10);
			t_int.push_back(i);
		}
		for(int j = i+1; j<onScreen2.size(); j++)
		{
			std::shared_ptr<object> o2 = onScreen2[j];
			if(o1->getVectorLength(o2)<50){
			
				//std::cout << "Checking collisions for objects " << i << " and " << j << std::endl;
			
				if(o1->collides(o2) && !(std::dynamic_pointer_cast<bullet>(o1)
					&&std::dynamic_pointer_cast<bullet>(o2)))
				{
					t_int.push_back(i);
					t_int.push_back(j);
				}
			}
		}
	}
	
	std::sort(t_int.begin(), t_int.end());
	std::reverse(t_int.begin(), t_int.end());
	std::vector<int>::iterator it;
	it = std::unique(t_int.begin(), t_int.end());
	t_int.resize(std::distance(t_int.begin(), it));

	
	for (int i : t_int)
	{
		if(std::dynamic_pointer_cast<asteroid>(onScreen2[i]))
		{
			//std::cout << "breaking up asteroid " << i << std::endl;
			std::vector<std::shared_ptr<object>> temp =
				std::dynamic_pointer_cast<asteroid>(onScreen2[i])->breakupAsteroid2();		
			for (int j =0; j < temp.size(); j++)
					onScreen2.push_back(temp.at(j));
			//delete(static_cast<asteroid*>(onScreen[i]));
			onScreen2.erase(onScreen2.begin()+(i));
		}
		if(std::dynamic_pointer_cast<bullet>(onScreen2[i]))
		{
			//delete (static_cast<bullet * >(onScreen[i]));
			onScreen2.erase(onScreen2.begin()+(i));
			bulletsHit++;
		}
	}
	//std::cout << "got past breakUPalgorithem\n ";

	for(int i = 0; i < onScreen2.size(); i++)
	{
		std::shared_ptr<object> o = onScreen2[i];
		if (!r->insideOctogon(o->getLocation()))
		{
			if (std::dynamic_pointer_cast<bullet> (o))
			{
				//delete(onScreen[i]);
				onScreen2.erase(onScreen2.begin()+i);
			}
			if (std::dynamic_pointer_cast<asteroid> (o))
			{
				o->setLocation(-1*(o->getLocation().x), -1*(o->getLocation().y));
			}
		}
	}
	if(dynamic_cast<enterprise*>(player)->getHealth()<=0)
	{
		gamestate=2;
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
		onScreen2.push_back(std::make_shared<asteroid>(asteroid()));
		point loc;
		loc.x = INT32_MAX;
		loc.y = INT32_MAX;
		while(!r->insideOctogon(loc))
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
		onScreen2.back()->setLocation(loc.x, loc.y);
	}
}*/

void mode::init()
{
	std::cout << "Wrong init\n";
	//r->initOctogon();
}/**/

std::vector<object*> mode::getOnScreen()
{
	return onScreen;
}

std::vector<std::shared_ptr<object>> mode::getOnScreen2()
{
	return *onScreen2;
}

void mode::addToOnScreen(object * obj)
{
	onScreen.push_back(obj);
}
void mode::addToOnScreen(std::shared_ptr<object> obj)
{
	onScreen2->push_back(obj);
}
/*
void mode::drawLevel()
{
	r->drawOctogon();
}

void mode::drawObjects()
{
	int i = 0;
	for(std::weak_ptr<object> o : onScreen2)
	{
		char a[10];
		sprintf(a, "%d", i);
		if(auto opt = o.lock())
		{
			opt->render();
			i++;
			r->drawString(opt->getLocation().x, opt->getLocation().y, a);
		}

	}
	player->render();

	
}

void mode::drawScore()
{
	r->setFont(GLUT_BITMAP_HELVETICA_12);

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
	r->drawString(-280, -230, bulletsFiredStr);
	r->drawString(-280, -270, astsOnScr1);
	
	// draw the strings, right side.
	r->drawString(180, -230, astsHit);
	r->drawString(180, -215, mode);
	r->drawString(180, -270, hrStr);
	
	r->drawString(-280, 265, health);
}

void mode::drawAll()
{
	drawLevel();
	drawObjects();
	drawScore();
}
*/
std::string mode::getName()
{
	//std::cout << name << std::endl;
	return name;
}

/*void mode::keyboardFunc(char key, int x, int y)
{

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
}*/
