
#include "detectcollision.h"

bool detectCollision:: detectCollision(vector <asteroids> a, vector <bullets> b, ship c) 
{
	//Idea:  Narrow down searches by dividing into quadrants? 
	//       Therefore less comparisons and would make game run 
	//       smoother? (Woudl have to figure out how to do intersections
	//       of quadrants. 
	//       or do a 9 by 9 and run a few that are between 
	//
	//       Do a separate list of new asteroids that have to be added.
	//       add them at the end? 
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = 1; j + 1 < a.size(); j++)
		{
			//insert code to get points from asteroids and compare
			if (compare (a[i], a[j]))
			{
				//reflect code
			}
		}
	}
	for (int i = 0; i < a.size (); i++)
	{
		for (int j = 0; j < b.size(); j++
		{
			//insert code to compare asteroids and bullets
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
