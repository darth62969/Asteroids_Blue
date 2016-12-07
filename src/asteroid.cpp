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
vector<point> astPosPnts;
vector<triangle> astTris;
bool clipped;
int numsides = 0;

asteroid::asteroid()
{
/*	todo:
 *	generate random number between 0 and 8;
 * 	add 4 to that number
 *	genreate random points between max_x and max_y
 *	tessellate points and save as triangles
 * 	return asteroid
 */
 	numsides = rand()% (ASTEROID_MAX_SIZE - ASTEROID_MIN_SIZE + 1) + ASTEROID_MIN_SIZE;
#ifdef LOGGING	 
	asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
	asteroidLogger << "Number of sides to generate : " << numsides << endl;
#endif
	center.x = rand() % (WORLD_COORDINATE_MAX_X + 1) + WORLD_COORDINATE_MIN_X;
	center.y = rand() % (WORLD_COORDINATE_MAX_Y + 1) + WORLD_COORDINATE_MIN_Y;
	rotation = rand() % 360;
	rotation *= M_PI / 180.0;
#ifdef LOGGING
	asteroidLogger << "Bottom Left corner of asteroid at : " << center.x << " " << center.y << endl;
#endif
	int i = rand();
	for (int j = 0; j < numsides; j++)
	{
		srand (static_cast <unsigned> (time(0))*(i*(j+67)/10));
		point b;
		b.x = rand() % (ASTEROID_MAX_X+1);
		b.y = rand() % (ASTEROID_MAX_Y+1);
		astPnts.push_back(b);
		i++;
	}

	sortPoints();
	tessellateAsteriod();
	//rotation = drand48();
	float rotation = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
#ifdef LOGGING	
	asteroidLogger << "Rotation was set to : " << rotation << "\n\n";
	asteroidLogger.close();
#endif
}

asteroid::asteroid(triangle a, point location, point offset, int num)
{
#ifdef LOGGING
	asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
	asteroidLogger << "Creating Simple Asteroid #" << num << endl;
	asteroidLogger.close();
#endif
	astPnts.push_back(a.a);
	astPnts.push_back(a.b);
	astPnts.push_back(a.c);

	astTris.push_back(a);

	int j = rand();
	srand (static_cast <unsigned> (time(0))*(num*(j+67)/10));	

	rotation = rand() % 360;
	rotation *= M_PI / 180.0;

	center.x = location.x + offset.x;
	center.y = location.y + offset.y;
#ifdef LOGGING
	asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
	asteroidLogger << "Created Simple Asteroid\n\n";
	asteroidLogger.close();
#endif
}

point asteroid::getCenter()
{
	return center;
}

void asteroid::incrementLocation()
{
	if(paused)
		return;
	center.x += cos(rotation)/2*(60/FPS);
	center.y += sin(rotation)/2*(60/FPS);
	/*	
	switch((int) center.x)
	{
		case WORLD_COORDINATE_MAX_X:
			center.x = WORLD_COORDINATE_MIN_X+1;
			break;
		case WORLD_COORDINATE_MIN_X:
			center.x = WORLD_COORDINATE_MAX_X-1;
			break;
	}

	switch((int) center.y)
	{
		case WORLD_COORDINATE_MAX_Y:
			center.y = WORLD_COORDINATE_MIN_Y+1;
			break;
		case WORLD_COORDINATE_MIN_Y:
			center.y = WORLD_COORDINATE_MAX_Y-1;
			break;
	}
	*/
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
	asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
	asteroidLogger << "Creating Simple Asteroid #" << num << endl;
	asteroidLogger.close();
#endif
	astPnts.clear();
	astPnts.push_back(a.a);
	astPnts.push_back(a.b);
	astPnts.push_back(a.c);
	astTris.clear();	
	astTris.push_back(a);

	int j = rand();
	srand (static_cast <unsigned> (time(0))*(num*(j+67)/10));	

	rotation = rand() % 360;
	rotation *= M_PI / 180.0;

	center.x = location.x + offset.x;
	center.y = location.y + offset.y;
#ifdef LOGGING
	asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
	asteroidLogger << "Created Simple Asteroid\n" << endl;
	asteroidLogger.close();
#endif
}

void asteroid::setPoints(std::vector<point> v){
	astPnts = v;

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
	asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
	asteroidLogger << "Breaking up asteroid into " << astTris.size() << " asteroids.\n";
	asteroidLogger.close();
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
				asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
				asteroidLogger << tmpt.b.x << ">" << tmpt.c.x << endl; 
				asteroidLogger.close();
#endif
				tmpp.x=tmpt.c.x;
				tmpt.a.x-=tmpp.x;
				tmpt.b.x-=tmpp.x;
				tmpt.c.x-=tmpp.x;
			}
			else
			{
#ifdef LOGGING				
				asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
				asteroidLogger << tmpt.c.x << ">" << tmpt.b.x << endl;
				asteroidLogger.close();
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
				asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
				asteroidLogger << tmpt.a.x << ">" << tmpt.c.x << endl;
				asteroidLogger.close(); 
#endif
				tmpp.x=tmpt.c.x;
				tmpt.a.x-=tmpp.x;
				tmpt.b.x-=tmpp.x;
				tmpt.c.x-=tmpp.x;
			}
			else
			{
#ifdef LOGGING
				asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
				asteroidLogger << tmpt.c.x << ">" << tmpt.a.x << endl;
				asteroidLogger.close(); 
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
		
		
		asteroid a(tmpt, center, tmpp, i);
		//a.createAsteroid(tmpt, center, tmpp, i);
		breakup.push_back(a);
	}

	return breakup;
}

point intersect(point v1, point v2, point v3, point v4)
{
	float ua_num = ((v3.x - v1.x) * -(v4.y - v3.y)) - (-(v4.x - v3.x) * (v3.y - v1.y));
	float den = ((v2.x - v1.x) * -(v4.y - v3.y)) - (-(v4.x - v3.x) * (v2.y - v1.y));

	float ub_num = ((v2.x - v1.x) * (v3.y - v1.y)) - ((v3.x - v1.x) * (v2.y - v1.y));

	float ua = ua_num / den;
	float ub = ub_num / den;

	point v;
	v.x = -100;
	v.y = -100;

	if((ua > 0.0) && (ua < 1.0) && (ub > 0.0) && (ub < 1.0))
	{
		v.x = v1.x + ua * (v2.x - v1.x);
		v.y = v1.y + ua * (v2.y - v1.y);
	}

	return v;
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
				point v = intersect(temp.at(i), temp.at(k), temp.at(n), temp.at(n+1));
				if(v.x != -100 && v.y != -100)
					intersection = true;
			}

			// Check if the newly created diagonal intersects with the last line segment.
			point v = intersect(temp.at(i), temp.at(k), temp.back(), temp.front());
			if(v.x != -100 && v.y != -100)
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

