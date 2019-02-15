#include <algorithm>
#include "normal.h"
#include "asteroid.h"
#include "bullet.h"
#include "enterprise.h"
#include "render.h"


std::uniform_real_distribution<double> xlocdist(WORLD_COORDINATE_MIN_X, WORLD_COORDINATE_MAX_X);
std::uniform_real_distribution<double> ylocdist(WORLD_COORDINATE_MIN_Y, WORLD_COORDINATE_MAX_Y);
//std::uniform_real_distribution<double> spddist(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED);

int gamestate=0;

normal::normal()
{
	std::cout << "Loading Normal...\n";
	maxLevel=1;
	std::cout << "Initiating Octogon...\n";
	//r2->initOctogon();
	std::cout << "Generating Level...\n";
	generateLevel();
	std::cout << "Establishing the Enterprise...\n";
	player = new enterprise();
	std::cout << "Setting Name to Normal...\n";
	name = "Normal";

	std::cout << "Seeding RNG...\n";
	std::chrono::high_resolution_clock::time_point s = 
		std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::duration d = 
		std::chrono::high_resolution_clock::now()-s;
	unsigned s2 = d.count();
	generator.seed(s2);

	std::cout << "Loaded Normal\n";
}

int normal::step()
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
	//std::cout << "got past break UP Algorithem\n ";

	for(int i = 0; i < onScreen2.size(); i++)
	{
		std::shared_ptr<object> o = onScreen2[i];
		if (!r2->insideOctogon(o->getLocation()))
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



void normal::generateLevel()
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
		while(!r2->insideOctogon(loc))
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
}

void normal::init()
{
	std::cout << "Normal Mode Loaded" << std::endl;
	//r2->initOctogon();
}

/*std::vector<object*> normal::getOnScreen()
{
	return onScreen;
}

std::vector<std::shared_ptr<object>> normal::getOnScreen2()
{
	return onScreen2;
}

void normal::addToOnScreen(object * obj)
{
	onScreen.push_back(obj);
}
void normal::addToOnScreen(std::shared_ptr<object> obj)
{
	onScreen2.push_back(obj);
}*/

void normal::drawLevel()
{
	r2->drawOctogon();
}

void normal::drawObjects()
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
			r2->drawString(opt->getLocation().x, opt->getLocation().y, a);
		}

	}
	player->render();

	
}

void normal::drawScore()
{
	r2->setFont(GLUT_BITMAP_HELVETICA_12);

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
	char modeC[50];
	sprintf(modeC, "Game Mode: %s", "Normal");
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
	r2->drawString(-280, -230, bulletsFiredStr);
	r2->drawString(-280, -270, astsOnScr1);
	
	// draw the strings, right side.
	r2->drawString(180, -230, astsHit);
	r2->drawString(180, -215, modeC);
	r2->drawString(180, -270, hrStr);
	
	r2->drawString(-280, 265, health);
}

void normal::drawAll()
{
	drawLevel();
	drawObjects();
	drawScore();
}

std::string normal::getName()
{
	return name;
}

void normal::keyboardFunc(char key, int x, int y)
{

}

void normal::mouseFunc(int button, int state, int x, int y)
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
void normal::passiveMouseFunc(int x, int y)
{
	point pnt = dynamic_cast<ship *>(player)->getAtkPnts()[0];
	double bearing =(atan2f(pnt.y-y, pnt.x-x));
	player->setRotation(bearing);
}

extern "C" mode * create()
{
	return new normal();
}
extern "C" mode * destroy(mode * m)
{
	delete (m);
}