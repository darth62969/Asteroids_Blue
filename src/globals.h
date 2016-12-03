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

#endif
