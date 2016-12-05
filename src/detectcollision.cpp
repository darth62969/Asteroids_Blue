/* 
 * Collision Detection Class for Asteroids: RETURN OF METEOR
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

bool intersect(vertex a,vertex b,vertex c,vertex d)
{
    float den = ((d.getY()-c.getY())*(b.getX()-a.getX())-(d.getX()-c.getX())*(b.getY()-a.getY()));
    float num1 = ((d.getX() - c.getX())*(a.getY()-c.getY()) - (d.getY()- c.getY())*(a.getX()-c.getX()));
    float num2 = ((b.getX()-a.getX())*(a.getY()-c.getY())-(b.getY()-a.getY())*(a.getX()-c.getX()));
    float u1 = num1/den;
    float u2 = num2/den;

    if (den == 0 && num1  == 0 && num2 == 0)
        /* The two lines are coincidents */
        return 1;
    if (den == 0)
        /* The two lines are parallel */
        return 0;
    if (u1 <0 || u1 > 1 || u2 < 0 || u2 > 1)
        /* Lines do not collide */
        return 0;
    /* Lines DO collide */
    return 1;
}

void detectCollision(vector <asteroids> a, vector <bullets> b, ship c) 
{
	//Idea:  Narrow down searches by dividing into quadrants? 
	//       Therefore less comparisons and would make game run 
	//       smoother? (Woudl have to figure out how to do intersections
	//       of quadrants. 
	//       or do a 9 by 9 and run a few that are between 
	//
	//       Do a separate list of new asteroids that have to be added.
	//       add them at the end? 


	//checks collisions between asteroids vs asteroids
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = 1; j + 1 < a.size(); j++)
		{
			if (intersect(a[i].x, a[i].y,  a[j].x, a[j].y))
			{
				//reflect code
				a[i].newRotation();
				a[j].newRotation();
			}
		}
	}

	//creates temporary asteroid vector that is later ona dded back.
	vector <asteroid> n;
	
	//checks collisions between asteroids and bullets
	for (int i = 0; i < a.size (); i++)
	{
		for (int j = 0; j < b.size(); j++
		{
			if (intersect(a[i].x, a[i].y,  b[j].x, b[j].y))
			{
				//separates asteroid. 
				a[i].
				
				//delete bullet
			}

		}
	}
	for (int i = 0; i < a.size(); i++)
	{
		//Idea:  Narrow down the asteroids in this one 
		//	 by searching through the asteroids and 
		//	 only take the ones that have ships in a 
		//	 range? 
		//insert code to compare position of ship to asteroids
	}	
}

bool compare (asteroid first, asteroid second)
{
	vector <point> firstPoint = first.getPoints();
	vector <point> secondPoint = second.getPoints();
	for (int i = 0; i < firstPoint.size(); i++)
	{
		for (int j = 0; j < secondPoint.size(); j++)
		{
			if (intersectAsteroids(firstPoint[i], secondPoint [j])
			{
				return 1;
			}
		}
	}
	return 0;
}
