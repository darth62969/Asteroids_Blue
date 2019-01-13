/* 
 * Globals Header for Asteroids: RETURN OF METEOR
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

#ifndef GLOBALS
#define GLOBALS

#include <vector>
#include "asteroid.h"
#include "ship.h"
#include "bullet.h"

// The Ship
//extern enterprise player;

// other stuff
//extern std::vector<point> octogon;// defines octogon in ccw order
extern std::vector<point> clipPts;// contains points needed for clipping
extern double origin;//Center of the octagon 
// i don't like the asteroidBelt being global. i will get an explanagion later.
//extern std::vector<bullet> bullets;
//extern std::vector<asteroid> asteroidBelt;
//extern std::vector<asteroid> allGood;
//extern std::vector<ship> enemies;
extern bool gameOver;
extern int gamestate;
extern int GameMode;
extern int filled;

// Log Writers
/*
extern ofstream asteroidLogger;
extern ofstream shipLogger;
extern ofstream collisionLogger;
extern ofstream bulletLogger;
extern ofstream transformationLogger;*/
extern char* ASTEROID_LOG_PATH;
extern char* SHIP_LOG_PATH;
extern char* COLLISION_LOG_PATH;
extern char* BULLET_LOG_PATH;
extern char* TRANSFORMATION_LOG_PATH;

extern double FPS;

extern bool paused;

extern int bulletsHit;





/*std::binomial_distribution<int> numsidesdist(ASTEROID_MIN_SIZE, ASTEROID_MAX_SIZE);
std::uniform_real_distribution<double> dirdist(0, 2*M_PI);
std::uniform_real_distribution<double> xlocdist(WORLD_COORDINATE_MIN_X, WORLD_COORDINATE_MAX_X);
std::uniform_real_distribution<double> ylocdist(WORLD_COORDINATE_MIN_Y, WORLD_COORDINATE_MAX_Y);
std::uniform_real_distribution<double> spddist(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED);
std::uniform_int_distribution<int> sizedist(ASTEROID_MIN_SIZE, ASTEROID_MAX_SIZE);*/
#endif

