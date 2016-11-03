#include "structs.h"
#include "headers.h"

ship createShip(void)
{
	/* Create a ship, enterprise, with points at (450, 450), (450, 550), and (550, 500).
	 * These points will need to be changed later depending on the size of our window.
	 */
	ship temp;
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
	temp.body = body;

	// Rotation will be changed if the user presses the left or right arrow keys.
	temp.rotation = 0.0;

	return temp;
}
