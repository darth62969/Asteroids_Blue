#include "headers.h"
#include "structs.h"
#include "globals.h"
#include "prototypes.h"

float rotation;
point translation;
std::vector<point> astPnts;
std::vector<triangle> astTris;
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
 	
	while (numsides<ASTEROID_MIN_SIZE) 
		numsides = lrand48()%ASTEROID_MAX_SIZE;
	std::cout << "number of sides to generate " << numsides << std::endl;
	for (int i = 0; i < numsides; i++)
	{
		point b;
		b.x= lrand48()%ASTEROID_MAX_X;
		b.y= lrand48()%ASTEROID_MAX_Y;
		astPnts.push_back(b);
		std::cout << "generated x: " << b.x << " generated y:" << b.y << std::endl;
	}

	rotation = drand48();
	std::cout << "rotation was set to " << rotation << std::endl;
}

std::vector<asteroid> asteroid::breakupAsteroid()
{
/*	todo:
 *	get trinagle set to a.
 *	createAsteroid(traingle a)
 * 	repeat till last triangle pointer.
*/
}
