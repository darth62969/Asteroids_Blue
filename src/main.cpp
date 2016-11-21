/*
 *
 */
#include "headers.h"
#include "structs.h"
#include "globals.h"
#include "prototypes.h"

#define SPACEBAR 32

//Global Varianbles
ship enterprise = createShip();

//Runtime Variables go here
vector<asteroid> asteroidBelt;

vector<bullet> bullets;

float shipRotation = 0.0;

bool filled = false;

void initiateOctogon(void);

void debugDisplay(void)
{
	initiateOctogon();  // Clear display window
    	glColor3f ( 0.1, 0.5, 0.0 );      // Set line segment color to green
    
    	for (int i = 0; i < (asteroidBelt.size()); i++)
    	{
		vector<point> a = asteroidBelt.at(i).getPoints();
		point b = asteroidBelt.at(i).getCenter();
		for (int j = 0; j < (a.size()); j++)
        	{
           		glBegin (GL_LINES);
      	       		glVertex2d(a.at(j).x + b.x, a.at(j).y + b.y);
	           	glVertex2d( a.at((j+1)%a.size()).x + b.x, a.at((j+1)%a.size()).y +b.y);
           		glEnd ();         
        	}
	}
/*  	
	glPushMatrix();
	

	glTranslatef(WINDOW_MAX_X/2, WINDOW_MAX_Y/2, 0.0);
	glRotatef(enterprise.rotation)	
	glTranslate(-(WINDOW_MAX_X/2), -(WINDOW_MAX_Y/2), 0.0);*/
	
	/*
	glBegin(GL_TRIANGLES);
		glVertex2d(enterprise.body.a.x, enterprise.body.a.y);
		glVertex2d(enterprise.body.b.x, enterprise.body.b.y);
		glVertex2d(enterprise.body.c.x, enterprise.body.c.y);
	glEnd();*/
	drawShip(enterprise);		
/*
	glPopMatrix();
*/
	for(int i = 0; i < bullets.size(); i++){
		glPushMatrix();
			glTranslatef(bullets[i].translation.x, bullets[i].translation.y, 0.0);
			glBegin(GL_POINTS);
				glVertex2f(bullets[i].location.x, bullets[i].location.y);
			glEnd();
		glPopMatrix();
	}

//	glFlush();
	

	

	glutSwapBuffers();
}

void gameView()
{
	//output game to window
	debugDisplay();

}
void gameLoop()
{
	glutPostRedisplay();
}
void initiateGameDisplay()
{
	//build window dependencies
}


void initiateAsteroids()
{
	//Generate Asteroids
	int i= 0;
	while (i<NUMBER_OF_ASTEROIDS)
	{	
		asteroid a = asteroid();
		asteroidBelt.push_back(a);
		i++;
	}
	cout << asteroidBelt.size();
}

void initiateShip()
{
	//Build Ship and ship dependencies.
	enterprise = createShip();
	

}

void initiateWindow(int argc, char** argv)
{
	//build window
    glutInit(&argc,argv);
	//glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); /* default, not needed */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_MAX_X,WINDOW_MAX_Y); /* set pixel window */
	glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
	glutCreateWindow("Asteroids: RETURN OF METEOR");
}
void initiateGL( void )
{
	glClearColor(1.0,1.0,1.0,1.0); /* white background */
    	glColor3f(1.0, 0.0, 0.0); /* draw in red */
    	glPointSize(10.0);

    	glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
	gluOrtho2D(WORLD_COORDINATE_MIN_X, WORLD_COORDINATE_MAX_X,
        WORLD_COORDINATE_MIN_Y, WORLD_COORDINATE_MAX_Y);
	glMatrixMode(GL_MODELVIEW);
}

void initiateOctogon(void){
	glClear(GL_COLOR_BUFFER_BIT);
	vector<point> pts; 
	point p = {WORLD_COORDINATE_MIN_X ,WORLD_COORDINATE_MAX_Y / 2,0,1};
	
	rotatePoint(p,45.0/2.0);
	pts.push_back(p);
	
	for (int i = 0; i < 7; i++){
		rotatePoint(p,45);
		pts.push_back(p);
	}	

	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POLYGON);
		for(int i = 0; i < pts.size(); i ++){
			glVertex2f( pts[i].x , pts[i].y);
		}
	glEnd();
}

void keyboard(unsigned char key, int x, int y){
	
	//if(key == 's' || key == 'S')
		// start game

	//if(key == 'p' || key == 'P')
		//pause movement

	if(key == 'q' || key == 'Q')
		exit(0);

	if(key == 't' || key == 'T')
		filled = false;

	if(key == 'f' || key == 'F')
		filled = true;	
	if(key == 'w' || key == 'W')
		enterprise.rotation += 1.0;
	if(key == 's' || key == 'S')
		enterprise.rotation -= 1.0;
		

}

void specialKeys(int key, int x, int y){
	switch(key){
		case GLUT_KEY_RIGHT:
			enterprise.rotation += 1.0;
			glutIdleFunc(gameLoop);
			break;

		case GLUT_KEY_LEFT:
			enterprise.rotation -= 1.0;
			glutIdleFunc(gameLoop);
			break;	

		case SPACEBAR:
			//fire missiles
			//bullet shot = createBullet();
			//bullets.push_back(shot);
			//bullet.firebullet();
			glutIdleFunc(gameLoop);
			break;		

		//default: break;
	}
}

int main(int argc, char** argv)
{
	initiateWindow(argc, argv); /* Set up Window */
	initiateGL();
	initiateOctogon();
	initiateShip();
	initiateAsteroids();
	initiateGameDisplay();
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys); 
	glutDisplayFunc(gameView);
	glutIdleFunc(gameLoop);
	glutMainLoop();
}
