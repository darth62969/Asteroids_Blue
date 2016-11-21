#ifndef PROTOTYPES
#define PROTOTYPES

#include "structs.h"

ship createShip(void);

void rotatePoint(point& p, double theta);
void scalePoint(point& p,double scale);
void translatePoint(point& p, double x, double y, double z);

void drawShip(ship a);
#endif
