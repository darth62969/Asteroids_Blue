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


point center;
float rotation;
point translation;
vector<point> astPnts;
vector<triangle> astTris;
bool clipped;
int numsides = 0;

asteroid::asteroid()
{
/*	Algorithem:
 *	Generate random number between 0 and 8; 
 * 	Add 4 to that number so that that number is between 4 and 12 sides.
 *  Set the center to (0,0)
 *  Get the points for the Enterprise.
 *  Find a location for the asteroid that is within the octogon and away from the ship.
 * 
 *	Generate random points between max_x and max_y
 *	Tessellate points and save as triangles
 * 	Return the asteroid
 */

	int r = rand();
	srand (static_cast <unsigned> (time(0))*r/10);	

// Generating a Random Number and adding 4, this will be the number of sides the asteroid has. 
 	numsides = rand()% (ASTEROID_MAX_SIZE - ASTEROID_MIN_SIZE + 1) + ASTEROID_MIN_SIZE;

// Logging for debug information, this tells us what the the program is doing. 
// The number of sides it is going to generate

#ifdef LOGGING	 
	//asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
	//asteroidLogger << "Number of sides to generate : " << numsides << endl;
#endif

//Setting the center (x,y) to (0,0)
	center.x = 0;
	center.y = 0;
	
// Getting the point of the ship so that we can check the location of the asteriods against it.
// This prevents insta-"Game Overs". 
#ifndef SHIPTEST
	vector<point> cmd;
	cmd.push_back(enterprise.body.a);
	cmd.push_back(enterprise.body.b);
	cmd.push_back(enterprise.body.c);

// Since we store the ship in ratios, we scale the ship to get the accurate representation of 
// where it is on the map.
	for (int i = 0; i < 3; i++)
	{
		scalePoint(cmd[i], 7);
		rotatePoint(cmd[i], enterprise.rotation);
		cmd[i].x += WORLD_COORDINATE_MAX_X/2;
		cmd[i].y += WORLD_COORDINATE_MAX_Y/2;
	}

// This finds the center of the ship. 
	int x = (cmd[0].x + cmd[1].x + cmd[2].x)/3;
	int y = (cmd[0].y + cmd[1].y + cmd[2].y)/3;
#endif

// While the center is not wihtin the octogon, generate random positions
	while(!insideOctogon(center))
	{
		// Keep generateing points till the asteroid is not withing range of the ship
		do
		{
			center.x = rand() % (WORLD_COORDINATE_MAX_X + 1) + WORLD_COORDINATE_MIN_X;
			center.y = rand() % (WORLD_COORDINATE_MAX_Y + 1) + WORLD_COORDINATE_MIN_Y;
		}
		while(getVectorLength(center, point{WORLD_COORDINATE_MAX_X/2, WORLD_COORDINATE_MAX_Y/2, 0, 1})<50);

		// Check the new asteroid for it's vecinity to other asteriods.
		bool nv = false;
		for (int i = 0; i < asteroidBelt.size(); i++)
		{
			// If it is withing range of an asteroid set center back to (0,0)
			// This causes it to try again, till it finds a position that works.
			if (abs(center.x - asteroidBelt[i].getCenter().x) <= 20 && abs(center.y - asteroidBelt[i].getCenter().y) <= 20)
			{
				center.x = 0;
				center.y = 0;
			}
		}
	}
	// Generate a random "translation.angle" or directional vector, in radians.
	translation.angle = rand() % 360;
	translation.angle *= M_PI / 180.0;
	//cout << translation.angle << endl;
	translation.w = ((rand() % 16)+1)/4.0;


	// This logging protocal lets us know where the center of the asteroid is. 
#ifdef LOGGING
	//asteroidLogger << "Bottom Left corner of asteroid at : " << center.x << " " << center.y << endl;
#endif

// Random number for seed.
	int i = rand();
	srand (static_cast <unsigned> (time(0))*(i*(0+67)/10));
	point b;
	b.x = rand() % (ASTEROID_MAX_X+1);
	b.y = rand() % (ASTEROID_MAX_Y+1);
	astPnts.push_back(b); 

// This generates the sides. 	
	for (int j = 1; j < numsides; j++)
	{
		//seed the psudo-random number generator. 
		srand (static_cast <unsigned> (time(0))*(i*(j+67)/10));
		// Increment i for the next point.
		i++;
		bool goodpoint = false;
		while(!goodpoint)
		{			
			//generate a random point. 
			b.x = rand() % (ASTEROID_MAX_X+1);
			b.y = rand() % (ASTEROID_MAX_Y+1);
			int goodDistance=0;
			//check  the point against other points. to ensure that they are not of a minimum distance from each other.
			for (int k = j-1; k >= 0; k--)
			{
				// if within that distance try again.
				point a = astPnts[k];
				if(getVectorLength(b, a) >= ASTEROID_MIN_DIST)
				{ 
					goodDistance++;
				}
			}
			if(goodDistance==astPnts.size())
			{
				goodpoint=true;
			}
			// if all is good, add it to the list.
			if(goodpoint)
			{
				astPnts.push_back(b);
			}

		}
		
	}

	sortPoints();
	tessellateAsteriod();
	//translation.angle = drand48();
	float rotation = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
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
	astPnts.push_back(a.a);
	astPnts.push_back(a.b);
	astPnts.push_back(a.c);

	astTris.push_back(a);

	int j = rand();
	srand (static_cast <unsigned> (time(0))*(num*(j+67)/10));	
	Orotation *= 180/M_PI;
	translation.angle = Orotation+num*2;
	translation.angle *= M_PI / 180.0;
	translation.w = (rand()%16+1)/4.0;

	center.x = location.x + offset.x;
	center.y = location.y + offset.y;
#ifdef LOGGING
	//asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
	//asteroidLogger << "Created Simple Asteroid\n\n";
	//asteroidLogger.close();
#endif
}

point asteroid::getCenter()
{
	return center;
}
float asteroid::getVectorLength(point a, point b)
{
	return sqrt(pow(abs(a.x-b.x),2)+pow(abs(a.y-b.y),2));
}


float asteroid::getVectorLength(asteroid b)
{
	return sqrt(pow(abs(center.x-b.getCenter().x),2)+pow(abs(center.y-b.getCenter().y),2));
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
		double bearing = atan2f(center.y-infl[i].getCenter().y, center.x-infl[i].getCenter().x);		
		
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
		if (translation.w>3)
			translation.w = 3;
		if (translation.w < .5)
			translation.w = .5;
	}

	// After we calculate the positions of the asteroids, we need to move them. so we move the center by use of trig.
	center.x += cos(translation.angle)*translation.w/**(60/FPS)*/;
	center.y += sin(translation.angle)*translation.w/**(60/FPS)*/;
	
	//this checks to see if it is still in the octogon them moves it to where it to the other side.
	if(!insideOctogon(center)){
		point position {center.x-origin,center.y-origin,0,1};
		center.x -= 2*position.x; 
		center.y -= 2*position.y; 
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

	center.x = location.x + offset.x;
	center.y = location.y + offset.y;
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
		asteroid a(tmpt, center, tmpp, i, rotate);
		//a.createAsteroid(tmpt, center, tmpp, i);
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
 	vector<point> temp = astPnts;
	// Begin at vertex 0.
	int i=0;

	// While there are more than three vertices left in points, run the following code.
	while(temp.size() > 3)
	{
		// Set the middle vertex as the vertex immediately following i. Set the third vertex as the vertex immediately following j.
		int j=i+1;
		int k=j+1;
		// If j is vertex 0, set j to 0 and k to 1. 
		if(j == temp.size())
		{
			j = 0;
			k = 1;
		}
		// If k is vertex 0, set k to 0.
		else if(k == temp.size())
			k = 0;	
	
		float l1_x = temp.at(i).x - temp.at(j).x;
		float l1_y = temp.at(i).y - temp.at(j).y;
		float l2_x = temp.at(k).x - temp.at(j).x;
		float l2_y = temp.at(k).y - temp.at(j).y;	
		// z is the z component of the cross product of l1 (i to j) and l2 (k to j).
		float z = l1_x*l2_y - l2_x*l1_y;

		// If CW winding occurs, set the starting vertex to j.
		if(z > 0.0)
			i = j;
		// If the middle point lies on a line segment connecting the first and third points, erase it.
		else if(z == 0.0)
			temp.erase(temp.begin() + j);
		// If CCW winding occurs, run the following code.
		else if(z < 0.0)
		{
			// In the special circumstance that k is vertex 2, determine if all the remaining vertices would cause concavity. Determine the z component of the cross product of l1 (k to each remaining vertex) and l2 (i to each remaining vertex).
			float z2 = -1.0;
			if(k == 2)
			{	
				for(int m=3; m<temp.size(); m++)
				{	
					float l1_x = temp.at(k).x - temp.at(m).x;
					float l1_y = temp.at(k).y - temp.at(m).y;
					float l2_x = temp.at(i).x - temp.at(m).x;
					float l2_y = temp.at(i).y - temp.at(m).y;
					z2 = l1_x*l2_y - l2_x*l1_y;
					// If the angle is convex or the points lie on a line, break out of the loop.
					if(z2 <= 0.0)
						break;
				}
			}

			// Declare and initialize the boolean intersection as false.
			bool intersection = false;

			// Check if the newly created diagonal intersects with any formed line segment.
			for(int n=0; n<temp.size()-1; n++)
			{
				bool v = intersect(temp.at(i), temp.at(k), temp.at(n), temp.at(n+1));
				if(v)
					intersection = true;
			}

			// Check if the newly created diagonal intersects with the last line segment.
			bool v = intersect(temp.at(i), temp.at(k), temp.back(), temp.front());
			if(v)
				intersection = true;

			// If no intersection has occurred and no CW winding occurs in the special circumstance, run the following code.
			if(!intersection && z2 <= 0.0)
			{
				// Declare and initalize a triangle holding the three vertices, i, j, and j+1.
				triangle t;
				t.a = temp.at(i);
				t.b = temp.at(j);
				t.c = temp.at(k);
				astTris.push_back(t);

				// Erase the middle vertex.
				temp.erase(temp.begin() + j);

				// If i is not at 0, reset it to 0.
				if(i != 0)
					i = 0;
			}
			// If an intersection has occurred or CW winding occurs in the special circumstance, set the starting vertex to j.
			else
				i = j;
		}
	}
	// Create the final triangle with the remaining three vertices in points.	
	triangle t;
	t.a = temp.front();
	t.b = temp.at(1);
	t.c = temp.back();
	astTris.push_back(t);
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

vector<point> asteroid::getRealPoints(){

	vector<point> v;

	for(int i = 0; i < astPnts.size(); i++){

		point p = {astPnts[i].x + center.x,astPnts[i].y + center.y, 0, 1};
		/*asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
		asteroidLogger << "real points are: " << p.x << " " << p.y << "\n";
		asteroidLogger.close();	*/
		v.push_back(p);
	}
	return v;
}
