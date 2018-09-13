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

#include <cmath>
#include <GL/glut.h>
//#include <gl/GL.h>
//#include <gl/GLU.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "asteroid.h"
#include <sstream>
#include <random>
#include <chrono>

#ifdef SHIPTEST
#include "ship.h"
#endif

//#include "detectcollision.cpp"

using namespace std;

//Window Constants
const int WINDOW_MAX_X = 600;
const int WINDOW_MAX_Y = 600;
const int WINDOW_POSITION_X = 100;
const int WINDOW_POSITION_Y = 100;
const int WORLD_COORDINATE_MIN_X = 0;
const int WORLD_COORDINATE_MIN_Y = 0;
const int WORLD_COORDINATE_MAX_X = 600;
const int WORLD_COORDINATE_MAX_Y = 600;

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

extern std::mt19937_64 generator;
#endif

