/* 
 * Header File for Asteroids: RETURN OF METEOR
 * 
 * Made by:
 * Jonathan Oakes
 * Braeden Brettin
 * Ted Dorfeuille 
 * Chris Le
 * Emily Herron
 * 
 * for the Class:
 * Intro to Computer Graphics (CSC315)
 * 
 * At:
 * Mercer Univercity  
 */

#ifndef HEADERS
#define HEADERS
#define _USE_MATH_DEFINES

#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <thread>
#include <vector>

#include <GL/glut.h>

#include "render.h"

/*
#include "asteroid.h"
#include "bullet.h"
#include "enterprise.h"
#include "fighter.h"
#include "globals.h"
#include "mode.h"
#include "object.h"
#include "render.h"
#include "prototypes.h"
#include "ship.h"
#include "structs.h"
#include "windowProperties.h"
*/


//Asteroid Contants
const int ASTEROID_MAX_X = 20;
const int ASTEROID_MAX_Y = 20;
const float ASTEROID_MIN_DIST = 5; 
const int ASTEROID_MAX_SIZE = 20;
const int ASTEROID_MIN_SIZE = 4;
const double ASTEROID_MIN_SPEED = .5;
const double ASTEROID_MAX_SPEED = 2;
const int ASTEROID_MAX_AVG = 20;
const int ASTEROID_MIN_AVG = 10;
//const int ASTEROID_MAX_SIZE = 40;
//const int ASTEROID_MIN_SIZE = 5;
const double ASTEROID_IRREGULARITY =.99;
const double ASTEROID_SPIKEYNESS = .8;


//World Constants
const int NUMBER_OF_ASTEROIDS = 50;
const int ENDLESS_ASTEROIDS =25;
const double GRAVITY_POTENTIAL = 1;
const double ASTEROID_MASS = .4;

//extern std::mt19937_64 generator;
extern render * r;
#endif

