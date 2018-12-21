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
 * Mercer University  
 */

#include "prototypes.h"
#include "globals.h"
#include "headers.h"

//checks proximity of asteroids
bool asteroidProximity(asteroid ast1, asteroid ast2)
{
	if (	abs(ast2.getLocation().x - ast1.getLocation().x) <= ASTEROID_MAX_X 
		&& 	abs(ast2.getLocation().y - ast1.getLocation().y) <= ASTEROID_MAX_Y)
	{
		return true;
	}
	else
		return false; 
}

//checks proximity of asteroids and bullets
bool bulletProximity(asteroid ast1, bullet b1)
{
	if (	abs(b1.getLocation().x - ast1.getLocation().x) <= ASTEROID_MAX_X 
		&& 	abs(b1.getLocation().y - ast1.getLocation().y) <= ASTEROID_MAX_Y)
	{
		return true;
	}
	else
		return false; 
}
bool bulletProximity(ship shp1, bullet b1)
{
	if (	abs(b1.getLocation().x - shp1.getLocation().x) <= 50 
		&& 	abs(b1.getLocation().y - shp1.getLocation().y) <= 50)
	{
		return true;
	}
	else
		return false; 
}

//checks proximity of ship and asteroid
bool shipProximity(asteroid ast1, vector<point> b2)
{
	int x = (b2[0].x + b2[1].x + b2[2].x)/3;
	int y = (b2[0].y + b2[1].y + b2[2].y)/3;

	if (	abs(x - ast1.getLocation().x) <= ASTEROID_MAX_X*5 
		&& 	abs(y - ast1.getLocation().y) <= ASTEROID_MAX_Y*5)
	{
		return true;
	}
	else
		return false; 
}

bool intersect(point v1, point v2, point v3, point v4)
{
	float ua_num = ((v3.x - v1.x) * -(v4.y - v3.y)) - (-(v4.x - v3.x) * (v3.y - v1.y));
	float den = ((v2.x - v1.x) * -(v4.y - v3.y)) - (-(v4.x - v3.x) * (v2.y - v1.y));

	float ub_num = ((v2.x - v1.x) * (v3.y - v1.y)) - ((v3.x - v1.x) * (v2.y - v1.y));

	float ua = ua_num / den;
	float ub = ub_num / den;

	point v;
	v.x = -100;
	v.y = -100;

	if((ua > 0.0) && (ua < 1.0) && (ub > 0.0) && (ub < 1.0))
	{
		return true;
	}

	return false;
}

void detectCollision(int index) 
{
	//Idea:  Narrow down searches by dividing into quadrants? 
	//       Therefore less comparisons and would make game run 
	//       smoother? (Would have to figure out how to do intersections
	//       of quadrants. 
	//       or do a 9 by 9 and run a few that are between 
	//
	//       Do a separate list of new asteroids that have to be added.
	//       add them at the end? 
	
	//creates a temporary array of vectors to stop new vectors
	vector<asteroid> n;

	//gets points of asteroid 1
	vector<point> a1;
	switch (GameMode)
	{
		case 0:
		case 1:
			a1 = asteroidBelt[index].getPoints();
			break;
		case 2:
			a1 = enemies[index].getPoints();
	}
	

	//collision of a ship vs asteroids
	//Idea:  Narrow down the asteroids in this one 
	//	 by searching through the asteroids and 
	//	 only take the ones that have ships in a 
	//	 range? 
		
	//gets points of ship
	
	vector<point> cmd;
	cmd=player.getPoints();

	switch (GameMode)
	{
		case 0:
		case 1:
			// If the ship is in proximity of the asteroid, check every line segment to see if a collision actually occurs.
			if (shipProximity(asteroidBelt[index], cmd))
			{
				for (int j = 0; j < a1.size(); j++)
				{
					for (int k = 0; k < cmd.size(); k++)
					{	
						//makes sure to check every line
						if (j == a1.size()-1 && k == cmd.size()-1)
						{

							point tempj;
							tempj.x = a1[j].x + asteroidBelt[index].getLocation().x;
							tempj.y = a1[j].y + asteroidBelt[index].getLocation().y;
							point temp0;
							temp0.x = a1[0].x + asteroidBelt[index].getLocation().x;
							temp0.y = a1[0].y + asteroidBelt[index].getLocation().y;

							if (intersect(tempj, temp0, cmd[k], cmd[0]))
							{
								asteroidBelt.erase(asteroidBelt.begin()+index);
								player.damageHealth(10);
								if (player.getHealth()>=0)
								{
									//gameover code
									gamestate = 2;
									gameOver = true;
								}
							}
						}
						else if (j == a1.size()-1)
						{	
							point tempj;
							tempj.x = a1[j].x + asteroidBelt[index].getLocation().x;
							tempj.y = a1[j].y + asteroidBelt[index].getLocation().y;
							point temp0;
							temp0.x = a1[0].x + asteroidBelt[index].getLocation().x;
							temp0.y = a1[0].y + asteroidBelt[index].getLocation().y;

							if (intersect(tempj, temp0, cmd[k], cmd[k+1]))
							{	
								asteroidBelt.erase(asteroidBelt.begin()+index);
								player.damageHealth(10);
								if (player.getHealth()<=0)
								{
									//gameover code
									gamestate = 2;
									gameOver = true;
								}
							}	
						}
						else if (k == cmd.size()-1)
						{
							point tempj;
							tempj.x = a1[j].x + asteroidBelt[index].getLocation().x;
							tempj.y = a1[j].y + asteroidBelt[index].getLocation().y;
							point tempj1;
							tempj1.x = a1[j+1].x + asteroidBelt[index].getLocation().x;
							tempj1.y = a1[j+1].y + asteroidBelt[index].getLocation().y;

							if (intersect(tempj, tempj1, cmd[k], cmd[0]))
							{
								asteroidBelt.erase(asteroidBelt.begin()+index);
								player.damageHealth(10);
								if (player.getHealth()<=0)
								{
									//gameover code
									gamestate = 2;
									gameOver = true;
								}
							}	
						}
						else
						{
							point tempj;
							tempj.x = a1[j].x + asteroidBelt[index].getLocation().x;
							tempj.y = a1[j].y + asteroidBelt[index].getLocation().y;
							point tempj1;
							tempj1.x = a1[j+1].x + asteroidBelt[index].getLocation().x;
							tempj1.y = a1[j+1].y + asteroidBelt[index].getLocation().y;

							if (intersect(tempj, tempj1, cmd[k], cmd[k+1]))
							{
								asteroidBelt.erase(asteroidBelt.begin()+index);
								player.damageHealth(10);
								if (player.getHealth()<=0)
								{
									//gameover code
									gamestate = 2;
									gameOver = true;
								}
							}
						}
					}
				}
			}
			break;
	}
	//collision of asteroid and bullet
	bool collision = false; 
	for (int j = 0; j < bullets.size(); j++)
	{
		//if the asteroid is already collided, ignore asteroid
		if(collision == 1)
		{
			break;
		}
		else
		{
			switch(GameMode)
			{
				case 0:
				case 1:
				/*	if (bulletProximity (asteroidBelt[index], bullets[j]))
					{
						bullet tmpbul; 
						tmpbul.location.x = bullets.at(j).location.x - 10.0 * cos(bullets.at(j).theta);
						tmpbul.location.y = bullets.at(j).location.y - 10.0 * sin(bullets.at(j).theta);
						for (int k = 0; k < a1.size(); k++)
 						{
 							if (k == a1.size()-1)
 							{
								point tempk;
 				    			tempk.x = a1[k].x + asteroidBelt[index].getLocation().x;
	     						tempk.y = a1[k].y + asteroidBelt[index].getLocation().y;
	    						point tempk0;
	    						tempk0.x = a1[0].x + asteroidBelt[index].getLocation().x;
  								tempk0.y = a1[0].y + asteroidBelt[index].getLocation().y;

								if(intersect(tempk, tempk0, tmpbul.location, bullets[j].location))
								{
									//separate asteroid
									vector <asteroid> tmp;
									tmp = asteroidBelt[index].breakupAsteroid();

									//deletes asteroid
									asteroidBelt.erase(asteroidBelt.begin()+index);

									//prepares to add asteroids
									n.insert(n.end(), tmp.begin(), tmp.end());

									//delete bullet							
									bullets.erase(bullets.begin()+j); 
						
									//add score
									bulletsHit++;
						
									collision = true; 
									//breaks out of checking specific bullet loop
									break;
								}
							}
							else 
							{
								point tempk2;
 				   				tempk2.x = a1[k].x + asteroidBelt[index].getLocation().x;
	     						tempk2.y = a1[k].y + asteroidBelt[index].getLocation().y;
		    					point tempk1;
		    					tempk1.x = a1[k+1].x + asteroidBelt[index].getLocation().x;
    							tempk1.y = a1[k+1].y + asteroidBelt[index].getLocation().y;
            
							if (intersect(tempk2, tempk1, tmpbul.location, bullets[j].location))
							{
								//separate asteroid
								vector <asteroid> tmp;
								tmp = asteroidBelt[index].breakupAsteroid();

								//deletes asteroid			
								asteroidBelt.erase(asteroidBelt.begin()+index);

								//prepares to add asteroids
								n.insert(n.end(), tmp.begin(), tmp.end());

								//delete bullet
								bullets.erase(bullets.begin()+j);
							
								//add score
								bulletsHit++;

								collision = true; 

								//breaks out of checking specific bullet loop
								break;
								}
							}						
						}
					}*/
					break;

			case 2:
				if (bulletProximity (enemies[index], bullets[j]))
					{/*
						bullet tmpbul; 
						tmpbul.location.x = bullets.at(j).location.x - 2.0 * cos(bullets.at(j).theta);
						tmpbul.location.y = bullets.at(j).location.y - 2.0 * sin(bullets.at(j).theta);
						for (int k = 0; k < a1.size(); k++)
 						{
 							if (k == a1.size()-1)
 							{
								point tempk;
 				    			tempk.x = a1[k].x;
	     						tempk.y = a1[k].y;
	    						point tempk0;
	    						tempk0.x = a1[0].x;
  								tempk0.y = a1[0].y;

								if(intersect(tempk, tempk0, tmpbul.location, bullets[j].location))
								{
									int remaining = enemies[index].damageHealth(10);
									if (remaining <=0)
										enemies.erase(enemies.begin()+index);

									//delete bullet							
									bullets.erase(bullets.begin()+j); 
						
									//add score
									bulletsHit++;
						
									collision = true; 
									//breaks out of checking specific bullet loop
									break;
								}
							}
							else 
							{
								point tempk2;
 				   				tempk2.x = a1[k].x;
	     						tempk2.y = a1[k].y;
		    					point tempk1;
		    					tempk1.x = a1[k+1].x;
    							tempk1.y = a1[k+1].y;
            
								if(intersect(tempk2, tempk1, tmpbul.location, bullets[j].location))
								{
									int remaining = enemies[index].damageHealth(10);
									if (remaining <=0)
										enemies.erase(enemies.begin()+index);
										
									//delete bullet							
									bullets.erase(bullets.begin()+j); 
						
									//add score
									bulletsHit++;
						
									collision = true; 
									//breaks out of checking specific bullet loop
									break;
								}
							}
						}	*/					
					}
			}
		}
	}
	

	//asteroid asteroid collision
	switch(GameMode)
	{
		case 0:
		case 1:
	
			if(!collision)
			{
				if (index == asteroidBelt.size()-1)
				{
					return;
				}
				else
				{
					for (int j = index+1; j < asteroidBelt.size(); j++) //asteroid2
					{
						if(collision)
						{
						 	break;
						}

						// Get points of asteroid 2.
						vector <point> a2;
						a2 = asteroidBelt[j].getPoints();
			
						// Check for proximity. 
						if (asteroidProximity (asteroidBelt[index], asteroidBelt[j]))
						{
							for (int k = 0; k < a1.size(); k++) //checks points of asteroid 1
							{
								if (collision)
								{ 
									break;
								}
								for (int l = 0; l < a2.size(); l++) //checks points of asteroid 2
								{
									if (collision) 
									{
										break;
									}
									vector<asteroid> triIndex; 
									vector<asteroid> triJ;

									//checks final line of both asteorids
									if (k == a1.size()-1 && l == a2.size()-1)
									{
										point tempa1k;
										tempa1k.x = a1[k].x + asteroidBelt[index].getLocation().x;
										tempa1k.y = a1[k].y + asteroidBelt[index].getLocation().y;
										point tempa10;
										tempa10.x = a1[0].x + asteroidBelt[index].getLocation().x;
										tempa10.y = a1[0].y + asteroidBelt[index].getLocation().y;
										point tempa2l;
										tempa2l.x = a2[l].x + asteroidBelt[j].getLocation().x;
										tempa2l.y = a2[l].y + asteroidBelt[j].getLocation().y;
										point tempa20;
										tempa20.x = a2[0].x + asteroidBelt[j].getLocation().x;
										tempa20.y = a2[0].y + asteroidBelt[j].getLocation().y;

										if (intersect(tempa1k, tempa10, tempa2l, tempa20))
										{	
											// Breaks asteroids.		
											triIndex = asteroidBelt[index].breakupAsteroid(); 
											triJ = asteroidBelt[j].breakupAsteroid();

											// Deletes the two asteroids.
											asteroidBelt.erase(asteroidBelt.begin()+index);
											asteroidBelt.erase(asteroidBelt.begin()+(j-1));

											// Stores new asteroids in new vector.
											for(int m = 0; m < triIndex.size(); m++)
												n.push_back(triIndex[m]);
											for(int m = 0; m < triIndex.size(); m++)
												n.push_back(triIndex[m]);

											collision = true;
											break;
										}	
									}
									else if(k == a1.size()-1)
									{
										point tempa1k;
										tempa1k.x = a1[k].x + asteroidBelt[index].getLocation().x;
										tempa1k.y = a1[k].y + asteroidBelt[index].getLocation().y;
										point tempa10;
										tempa10.x = a1[0].x + asteroidBelt[index].getLocation().x;
										tempa10.y = a1[0].y + asteroidBelt[index].getLocation().y;
										point tempa2l;
										tempa2l.x = a2[l].x + asteroidBelt[j].getLocation().x;
										tempa2l.y = a2[l].y + asteroidBelt[j].getLocation().y;
										point tempa2l1;
										tempa2l1.x = a2[l+1].x + asteroidBelt[j].getLocation().x;
										tempa2l1.y = a2[l+1].y + asteroidBelt[j].getLocation().y;

										if (intersect(tempa1k, tempa10, tempa2l, tempa2l1))
										{	
											// Breaks asteroids.		
											triIndex = asteroidBelt[index].breakupAsteroid(); 
											triJ = asteroidBelt[j].breakupAsteroid();

											// Deletes the two asteroids.
											asteroidBelt.erase(asteroidBelt.begin()+index);
											asteroidBelt.erase(asteroidBelt.begin()+(j-1));

											// Stores new asteroids in new vector.
											for(int m = 0; m < triIndex.size(); m++)
												n.push_back(triIndex[m]);
											for(int m = 0; m < triIndex.size(); m++)
												n.push_back(triIndex[m]);

											collision = true;
											break;
										}	
									}
									else if (l == a2.size()-1)
									{

										point tempa1k;
										tempa1k.x = a1[k].x + asteroidBelt[index].getLocation().x;
										tempa1k.y = a1[k].y + asteroidBelt[index].getLocation().y;
										point tempa1k1;
										tempa1k1.x = a1[k+1].x + asteroidBelt[index].getLocation().x;
										tempa1k1.y = a1[k+1].y + asteroidBelt[index].getLocation().y;
										point tempa2l;
										tempa2l.x = a2[l].x + asteroidBelt[j].getLocation().x;
										tempa2l.y = a2[l].y + asteroidBelt[j].getLocation().y;
										point tempa20;
										tempa20.x = a2[0].x + asteroidBelt[j].getLocation().x;
										tempa20.y = a2[0].y + asteroidBelt[j].getLocation().y;

										if (intersect(tempa1k, tempa1k1, tempa2l, tempa20))
										{	
											// Breaks asteroids.		
											triIndex = asteroidBelt[index].breakupAsteroid(); 
											triJ = asteroidBelt[j].breakupAsteroid();

											// Deletes the two asteroids.
											asteroidBelt.erase(asteroidBelt.begin()+index);
											asteroidBelt.erase(asteroidBelt.begin()+(j-1));

											// Stores new asteroids in new vector.
											for(int m = 0; m < triIndex.size(); m++)
												n.push_back(triIndex[m]);
											for(int m = 0; m < triIndex.size(); m++)
												n.push_back(triIndex[m]);

											collision = true;
											break;
										}	
									}
									else
									{

										point tempa1k;
										tempa1k.x = a1[k].x + asteroidBelt[index].getLocation().x;
										tempa1k.y = a1[k].y + asteroidBelt[index].getLocation().y;
										point tempa1k1;
										tempa1k1.x = a1[k+1].x + asteroidBelt[index].getLocation().x;
										tempa1k1.y = a1[k+1].y + asteroidBelt[index].getLocation().y;
										point tempa2l;
										tempa2l.x = a2[l].x + asteroidBelt[j].getLocation().x;
										tempa2l.y = a2[l].y + asteroidBelt[j].getLocation().y;
										point tempa2l1;
										tempa2l1.x = a2[l+1].x + asteroidBelt[j].getLocation().x;
										tempa2l1.y = a2[l+1].y + asteroidBelt[j].getLocation().y;

										if (intersect(tempa1k, tempa1k1, tempa2l, tempa2l1))
										{	
											// Breaks asteroids.		
											triIndex = asteroidBelt[index].breakupAsteroid(); 
											triJ = asteroidBelt[j].breakupAsteroid();

											// Deletes the two asteroids.
											asteroidBelt.erase(asteroidBelt.begin()+index);
											asteroidBelt.erase(asteroidBelt.begin()+(j-1));

											// Stores new asteroids in new vector.
											for(int m = 0; m < triIndex.size(); m++)
												n.push_back(triIndex[m]);
											for(int m = 0; m < triIndex.size(); m++)
												n.push_back(triIndex[m]);

											collision = true;
											break;
										}
									}
								}
							}	
						}
					}	
				}
			}
		
		if(n.size() != 0)
		{
			asteroidBelt.insert(asteroidBelt.end(), n.begin(), n.end());
		}	
	}
}	
#ifdef SHIPTEST	
int detectCollision(ship s, bullet b)
{
	vector<triangle> temp = s.getTriangles();
	for (int i = 0; i < temp.size(); i++)
	{
		if (PointInTriangle(b.getLocation(), temp[i].a, temp[i].b, temp[i].c))
			return 0;
	}
	return 1;
	//return collision;
}
int detectCollision(asteroid a, bullet b)
{
	int collision = 1;
	vector<triangle> temp = a.getTess2();
	vector<point> temp2 = a.getRealPoints();
	for (int i = 0; i < temp.size(); i++)
	{
		if (PointInTriangle(b.getLocation(), temp[i].a, temp[i].b, temp[i].c))
			return 0;
	}
	point tmp[2];
	tmp[0]=b.getLocation();
	tmp[1].x = tmp[0].x+2*cos(tmp[0].angle);
	tmp[1].x = tmp[0].y+2*sin(tmp[0].angle);
	for (int i = 0; i < temp2.size(); i++)
 	{
		if(intersect(temp2[i], temp2[(i+1)%temp2.size()], tmp[0], tmp[1]))
		{
			return 0;
		}
	 }
	return 1;
}
#endif