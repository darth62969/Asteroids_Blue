#include "structs.h"
#include "globals.h"
#include "prototypes.h"

bullet createBullet()
{
	bullet shot;

	// The bullet will originate at the front of the ship.
	shot.location = enterprise.body.a;
	
	// Convert the rotation (float) of enterprise to radians.
	shot.theta = enterprise.rotation * M_PI / 180.0;

	//point translation;
	//translation.x = cos(theta);
	//translation.y = sin(theta);

	/* The translation (point) of shot will indicate how many pixels
	 * shot will move in each pass through the pipeline.
	 */
	//shot.translation = translation;
	//shot.location = {WORLD_COORDINATE_MAX_X/2, WORLD_COORDINATE_MAX_Y/2, 0, 0, 0};


	return shot;
}

void drawBullet(bullet shot){
	
	glBegin(GL_POINTS);
		glVertex2f(shot.location.x, shot.location.y);
	glEnd();
	
}

void fireBullet(bullet shot){
	
	//glTranslatef(shot.translation.x, shot.translation.y, 0.0);
 	point trans = shot.location;
	//rotatePoint(trans, shot.theta);
	glBegin(GL_POINTS);
		glVertex2f(trans.x, trans.y);
	glEnd();
	
	//drawBullet(shot);
}



