/* 
 * Bullet Operations for Asteroids: RETURN OF METEOR
 * 
 * Made by:
 * Jonathan Oakes
 * Braeden Brettin
 * Ted Dorfeuille 
 * Chris Le
 * Emily Herron
 * 
 * For the class:
 * Intro to Computer Graphics (CSC315)
 * 
 * At:
 * Mercer Univercity  
 */

#include "structs.h"
#include "globals.h"
#include "prototypes.h"

bullet createBullet()
{
	bullet shot;

	// The bullet will originate at the front of the ship.
	shot.location = enterprise.aLocation;
	// Convert the rotation (float) of enterprise to radians.
	shot.theta = enterprise.rotation * M_PI / 180.0;

	return shot;
}

void drawBullet(bullet shot)
{
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

void deleteBullet()
{
	 
}
