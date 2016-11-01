#include "structs.h"

ship createShip(void)
{
	ship enterprise;
	triangle body;
	point a;
	a.x = 550.0;
	a.y = 500.0;
	point b;
	b.x = 450.0;
	b.y = 550.0;
	point c;
	c.x = 450.0;
	c.y = 450.0;
	body.a = a;
	body.b = b;
	body.c = c;
	enterprise.body = body;
	// Rotation will be changed if the user presses the left or right arrow keys.
	enterprise.rotation = 0.0;

	return enterprise;
}
