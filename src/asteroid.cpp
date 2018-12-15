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

#include "headers.h"
#include "structs.h"
#include "globals.h"
#include "prototypes.h"
#include <random>
#include <chrono>


point location;
float rotation;
point translation;
vector<point> astPnts;
vector<triangle> astTris;
bool clipped;
int numsides = 0;

std::uniform_int_distribution<int> numsidesdist(ASTEROID_MIN_SIZE, ASTEROID_MAX_SIZE);
std::uniform_real_distribution<double> dirdist(0, 2*M_PI);
std::uniform_real_distribution<double> xlocdist(WORLD_COORDINATE_MIN_X, WORLD_COORDINATE_MAX_X);
std::uniform_real_distribution<double> ylocdist(WORLD_COORDINATE_MIN_Y, WORLD_COORDINATE_MAX_Y);
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

// Logging for debug information, this tells us what the the program is doing. 
// The number of sides it is going to generate

#ifdef LOGGING	 
	//asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
	//asteroidLogger << "Number of sides to generate : " << numsides << endl;
#endif

//Setting the location (x,y) to (0,0)
	location.x = INT32_MAX;
	location.y = INT32_MAX;
	
// While the location is not wihtin the octogon, generate random positions
	while(!insideOctogon(location))
	{
		// Keep generateing points till the asteroid is not withing range of the ship
		do
		{
			location.x = xlocdist(generator);
			location.y = ylocdist(generator);
		}
		while(getVectorLength(location, point{0, 0, 0, 1})<100);

		// Check the new asteroid for it's vecinity to other asteriods.
		bool nv = false;
		for (int i = 0; i < asteroidBelt.size(); i++)
		{
			// If it is withing range of an asteroid set location back to (0,0)
			// This causes it to try again, till it finds a position that works.
			if (abs(location.x - asteroidBelt[i].getLocation().x) <= 2*ASTEROID_MAX_AVG && abs(location.y - asteroidBelt[i].getLocation().y) <= 2*ASTEROID_MAX_AVG)
			{
				location.x = INT32_MAX;
				location.y = INT32_MAX;
			}
		}
	}
	// Generate a random "translation.angle" or directional vector, in radians.
	translation.angle = dirdist(generator);
	//cout << translation.angle << endl;
	translation.w = spddist(generator);


	// This logging protocal lets us know where the location of the asteroid is. 
#ifdef LOGGING
	//asteroidLogger << "Bottom Left corner of asteroid at : " << location.x << " " << location.y << endl;
#endif

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
	tesselate(&lyr);
	lyrs.push_back(lyr);


	//sortPoints();
	//tessellateAsteriod();
	//translation.angle = drand48();
#ifdef LOGGING	
	//asteroidLogger << "translation.angle was set to : " << translation.angle << "\n\n";
	//asteroidLogger.close();
#endif
}

asteroid::asteroid(triangle a, point location, point offset, int num, float Orotation)
{
#ifdef LOGGING
	//asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
	//asteroidLogger << "Creating Simple Asteroid #" << num << endl;
	//asteroidLogger.close();
#endif
	layer lyr;
	lyr.pnts.push_back(a.a);
	lyr.pnts.push_back(a.b);
	lyr.pnts.push_back(a.c);

	lyr.tris.push_back(a);

	int j = rand();
	srand (static_cast <unsigned> (time(0))*(num*(j+67)/10));	
	Orotation *= 180/M_PI;
	translation.angle = Orotation+num*2;
	translation.angle *= M_PI / 180.0;
	translation.w = (rand()%16+1)/2.0;

	location.x = location.x + offset.x;
	location.y = location.y + offset.y;
#ifdef LOGGING
	//asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
	//asteroidLogger << "Created Simple Asteroid\n\n";
	//asteroidLogger.close();
#endif
}

point asteroid::getCenter()
{
	return location;
}
float asteroid::getVectorLength(point a, point b)
{
	return sqrt(pow(abs(a.x-b.x),2)+pow(abs(a.y-b.y),2));
}


float asteroid::getVectorLength(asteroid b)
{
	return sqrt(pow(abs(location.x-b.getLocation().x),2)+pow(abs(location.y-b.getLocation().y),2));
}

vector<asteroid> asteroid::getInfluencers()
{
	vector<asteroid> infl;
	for (int i=0; i < asteroidBelt.size()-1; i++)
	{
		if (0 < getVectorLength(asteroidBelt[i]) && getVectorLength(asteroidBelt[i]) <= 100 )
		{
			infl.push_back(asteroidBelt[i]);
		}
	}
	return infl;
}

void asteroid::incrementLocation()
{
	// If Paused, return. this is to ensure the program does not continue if the game is paused. (depreciated)
	if(paused)
		return;

	//This is a vector for the asteroid's gravity influence effect.
	vector<asteroid> infl = getInfluencers();

	//This takes the vector returned by getInfluencers and calculates the new direction of the current asteroid.
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
		if (bearing <= translation.angle)
		{
		 	Dbearing = translation.angle - bearing;
		}
		if (bearing > translation.angle)
		{
			Dbearing = bearing - translation.angle;
		}

		// We need to calculate the gravity potential for the asteroids. this is the amount of "force" that is going to be aplied in the
		// direction of the influncer.
		double magnatude = GRAVITY_POTENTIAL*((2*ASTEROID_MASS)/getVectorLength(infl[i]));

		// Here we are calculating variables that were half phased out... cause debug issues.
		double Uvelocity = pow(translation.w,2)+pow(magnatude,2);
		double Ubearing = cos(M_PI-(Dbearing));

		// Here we are calculating the new speed. this takes the previous speed, and add the calculated values of the change in velocity and direction.
		// Vector math is a pain in the behind. you don't want to know how long it took me to find the trig for these calcuations.
		translation.w = pow(pow(translation.w,2)+pow(magnatude,2) - ((2 * magnatude * translation.w)*Ubearing), .5);
		translation.angle += asinf((magnatude*sin((M_PI-Dbearing)))/translation.w);

		// Here i'm setting a minimum and maximum speed for gameplay purposes.
		if (translation.w >  1.5)
			translation.w =  1.5;
		if (translation.w < .2)
			translation.w = .2;
	}

	// After we calculate the positions of the asteroids, we need to move them. so we move the location by use of trig.
	location.x += cos(translation.angle)*translation.w/**(60/FPS)*/;
	location.y += sin(translation.angle)*translation.w/**(60/FPS)*/;
	
	//this checks to see if it is still in the octogon them moves it to where it to the other side.
	if(!insideOctogon(location)){
		location.x*=-1;
		location.y*=-1;
	}
}

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

void asteroid::clear()
{
	astPnts.clear();
	astTris.clear();
}

void asteroid::createAsteroid(triangle a, point location, point offset, int num)
{
#ifdef LOGGING
	//asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
	//asteroidLogger << "Creating Simple Asteroid #" << num << endl;
	//asteroidLogger.close();
#endif
	astPnts.clear();
	astPnts.push_back(a.a);
	astPnts.push_back(a.b);
	astPnts.push_back(a.c);
	astTris.clear();	
	astTris.push_back(a);

	int j = rand();
	srand (static_cast <unsigned> (time(0))*(num*(j+67)/10));	

	translation.angle = rand() % 360;
	translation.angle *= M_PI / 180.0;
	translation.w = ((rand()%16)+1)/4.0;

	location.x = location.x + offset.x;
	location.y = location.y + offset.y;
#ifdef LOGGING
	//asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
	//asteroidLogger << "Created Simple Asteroid\n" << endl;
	//asteroidLogger.close();
#endif
}

vector<asteroid> asteroid::breakupAsteroid()
{
/*
 *	todo:
 *	get trinagle set to a.
 *	createAsteroid(traingle a)
 * 	repeat through last triangle pointer.
 */
#ifdef LOGGING
	//asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
	//asteroidLogger << "Breaking up asteroid into " << astTris.size() << " asteroids.\n";
	//asteroidLogger.close();
#endif

	vector<asteroid> breakup;
	for(int i = 0; i < astTris.size(); i++)
	{
		if (astTris.size()==1)
			break;

		triangle tmpt = astTris.at(i);
		point tmpp;

		if (tmpt.a.x > tmpt.b.x)
		{
			if (tmpt.b.x > tmpt.c.x)
			{
#ifdef LOGGING
//				asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
//				asteroidLogger << tmpt.b.x << ">" << tmpt.c.x << endl; 
//				asteroidLogger.close();
#endif
				tmpp.x=tmpt.c.x;
				tmpt.a.x-=tmpp.x;
				tmpt.b.x-=tmpp.x;
				tmpt.c.x-=tmpp.x;
			}
			else
			{
#ifdef LOGGING				
//				asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
//				asteroidLogger << tmpt.c.x << ">" << tmpt.b.x << endl;
//				asteroidLogger.close();
#endif
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
#ifdef LOGGING
//				asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
//				asteroidLogger << tmpt.a.x << ">" << tmpt.c.x << endl;
//				asteroidLogger.close();
#endif
				tmpp.x=tmpt.c.x;
				tmpt.a.x-=tmpp.x;
				tmpt.b.x-=tmpp.x;
				tmpt.c.x-=tmpp.x;
			}
			else
			{
#ifdef LOGGING
//				asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
//				asteroidLogger << tmpt.c.x << ">" << tmpt.a.x << endl;
//				asteroidLogger.close();
#endif
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
		}
		
		//translation.angle MUST BE A RANDOM FLOAT
		//srand (static_cast <unsigned> (time(0))*((asteroidBelt.size()+67)/10));
		float rotate = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		asteroid a(tmpt, location, tmpp, i, rotate);
		//a.createAsteroid(tmpt, location, tmpp, i);
		breakup.push_back(a);
	}
#ifdef LOGGING
//	asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
//	asteroidLogger << "Breaking up asteroid into " << astTris.size() << " asteroids.\n";
//	asteroidLogger.close();
#endif

	return breakup;
}


void asteroid::tessellateAsteriod()
{
/* 	todo:
 * 	Organize points in astPnts in counterclockwise direction
 *	Create Triangles from astPnts and save them in to astTris
 */
	std::vector<point> temp = astPnts;
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
		for (int i1  = 0; i1 < astPnts.size(); i1++)
		{
			if(intersect(astPnts[i1], astPnts[(i1+1)%astPnts.size()], A, B))
				insect=true;
			if(intersect(astPnts[i1], astPnts[(i1+1)%astPnts.size()], B, C))
				insect = true;
			if(intersect(astPnts[i1], astPnts[(i1+1)%astPnts.size()], C, A))
				insect = true;

			if(insect)
			{	/*
				std::cout << std::endl << "INTERSECT!!" << std::endl;
				std::cout << "A = ( " << A.x << " , " << A.y << " ) " << std::endl;
				std::cout << "B = ( " << B.x << " , " << B.y << " ) " << std::endl;
				std::cout << "C = ( " << C.x << " , " << C.y << " ) " << std::endl;
				std::cout << "astPnts 1 = ( " << astPnts[i1].x << " , " << astPnts[i1].y << " ) " << std::endl;
				std::cout << "astPnts 1 = ( " << astPnts[i1%astPnts.size()].x << " , " << astPnts[i1%astPnts.size()].y << " ) " << std::endl;*/
				break;
			}
		}

		for (int i1  = 0; i1 < astTris.size(); i1++)
		{
			point temp1[3] = {astTris[i1].a, astTris[i1].b, astTris[i1].c};
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
			{	/*
				std::cout << std::endl << "INTERSECT!!" << std::endl;
				std::cout << "A = ( " << A.x << " , " << A.y << " ) " << std::endl;
				std::cout << "B = ( " << B.x << " , " << B.y << " ) " << std::endl;
				std::cout << "C = ( " << C.x << " , " << C.y << " ) " << std::endl;
				std::cout << "Triangle 1 = ( " << temp[0].x << " , " << temp1[0].y << " ) " << std::endl;
				std::cout << "Triangle 2 = ( " << temp[1].x << " , " << temp1[1].y << " ) " << std::endl;
				std::cout << "Triangle 3 = ( " << temp[2].x << " , " << temp1[2].y << " ) " << std::endl;
				*/
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
				{/*
					std::cout << std::endl << "WITHIN!!" << std::endl;
					std::cout << "A = ( " << A.x << " , " << A.y << " ) " << std::endl;
					std::cout << "B = ( " << B.x << " , " << B.y << " ) " << std::endl;
					std::cout << "C = ( " << C.x << " , " << C.y << " ) " << std::endl;
					std::cout << "Point = ( " << temp[i].x << " , " << temp[i].y << " ) " << std::endl;*/
					within = true;
				}
			}

			if (z<0 && !within)
			{
				tri.a = A;
				tri.b = B;
				tri.c = C;
				astTris.push_back(tri);

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
			{/*
				std::cout << std::endl << "NOT CONCAVE!!" << std::endl;
				std::cout << "A = ( " << A.x << " , " << A.y << " ) " << std::endl;
				std::cout << "B = ( " << B.x << " , " << B.y << " ) " << std::endl;
				std::cout << "C = ( " << C.x << " , " << C.y << " ) " << std::endl;*/
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
	// Sorts astPnts in CCW order.
	// Declare a vector sortedPoints of points.
	vector<point> sortedPoints;

	// Calculate the centroid of the polygon formed by astPnts.
	float xsum = 0.0;
	float ysum = 0.0;
	for(int i=0; i<astPnts.size(); i++)
	{
		xsum += astPnts.at(i).x;
		ysum += astPnts.at(i).y;
	}
	float midx = xsum / astPnts.size();
	float midy = ysum / astPnts.size();

	// Declare an array of floats to hold the angles.
	float angles[astPnts.size()];

	// For each point in astPnts, calculate its angle by comparing it to the centroid of the polygon formed by astPnts.
	for(int i=0; i<astPnts.size(); i++)
	{
		angles[i] = atan2(astPnts.at(i).y - midy, astPnts.at(i).x - midx);
		astPnts.at(i).angle = angles[i];
	}

	// Sort angles in ascending order.
	sort(angles, angles+astPnts.size(), less<float>());

	// Transfer the sorted points to sortedPoints.
	for(int j=0; j<astPnts.size(); j++)
		for(int k=0; k<astPnts.size(); k++)
			if(angles[j] == astPnts.at(k).angle)
				sortedPoints.push_back(astPnts.at(k));

	// Transfer sortedPoints to astPnts.
	astPnts = sortedPoints;
}

vector<point> asteroid::getPoints()
{
	return astPnts;
}

vector<triangle> asteroid::getTess()
{
	return astTris;
}
vector<triangle> asteroid::getTess2()
{
	vector<triangle> temp = astTris;
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


vector<point> asteroid::getRealPoints(){

	vector<point> v;

	for(int i = 0; i < astPnts.size(); i++){

		point p = {astPnts[i].x + location.x,astPnts[i].y + location.y, 0, 1};
		/*asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
		asteroidLogger << "real points are: " << p.x << " " << p.y << "\n";
		asteroidLogger.close();	*/
		v.push_back(p);
	}
	return v;
}
