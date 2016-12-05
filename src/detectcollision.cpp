
#include "detectcollision.h"

bool intersect(vertex a,vertex b,vertex c,vertex d)
{
    float den = ((d.y-c.y)*(b.x-a.x)-(d.x-c.x)*(b.y-a.y));
    float num1 = ((d.x - c.x)*(a.y-c.y) - (d.y- c.y)*(a.x-c.x));
    float num2 = ((b.x-a.x)*(a.y-c.y)-(b.y-a.y)*(a.x-c.x));
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


void detectCollision:: detectCollision(vector <asteroids> a, vector <bullets> b1, ship c1) 
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
	//looks at asteroids
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = i+1; j < a.size()-1; j++)
		{
			vector <point> a1;
			a1 = a[i].getTesPoints();
			vector <point> a2;
			a2 = a[j].getTesPoints();
			for (int k = 0; k < a1.size(); k++)
			{
				for (int l = 0; l < a2.size(); l++)
				{
					if (k==a1.size()-1 && l ==a2.size()-1)
					{
						if (intersect(a1[k], a1[0],  a2[l], a2[0]))
						{	
							//reflect code
							a[i].newRotation();
							a[j].newRotation();
						}	

					}	
					else if(k == a1.size()-1)
					{
						if (intersect(a1[k], a1[0],  a2[l], a2[l+1]))
						{	
							//reflect code
							a[i].newRotation();
							a[j].newRotation();
						}	
					}
					else if (l == a2.size()-1)
					{
						if (intersect(a1[k], a1[k+1],  a2[l], a2[l+1]))
						{	
							//reflect code
							a[i].newRotation();
							a[j].newRotation();
						}	
					}
					else
					{
						if (intersect(a1[k], a1[k+1],  a2[l], a2[l+1]))
						{	
							//reflect code
							a[i].newRotation();
							a[j].newRotation();
						}
					}
				}
			}	
		}	
	}
	//creates temporary asteroid vector that is later ona dded back.
	vector <asteroid> n;
	
	//checks collisions between asteroids and bullets
	for (int i = 0; i < a.size (); i++)
	{
		vector<point> a3;
		a3 = a[i].getTesPoints();
		for (int j = 0; j < a3.size(); j++)
		{
			for (int k = 0; k < b1.size(); k++)
			{
				if (j == a3.size()-1)
				{
					if(intersect(a3[j], a3[0], b1[j], b1[j]))
					{
						//separate asteroid
						vector <asteroid> tmp;
						tmp = breakupAsteroid(a3[j]);
						n.insert(a.end(), tmp.begin(), tmp.end());
						for (int m = i; m < a.size()-1; m++)
						{
							a[m] = a[m+1];
						}
						a.pop_back();

						//delete bullet
						for (int l = j; l < b1.size()-1; l++)
						{
							b1[j] = b1[j+1];
						}
						b1.pop_back();
						
						//add score
					}
				}
				else if (intersect(a3[i], a3[i+1],  b[j], b[j]))
				{
					//separates asteroid. 
					vector <asteroid> tmp;
					tmp = breakupAsteroid(a3[j]);
					n.insert(a.end(), tmp.begin(), tmp.end());
					for (int m = i; m < a.size()-1; m++)
					{
						a[m] = a[m+1];
					}
					a.pop_back();

					//delete bullet
					for (int l = j; l < b1.size()-1; l++)
					{
						b1[j] = b1[j+1];
					}
					b1.pop_back();

					//add to score
				}
			}
		}
	}
		//collision of a ship vs asteroids
		for (int i = 0; i < a.size(); i++)
		{
			//Idea:  Narrow down the asteroids in this one 
			//	 by searching through the asteroids and 
			//	 only take the ones that have ships in a 
			//	 range? 
			//insert code to compare position of ship to asteroids
			for (int j = 0; j < b.size(); j++)
			{
//				if (intersect(a[i], a[i].y, c[j]
			}
		}	
	}
}	
