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
std::vector<asteroid> asteroidBelt;

void debugDisplay(void)
{
	glClear ( GL_COLOR_BUFFER_BIT );  // Clear display window
    glColor3f ( 0.1, 0.5, 0.0 );      // Set line segment color to green
    
    for (int i = 0; i < (asteroidBelt.size()); i++)
    {
		std::vector<point> a = asteroidBelt.at(i).getPoints();
		for (int j = 0; j < (a.size()); j++)
        {
           	glBegin (GL_LINES);
      	       	glVertex2d(a.at(j).x*100, a.at(j).y*100);
	           	glVertex2d( a.at((j+1)%a.size()).x*100, a.at((j+1)%a.size()).y*100);
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
	while (i<2)
	{	
		asteroid a = asteroid();
		asteroidBelt.push_back(a);
		i++;
	}
	std::cout << asteroidBelt.size();
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
void initiateStuff( void )
{
	glClearColor(0.0, 0.0, 0.0, 0.0); /* white background */
    glColor3f(1.0, 0.0, 0.0); /* draw in red */
    glPointSize(10.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(WORLD_COORDINATE_MIN_X, WORLD_COORDINATE_MAX_X,
        WORLD_COORDINATE_MIN_Y, WORLD_COORDINATE_MAX_Y);
	glMatrixMode(GL_MODELVIEW);
}

void Pipeline(void){

	// 

}

int main(int argc, char** argv)
{
	initiateWindow(argc, argv); /* Set up Window */
	initiateStuff();
    initiateShip();
	initiateAsteroids();
	initiateGameDisplay();
	glutDisplayFunc(gameView);
	glutIdleFunc(gameLoop);
	glutMainLoop();
	

}
