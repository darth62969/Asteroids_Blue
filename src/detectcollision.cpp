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
	#ifdef LOGGING/*
	collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
	collisionLogger << "\nChecking asteroid proximity \n";
	collisionLogger << "\nBottom left of ast1\n";
	collisionLogger << ast1.getCenter().x << " " << ast1.getCenter().y;
	collisionLogger << "\nBottom left of ast2\n";
	collisionLogger << ast2.getCenter().x << " " << ast2.getCenter().y;
	collisionLogger.close();*/
	#endif

	if (abs(ast2.getCenter().x - ast1.getCenter().x) <= ASTEROID_MAX_X && abs(ast2.getCenter().y - ast1.getCenter().y) <= ASTEROID_MAX_Y)
	{
		#ifdef LOGGING/*
		collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
		collisionLogger << "Detected asteroid in proximity of another asteroid\n";
		collisionLogger.close();*/
		#endif

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
	if (abs(b1.location.x - ast1.getCenter().x) <= ASTEROID_MAX_X && abs(b1.location.y - ast1.getCenter().y) <= ASTEROID_MAX_Y)
	{
#ifdef LOGGING/*
		collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
		collisionLogger << "Detected Bullet in proximity\n";
		collisionLogger.close();*/
#endif		
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

	#ifdef LOGGING/*
	collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
	collisionLogger << "\nChecking ship proximity\n";
	collisionLogger << "\nPoints of ship\n";
	collisionLogger << b2[0].x << " " << b2[0].y << " " << b2[1].x << " " << b2[1].y << " " << b2[2].x << " " << b2[2].y <<"\n";
	collisionLogger << "\nBottom left of asteroid\n";
	collisionLogger << ast1.getCenter().x << " " << ast1.getCenter().y << endl;
	collisionLogger.close();*/
	#endif

	if (abs(x - ast1.getCenter().x) <= ASTEROID_MAX_X*5 && abs(y - ast1.getCenter().y) <= ASTEROID_MAX_Y*5)
	{
		#ifdef LOGGING/*
		collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
		collisionLogger << "Detected Ship in proximity of asteroid\n";
		collisionLogger.close();*/
		#endif		

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

#ifdef LOGGING

if(!paused)
{
	//collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
	//collisionLogger << "\nv1 = (" << v1.x << "," << v1.y << ") : "; 
	//collisionLogger << "v2 = (" << v2.x << "," << v2.y << ") : ";
	//collisionLogger << "v3 = (" << v3.x << "," << v3.y << ") : ";
	//collisionLogger << "v1 = (" << v4.x << "," << v4.y << ")";
	//collisionLogger << "\nua_num = " << ua_num;
	//collisionLogger << "; ndem = " << den;
	//collisionLogger << "; nub_num = " << ub_num;
	//collisionLogger << "; ua = " << ua;
	//collisionLogger << "; ub = " << ub;
	//collisionLogger <<"\nua > 0.0 = " << (ua > 0.0) << " | " << "ua < 1.0 " << (ua < 1.0);
	//collisionLogger <<"\nub > 0.0 = " << (ub > 0.0) << " | " << "ub < 1.0 " << (ub < 1.0);
	//collisionLogger.close();
}
#endif

	point v;
	v.x = -100;
	v.y = -100;

	if((ua > 0.0) && (ua < 1.0) && (ub > 0.0) && (ub < 1.0))
	{
		#ifdef LOGGING
		//collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
		//collisionLogger << "\n\nentered true\n";
		//collisionLogger.close();
		#endif
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
	a1 = asteroidBelt[index].getPoints();

	//collision of a ship vs asteroids
	//Idea:  Narrow down the asteroids in this one 
	//	 by searching through the asteroids and 
	//	 only take the ones that have ships in a 
	//	 range? 
		
	//gets points of ship
	#ifndef SHIPTEST
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
					#ifdef LOGGING/*
					collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
					collisionLogger << "checking line segment " << asteroidBelt[index].getCenter().x + a1[j].x << " " << asteroidBelt[index].getCenter().y + a1[j].y << " to " << asteroidBelt[index].getCenter().x + a1[0].x << " " << asteroidBelt[index].getCenter().y + a1[0].y;
					collisionLogger << " against " << cmd[k].x << " " << cmd[k].y << " to " << cmd[0].x << " " << cmd[0].y << endl;
					collisionLogger.close();*/
					#endif

					point tempj;
					tempj.x = a1[j].x + asteroidBelt[index].getCenter().x;
					tempj.y = a1[j].y + asteroidBelt[index].getCenter().y;
					point temp0;
					temp0.x = a1[0].x + asteroidBelt[index].getCenter().x;
					temp0.y = a1[0].y + asteroidBelt[index].getCenter().y;

					if (intersect(tempj, temp0, cmd[k], cmd[0]))
					{
						#ifdef LOGGING/*
						collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
						collisionLogger << "Game Over\n";
						collisionLogger.close();*/
						#endif

						//gameover code
						gamestate = 2;
						gameOver = true;
					}
				}
				else if (j == a1.size()-1)
				{
					#ifdef LOGGING/*
					collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
					collisionLogger << "checking line segment " << asteroidBelt[index].getCenter().x + a1[j].x << " " << asteroidBelt[index].getCenter().y + a1[j].y << " to " << asteroidBelt[index].getCenter().x + a1[0].x << " " << asteroidBelt[index].getCenter().y + a1[0].y;
					collisionLogger << " against " << cmd[k].x << " " << cmd[k].y << " to " << cmd[k+1].x << " " << cmd[k+1].y << endl;
					collisionLogger.close();*/
					#endif

					point tempj;
					tempj.x = a1[j].x + asteroidBelt[index].getCenter().x;
					tempj.y = a1[j].y + asteroidBelt[index].getCenter().y;
					point temp0;
					temp0.x = a1[0].x + asteroidBelt[index].getCenter().x;
					temp0.y = a1[0].y + asteroidBelt[index].getCenter().y;

					if (intersect(tempj, temp0, cmd[k], cmd[k+1]))
					{	
						#ifdef LOGGING/*
						collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
						collisionLogger << "Game Over\n";
						collisionLogger.close();*/
						#endif

						//gameover code
						gamestate = 2;
						gameOver = true;
						
					}	
				}
				else if (k == cmd.size()-1)
				{
					#ifdef LOGGING/*
					collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
					collisionLogger << "checking line segment " << asteroidBelt[index].getCenter().x + a1[j].x << " " << asteroidBelt[index].getCenter().y + a1[j].y << " to " << asteroidBelt[index].getCenter().x + a1[j+1].x << " " << asteroidBelt[index].getCenter().y + a1[j+1].y;
					collisionLogger << " against " << cmd[k].x << " " << cmd[k].y << " to " << cmd[0].x << " " << cmd[0].y << endl;
					collisionLogger.close();*/
					#endif

					point tempj;
					tempj.x = a1[j].x + asteroidBelt[index].getCenter().x;
					tempj.y = a1[j].y + asteroidBelt[index].getCenter().y;
					point tempj1;
					tempj1.x = a1[j+1].x + asteroidBelt[index].getCenter().x;
					tempj1.y = a1[j+1].y + asteroidBelt[index].getCenter().y;

					if (intersect(tempj, tempj1, cmd[k], cmd[0]))
					{
						#ifdef LOGGING/*
						collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
						collisionLogger << "Game Over\n";
						collisionLogger.close();*/
						#endif	

						//gameover code
						gamestate = 2;
						gameOver = true;
					}	
				}
				else
				{
					#ifdef LOGGING/*
					collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
					collisionLogger << "checking line segment " << asteroidBelt[index].getCenter().x + a1[j].x << " " << asteroidBelt[index].getCenter().y + a1[j].y << " to " << asteroidBelt[index].getCenter().x + a1[j+1].x << " " << asteroidBelt[index].getCenter().y + a1[j+1].y;
					collisionLogger << " against " << cmd[k].x << " " << cmd[k].y << " to " << cmd[k+1].x << " " << cmd[k+1].y << endl;
					collisionLogger.close();*/
					#endif

					point tempj;
					tempj.x = a1[j].x + asteroidBelt[index].getCenter().x;
					tempj.y = a1[j].y + asteroidBelt[index].getCenter().y;
					point tempj1;
					tempj1.x = a1[j+1].x + asteroidBelt[index].getCenter().x;
					tempj1.y = a1[j+1].y + asteroidBelt[index].getCenter().y;

					if (intersect(tempj, tempj1, cmd[k], cmd[k+1]))
					{
						#ifdef LOGGING/*
						collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
						collisionLogger << "Game Over\n";
						collisionLogger.close();*/
						#endif	

						//gameover code
						gamestate = 2;
						gameOver = true;
					}
				}
			}
		}
	}
#endif
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
				bullet tmpbul; 
				tmpbul.location.x = bullets.at(j).location.x - 2.0 * cos(bullets.at(j).theta)*(60/FPS);
				tmpbul.location.y = bullets.at(j).location.y - 2.0 * sin(bullets.at(j).theta)*(60/FPS);
 #ifdef LOGGING	/*				
 				collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
 				collisionLogger << "Detected bullet in proximity of asteroid\n";
				collisionLogger.close();*/
#endif
				for (int k = 0; k < a1.size(); k++)
 				{
 					if (k == a1.size()-1)
 					{
						point tempk;
 				    		tempk.x = a1[k].x + asteroidBelt[index].getCenter().x;
	     					tempk.y = a1[k].y + asteroidBelt[index].getCenter().y;
	    					point tempk0;
	    					tempk0.x = a1[0].x + asteroidBelt[index].getCenter().x;
  						tempk0.y = a1[0].y + asteroidBelt[index].getCenter().y;

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
 				   		tempk2.x = a1[k].x + asteroidBelt[index].getCenter().x;
	     					tempk2.y = a1[k].y + asteroidBelt[index].getCenter().y;
	    					point tempk1;
	    					tempk1.x = a1[k+1].x + asteroidBelt[index].getCenter().x;
    						tempk1.y = a1[k+1].y + asteroidBelt[index].getCenter().y;
            
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
			}
		}
	}

	//asteroid asteroid collision
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
					//#ifdef LOGGING				
					//collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
					//collisionLogger << "already collided\n";
					//collisionLogger.close();
					//#endif

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
								#ifdef LOGGING/*
								collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
								collisionLogger << "checking line segment " << asteroidBelt[index].getCenter().x + a1[k].x << " " << asteroidBelt[index].getCenter().y + a1[k].y << " to " << asteroidBelt[index].getCenter().x + a1[0].x << " " << asteroidBelt[index].getCenter().y + a1[0].y;
								collisionLogger << " against " << asteroidBelt[j].getCenter().x + a2[l].x << " " << asteroidBelt[j].getCenter().y + a2[l].y << " to " << asteroidBelt[j].getCenter().x + a2[0].x << " " << asteroidBelt[j].getCenter().y + a2[0].y;
								collisionLogger.close();*/
								#endif

								point tempa1k;
								tempa1k.x = a1[k].x + asteroidBelt[index].getCenter().x;
								tempa1k.y = a1[k].y + asteroidBelt[index].getCenter().y;
								point tempa10;
								tempa10.x = a1[0].x + asteroidBelt[index].getCenter().x;
								tempa10.y = a1[0].y + asteroidBelt[index].getCenter().y;
								point tempa2l;
								tempa2l.x = a2[l].x + asteroidBelt[j].getCenter().x;
								tempa2l.y = a2[l].y + asteroidBelt[j].getCenter().y;
								point tempa20;
								tempa20.x = a2[0].x + asteroidBelt[j].getCenter().x;
								tempa20.y = a2[0].y + asteroidBelt[j].getCenter().y;

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
								#ifdef LOGGING/*
								collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
								collisionLogger << "checking line segment " << asteroidBelt[index].getCenter().x + a1[k].x << " " << asteroidBelt[index].getCenter().y + a1[k].y << " to " << asteroidBelt[index].getCenter().x + a1[0].x << " " << asteroidBelt[index].getCenter().y + a1[0].y;
								collisionLogger << " against " << asteroidBelt[j].getCenter().x + a2[l].x << " " << asteroidBelt[j].getCenter().y + a2[l].y << " to " << asteroidBelt[j].getCenter().x + a2[l+1].x << " " << asteroidBelt[j].getCenter().y + a2[l+1].y;
								collisionLogger.close();*/
								#endif

								point tempa1k;
								tempa1k.x = a1[k].x + asteroidBelt[index].getCenter().x;
								tempa1k.y = a1[k].y + asteroidBelt[index].getCenter().y;
								point tempa10;
								tempa10.x = a1[0].x + asteroidBelt[index].getCenter().x;
								tempa10.y = a1[0].y + asteroidBelt[index].getCenter().y;
								point tempa2l;
								tempa2l.x = a2[l].x + asteroidBelt[j].getCenter().x;
								tempa2l.y = a2[l].y + asteroidBelt[j].getCenter().y;
								point tempa2l1;
								tempa2l1.x = a2[l+1].x + asteroidBelt[j].getCenter().x;
								tempa2l1.y = a2[l+1].y + asteroidBelt[j].getCenter().y;

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
								#ifdef LOGGING/*
								collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
								collisionLogger << "checking line segment " << asteroidBelt[index].getCenter().x + a1[k].x << " " << asteroidBelt[index].getCenter().y + a1[k].y << " to " << asteroidBelt[index].getCenter().x + a1[k+1].x << " " << asteroidBelt[index].getCenter().y + a1[k+1].y;
								collisionLogger << " against " << asteroidBelt[j].getCenter().x + a2[l].x << " " << asteroidBelt[j].getCenter().y + a2[l].y << " to " << asteroidBelt[j].getCenter().x + a2[0].x << " " << asteroidBelt[j].getCenter().y + a2[0].y;
								collisionLogger.close();*/
								#endif

								point tempa1k;
								tempa1k.x = a1[k].x + asteroidBelt[index].getCenter().x;
								tempa1k.y = a1[k].y + asteroidBelt[index].getCenter().y;
								point tempa1k1;
								tempa1k1.x = a1[k+1].x + asteroidBelt[index].getCenter().x;
								tempa1k1.y = a1[k+1].y + asteroidBelt[index].getCenter().y;
								point tempa2l;
								tempa2l.x = a2[l].x + asteroidBelt[j].getCenter().x;
								tempa2l.y = a2[l].y + asteroidBelt[j].getCenter().y;
								point tempa20;
								tempa20.x = a2[0].x + asteroidBelt[j].getCenter().x;
								tempa20.y = a2[0].y + asteroidBelt[j].getCenter().y;

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
								#ifdef LOGGING
								//collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
								//collisionLogger << "checking line segment " << asteroidBelt[index].getCenter().x + a1[k].x << " " << asteroidBelt[index].getCenter().y + a1[k].y << " to " << asteroidBelt[index].getCenter().x + a1[k+1].x << " " << asteroidBelt[index].getCenter().y + a1[k+1].y;
								//collisionLogger << " against " << asteroidBelt[j].getCenter().x + a2[l].x << " " << asteroidBelt[j].getCenter().y + a2[l].y << " to " << asteroidBelt[j].getCenter().x + a2[j+1].x << " " << asteroidBelt[j].getCenter().y + a2[j+1].y;
								//collisionLogger.close();
								#endif

								point tempa1k;
								tempa1k.x = a1[k].x + asteroidBelt[index].getCenter().x;
								tempa1k.y = a1[k].y + asteroidBelt[index].getCenter().y;
								point tempa1k1;
								tempa1k1.x = a1[k+1].x + asteroidBelt[index].getCenter().x;
								tempa1k1.y = a1[k+1].y + asteroidBelt[index].getCenter().y;
								point tempa2l;
								tempa2l.x = a2[l].x + asteroidBelt[j].getCenter().x;
								tempa2l.y = a2[l].y + asteroidBelt[j].getCenter().y;
								point tempa2l1;
								tempa2l1.x = a2[l+1].x + asteroidBelt[j].getCenter().x;
								tempa2l1.y = a2[l+1].y + asteroidBelt[j].getCenter().y;

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
