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
/*#ifdef LOGGING
	collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
	collisionLogger << "\nChecking asteroid proximity \n";
	collisionLogger << abs(ast2.getCenter().x - ast1.getCenter().x);
	collisionLogger << " <= 20 : " << (abs(ast2.getCenter().x - ast1.getCenter().x) <= 20) << endl;
	collisionLogger << abs(ast2.getCenter().y - ast1.getCenter().y);
	collisionLogger << " <= 20 : " << (abs(ast2.getCenter().y - ast1.getCenter().y) <= 20) << endl;
	collisionLogger.close();
#endif*/
	if (abs(ast2.getCenter().x - ast1.getCenter().x) <= 20 && abs(ast2.getCenter().y - ast1.getCenter().y) <= 20)
	{
/*#ifdef LOGGING
		collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
		collisionLogger << "Detected Asteroid in proximity of another Asteroid\n";
		collisionLogger.close();
#endif*/
		return true;
	}
	else
		return false; 
}

//checks proximity of asteroids and bullets
bool bulletProximity(asteroid ast1, bullet b1)
{
#ifdef LOGGING
/*	collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
	collisionLogger << "\nChecking bullet proximity \n";
	collisionLogger << abs(b1.location.x - ast1.getCenter().x);
	collisionLogger << " <= 20 : " << (abs(b1.location.x - ast1.getCenter().x) <= 20) << endl;
	collisionLogger << abs(b1.location.y - ast1.getCenter().y);
	collisionLogger << " <= 20 : " << (abs(b1.location.y - ast1.getCenter().y) <= 20) << endl;
	collisionLogger.close();*/ 
#endif
	if (abs(b1.location.x - ast1.getCenter().x) <= 20 && abs(b1.location.y - ast1.getCenter().y) <= 20)
	{
#ifdef LOGGING
		collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
		collisionLogger << "Detected Bullet in proximity\n";
		collisionLogger.close();
#endif		
		return true;
	}
	else
		return false; 
}

/*
//checks proximity of ship and asteroid
bool shipProximity(asteroid ast1, vector<point> b2)
{
	int x = (b2[0].x + b2[1].x + b2[2].x)/3;  int y = (b2[0].y + b2[1].y + b2[2].y)/3;

	#ifdef LOGGING
	collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
	collisionLogger << "\n Checking ship proximity \n";
	collisionLogger << "\n Points of ship \n";
	collisionLogger << b2[0].x << " " << b2[0].y << " " << b2[1].x << " " << b2[1].y << " " << b2[2].x << " " << b2[2].y <<"\n";
	collisionLogger << ast1.getCenter().x << " " << ast1.getCenter().y << endl;
	collisionLogger.close();
	#endif

	if (abs(x - ast1.getCenter().x) <= 20 && abs(y - ast1.getCenter().y) <= 20)
	{
		#ifdef LOGGING
		collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
		collisionLogger << "Detected Ship in proximity of asteroid\n";
		collisionLogger.close();
		#endif		

		return true;
	}
	else
		return false; 
}
*/

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
	vector <asteroid> n;

	//checks collision between asteroids vs asteroids
//	for (int i = 0; i < asteroidBelt.size(); i++)//asteroid 1
//	{

	//gets points of asteroid 1
	vector<point> a1;
	a1 = asteroidBelt[index].getPoints();
/*
	asteroid ast;
	ast = asteroidBelt[index];
*/
	//collision of a ship vs asteroids
	//Idea:  Narrow down the asteroids in this one 
	//	 by searching through the asteroids and 
	//	 only take the ones that have ships in a 
	//	 range? 
		
	//gets points of ship
	vector<point> cmd;
	cmd.push_back(enterprise.body.a);
	cmd.push_back(enterprise.body.b);
	cmd.push_back(enterprise.body.c);

	for (int i = 0; i < 3; i++)
	{
		scalePoint(cmd[i], 7);
		rotatePoint(cmd[i], enterprise.rotation);
		cmd[i].x += WORLD_COORDINATE_MAX_X/2;
		cmd[i].y += WORLD_COORDINATE_MAX_Y/2;
	}
/*
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
					#ifdef LOGGING
					collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
					collisionLogger << "checking line segment " << ast.getCenter().x + a1[j].x << " " << ast.getCenter().y + a1[j].y << " to " << ast.getCenter().x + a1[0].x << " " << ast.getCenter().y + a1[0].y;
					collisionLogger << " against " << cmd[k].x << " " << cmd[k].y << " to " << cmd[0].x << " " << cmd[0].y << endl;
					collisionLogger.close();
					#endif

					point tempj;
					tempj.x = a1[j].x + ast.getCenter().x;
					tempj.y = a1[j].y + ast.getCenter().y;
					point temp0;
					temp0.x = a1[0].x + ast.getCenter().x;
					temp0.y = a1[0].y + ast.getCenter().y;
					if (intersect(tempj, temp0, cmd[k], cmd[0]))
					{
						#ifdef LOGGING
						collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
						collisionLogger << "Game Over\n";
						collisionLogger.close();
						#endif

						//gameover code
						gameOver = true;
					}
				}
				else if (j == a1.size()-1)
				{
					#ifdef LOGGING
					collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
					collisionLogger << "checking line segment " << ast.getCenter().x + a1[j].x << " " << ast.getCenter().y + a1[j].y << " to " << ast.getCenter().x + a1[0].x << " " << ast.getCenter().y + a1[0].y;
					collisionLogger << " against " << cmd[k].x << " " << cmd[k].y << " to " << cmd[k+1].x << " " << cmd[k+1].y << endl;
					collisionLogger.close();
					#endif

					point tempj;
					tempj.x = a1[j].x + ast.getCenter().x;
					tempj.y = a1[j].y + ast.getCenter().y;
					point temp0;
					temp0.x = a1[0].x + ast.getCenter().x;
					temp0.y = a1[0].y + ast.getCenter().y;
					if (intersect(tempj, temp0, cmd[k], cmd[k+1]))
					{	
						#ifdef LOGGING
						collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
						collisionLogger << "Game Over\n";
						collisionLogger.close();
						#endif

						//gameover code
						gameOver = true;
						
					}	
				}
				else if (k == cmd.size()-1)
				{
					#ifdef LOGGING
					collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
					collisionLogger << "checking line segment " << ast.getCenter().x + a1[j].x << " " << ast.getCenter().y + a1[j].y << " to " << ast.getCenter().x + a1[j+1].x << " " << ast.getCenter().y + a1[j+1].y;
					collisionLogger << " against " << cmd[k].x << " " << cmd[k].y << " to " << cmd[0].x << " " << cmd[0].y << endl;
					collisionLogger.close();
					#endif

					point tempj;
					tempj.x = a1[j].x + ast.getCenter().x;
					tempj.y = a1[j].y + ast.getCenter().y;
					point tempj1;
					tempj1.x = a1[j+1].x + ast.getCenter().x;
					tempj1.y = a1[j+1].y + ast.getCenter().y;
					if (intersect(tempj, tempj1, cmd[k], cmd[0]))
					{
						#ifdef LOGGING
						collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
						collisionLogger << "Game Over\n";
						collisionLogger.close();
						#endif	

						//gameover code
						gameOver = true;
					}	
				}
				else
				{
					#ifdef LOGGING
					collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
					collisionLogger << "checking line segment " << ast.getCenter().x + a1[j].x << " " << ast.getCenter().y + a1[j].y << " to " << ast.getCenter().x + a1[j+1].x << " " << ast.getCenter().y + a1[j+1].y;
					collisionLogger << " against " << cmd[k].x << " " << cmd[k].y << " to " << cmd[k+1].x << " " << cmd[k+1].y << endl;
					collisionLogger.close();
					#endif

					point tempj;
					tempj.x = a1[j].x + ast.getCenter().x;
					tempj.y = a1[j].y + ast.getCenter().y;
					point tempj1;
					tempj1.x = a1[j+1].x + ast.getCenter().x;
					tempj1.y = a1[j+1].y + ast.getCenter().y;
					if (intersect(tempj, tempj1, cmd[k], cmd[k+1]))
					{
						#ifdef LOGGING
						collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
						collisionLogger << "Game Over\n";
						collisionLogger.close();
						#endif	

						//gameover code
						gameOver = true;
					}
				}
			}
		}
	}
*/
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
			if (bulletProximity (asteroidBelt[index], bullets[j]))
			{
#ifdef LOGGING	/*				
				collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
				collisionLogger << "Detected bullet in proximity of asteroid\n";
				collisionLogger.close();*/
#endif
				for (int k = 0; k < a1.size(); k++)
				{
					if (k == a1.size()-1)
					{
						if(intersect(a1[k], a1[0], bullets[j].location, bullets[j].location))
						{
							//separate asteroid
							vector <asteroid> tmp;
							tmp = asteroidBelt[index].breakupAsteroid();

							//deletes asteroid
							for (int l = index; l < asteroidBelt.size()-1; l++)
							{
								asteroidBelt[l] = asteroidBelt[l+1];
							}
							asteroidBelt.pop_back();

							//prepares to add asteroids
							n.insert(n.end(), tmp.begin(), tmp.end());

							//delete bullet
							for (int l = j; l < bullets.size()-1; l++)
							{
								bullets[j] = bullets[j+1];
							}
							bullets.pop_back();
							
							//add score

							
							collision = true; 
							//breaks out of checking specific bullet loop
							break;
						}
					}
					else 
					{
						if (intersect(a1[k], a1[k+1],  bullets[j].location, bullets[j].location))
						{
							//separate asteroid
							vector <asteroid> tmp;
							tmp = asteroidBelt[index].breakupAsteroid();

							//deletes asteroid
							for (int l = index; l < asteroidBelt.size()-1; l++)
							{
								asteroidBelt[l] = asteroidBelt[l+1];
							}
							asteroidBelt.pop_back();

							//prepares to add asteroids
							n.insert(n.end(), tmp.begin(), tmp.end());

							//delete bullet
							for (int l = j; l < bullets.size()-1; l++)
							{
								bullets[j] = bullets[j+1];
							}
							bullets.pop_back();
							
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
#ifdef LOGGING/*				
				collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
				collisionLogger << "Checking Asteroid Collisions\n";
				collisionLogger.close();*/
#endif

	if(collision == 1)
	{
/*#ifdef LOGGING				
				collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
				collisionLogger << "already collided\n";
				collisionLogger.close();
#endif*/
	}
	else
	{
		if (index == asteroidBelt.size()-1)
		{
		}
		else
		{
			for (int j = index+1; j < asteroidBelt.size(); j++) //asteroid2
			{
				if(collision == 1)
				{
/*#ifdef LOGGING				
					collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
					collisionLogger << "already collided\n";
					collisionLogger.close();
#endif*/
				 	break;
				}
				//gets points of asteroid 2
				vector <point> a2;
				a2 = asteroidBelt[j].getPoints();
			
				//checks for proximity 
				if (asteroidProximity (asteroidBelt[index], asteroidBelt[j]))
				{
					for (int k = 0; k < a1.size()-1; k++) //checks points of asteroid 1
					{
						if(collision==1)
						{ 
							break;
						}
						for (int l = 0; l < a2.size()-1; l++) //checks points of asteroid 2
						{
							if(collision==1) 
							{
								break;
							}
							vector<asteroid> tmp3; 
							vector<asteroid> tmp2;
							/*
							for (int k2 = k1+1; k2 < a1.size(); k1++) //checks points of asteroid 1
							{
								for (int l2 = l1+1; l2 < a2.size(); l2++) //checks points of asteroid 2
								{
									if (intersect(a1[k1], a1[0],  a2[l], a2[0]))
									{

									}*/

							
							//checks final line of both asteorids
							if (k==a1.size()-1 && l ==a2.size()-1)
							{
								if (intersect(a1[k], a1[0],  a2[l], a2[0]))
								{	
									//if intersections
									//breaks asteroids and stores in new vector		
									tmp3 = asteroidBelt[index].breakupAsteroid(); 
									tmp2 = asteroidBelt[index+1].breakupAsteroid();
									tmp3.insert(tmp3.end(),tmp2.begin(),tmp2.end());
									n.insert(n.end(),tmp3.begin(),tmp3.end());	
		
									//deletes the two asteroids
									asteroidBelt.erase(asteroidBelt.begin()+index);
									asteroidBelt.erase(asteroidBelt.begin()+j);

									collision = true;
									break; 
								}	
		
							}	

							else if(k == a1.size()-1)
							{
								if (intersect(a1[k], a1[0],  a2[l], a2[l+1]))
								{	
									//if intersections
									//breaks asteroids and stores in new vector		
									tmp3 = asteroidBelt[index].breakupAsteroid(); 
									tmp2 = asteroidBelt[index+1].breakupAsteroid();
									tmp3.insert(tmp3.end(),tmp2.begin(),tmp2.end());
									n.insert(n.end(),tmp3.begin(),tmp3.end());	
		
									//deletes the two asteroids

									asteroidBelt.erase(asteroidBelt.begin()+index);
									asteroidBelt.erase(asteroidBelt.begin()+j);

									collision = true;
									break; 
								}	
							}
							else if (l == a2.size()-1)
							{
								if (intersect(a1[k], a1[k+1],  a2[l], a2[l+1]))
								{	
									//if intersections
									//breaks asteroids and stores in new vector		 
									tmp3 = asteroidBelt[index].breakupAsteroid(); 
									tmp2 = asteroidBelt[index+1].breakupAsteroid();
									tmp3.insert(tmp3.end(),tmp2.begin(),tmp2.end());
									n.insert(n.end(),tmp3.begin(),tmp3.end());	
		
									//deletes the two asteroids
									
									asteroidBelt.erase(asteroidBelt.begin()+index);
									asteroidBelt.erase(asteroidBelt.begin()+j);

									collision = true;
									break; 
								}	
							}
							else
							{
								if (intersect(a1[k], a1[k+1],  a2[l], a2[l+1]))
								{	
									//if intersections
									//breaks asteroids and stores in new vector		
									tmp3 = asteroidBelt[index].breakupAsteroid(); tmp2 = asteroidBelt[index+1].breakupAsteroid();
									tmp3.insert(tmp3.end(),tmp2.begin(),tmp2.end());
									n.insert(n.end(),tmp3.begin(),tmp3.end());	
		
									//deletes the two asteroids

									asteroidBelt.erase(asteroidBelt.begin()+index);
									asteroidBelt.erase(asteroidBelt.begin()+j);

									collision = true;
									break; 
								}
							}
						}
					}	
				}
			}	
		}
			//if (collision == 1) index--;
		//}

	}
	if(n.size() != 0)
	{
		asteroidBelt.insert(asteroidBelt.end(),n.begin(),n.end());
	}	
}		
