/*
 *
 */
#include "headers.h"
void gameview()
{
	//output game to window
}

void initiateGameDisplay()
{
	//build window dependencies
}


void initiateAsteroids()
{
	//Generate Asteroids
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
	glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y)
	glutCreateWindow("Asteroids: RETURN OF METEOR");

	glClearColor(0.0, 0.0, 0.0, 0.0); /* white background */
        glColor3f(1.0, 0.0, 0.0); /* draw in red */
        glPointSize(10.0);
      	glMatrixMode(GL_PROJECTION);
      	glLoadIdentity();
      	gluOrtho2D(WORLD_COORDINATE_MIN_X, WORLD_COORDINATE_MAX_X,
                 WORLD_COORDINATE_MIN_Y, WORLD_COORDINATE_MAX_Y);
	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	
}

int main(int argc, char** argv)
{
	initiateWindow(argc, argv); /* Set up Window */
    	initiateShip();
	initiateAsteroids();
	initiateGameDisplay();
	glutDisplayFunc(gameview);
	glutIdleFunc(gameLoop);
	glutMainLoop();
	
}

