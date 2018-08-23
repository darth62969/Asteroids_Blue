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

#ifndef PROTOTYPES
#define PROTOTYPES

#include "structs.h"
#include "asteroid.h"
#include <vector>
//#include <GL/glut.h>

#ifndef SHIPTEST
ship createShip(void);
void rotateShip(ship& s);
void drawShip(ship a);
void resetShip();
#endif

void rotatePoint(point& p, double theta);
void rotatePointB(point& p, double theta);
void scalePoint(point& p,double scale);
void translatePoint(point& p, double x, double y, double z);
void buildTranslate( float x, float y, float z, float (&TM) [4][4]);
void applyTransformation( point& pnt, float (&TM)[4][4]);
void pmatm (int SIZE, float (&TM) [4][4], point& pnt);

void fireBullet(bullet shot);
bullet createBullet();
void drawBullet(bullet shot);

//void drawString(GLuint x, GLuint y, const char* string);

void clip();

int insideOctogon(point p);
bool intersect (point v1, point v2, point v3, point v4);
void detectCollision (int i); 
bool asteroidProximity (asteroid ast1, asteroid ast2);
bool bulletProximity (asteroid ast1, bullet b1);
bool shipProximity (asteroid ast1, std::vector <point> b2);
bool intersect1 (point v1, point v2, point v3, point v4);
void clipMeDaddy();


#endif
