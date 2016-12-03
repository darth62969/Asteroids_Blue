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

ship createShip(void);
void rotatePoint(point& p, double theta);
void rotatePointB(point& p, double theta);
void scalePoint(point& p,double scale);
void translatePoint(point& p, double x, double y, double z);
void rotateShip(ship& s);
void drawShip(ship a);
void fireBullet(bullet shot);
bullet createBullet();
void drawBullet(bullet shot);
void buildTranslate( float x, float y, float z, float (&TM) [4][4]);
void applyTransformation( point& pnt, float (&TM)[4][4]);
void pmatm (int SIZE, float (&TM) [4][4], point& pnt);

#endif
