#include "structs.h"
#include "globals.h"
#include "prototypes.h"

bullet createBullet(void)
{
	bullet shot;

	// The bullet will originate at the front of the ship.
	shot.location = enterprise.body.a;
	
	// Convert the rotation (float) of enterprise to radians.
	double theta = enterprise.rotation * M_PI / 180.0;

	point translation;
	translation.x = cos(theta);
	translation.y = sin(theta);

	/* The translation (point) of shot will indicate how many pixels
	 * shot will move in each pass through the pipeline.
	 */
	shot.translation = translation;

	return shot;
}
