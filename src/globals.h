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

#include "structs.h"
#include "headers.h"

// The Ship
extern ship enterprise;

// other stuff
extern vector<point> octogon;// defines octogon in ccw order
extern vector<point> clipPts;// contains points needed for clipping

// i don't like the asteroidBelt being global. i will get an explanagion later.
extern vector<asteroid> asteroidBelt;
extern vector<asteroid> allGood;


// Log Writers
extern ofstream asteroidLogger;
extern ofstream shipLogger;
extern ofstream collisionLogger;
extern ofstream bulletLogger;
extern ofstream transformationLogger;
extern char* ASTEROID_LOG_PATH;
extern char* SHIP_LOG_PATH;
extern char* COLLISION_LOG_PATH;
extern char* BULLET_LOG_PATH;
extern char* TRANSFORMATION_LOG_PATH;

extern double FPS;

extern bool paused;

#endif
