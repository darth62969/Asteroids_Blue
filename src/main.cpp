/*
 *
 */
#include "headers.h"
#include "structs.h"
#include "globals.h"
#include "prototypes.h"

//Global Varianbles
ship enterprise = createShip();

//Runtime Variables go here
vector<asteroid> asteroidBelt;

void debugDisplay(void)
{
	//glClear ( GL_COLOR_BUFFER_BIT );  // Clear display window
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
    	glFlush();
}

void gameView()
{
	//output game to window
	debugDisplay();

}
void gameLoop()
{

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

}

void initiateWindow(int argc, char** argv)
{
	//build window
    	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); /* default, not needed */
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

int main(int argc, char** argv)
{
	initiateWindow(argc, argv); /* Set up Window */
	initiateGL();
	initiateOctogon();
	initiateShip();
	initiateAsteroids();
	initiateGameDisplay();
	glutDisplayFunc(gameView);
	glutIdleFunc(gameLoop);
	glutMainLoop();
}
