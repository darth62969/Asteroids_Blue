#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "headers.h"
#include "mode.h"
#include "structs.h"

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
		virtual void doAction(mode * md);
		void tessellate(layer* lyr);

		virtual bool collides(object* other);
		virtual bool collides(std::shared_ptr<object> other);

		//get / set
		//virtual char* getType();
		point getLocation();
		void setLocation(double x, double y);
		void setLocation(point loc);
		double getRotation();
		void setRotation( double rot );
		virtual std::vector<point> getBounds();
		virtual std::vector<triangle> getTess();
		float getVectorLength(object * other);
		float getVectorLength(std::shared_ptr<object> other);
		
	protected:
		point location;


		/* 
		 * Base layer 0 is always the bounds of the object. 
		 * Use Layer 0 for collision detection
		 */
		std::vector<layer> lyrs;


};

#endif