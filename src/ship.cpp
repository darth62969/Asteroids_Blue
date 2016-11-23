#include "headers.h"
#include "structs.h"
#include "globals.h"
#include "prototypes.h"



ship createShip(void)
{
	/* Create a ship, enterprise, with points at (450, 450), (450, 550), and (550, 500).
	 * These points will need to be changed later depending on the size of our window.
	 */
	
	printf("world coords  %d %d\n", WORLD_COORDINATE_MAX_X/2, WORLD_COORDINATE_MAX_Y/2);	

	ship temp;
	triangle body;
	point a;
	a.x = 14.0 + WORLD_COORDINATE_MAX_X/2;
	a.y = 0.0 + WORLD_COORDINATE_MAX_Y/2;
	point b;
	b.x = -14.0 + WORLD_COORDINATE_MAX_X/2;
	b.y = -7.0 + WORLD_COORDINATE_MAX_Y/2;
	point c;
	c.x = -14.0 + WORLD_COORDINATE_MAX_X/2;
	c.y = 7.0 + WORLD_COORDINATE_MAX_Y/2;
	body.a = a;
	body.b = b;
	body.c = c;
	temp.body = body;

	printf("ship original location\n%f %f\n%f %f\n %f %f\n", temp.body.a.x, temp.body.a.y, temp.body.b.x, temp.body.b.y, temp.body.c.x, temp.body.c.y);


	// Rotation will be changed if the user presses the left or right arrow keys.
	temp.rotation = 0.0;

	return temp;
}  


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


void drawShip(ship s){

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
		for(int i = 0; i<3; i++)
		{    
			glVertex2d(s.body.a.x, s.body.a.y);
			glVertex2d(s.body.b.x, s.body.b.y);
			glVertex2d(s.body.c.x, s.body.c.y);
			printf("drew ship at %f %f\n%f %f\n %f %f\n", s.body.a.x, s.body.a.y, s.body.b.x, s.body.b.y, s.body.c.x, s.body.c.y);
		}
	glEnd();
}
