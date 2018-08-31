/* 
 * Transfromation Class for Asteroids: RETURN OF METEOR
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

#include "headers.h"
#include "structs.h"
#include "globals.h"
#include <math.h>

double TRANS[4][4];
double A[4][1];
double B[4][1];

void ptom(point& p, double m[][1])
{
	 m[0][0] = p.x;
	 m[1][0] = p.y;
	 m[2][0] = p.z;
	 m[3][0] = p.w;
}

void mtop(point& p, double m[][1])
{
	p.x = m[0][0];
	p.y = m[1][0];
	p.z = m[2][0];
	p.w = m[3][0];
}

void mVmult(double a[][4], int dim1a, int dim2a,
            double b[][1], int dim1b, int dim2b,
            double c[][1], int dim1c, int dim2c)
{
	int i, j, k;

	for (i=0; i<dim1a; i++)
	{
	    	for (j=0; j<dim2b; j++)
		{
	       		c[i][j] = 0.0;
	       		for (k=0; k<dim1a; k++)
				c[i][j] += a[i][k] * b[k][j];
	    	}
	}
}

void buildRotateZ(double mat[][4], double theta)
{
	//theta = theta * M_PI / 180.0;

	/* Define Rotation Matrix around Z-Axis */
	mat[0][0] = cos(theta); mat[0][1] = -sin(theta); mat[0][2] = 0.0; mat[0][3] = 0.0;
	mat[1][0] = sin(theta); mat[1][1] =  cos(theta); mat[1][2] = 0.0; mat[1][3] = 0.0;
	mat[2][0] =    0.0    ; mat[2][1] =     0.0    ; mat[2][2] = 1.0; mat[2][3] = 0.0;
	mat[3][0] =    0.0    ; mat[3][1] =     0.0    ; mat[3][2] = 0.0; mat[3][3] = 1.0;
}

void buildScale(double mat[][4], double x, double y, double z)
{
	/* Define Scaling  Matrix */
	mat[0][0] =     x     ; mat[0][1] =     0.0    ; mat[0][2] = 0.0; mat[0][3] = 0.0;
	mat[1][0] =    0.0    ; mat[1][1] =      y     ; mat[1][2] = 0.0; mat[1][3] = 0.0;
	mat[2][0] =    0.0    ; mat[2][1] =     0.0    ; mat[2][2] =  z ; mat[2][3] = 0.0;
	mat[3][0] =    0.0    ; mat[3][1] =     0.0    ; mat[3][2] = 0.0; mat[3][3] = 1.0;
}

void buildTranslate(double mat[][4], double x, double y, double z)
{
	/* Define Translation Matrix */

	mat[0][0] =    1.0    ; mat[0][1] =     0.0    ; mat[0][2] = 0.0; mat[0][3] =  x;
	mat[1][0] =    0.0    ; mat[1][1] =     1.0    ; mat[1][2] = 0.0; mat[1][3] =  y;
	mat[2][0] =    0.0    ; mat[2][1] =     0.0    ; mat[2][2] = 1.0; mat[2][3] =  z;
	mat[3][0] =    0.0    ; mat[3][1] =     0.0    ; mat[3][2] = 0.0; mat[3][3] = 1.0;
}

void rotatePoint(point& p,double theta)
{
	ptom(p, A);
	//double origin = (WORLD_COORDINATE_MAX_X / 2);

	buildTranslate(TRANS,origin*-1,origin*-1,0);
	mVmult(TRANS,4,4,A,4,1,B,4,1);	
	
	buildRotateZ(TRANS,theta);
	mVmult(TRANS,4,4,B,4,1,A,4,1);	

	buildTranslate(TRANS,origin,origin,0);
	mVmult(TRANS,4,4,A,4,1,B,4,1);	

	mtop(p,B);
}

void rotatePointB(point& p, double theta)
{
	ptom(p,A);
	
	buildRotateZ(TRANS, theta);
	mVmult(TRANS,4,4,A,4,1,B,4,1);

	mtop(p,B);
}

void scalePoint(point& p,double scale)
{
	ptom(p,A);
	
	buildScale(TRANS, scale, scale, 0);
	mVmult(TRANS, 4, 4, A, 4, 1, B, 4, 1);

	mtop(p, B);
}

void translatePoint(point& p,double x, double y, double z)
{
	ptom(p,A);
	
	buildTranslate(TRANS, x, y, z);
	mVmult(TRANS, 4, 4, A, 4, 1, B, 4, 1);

	mtop(p, B);
}

