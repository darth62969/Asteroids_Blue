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
	 * Create a ship, enterprise, with points at (450, 450), (450, 550), and (550, 500).
	 * These points will need to be changed later depending on the size of our window.
	 */
	
	//printf("world coords  %d %d\n", WORLD_COORDINATE_MAX_X/2, WORLD_COORDINATE_MAX_Y/2);	

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

	//printf("ship original location\n%f %f\n%f %f\n %f %f\n", temp.body.a.x, temp.body.a.y, temp.body.b.x, temp.body.b.y, temp.body.c.x, temp.body.c.y);

	return temp;
}  


// I don't think we use this function at all... 
void rotateShip(ship& s){

	float TM[4][4];

	//translatePoint(s.body.a, -(WORLD_COORDINATE_MAX_X/2), -(WORLD_COORDINATE_MAX_Y/2), 0.0);
	//translatePoint(s.body.b, -(WORLD_COORDINATE_MAX_X/2), -(WORLD_COORDINATE_MAX_Y/2), 0.0);
	//translatePoint(s.body.c, -(WORLD_COORDINATE_MAX_X/2), -(WORLD_COORDINATE_MAX_Y/2), 0.0);

	printf("begining ship rotation  %f %f\n%f %f\n %f %f\n", s.body.a.x, s.body.a.y, s.body.b.x, s.body.b.y, s.body.c.x, s.body.c.y);

	s.body.a.x -= WORLD_COORDINATE_MAX_X/2.0; s.body.a.y -= WORLD_COORDINATE_MAX_Y/2.0;
	s.body.b.x -= WORLD_COORDINATE_MAX_X/2.0; s.body.b.y -= WORLD_COORDINATE_MAX_Y/2.0;
	s.body.c.x -= WORLD_COORDINATE_MAX_X/2.0; s.body.c.y -= WORLD_COORDINATE_MAX_Y/2.0;
	
	printf("ship translated to origin  %f %f\n%f %f\n %f %f\n", s.body.a.x, s.body.a.y, s.body.b.x, s.body.b.y, s.body.c.x, s.body.c.y);
	
	rotatePointB(s.body.a, s.rotation);
    rotatePointB(s.body.b, s.rotation);
    rotatePointB(s.body.c, s.rotation);

	
	printf("ship rotated  %f %f\n%f %f\n %f %f\n", s.body.a.x, s.body.a.y, s.body.b.x, s.body.b.y, s.body.c.x, s.body.c.y);

	s.body.a.x += WORLD_COORDINATE_MAX_X/2.0; s.body.a.y += WORLD_COORDINATE_MAX_Y/2.0;
    s.body.b.x += WORLD_COORDINATE_MAX_X/2.0; s.body.b.y += WORLD_COORDINATE_MAX_Y/2.0;
    s.body.c.x += WORLD_COORDINATE_MAX_X/2.0; s.body.c.y += WORLD_COORDINATE_MAX_Y/2.0;


/*	
	rotatePointB(s.body.a, s.rotation);
	rotatePointB(s.body.b, s.rotation);
	rotatePointB(s.body.c, s.rotation); 	
*/	
	printf("ship translated to center  %f %f\n%f %f\n %f %f\n", s.body.a.x, s.body.a.y, s.body.b.x, s.body.b.y, s.body.c.x, s.body.c.y);
/*
	translatePoint(s.body.a, WORLD_COORDINATE_MAX_X/2.0, WORLD_COORDINATE_MAX_Y/2.0, 0.0);
        translatePoint(s.body.b, WORLD_COORDINATE_MAX_X/2.0, WORLD_COORDINATE_MAX_Y/2.0, 0.0);
        translatePoint(s.body.c, WORLD_COORDINATE_MAX_X/2.0, WORLD_COORDINATE_MAX_Y/2.0, 0.0);
*/
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
		//translatePoint(b[i], WORLD_COORDINATE_MAX_X/2, WORLD_COORDINATE_MAX_Y/2, 0);
	}

	//We want to save the location of the nose of the ship for use with the positioning of bullets later on
	enterprise.aLocation = {b[0].x+WORLD_COORDINATE_MAX_X/2, b[0].y+WORLD_COORDINATE_MAX_Y/2} ;

	///Now we want to draw the ship.
	glBegin(GL_TRIANGLES);
		for(int i = 0; i<3; i++)
		{    
			glVertex2d(b[i].x + WORLD_COORDINATE_MAX_X/2, b[i].y + WORLD_COORDINATE_MAX_Y/2);
			//glVertex2d(b[(i+1)%3].x + WORLD_COORDINATE_MAX_X/2, b[(i+1)%3].y + WORLD_COORDINATE_MAX_Y/2);
		}
	glEnd();
}

