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
const float ASTEROID_MIN_DIST = 4.5; 
const int ASTEROID_MAX_SIZE = 12;
const int ASTEROID_MIN_SIZE = 4;

//World Constants
const int NUMBER_OF_ASTEROIDS = 10;

#endif

