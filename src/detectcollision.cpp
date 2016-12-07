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
#include "prototypes.h"

//checks proximity of asteroids
bool asteroidProximity (asteroid ast1, asteroid ast2)
{
	if (abs(ast2.getCenter().x - ast1.getCenter().x) <= 20 && abs(ast2.getCenter().y - ast1.getCenter().y <= 20))
	{
		return 1;
	}
	else
	{
		return 0; 
	}
}

//checks proximity of asteroids and bullets
bool bulletProximity (asteroid ast1, bullet b1)
{
	if (abs(b1.location.x - ast1.getCenter().x) <= 20 && abs(b1.location.y - ast1.getCenter().y <= 20))
	{
		return 1;
	}
	else
	{
		return 0; 
	}
}

//checks proximity of ship and asteroid
bool shipProximity (asteroid ast1, vector <point> b2)
{
	int x = (b2[0].x + b2[1].x + b2[2].x)/3;  int y = (b2[0].y + b2[1].y + b2[2].y)/3;
	if (abs(x - ast1.getCenter().x) <= 20 && abs(y - ast1.getCenter().y <= 20))
	{
		return 1;
	}
	else
	{
		return 0; 
	}
}

bool intersect1 (point v1, point v2, point v3, point v4)
{
	point v;
	v = intersect(v1,v2,v3,v4);
	if (v.x == -100 && v.y == -100)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void detectCollision(vector <asteroid> a, vector <bullet> b, ship c) 
{
	//Idea:  Narrow down searches by dividing into quadrants? 
	//       Therefore less comparisons and would make game run 
	//       smoother? (Woudl have to figure out how to do intersections
	//       of quadrants. 
	//       or do a 9 by 9 and run a few that are between 
	//
	//       Do a separate list of new asteroids that have to be added.
	//       add them at the end? 
	

	//creates a temporary array of vectors to stop new vectors
	vector <asteroid> n;

	//checks collision between asteroids vs asteroids
	for (int i = 0; i < a.size(); i++)//asteroid 1
	{
		//checks collisions between asteroids and bullets
		//gets points of asteroid 1
		vector <point> a1;
		a1 = a[i].getPoints();

		//collision of a ship vs asteroids
		//Idea:  Narrow down the asteroids in this one 
		//	 by searching through the asteroids and 
		//	 only take the ones that have ships in a 
		//	 range? 
			
		//gets points of ship
		vector <point> cmd; 
		cmd.push_back(c.body.a); cmd.push_back(c.body.b); cmd.push_back(c.body.c);
		if (shipProximity (a[i], cmd))
		{
			for (int j = 0; j < a1.size(); j++)
			{
				for (int k = 0; k < cmd.size(); k++)
				{	
					//makes sure to check every line
					if (j == a1.size()-1 && k == cmd.size()-1)
					{
						if(intersect1(a1[j], a1[0], cmd[k], cmd[0]))
						{
							//gameover code
						}
					}
					else if(j == a1.size()-1)
					{
						if (intersect1(a1[j], a1[0],  cmd[k], cmd[k+1]))
						{	
							//gameover code
						}	
					}
					else if (k == cmd.size()-1)
					{
						if (intersect1(a1[j], a1[j+1],  cmd[k], cmd[0]))
						{	
							//gameover code
						}	
					}
					else
					{
						if (intersect1(a1[j], a1[j+1],  cmd[k], cmd[k+1]))
						{	
							//gameover code
						}
					}
				}
			}
		}

		//collision of asteroid and bullet
		bool collision = false; 
		for (int j = 0; j < b.size(); j++)
		{
			//if the asteroid is already collided, ignore asteroid
			if(collision == 1)
			{
				break;
			}
			else
			{
				if (bulletProximity (a[i], b[j]))
				{
					for (int k = 0; k < a1.size(); k++)
					{
						if (k == a1.size()-1)
						{
							if(intersect1(a1[k], a1[0], b[j].location, b[j].location))
							{
								//separate asteroid
								vector <asteroid> tmp;
								tmp = a[i].breakupAsteroid();
	
								//deletes asteroid
								for (int l = i; l < a.size()-1; l++)
								{
									a[l] = a[l+1];
								}
								a.pop_back();
	
								//prepares to add asteroids
								n.insert(n.end(), tmp.begin(), tmp.end());
	
								//delete bullet
								for (int l = j; l < b.size()-1; l++)
								{
									b[j] = b[j+1];
								}
								b.pop_back();
								
								//add score
	
								
								collision = true; 
								//breaks out of checking specific bullet loop
								break;
							}
						}
						else 
						{
							if (intersect1(a1[k], a1[k+1],  b[j].location, b[j].location))
							{
								//separate asteroid
								vector <asteroid> tmp;
								tmp = a[i].breakupAsteroid();
	
								//deletes asteroid
								for (int l = i; l < a.size()-1; l++)
								{
									a[l] = a[l+1];
								}
								a.pop_back();
	
								//prepares to add asteroids
								n.insert(n.end(), tmp.begin(), tmp.end());
	
								//delete bullet
								for (int l = j; l < b.size()-1; l++)
								{
									b[j] = b[j+1];
								}
								b.pop_back();
								
								//add score
	
	
								collision = true; 
								//breaks out of checking specific bullet loop
								break;
							}
						}						
					}
				}
			}
		}

		//asteroid asteroid collision 
		//if collision has already occured ignore specific asteroid for now
		if(collision == 1)
		{
			
		}
		else
		{
			if (i = a.size()-1)
			{
			}
			else
			{
				for (int j = i+1; j < a.size(); j++) //asteroid2
				{
					if(collision == 1) break;
					//gets points of asteroid 2
					vector <point> a2;
					a2 = a[j].getPoints();
				
					//checks for proximity 
					if (asteroidProximity (a[i], a[j]))
					{
						for (int k = 0; k < a1.size(); k++) //checks points of asteroid 1
						{
							if(collision==1) break;
							for (int l = 0; l < a2.size(); l++) //checks points of asteroid 2
							{
								if(collision==1) break;
								vector<asteroid> tmp3; vector<asteroid> tmp2;
								//checks final line of both asteorids
								if (k==a1.size()-1 && l ==a2.size()-1)
								{
									if (intersect1(a1[k], a1[0],  a2[l], a2[0]))
									{	
										//if intersections
										//breaks asteroids and stores in new vector		
										tmp3 = a[i].breakupAsteroid(); tmp2 = a[i+1].breakupAsteroid();
										tmp3.insert(tmp3.end(),tmp2.begin(),tmp2.end());
										n.insert(n.end(),tmp3.begin(),tmp3.end());	
			
										//deletes the two asteroids
										for (int m = i; m < a.size(); m++)
										{
											a[m] = a[m+1];
										}
										a.pop_back();

										for (int m = i; m < a.size(); m++)
										{
											a[m] = a[m+1];
										}
										a.pop_back();

										collision = true;
										break; 
									}	
			
								}	

								else if(k == a1.size()-1)
								{
									if (intersect1(a1[k], a1[0],  a2[l], a2[l+1]))
									{	
										//if intersections
										//breaks asteroids and stores in new vector		
										tmp3 = a[i].breakupAsteroid(); tmp2 = a[i+1].breakupAsteroid();
										tmp3.insert(tmp3.end(),tmp2.begin(),tmp2.end());
										n.insert(n.end(),tmp3.begin(),tmp3.end());	
			
										//deletes the two asteroids
										for (int m = i; m < a.size(); m++)
										{
											a[m] = a[m+1];
										}
										a.pop_back();

										for (int m = i; m < a.size(); m++)
										{
											a[m] = a[m+1];
										}
										a.pop_back();

										collision = true;
										break; 
									}	
								}
								else if (l == a2.size()-1)
								{
									if (intersect1(a1[k], a1[k+1],  a2[l], a2[l+1]))
									{	
										//if intersections
										//breaks asteroids and stores in new vector		 
										tmp3 = a[i].breakupAsteroid(); tmp2 = a[i+1].breakupAsteroid();
										tmp3.insert(tmp3.end(),tmp2.begin(),tmp2.end());
										n.insert(n.end(),tmp3.begin(),tmp3.end());	
			
										//deletes the two asteroids
										for (int m = i; m < a.size(); m++)
										{
											a[m] = a[m+1];
										}
										a.pop_back();

										for (int m = i; m < a.size(); m++)
										{
											a[m] = a[m+1];
										}
										a.pop_back();

										collision = true;
										break; 
									}	
								}
								else
								{
									if (intersect1(a1[k], a1[k+1],  a2[l], a2[l+1]))
									{	
										//if intersections
										//breaks asteroids and stores in new vector		
										tmp3 = a[i].breakupAsteroid(); tmp2 = a[i+1].breakupAsteroid();
										tmp3.insert(tmp3.end(),tmp2.begin(),tmp2.end());
										n.insert(n.end(),tmp3.begin(),tmp3.end());	
			
										//deletes the two asteroids
										for (int m = i; m < a.size(); m++)
										{
											a[m] = a[m+1];
										}
										a.pop_back();

										for (int m = i; m < a.size(); m++)
										{
											a[m] = a[m+1];
										}
										a.pop_back();

										collision = true;
										break; 
									}
								}
							}
						}	
					}
				}	
			}
			if (collision == 1) i--;
		}
	}
	if(n.size() != 0)
	{
		a.insert(a.end(),n.begin(),n.end());
	}	
}		
