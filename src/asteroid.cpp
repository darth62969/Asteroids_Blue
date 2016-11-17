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
/*	todo:
 *	generate raondome number between 0 and 8;
 * 	add 12 to that number
 *	genreate randome points between max_x and max_y
 *	teslate points save as triangles
 * 	return asteroid
 */
	numsides = rand()% (ASTEROID_MAX_SIZE-ASTEROID_MIN_SIZE + 1) + ASTEROID_MIN_SIZE;
	cout << "number of sides to generate " << numsides;
	center.x = rand() % (WORLD_COORDINATE_MAX_X + 1) + WORLD_COORDINATE_MIN_X;
	center.y = rand() % (WORLD_COORDINATE_MAX_Y + 1) + WORLD_COORDINATE_MIN_Y;
	cout << "\tcenter of asteroid at " << center.x << " " << center.y << endl;
	int i = rand();
	for (int j = 0; j < numsides; j++)
	{
		srand (static_cast <unsigned> (time(0))*(i*(j+67)/10));
		point b;
		b.x = rand() % (ASTEROID_MAX_X+1);
		b.y = rand() % (ASTEROID_MAX_Y+1);
		astPnts.push_back(b);
		i++;
	//	std::cout << "generated x: " << b.x << " generated y:" << b.y << std::endl;
	}

	sortPoints();
	//rotation = drand48();
	float rotation = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	cout << "rotation was set to " << rotation << std::endl;
}

point asteroid::getCenter()
{
	return center;
}

vector<asteroid> asteroid::breakupAsteroid()
{
/*	todo:
 *	get trinagle set to a.
 *	createAsteroid(traingle a)
 * 	repeat till last triangle pointer.
*/

	for(int i = 0; i < astTris.size(); i++)
 


}

void asteroid::tessilateAsteriod()
{
/* 	todo:
 * 	Organize points in astPnts in counterclockwise direction
 *	Create Triangles from astPnts and save them in to astTris
 */
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

float asteroid::getRotation()
{
	return rotation;
}
