#include "headers.h"
#include "structs.h"
#include "globals.h"
#include "prototypes.h"



ship createShip(void)
{
	/* Create a ship, enterprise, with points at (450, 450), (450, 550), and (550, 500).
	 * These points will need to be changed later depending on the size of our window.
	 */
	
	printf("world coords  %d %d\n", WORLD_COORDINATE_MAX_X/2, WORLD_COORDINATE_MAX_Y/2);	

	ship temp;
	triangle body;
	point a;
	a.x = 14.0 + WORLD_COORDINATE_MAX_X/2;
	a.y = 0.0 + WORLD_COORDINATE_MAX_Y/2;
	point b;
	b.x = -14.0 + WORLD_COORDINATE_MAX_X/2;
	b.y = -7.0 + WORLD_COORDINATE_MAX_Y/2;
	point c;
	c.x = -14.0 + WORLD_COORDINATE_MAX_X/2;
	c.y = 7.0 + WORLD_COORDINATE_MAX_Y/2;
	body.a = a;
	body.b = b;
	body.c = c;
	temp.body = body;

	printf("ship original location\n%f %f\n%f %f\n %f %f\n", temp.body.a.x, temp.body.a.y, temp.body.b.x, temp.body.b.y, temp.body.c.x, temp.body.c.y);


	// Rotation will be changed if the user presses the left or right arrow keys.
	temp.rotation = 0.0;

	return temp;
}

void applyTransformation( point& pnt, float (&TM)[4][4])
//void applyTransformation( vector<vertices> vertVect, float *TM ) 
// Applies the given transformation matrix TM to the vector vp containing
// all of the homegenous coordinates to define the object
{
	printf("%s\n", "apply transformation");

	int i;

	//for (i < 0; i < vertVect.size(); i++){
		pmatm(4, TM, pnt);
		printf("%f %f %f %f\n", pnt.x, pnt.y, pnt.z, pnt.w);		
	//} 
}

void pmatm (int SIZE, float (&TM) [4][4], point& pnt)
//void vmatm (int SIZE, float (&TM)[4][4], vector<vertex>& vect)
// Matrix-vector multiplication
// pA is a pointer to the first element of matrix A
// pB is a pointer to the first element of vector B
// On return, B will contain transformed coordinates
{
	printf("%s\n", "vmatm");

   int i, j;
   point temp;

   temp.x = 0, temp.y = 0, temp.z = 0, temp.w = 0;
   


   temp.x = pnt.x*TM[0][0] + pnt.y*TM[0][1] + pnt.z*TM[0][2] + pnt.w*TM[0][3]; 
   temp.y = pnt.x*TM[1][0] + pnt.y*TM[1][1] + pnt.z*TM[1][2] + pnt.w*TM[1][3];
   temp.z = pnt.x*TM[2][0] + pnt.y*TM[2][1] + pnt.z*TM[2][2] + pnt.w*TM[2][3];
   temp.w = pnt.x*TM[3][0] + pnt.y*TM[3][1] + pnt.z*TM[3][2] + pnt.w*TM[3][3];


	pnt.x = temp.x;
	pnt.y = temp.y;
	pnt.z = temp.z;
	pnt.w = temp.w;

	printf("%f %f %f %f\n", pnt.x, pnt.y, pnt.z, pnt.w);


}

void buildRotateZ( float theta, float (&TM) [4][4])
{
	printf("%s\n", "ROTATE");

// Constructs rotation matrix about Z axis

     float phi;

     // Convert degrees to radians

     phi = theta * M_PI / 180.0;

	TM[0][0] = cos(phi); 	TM[0][1] = -sin(phi); 	TM[0][2] = 0.0; 	TM[0][3] = 0.0;
        TM[1][0] = sin(phi); 	TM[1][1] = cos(phi); 	TM[1][2] = 0.0; 	TM[1][3] = 0.0;
        TM[2][0] = 0.0; 	TM[2][1] = 0.0; 	TM[2][2] = 1.0; 	TM[2][3] = 0.0;
        TM[3][0] = 0.0; 	TM[3][1] = 0.0; 	TM[3][2] = 0.0; 	TM[3][3] = 1.0;


 /*    pA[ 0] =  cos(phi); pA[ 1] = -sin(phi); pA[ 2] = 0.0; pA[ 3] = 0.0;
     pA[ 4] = sin(phi); pA[ 5] = cos(phi); pA[ 6] = 0.0; pA[ 7] = 0.0;
     pA[ 8] = 0.0;       pA[ 9] = 0.0;      pA[10] = 1.0; pA[11] = 0.0;
     pA[12] = 0.0;       pA[13] = 0.0;      pA[14] = 0.0; pA[15] = 1.0;
*/
}  


void rotateShip(ship& s){

	//float TM[4][4];

	//translatePoint(s.body.a, -(WORLD_COORDINATE_MAX_X/2), -(WORLD_COORDINATE_MAX_Y/2), 0.0);
	//translatePoint(s.body.b, -(WORLD_COORDINATE_MAX_X/2), -(WORLD_COORDINATE_MAX_Y/2), 0.0);
	//translatePoint(s.body.c, -(WORLD_COORDINATE_MAX_X/2), -(WORLD_COORDINATE_MAX_Y/2), 0.0);

	printf("begining ship rotation  %f %f\n%f %f\n %f %f\n", s.body.a.x, s.body.a.y, s.body.b.x, s.body.b.y, s.body.c.x, s.body.c.y);

	s.body.a.x -= WORLD_COORDINATE_MAX_X/2.0; s.body.a.y -= WORLD_COORDINATE_MAX_Y/2.0;
	s.body.b.x -= WORLD_COORDINATE_MAX_X/2.0; s.body.b.y -= WORLD_COORDINATE_MAX_Y/2.0;
	s.body.c.x -= WORLD_COORDINATE_MAX_X/2.0; s.body.c.y -= WORLD_COORDINATE_MAX_Y/2.0;
	printf("ship translated to origin  %f %f\n%f %f\n %f %f\n", s.body.a.x, s.body.a.y, s.body.b.x, s.body.b.y, s.body.c.x, s.body.c.y);


	buildRotateZ(s.rotation, TM);
	applyTransformation(s.body.a, TM);
        applyTransformation(s.body.b, TM);
        applyTransformation(s.body.c, TM);
	printf("ship rotated  %f %f\n%f %f\n %f %f\n", s.body.a.x, s.body.a.y, s.body.b.x, s.body.b.y, s.body.c.x, s.body.c.y);

	s.body.a.x += WORLD_COORDINATE_MAX_X/2.0; s.body.a.y += WORLD_COORDINATE_MAX_Y/2.0;
        s.body.b.x += WORLD_COORDINATE_MAX_X/2.0; s.body.b.y += WORLD_COORDINATE_MAX_Y/2.0;
        s.body.c.x += WORLD_COORDINATE_MAX_X/2.0; s.body.c.y += WORLD_COORDINATE_MAX_Y/2.0;


/*	
	rotatePointB(s.body.a, s.rotation);
	rotatePointB(s.body.b, s.rotation);
	rotatePointB(s.body.c, s.rotation); 	
*/	
	printf("ship translated to center  %f %f\n%f %f\n %f %f\n", s.body.a.x, s.body.a.y, s.body.b.x, s.body.b.y, s.body.c.x, s.body.c.y);
/*
	translatePoint(s.body.a, WORLD_COORDINATE_MAX_X/2.0, WORLD_COORDINATE_MAX_Y/2.0, 0.0);
        translatePoint(s.body.b, WORLD_COORDINATE_MAX_X/2.0, WORLD_COORDINATE_MAX_Y/2.0, 0.0);
        translatePoint(s.body.c, WORLD_COORDINATE_MAX_X/2.0, WORLD_COORDINATE_MAX_Y/2.0, 0.0);
*/
}


void drawShip(ship s){

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
		for(int i = 0; i<3; i++)
		{    
			//glVertex2d(b[i].x + WORLD_COORDINATE_MAX_X/2, b[i].y + WORLD_COORDINATE_MAX_Y/2);
			//glVertex2d(b[(i+1)%3].x + WORLD_COORDINATE_MAX_X/2, b[(i+1)%3].y + WORLD_COORDINATE_MAX_Y/2);
			glVertex2d(s.body.a.x, s.body.a.y);
			glVertex2d(s.body.b.x, s.body.b.y);
			glVertex2d(s.body.c.x, s.body.c.y);
			printf("drew ship at %f %f\n%f %f\n %f %f\n", s.body.a.x, s.body.a.y, s.body.b.x, s.body.b.y, s.body.c.x, s.body.c.y);
		}
	glEnd();
}
