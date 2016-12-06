/* 
 * Ship Operations for Asteroids: RETURN OF METEOR
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

#include "headers.h"
#include "structs.h"
#include "globals.h"
#include "prototypes.h"

ship createShip(void)
{
	/* 
	 * Create a ship, enterprise, in the middle of the window.
	 */

	// Create Ship
	ship temp;

	// Set the values to the ship's grid, these don't get changed.
	temp.body.a.x = 2;
	temp.body.a.y = 0.0;
	temp.body.b.x = -2.0;
	temp.body.b.y = -1.0;
	temp.body.c.x = -2;
	temp.body.c.y = 1.0;

	// Rotation will be changed if the user presses the left or right arrow keys.
	temp.rotation = 0.0;

	return temp;
}

// This is the function that draws the ship. 
void drawShip(ship a)
{
	/*
	 * Here we create a temporary point that we use to preform operations on and to draw the ship.
	 * We scale the this point and then rotate it so that it is the proper size for it to show properly
	 * Then we translate these points directly by the half the Max size of the World Coordinates  
	 */

	//Create Point to hold temperary points to draw the ship
	point b[3];

	//Copy the points in the ship (a) to b
	b[0] = {a.body.a.x, a.body.a.y, a.body.a.z, a.body.a.w, a.body.a.angle};
	b[1] = {a.body.b.x, a.body.b.y, a.body.b.z, a.body.b.w, a.body.b.angle};
	b[2] = {a.body.c.x, a.body.c.y, a.body.c.z, a.body.c.w, a.body.c.angle};

	//Now we want to scale each point then rotate it into position
	for (int i = 0; i < 3; i++)
	{
		scalePoint(b[i], 7);
		rotatePoint(b[i], a.rotation);
	}

	//We want to save the location of the nose of the ship for use with the positioning of bullets later on
	enterprise.aLocation = {b[0].x+WORLD_COORDINATE_MAX_X/2, b[0].y+WORLD_COORDINATE_MAX_Y/2} ;

	///Now we want to draw the ship.
	glBegin(GL_TRIANGLES);
		for(int i = 0; i<3; i++)
		{    
			glVertex2d(b[i].x + WORLD_COORDINATE_MAX_X/2, b[i].y + WORLD_COORDINATE_MAX_Y/2);
		}
	glEnd();
}

