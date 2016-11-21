#include "headers.h"
#include "structs.h"
#include "globals.h"
#include "prototypes.h"



ship createShip(void)
{
	/* Create a ship, enterprise, with points at (450, 450), (450, 550), and (550, 500).
	 * These points will need to be changed later depending on the size of our window.
	 */
	ship temp;
	triangle body;
	point a;
	a.x = 1;
	a.y = 0;
	point b;
	b.x = -1.0;
	b.y = -1.0;
	point c;
	c.x = -1.0;
	c.y = 1.0;
	body.a = a;
	body.b = b;
	body.c = c;
	temp.body = body;

	// Rotation will be changed if the user presses the left or right arrow keys.
	temp.rotation = 0.0;

	return temp;
}
/*
void rotate(){
	glTranslatef(WINDOW_MAX/2, WINDOW_MAX/2, 0.0);
	glRotatef(rotation, 0.0, 0.0, 1.0);
	glTranslatef(-(WINDOW_MAX/2), -(WINDOW_MAX/2), 0.0);  
}*/

void drawShip(ship a)
{
	point b[3];
	b[0] = {a.body.a.x, a.body.a.y, a.body.a.z, a.body.a.w, a.body.a.angle};
	b[1] = {a.body.b.x, a.body.b.y, a.body.b.z, a.body.b.w, a.body.b.angle};
	b[2] = {a.body.c.x, a.body.c.y, a.body.c.z, a.body.c.w, a.body.c.angle};
	for (int i =0; i < 3; i++)
	{
		scalePoint(b[i], 10);
		rotatePoint(b[i], a.rotation);
		//translatePoint(b[i], WORLD_COORDINATE_MAX_X/2, WORLD_COORDINATE_MAX_Y/2, 0);
	}
	glBegin(GL_LINES);
		for(int i = 0; i<3; i++)
		{
			glVertex2d(b[i].x + WORLD_COORDINATE_MAX_X/2, b[i].y + WORLD_COORDINATE_MAX_Y/2);
			glVertex2d(b[(i+1)%3].x + WORLD_COORDINATE_MAX_X/2, b[(i+1)%3].y + WORLD_COORDINATE_MAX_Y/2);
		}
	glEnd();
}

