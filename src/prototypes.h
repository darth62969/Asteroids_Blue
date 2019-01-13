/* 
 * Prototype Header for Asteroids: RETURN OF METEOR
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

#ifndef __PROTOTYPES_H__
#define __PROTOTYPES_H__

#include "headers.h"

void rotatePoint(point& p, double theta);
void rotatePointB(point& p, double theta);
void scalePoint(point& p,double scale);
void translatePoint(point& p, double x, double y, double z);
void buildTranslate( float x, float y, float z, float (&TM) [4][4]);
void applyTransformation( point& pnt, float (&TM)[4][4]);
void pmatm (int SIZE, float (&TM) [4][4], point& pnt);

float getVectorLength(point a, point b);


//void fireBullet(bullet shot);
//bullet createBullet();
//void drawBullet(bullet shot);

//void drawString(GLuint x, GLuint y, const char* string);

void clip();

int insideOctogon(point p);
bool intersect (point v1, point v2, point v3, point v4);
//void detectCollision (int i); 
//int detectCollision(ship s, bullet b);
//int detectCollision(asteroid a, bullet b);
//bool asteroidProximity (asteroid ast1, asteroid ast2);
//bool bulletProximity (asteroid ast1, bullet b1);
//bool shipProximity (asteroid ast1, std::vector <point> b2);
bool intersect1 (point v1, point v2, point v3, point v4);
void clipMeDaddy();

//source: https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
double sign (point p1, point p2, point p3);
bool PointInTriangle (point pt, point v1, point v2, point v3);

#endif
