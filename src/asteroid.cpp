/* 
 * Asteroid Class for Asteroids: RETURN OF METEOR
 * 
 * Made by:
 * Jonathan Oakes
 * Braeden Brettin
 * Ted Dorfeuille 
 * Chris Le
 * Emily Herron
 * 
 * for the Class:
 * Intro to Computer Graphics (CSC315)
 * 
 * At:
 * Mercer Univercity  
 */

#include "asteroid.h"


point location;
float rotation;
point translation;
//std::vector<point> lyrs[0].pnts;
//std::vector<triangle> lyrs[0].tris;
bool clipped;
int numsides = 0;

std::uniform_int_distribution<int> numsidesdist(ASTEROID_MIN_SIZE, ASTEROID_MAX_SIZE);
std::uniform_real_distribution<double> dirdist(0, 2*M_PI);
//std::uniform_real_distribution<double> xlocdist(WORLD_COORDINATE_MIN_X, WORLD_COORDINATE_MAX_X);
//std::uniform_real_distribution<double> ylocdist(WORLD_COORDINATE_MIN_Y, WORLD_COORDINATE_MAX_Y);
std::uniform_real_distribution<double> spddist(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED);
std::uniform_int_distribution<int> sizedist(ASTEROID_MIN_AVG, ASTEROID_MAX_AVG);

asteroid::asteroid()
{
/*	Algorithem:
 * 	Stet up Random Number Generators
 *	Generate random number between 0 and 8; 
 * 	Add 4 to that number so that that number is between 4 and 12 sides.
 *  Set the location to (0,0)
 *  Get the points for the Enterprise.
 *  Find a location for the asteroid that is within the octogon and away from the ship.
 * 
 *	Generate random points between max_x and max_y
 *	Tessellate points and save as triangles
 * 	Return the asteroid
 */

	int avgSize = sizedist(generator);

// Generating a Random Number and adding 4, this will be the number of sides the asteroid has. 
 	numsides = numsidesdist(generator);

	double irregularity= ASTEROID_IRREGULARITY*(2*M_PI)/numsides;
	double spikeyness= ASTEROID_SPIKEYNESS;

	double irlower = (2*M_PI)/numsides-irregularity;
	double irupper = (2*M_PI)/numsides+irregularity;
	double splower = spikeyness*avgSize;
	double spupper = 2*avgSize-splower;

	std::uniform_real_distribution<double> irdist(irlower, irupper);
	std::uniform_real_distribution<double> spkdist(splower, spupper);

	// Generate a random "location.angle" or directional vector, in radians.
	location.angle = dirdist(generator);
	//cout << location.angle << endl;
	location.w = spddist(generator);

// Random number for seed.
	layer lyr;
   	std::vector<double> angleSteps;

	double sum =0;
	double t=0;
	
	for (int i=0; i < numsides; i++)
	{
		t = irdist(generator);
		angleSteps.push_back(t);
		sum+=t;
	}
	t = sum/(2*M_PI);
	
	for (int i=0; i < angleSteps.size(); i++)
	{
		angleSteps[i]/=t;
	}
	double angle=irdist(generator);

	for (int i=0; i < numsides; i++)
	{
			double length = spkdist(generator);
			point tempp;
			tempp.x= length*cos(angle);
			tempp.y= length*sin(angle);
			lyr.pnts.push_back(tempp);
			angle+=angleSteps[i];
	}

	tessellate(&lyr);
	lyrs.push_back(lyr);

}

asteroid::asteroid(triangle a, point loc, point offset, int num, float Orotation)
{
	layer lyr;
	lyr.pnts.push_back(a.a);
	lyr.pnts.push_back(a.b);
	lyr.pnts.push_back(a.c);

	lyr.tris.push_back(a);
	lyr.clr = color{0.1,0.5,0.0};

	lyrs.push_back(lyr);

	int j = rand();
	srand (static_cast <unsigned> (time(0))*(num*(j+67)/10));	
	Orotation *= 180/M_PI;
	location.angle = Orotation;
	location.w = (rand()%16+1)/2.0;

	location.x = loc.x + offset.x;
	location.y = loc.y + offset.y;
}

point asteroid::getCenter()
{
	return location;
}
/*
float asteroid::getVectorLength(point a, point b)
{
	return sqrt(pow(abs(a.x-b.x),2)+pow(abs(a.y-b.y),2));
}*/


/*float asteroid::getVectorLength(asteroid b)
{
	return sqrt(pow(abs(location.x-b.getLocation().x),2)+pow(abs(location.y-b.getLocation().y),2));
}*/

std::vector<asteroid *> asteroid::getInfluencers(mode * md)
{
	std::vector<asteroid *> infl;
	for (int i=0; i < md->getOnScreen().size()-1; i++)
	{
		if(dynamic_cast<asteroid *>(md->getOnScreen()[i]))
		{
			int j = getVectorLength(md->getOnScreen()[i]);
			if (0 < j && j <= 100 )
			{
				infl.push_back(dynamic_cast<asteroid *>(md->getOnScreen()[i]));
			}
		}

	}
	return infl;
}

std::vector<std::shared_ptr<asteroid>> asteroid::getInfluencers2(mode * md)
{
	std::vector<std::shared_ptr<asteroid>> infl;
	for (int i=0; i < md->getOnScreen2().size()-1; i++)
	{
		if(std::dynamic_pointer_cast<asteroid>(md->getOnScreen2()[i]))
		{
			int j = getVectorLength(md->getOnScreen2()[i]);
			if (0 < j && j <= 100 )
			{
				infl.push_back(std::dynamic_pointer_cast<asteroid>(md->getOnScreen2()[i]));
			}
		}

	}
	return infl;
}

/*void asteroid::incrementLocation(mode * md)
{
	//This is a std::vector for the asteroid's gravity influence effect.
	std::vector<asteroid> infl = getInfluencers(mode * md);

	//This takes the std::vector returned by getInfluencers and calculates the new direction of the current asteroid.
	for(int i =0; i< infl.size(); i++)
	{
		// This is where we calculate  the bearing of the asteroid to the current influencer.
		double bearing = atan2f(location.y-infl[i].getLocation().y, location.x-infl[i].getLocation().x);		
		
		// This ensures this value is above 0.
		if(bearing < 0 )
			bearing+=M_PI;

		// Here we are checking to see if the setting a value DBearing that is needed for later calculations.
		// Dbearing is the difference in the angle between the direction the asteroid is going and the influencer.
		double Dbearing;
		if (bearing <= location.angle)
		{
		 	Dbearing = location.angle - bearing;
		}
		if (bearing > location.angle)
		{
			Dbearing = bearing - location.angle;
		}

		// We need to calculate the gravity potential for the asteroids. this is the amount of "force" that is going to be aplied in the
		// direction of the influncer.
		double magnatude = GRAVITY_POTENTIAL*((2*ASTEROID_MASS)/getVectorLength(infl[i]));

		// Here we are calculating variables that were half phased out... cause debug issues.
		double Uvelocity = pow(location.w,2)+pow(magnatude,2);
		double Ubearing = cos(M_PI-(Dbearing));

		// Here we are calculating the new speed. this takes the previous speed, and add the calculated values of the change in velocity and direction.
		// Vector math is a pain in the behind. you don't want to know how long it took me to find the trig for these calcuations.
		location.w = pow(pow(location.w,2)+pow(magnatude,2) - ((2 * magnatude * location.w)*Ubearing), .5);
		location.angle += asinf((magnatude*sin((M_PI-Dbearing)))/location.w);

		// Here i'm setting a minimum and maximum speed for gameplay purposes.
		if (location.w >  1.5)
			location.w =  1.5;
		if (location.w < .2)
			location.w = .2;
	}

	// After we calculate the positions of the asteroids, we need to move them. so we move the location by use of trig.
	location.x += cos(location.angle)*location.w/**(60/FPS)*/;
/*	location.y += sin(location.angle)*location.w/**(60/FPS)*/;
	
/*	//this checks to see if it is still in the octogon them moves it to where it to the other side.
	if(!insideOctogon(location)){
		location.x*=-1;
		location.y*=-1;
	}
}*/

void asteroid::render() 
{
	switch(filled)
	{
	// If not filled
		case 0:
			for (int j = 0; j < (lyrs[0].pnts.size()); j++)
     		{
				glBegin (GL_LINES);
					glVertex2d(lyrs[0].pnts[j].x+location.x, lyrs[0].pnts[j].y+location.y);
					glVertex2d(lyrs[0].pnts[(j+1)%lyrs[0].pnts.size()].x + location.x , lyrs[0].pnts[(j+1)%lyrs[0].pnts.size()].y + location.y);
				glEnd ();         
       		}
			break;

			// If filled
		case 1:
			// Draw the triangles
			for (triangle t : lyrs[0].tris)
        	{
				glBegin (GL_TRIANGLES);
					glVertex2d(t.a.x + location.x, t.a.y + location.y);
					glVertex2d(t.b.x + location.x, t.b.y + location.y);
					glVertex2d(t.c.x + location.x, t.c.y + location.y);
				glEnd ();         
        	}
			
			break;
			// If filled == 2
		case 2: 
			// draw the triangles, and the tesselations.
			for (triangle t : lyrs[0].tris)
			{
				glBegin (GL_LINES);
					glVertex2d(t.a.x + location.x, t.a.y + location.y);
					glVertex2d(t.b.x + location.x, t.b.y + location.y);
					glVertex2d(t.b.x + location.x, t.b.y + location.y);
					glVertex2d(t.c.x + location.x, t.c.y + location.y);
					glVertex2d(t.c.x + location.x, t.c.y + location.y);
					glVertex2d(t.a.x + location.x, t.a.y + location.y);
				glEnd();
			}
		}
}
void asteroid::doAction(mode * md)
{
	//This is a vector for the asteroid's gravity influence effect.
	//std::vector<asteroid *> infl = getInfluencers(md);
	std::vector<std::shared_ptr<asteroid>> infl = getInfluencers2(md);

	//This takes the vector returned by getInfluencers and calculates the new direction of the current asteroid.
	for(int i =0; i< infl.size(); i++)
	{
		// This is where we calculate  the bearing of the asteroid to the current influencer.
		double bearing = atan2f(location.y-infl[i]->getLocation().y, location.x-infl[i]->getLocation().x);		
		
		// This ensures this value is above 0.
		if(bearing < 0 )
			bearing+=M_PI;

		// Here we are checking to see if the setting a value DBearing that is needed for later calculations.
		// Dbearing is the difference in the angle between the direction the asteroid is going and the influencer.
		double Dbearing;
		if (bearing <= location.angle)
		{
		 	Dbearing = location.angle - bearing;
		}
		if (bearing > location.angle)
		{
			Dbearing = bearing - location.angle;
		}

		// We need to calculate the gravity potential for the asteroids. this is the amount of "force" that is going to be aplied in the
		// direction of the influncer.
		double magnatude = GRAVITY_POTENTIAL*((2*ASTEROID_MASS)/getVectorLength(infl[i]));

		// Here we are calculating variables that were half phased out... cause debug issues.
		double Uvelocity = pow(location.w,2)+pow(magnatude,2);
		double Ubearing = cos(M_PI-(Dbearing));

		// Here we are calculating the new speed. this takes the previous speed, and add the calculated values of the change in velocity and direction.
		// Vector math is a pain in the behind. you don't want to know how long it took me to find the trig for these calcuations.
		location.w = pow(pow(location.w,2)+pow(magnatude,2) - ((2 * magnatude * location.w)*Ubearing), .5);
		location.angle += asinf((magnatude*sin((M_PI-Dbearing)))/location.w);

		// Here i'm setting a minimum and maximum speed for gameplay purposes.
		if (location.w >  1.5)
			location.w =  1.5;
		if (location.w < .2)
			location.w = .2;
	}

	// After we calculate the positions of the asteroids, we need to move them. so we move the location by use of trig.
	location.x += cos(location.angle)*location.w/**(60/FPS)*/;
	location.y += sin(location.angle)*location.w/**(60/FPS)*/;
	
	//this checks to see if it is still in the octogon them moves it to where it to the other side.
/*	if(!insideOctogon(location)){
		location.x*=-1;
		location.y*=-1;
	}*/
}

void asteroid::clear()
{
	lyrs[0].pnts.clear();
	lyrs[0].tris.clear();
}

void asteroid::createAsteroid(triangle a, point location, point offset, int num)
{
	lyrs[0].pnts.clear();
	lyrs[0].pnts.push_back(a.a);
	lyrs[0].pnts.push_back(a.b);
	lyrs[0].pnts.push_back(a.c);
	lyrs[0].tris.clear();	
	lyrs[0].tris.push_back(a);

	int j = rand();
	srand (static_cast <unsigned> (time(0))*(num*(j+67)/10));	

	location.angle = rand() % 360;
	location.angle *= M_PI / 180.0;
	location.w = ((rand()%16)+1)/4.0;

	location.x = location.x + offset.x;
	location.y = location.y + offset.y;
}

std::vector<object *> asteroid::breakupAsteroid()
{
/*
 *	todo:
 *	get trinagle set to a.
 *	createAsteroid(traingle a)
 * 	repeat through last triangle pointer.
 */


	

	std::vector<object *> breakup;
	if (lyrs[0].tris.size()==1)
		return breakup;

	double rotate = location.angle+(M_PI)/3;
	for(int i = 0; i < lyrs[0].tris.size(); i++)
	{	
		triangle tmpt = lyrs[0].tris.at(i);
		point tmpp = tmpt.a;
		point temp_p[3] = {tmpt.a, tmpt.b, tmpt.c};
		for (point p : temp_p)
		{
			tmpp.x = p.x<tmpp.x ? p.x : tmpp.x;
			tmpp.y = p.x<tmpp.y ? p.y : tmpp.y;
		}
		for (int i = 0; i > 3; i++)
		{
			temp_p[i].x-=tmpp.x;
			temp_p[i].y-=tmpp.y;
		}
		tmpt.a = temp_p[0];
		tmpt.b = temp_p[1];
		tmpt.c = temp_p[2];
		std::cout << "Added triangle ";
		for (point p : temp_p)
		{
			std::cout << "( " << p.x << " , " << p.y << " )";
		}
		std::cout << std::endl;
/*
		if (tmpt.a.x > tmpt.b.x)
		{
			if (tmpt.b.x > tmpt.c.x)
			{
				tmpp.x=tmpt.c.x;
				tmpt.a.x-=tmpp.x;
				tmpt.b.x-=tmpp.x;
				tmpt.c.x-=tmpp.x;
			}
			else
			{
				tmpp.x=tmpt.b.x;
				tmpt.a.x-=tmpp.x;
				tmpt.b.x-=tmpp.x;
				tmpt.c.x-=tmpp.x;
			}
		}
		else
		{
			if (tmpt.a.x > tmpt.c.x)
			{
				tmpp.x=tmpt.c.x;
				tmpt.a.x-=tmpp.x;
				tmpt.b.x-=tmpp.x;
				tmpt.c.x-=tmpp.x;
			}
			else
			{
				tmpp.x=tmpt.a.x;
				tmpt.a.x-=tmpp.x;
				tmpt.b.x-=tmpp.x;
				tmpt.c.x-=tmpp.x;
			}
		}

		if (tmpt.a.y > tmpt.b.y)
		{
			if (tmpt.b.y > tmpt.c.y)
			{
				tmpp.y=tmpt.c.y;
				tmpt.a.y-=tmpp.y;
				tmpt.b.y-=tmpp.y;
				tmpt.c.y-=tmpp.y;
			}
			else
			{
				tmpp.y=tmpt.b.y;
				tmpt.a.y-=tmpp.y;
				tmpt.b.y-=tmpp.y;
				tmpt.c.y-=tmpp.y;
			}
		}
		else
		{
			if (tmpt.a.y > tmpt.c.y)
			{
				tmpp.y=tmpt.c.y;
				tmpt.a.y-=tmpp.y;
				tmpt.b.y-=tmpp.y;
				tmpt.c.y-=tmpp.y;
			}
			else
			{
				tmpp.y=tmpt.a.y;
				tmpt.a.y-=tmpp.y;
				tmpt.b.y-=tmpp.y;
				tmpt.c.y-=tmpp.y;
			}
		}*/

		object * a = new asteroid(tmpt, location, tmpp, i, rotate);
		breakup.push_back(a);
		rotate -= ((2.0*M_PI)/(3.0*lyrs[0].tris.size()));
	}
	return breakup;
}

std::vector<std::shared_ptr<object>> asteroid::breakupAsteroid2()
{
/*
 *	todo:
 *	get trinagle set to a.
 *	createAsteroid(traingle a)
 * 	repeat through last triangle pointer.
 */
	std::vector<std::shared_ptr<object>> breakup;
	if (lyrs[0].tris.size()<=2)
		return breakup;

	double rotate = location.angle+(M_PI)/3;
	for(int i = 0; i < lyrs[0].tris.size(); i++)
	{	
		triangle tmpt = lyrs[0].tris.at(i);
		point tmpp = tmpt.a;
		point temp_p[3] = {tmpt.a, tmpt.b, tmpt.c};
		for (point p : temp_p)
		{
			tmpp.x = p.x<tmpp.x ? p.x : tmpp.x;
			tmpp.y = p.x<tmpp.y ? p.y : tmpp.y;
		}
		for (int i = 0; i > 3; i++)
		{
			temp_p[i].x-=tmpp.x;
			temp_p[i].y-=tmpp.y;
		}
		tmpt.a = temp_p[0];
		tmpt.b = temp_p[1];
		tmpt.c = temp_p[2];
		/*std::cout << "Added triangle ";
		for (point p : temp_p)
		{
			std::cout << "( " << p.x << " , " << p.y << " )";
		}
		std::cout << std::endl;*/

		std::shared_ptr<object> a = std::make_shared<asteroid>(asteroid(tmpt, location, tmpp, i, rotate));
		breakup.push_back(a);
		rotate -= ((2.0*M_PI)/(3.0*lyrs[0].tris.size()));
	}
	return breakup;
}

void asteroid::tessellateAsteriod()
{
/* 	todo:
 * 	Organize points in lyrs[0].pnts in counterclockwise direction
 *	Create Triangles from lyrs[0].pnts and save them in to lyrs[0].tris
 */
	std::vector<point> temp = lyrs[0].pnts;
	point A = temp[0];
	point B = temp[1];
	point C = temp[2];
	int Ai = 0;
	int Bi = 1;
	int Ci = 2;
	triangle tri;
	double z;

	int i = 0;
	// While there are more than three vertices left in points, run the following code.
	while(temp.size() >= 3)
	{
		//cout << intersect (temp[0], temp[1], A, B) << std::endl;

		bool insect = false;
		for (int i1  = 0; i1 < lyrs[0].pnts.size(); i1++)
		{
			if(intersect(lyrs[0].pnts[i1], lyrs[0].pnts[(i1+1)%lyrs[0].pnts.size()], A, B))
				insect=true;
			if(intersect(lyrs[0].pnts[i1], lyrs[0].pnts[(i1+1)%lyrs[0].pnts.size()], B, C))
				insect = true;
			if(intersect(lyrs[0].pnts[i1], lyrs[0].pnts[(i1+1)%lyrs[0].pnts.size()], C, A))
				insect = true;

			if(insect)
			{	
				break;
			}
		}

		for (int i1  = 0; i1 < lyrs[0].tris.size(); i1++)
		{
			point temp1[3] = {lyrs[0].tris[i1].a, lyrs[0].tris[i1].b, lyrs[0].tris[i1].c};
			for (int j1=0; j1<3; j1++)
			{
				if(intersect(temp1[j1], temp1[(j1+1)%3], A, B))
					insect = true;
				if(intersect(temp1[j1], temp1[(j1+1)%3], B, C))
					insect = true;
				if(intersect(temp1[j1], temp1[(j1+1)%3], C, A))
					insect = true;
			}
			if(insect)
			{	
				break;
			}
		}
		if (insect)
		{
			Ci++;
			if(Ci>=temp.size())
			{
				Bi++;
				if(Bi>=temp.size()-1)
				{
					temp.erase(temp.begin());
					Bi=Ai+1;
					Ci=Bi+1;
					A=temp[Ai];
					B=temp[Bi];
					C=temp[Ci];
					
					
				}
				else
				{
					Ci=Bi+1;
					B=temp[Bi];
					C=temp[Ci];
				}
			}
			else
			{
				C=temp[Ci];
			}
		}

		if(!insect)
		{
			point l1;
			l1.x = A.x - B.x;
			l1.y = A.y - B.y;

			point l2;
			l2.x = C.x - B.x;
			l2.y = C.y - B.y;

			z = l1.x*l2.y - l2.x*l1.y;

			bool within = false;
			for (int i =0; i < temp.size(); i ++)
			{
				if(PointInTriangle(temp[i], A, B, C) && Ai!=i && Bi!=i && Ci!=i)
				{
					within = true;
				}
			}

			if (z<0 && !within)
			{
				tri.a = A;
				tri.b = B;
				tri.c = C;
				lyrs[0].tris.push_back(tri);

				Bi++;
				if(Bi>=temp.size()-1)
				{
					temp.erase(temp.begin());
					Bi=Ai+1;
					Ci=Bi+1;
					A=temp[Ai];
					B=temp[Bi];
					C=temp[Ci];
				}
				else
				{
					Ci=Bi+1;
					B=temp[Bi];
					C=temp[Ci];
				}
			}
			else
			{
				Ci++;
				if(Ci>=temp.size())
				{
					Bi++;
					if(Bi>=temp.size()-1)
					{
						temp.erase(temp.begin());
						Bi=Ai+1;
						Ci=Bi+1;
						A=temp[Ai];
						B=temp[Bi];
						C=temp[Ci];
					}
					else
					{
						Ci=Bi+1;
						B=temp[Bi];
						C=temp[Ci];
					}
				}
				else
				{
					C=temp[Ci];
				}
			}

		}
	}
}

void asteroid::sortPoints()
{
	// Sorts lyrs[0].pnts in CCW order.
	// Declare a vector sortedPoints of points.
	std::vector<point> sortedPoints;
	

	// Calculate the centroid of the polygon formed by lyrs[0].pnts.
	float xsum = 0.0;
	float ysum = 0.0;
	for(int i=0; i<lyrs[0].pnts.size(); i++)
	{
		xsum += lyrs[0].pnts.at(i).x;
		ysum += lyrs[0].pnts.at(i).y;
	}
	float midx = xsum / lyrs[0].pnts.size();
	float midy = ysum / lyrs[0].pnts.size();

	// Declare an array of floats to hold the angles.
	const int angl_s = lyrs[0].pnts.size();
	float angles[angl_s];

	// For each point in lyrs[0].pnts, calculate its angle by comparing it to the centroid of the polygon formed by lyrs[0].pnts.
	for(int i=0; i<lyrs[0].pnts.size(); i++)
	{
		angles[i] = atan2(lyrs[0].pnts.at(i).y - midy, lyrs[0].pnts.at(i).x - midx);
		lyrs[0].pnts.at(i).angle = angles[i];
	}

	// Sort angles in ascending order.
	sort(angles, angles+lyrs[0].pnts.size(), std::less<float>());

	// Transfer the sorted points to sortedPoints.
	for(int j=0; j<lyrs[0].pnts.size(); j++)
		for(int k=0; k<lyrs[0].pnts.size(); k++)
			if(angles[j] == lyrs[0].pnts.at(k).angle)
				sortedPoints.push_back(lyrs[0].pnts.at(k));

	// Transfer sortedPoints to lyrs[0].pnts.
	lyrs[0].pnts = sortedPoints;
}
std::vector<point> asteroid::getBounds()
{
	std::vector<point> t = lyrs[0].pnts;

	for (int i = 0; i < t.size(); i++)
	{
		double x = t[i].x+location.x;
		double y = t[i].y+location.y;
		t[i] = point{x, y, t[i].z};

	}
	return t;
	
}

std::vector<point> asteroid::getPoints()
{
	return lyrs[0].pnts;
}
/*
std::vector<triangle> asteroid::getTess()
{
	return lyrs[0].tris;
}*/
std::vector<triangle> asteroid::getTess2()
{
	std::vector<triangle> temp = lyrs[0].tris;
	for (int i =0; i < temp.size(); i++)
	{
		point a[3] = {temp[i].a, temp[i].b, temp[i].c};
		for (int j = 0; j < 3; j++ )
		{
			a[j].x += location.x;
			a[j].y += location.y;
		}
		temp[i].a = a[0];
		temp[i].b = a[1];
		temp[i].c = a[2];
	}
	return temp;
}

/*
std::vector<point> asteroid::getRealPoints(){

	std::vector<point> v;

	for(int i = 0; i < lyrs[0].pnts.size(); i++){

		point p = {lyrs[0].pnts[i].x + location.x, lyrs[0].pnts[i].y + location.y, 0, 1};
		/*asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
		asteroidLogger << "real points are: " << p.x << " " << p.y << "\n";
		asteroidLogger.close();	
		v.push_back(p);
	}
	return v;
}*/
