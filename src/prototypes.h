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

void buildTranslate( float x, float y, float z, float (&TM) [4][4]);

void applyTransformation( point& pnt, float (&TM)[4][4]);

void pmatm (int SIZE, float (&TM) [4][4], point& pnt);


#endif
