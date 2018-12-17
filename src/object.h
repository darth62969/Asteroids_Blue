#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "structs.h"
#include <vector>
#include <random>

struct layer
{
	std::vector<point>    pnts;
	std::vector<triangle> tris;
	color clr;
};


class object
{
	public:
		//Virtual Fucntions
		virtual void render() = 0;
		virtual void doAction();
		void tessellate(layer* lyr);

		//get / set
		point getLocation();
		void setLocation(double x, double y);
		void setLocation(point loc);
		double getRotation();
		void setRotation( double rot );
		virtual std::vector<point> getBounds();
		
	protected:
		point location;

		/* 
		 * Base layer 0 is always the bounds of the object. 
		 * Use Layer 0 for collision detection
		 */
		std::vector<layer> lyrs;


};


#endif