/* 
 * Main program for Asteroids: RETURN OF METEOR
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
#include "prototypes.h"

#define SPACEBAR 32

//Global Varianbles

//The Ship
ship enterprise = createShip();

//Log Writers

ofstream asteroidLogger;		// Asteroid loggger, records information about the asteroids into the asteroid log file.
ofstream shipLogger;			// Ship logger, records information about the ship into the ship log.
ofstream collisionLogger;		// Collision logger, records information about colitions into the collision log.
ofstream bulletLogger;			// Bullet Logger, records information about bullets into the bullet log.
ofstream transformationLogger;	// Transfomration logger, records information about transforms into tranformmation log.

// Log paths. Should be relative to where the executable is but...
// These should be self explanitory. 

char* ASTEROID_LOG_PATH = "asteroid_log.txt";
char* SHIP_LOG_PATH = "ship_log.txt";
char* COLLISION_LOG_PATH = "collision_log.txt";
char* BULLET_LOG_PATH = "bullet_log.txt";
char* TRANSFORMATION_LOG_PATH = "transformation_log.txt";

//Runtime Variables go here
vector<asteroid> asteroidBelt; 	// Holds all asteroids

vector<bullet> bullets; 		// Holds all bullets

float deltaRot = 1.0; 			// For use in the accelleration of ship rotation 

bool rightKeyPressed = false;	// These are for the ship rotation functions
bool rightReached10 = false;	//

bool leftKeyPressed = false;	// Also for ship rotation, tells us if the ship's
bool leftReached10 = false;		// rotatition reached 10

int timeKeyPressed = 0;			// Iterator for Debug reasons

//float shipRotation = 0.0;		// Unused variable

int filled = 0;					// 0 if lines should be drawn, 1 if filled (asteroids)   

void initiateOctogon(void);

/*
 * Debug Display Funtion:
 * Displays information about the current game state like FPS and Asteroid Count.
 */

void debugDisplay(void)
{
	char * debugText = "debug active";

	/*initiateOctogon();  // Clear display window
    	glColor3f ( 0.1, 0.5, 0.0 );      // Set line segment color to green
	glPointSize(4.0);

	//Pipeline();
    switch(filled)
	{
		case 0:
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
			break;
		case 1:
			for (int i = 0; i < (asteroidBelt.size()); i++)
    		{
				vector<triangle> a = asteroidBelt.at(i).getTess();
				point b = asteroidBelt.at(i).getCenter();
				for (int j = 0; j < (a.size()); j++)
        		{
					glBegin (GL_TRIANGLES);
						glVertex2d(a.at(j).a.x + b.x, a.at(j).a.y + b.y);
						glVertex2d(a.at(j).b.x + b.x, a.at(j).b.y + b.y);
						glVertex2d(a.at(j).c.x + b.x, a.at(j).c.y + b.y);
						glVertex2d(a.at(j).a.x + b.x, a.at(j).a.y + b.y);
					glEnd ();         
        		}
			}
	}

	
	drawShip(enterprise);		


	glColor3f(1.0, 1.0, 0.0);
	for(int i = 0; i < bullets.size(); i++){
			drawBullet(bullets[i]);
		
	}

	glutSwapBuffers();*/


}

/*
 * Main Display Fucntion
 * Displays everything from the Asteroids to the Bullets to the Scoreboard 
 */

void gameView()
{
	//output game to window
	initiateOctogon();  				// Draw the Octogon on Screen 
    glColor3f ( 0.1, 0.5, 0.0 );      	// Set draw color to green
	glPointSize(4.0);					// Set the Point size to 4

	//Pipeline();
    
	//Draw the asteroids
	
	switch(filled)
	{
		//If not filled
		case 0:
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
			break;

		// If filled
		case 1:
			for (int i = 0; i < (asteroidBelt.size()); i++)
    		{
				// Get the tesslated Triangles for the Asteroid.
				vector<triangle> a = asteroidBelt.at(i).getTess();
				// Get the center
				point b = asteroidBelt.at(i).getCenter();
				// Draw the triangles
				for (int j = 0; j < (a.size()); j++)
        		{
					glBegin (GL_TRIANGLES);
						glVertex2d(a.at(j).a.x + b.x, a.at(j).a.y + b.y);
						glVertex2d(a.at(j).b.x + b.x, a.at(j).b.y + b.y);
						glVertex2d(a.at(j).c.x + b.x, a.at(j).c.y + b.y);
//						glVertex2d(a.at(j).a.x + b.x, a.at(j).a.y + b.y);
					glEnd ();         
        		}
			}
	}

	// Draw the ship
	drawShip(enterprise);		

	// Draw the pullets.
	glColor3f(1.0, 1.0, 0.0);
	for(int i = 0; i < bullets.size(); i++){
			drawBullet(bullets[i]);
		
	}

#ifdef DEBUG
	// If DEBUG has been defined, draw the debug display.
	debugDisplay();
#endif

	// Swap the buffers.
	glutSwapBuffers();


}


void gameLoop()
{
	// Open the Ship Log file to record debug information.
	shipLogger.open(SHIP_LOG_PATH, ofstream::out|ofstream::app);

	// If the right arrow key has been pressed rotate the ship
	// Starting at 1 degree then moving to 10 degrees at a time.
	if (rightKeyPressed) 
	{
		if (deltaRot < 10.0 && !rightReached10)
		{
			deltaRot *= 1.1;			// Multiply deltaRot by 1.1.

			if (deltaRot >= 10) 		// If deltaRot reached or 
			{							// went above 10 reset it 
				rightReached10 = true;	// to 10.
				deltaRot = 10;
			}
			
		}

		// Decrement ship rotation by deltaRot (counterclockwise)
		enterprise.rotation = (int)(enterprise.rotation-deltaRot)%360;
		
		// Increment Timekey pressed
		timeKeyPressed++;

		// Log Changes
		shipLogger << endl << "Ship Rotation : " << enterprise.rotation << endl; 
		shipLogger << "Delta Rot : " << deltaRot << endl;
		shipLogger << "Time Right Arrow Pressed = " << timeKeyPressed;
	}

	// If the left arrow key has been pressed rotate the ship
	// Starting at 1 degree then moving to 10 degrees at a time.
	if (leftKeyPressed)
	{
		if (deltaRot < 10.0 && !leftReached10)
		{
			deltaRot *= 1.1;			// Multiply deltaRot by 1.1.
			
			if (deltaRot >= 10)			// If deltaRot reached o
			{							// went above 10 reset it
				leftReached10 = true;	// to 10.
				deltaRot = 10;
			}
			
		}
		
		// Decrement ship rotation by deltaRot (counterclockwise)
		enterprise.rotation = (int)(enterprise.rotation+deltaRot)%360;

		// Increment Timekey pressed
		timeKeyPressed++;

		// Log Changes
		shipLogger << endl << "Ship Rotation : " << enterprise.rotation << endl; 
		shipLogger << "Delta Rot : " << deltaRot << endl;
		shipLogger << "Time Right Arrow Pressed = " << timeKeyPressed << endl;
	}
	
	//Close the ship logger to save changes.
	shipLogger.close();

	// Iterate through and Increment each bullet's location
	for(int i=0; i <bullets.size();i++)
	{
		// We use sine and cosine because we need to tesslate them 
		// along the direction they need to be going or the direction
		// they were shot. We are moving them by 2 each time. 
		bullets.at(i).location.x += 2.0 * cos(bullets.at(i).theta); 
		bullets.at(i).location.y += 2.0 * sin(bullets.at(i).theta);
	}

	// Iterate through and Increment each asteroid's location
	for(int i=0; i <asteroidBelt.size();i++)
	{
		// We use use a function here be cause asteroids are objects
		// and their center, or the location of their left bottom corner
		// is protected. see this function in asteroids.cpp for more information 
		asteroidBelt.at(i).incrementLocation();
	}

	//glutPostRedisplay();	
}

/* 
 * This is supposed to build game window dependencies. Like the storeboard  
 * and other variables that would need to be initiallized. It is currently empty
 */

void initiateGameDisplay()
{
	//build window dependencies
}

/*
 * This function intitiates the number of asteroids that are supposed ot be displayed.
 * It generates that set number and logs the information about the asteroids into the 
 * asteroid log file.
 */

void initiateAsteroids()
{
	// Open log file, record number of asteroids we are going to gnerate, then close to 
	// save changes.
	asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
	asteroidLogger << "\nGenerating " << NUMBER_OF_ASTEROIDS << " asteroids\n\n";
	asteroidLogger.close();

	//Generate Asteroids
	int i = 0;
	while (i<NUMBER_OF_ASTEROIDS)
	{	
		// Open log file, record the asteroid we are on, then close to save changes.
		asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
		asteroidLogger << "Asteroid #" << i << endl;
		asteroidLogger.close();
		// Create an asteroid then push it into the asteroidBelt.
		asteroid a = asteroid();
		asteroidBelt.push_back(a);
		i++;		//increment i.
	}

	// Open log file, record that we have generated asteroidBelt.size() asteroids,
	// then close to save changes.
	asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
	asteroidLogger << "\nGenerated " << asteroidBelt.size() << " asteroids\n";
	asteroidLogger.close();
}

/*
 * This function initiates the enterprise, we might not need this.
 */

void initiateShip()
{
	//Build Ship and ship dependencies.
	enterprise = createShip();
}

/*
 * This function initiates the window. 
 */

void initiateWindow(int argc, char** argv)
{
	//build window
    glutInit(&argc,argv);
	//glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); /* default, not needed */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_MAX_X, WINDOW_MAX_Y); /* set pixel window */
	glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
	glutCreateWindow("Asteroids: RETURN OF METEOR");
}

/*
 * This funtion also initiates the window... sets the interior mainly.  
 */
void initiateGL( void )
{
	glClearColor(0.0,0.0,0.0,1.0); /* black background */
	
	//glColor3f(1.0, 0.0, 0.0); /* draw in red */
    //glPointSize(10.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluOrtho2D(WORLD_COORDINATE_MIN_X, WORLD_COORDINATE_MAX_X,
        WORLD_COORDINATE_MIN_Y, WORLD_COORDINATE_MAX_Y);
	glMatrixMode(GL_MODELVIEW);
}

/*
 * We draw the octogon here, we should probubly save the points generated by the octogon though... 
 */

void initiateOctogon(void)
{
	// Clear the buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// create a vector to hold the points.
	vector<point> pts; 

	// Set the first point, rotate it then push it to the vector of points.
	point p = {WORLD_COORDINATE_MIN_X ,WORLD_COORDINATE_MAX_Y / 2,0,1};
	rotatePoint(p,45.0/2.0);
	pts.push_back(p);
	
	// Repeat the rotation of the next 7 points.
	for (int i = 0; i < 7; i++)
	{
		rotatePoint(p,45);
		pts.push_back(p);
	}	

	// Set color to grean then draw the octogon as lines.
	glColor3f(0.1,0.5,0.0);
	glBegin(GL_LINES);
		for(int i = 0; i < pts.size(); i ++){
			glVertex2f( pts[i].x , pts[i].y);
			glVertex2f( pts[(i+1)%pts.size()].x , pts[(i+1)%pts.size()].y);
		}
	glEnd();
}

/*
 * Keyboard Function, we need these to 
 *
 */

void keyboard(unsigned char key, int x, int y)
{
	
	//if(key == 's' || key == 'S')
		// start game

	//if(key == 'p' || key == 'P')
		//pause movement

	if(key == 'q' || key == 'Q')
		exit(0);

	if(key == 't' || key == 'T')
	{
		filled = 0;
		glutIdleFunc(gameLoop);
	}

	if(key == 'f' || key == 'F')
	{
		filled = 1;	
		glutIdleFunc(gameLoop);
	}

	if(key == 'a' || key == 'A')
	{
		enterprise.rotation += 2.5;
		glutIdleFunc(gameLoop);
	}		

	if(key == 'd' || key == 'D')
	{
		enterprise.rotation -= 2.5;
		glutIdleFunc(gameLoop);
	}

	if(key == ' ')
	{
		bullet shot = createBullet();
		bullets.push_back(shot);
		fireBullet(shot);
		glutIdleFunc(gameLoop);
	}
	if(key == 'b')
	{
		vector<asteroid> temp = asteroidBelt.at(0).breakupAsteroid();
		for (int i = 0; i < temp.size(); i++)
		{
			asteroidBelt.push_back(temp.at(i));
		}
		asteroidBelt.erase(asteroidBelt.begin());
	}
}

void specialKeys(int key, int x, int y){
	switch(key){
		case GLUT_KEY_RIGHT:
			rightKeyPressed = true;
			glutIdleFunc(gameLoop);
			break;

		case GLUT_KEY_LEFT:
			leftKeyPressed = true;
			glutIdleFunc(gameLoop);
			break;	

		/*case SPACEBAR:
			//fire missiles
			bullet shot = createBullet();
			bullets.push_back(shot);
			fireBullet(shot);
			glutIdleFunc(gameLoop);
			break;		*/

		default: break;
	}
}

void keyReleased (int key, int x, int y){
	switch (key) {
		case GLUT_KEY_RIGHT:
			deltaRot = 1.0;
			timeKeyPressed = 0;
			rightKeyPressed = false;
			rightReached10 = false;
			break;

		case GLUT_KEY_LEFT:
			deltaRot = 1.0;
			timeKeyPressed = 0;
			leftKeyPressed = false;
			leftReached10 = false;
			break;
	}			
}

int main(int argc, char** argv)
{
	asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::trunc);
	asteroidLogger << "Asteroid Logging Started" << endl;
	asteroidLogger.close();
	shipLogger.open(SHIP_LOG_PATH, ofstream::out|ofstream::trunc);
	shipLogger << "Ship Logger Started" << endl;
	shipLogger.close();
	initiateWindow(argc, argv); /* Set up Window */
	initiateGL();
	initiateOctogon();
	initiateShip();
	initiateAsteroids();
	initiateGameDisplay();
	glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys); 
	glutSpecialUpFunc(keyReleased);
	glutDisplayFunc(gameView);
	glutIdleFunc(gameLoop);
	glutMainLoop();
}
