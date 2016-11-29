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
	a.x = 2;
	a.y = 0.0;
	point b;
	b.x = -2.0;
	b.y = -1.0;
	point c;
	c.x = -2;
	c.y = 1.0;
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


void drawShip(ship a)
{
	point b[3];
	b[0] = {a.body.a.x, a.body.a.y, a.body.a.z, a.body.a.w, a.body.a.angle};
	b[1] = {a.body.b.x, a.body.b.y, a.body.b.z, a.body.b.w, a.body.b.angle};
	b[2] = {a.body.c.x, a.body.c.y, a.body.c.z, a.body.c.w, a.body.c.angle};
	for (int i = 0; i < 3; i++)
	{
		scalePoint(b[i], 7);
		rotatePoint(b[i], a.rotation);
		//translatePoint(b[i], WORLD_COORDINATE_MAX_X/2, WORLD_COORDINATE_MAX_Y/2, 0);
	}
	enterprise.aLocation = {b[0].x+WORLD_COORDINATE_MAX_X/2, b[0].y+WORLD_COORDINATE_MAX_Y/2} ;
	glBegin(GL_TRIANGLES);
		for(int i = 0; i<3; i++)
		{    
			glVertex2d(b[i].x + WORLD_COORDINATE_MAX_X/2, b[i].y + WORLD_COORDINATE_MAX_Y/2);
			//glVertex2d(b[(i+1)%3].x + WORLD_COORDINATE_MAX_X/2, b[(i+1)%3].y + WORLD_COORDINATE_MAX_Y/2);
		}
	glEnd();
}

