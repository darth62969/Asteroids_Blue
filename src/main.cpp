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

//Global Variables

//The Ship
ship enterprise = createShip();
vector<point> octogon; bool noOctogon = 1;
vector<point> clipPts;

//Log Writers
ofstream asteroidLogger;		// Asteroid loggger, records information about the asteroids into the asteroid log file.
ofstream shipLogger;			// Ship logger, records information about the ship into the ship log.
ofstream collisionLogger;		// Collision logger, records information about colitions into the collision log.
ofstream bulletLogger;			// Bullet Logger, records information about bullets into the bullet log.
ofstream transformationLogger;		// Transfomration logger, records information about transforms into tranformmation log.
ofstream generalLogger;

// Log paths
char* ASTEROID_LOG_PATH = "logs/asteroid_log.txt";
char* SHIP_LOG_PATH = "logs/ship_log.txt";
char* COLLISION_LOG_PATH = "logs/collision_log.txt";
char* BULLET_LOG_PATH = "logs/bullet_log.txt";
char* TRANSFORMATION_LOG_PATH = "logs/transformation_log.txt";
char* GENERAL_LOG_PATH = "logs/general_log.txt";

//Runtime Variables
vector<asteroid> asteroidBelt; 	// Holds all asteroids
vector<bullet> bullets; 	// Holds all bullets

float deltaRot = 1.0; 		// For use in the accelleration of ship rotation 

double FPS = 0.0;	// FPS calcuatitions 
double avgFPS;
double origin = (WORLD_COORDINATE_MAX_X / 2);

bool rightKeyPressed = false;	// These are for the ship rotation functions
bool rightReached10 = false;	// right rotation reached 10
bool leftKeyPressed = false;	// Also for ship rotation, tells us if the ship's
bool leftReached10 = false;		// left rotation reached 10
bool spacePressed = false;		// This is for firing bullets.
bool paused = true;				// For pause screen 
bool gameOver = false;

int timeKeyPressed = 0;		// Iterator for Debug reasons
int filled = 0;			// 0 if lines should be drawn, 1 if filled (asteroids)   
int frames = 0;
int timeC = 0;
int timeP = 0;
int bulletsFired = 0;
int bulletsHit = 0;

void *currentfont;

void initiateOctogon();
void drawOctogon(void);

void drawString(GLuint x, GLuint y, const char* string);



void setFont(void *font)
{
	currentfont = font;
}

void displayScore(void)
{

	double hitRatio;
	
	if (bulletsHit != 0)
		hitRatio = (double)bulletsHit/(double)bulletsFired*100.0;
	else 
		hitRatio = 0;

	setFont(GLUT_BITMAP_HELVETICA_12);

	char bulletsFiredStr[50];
	char astsOnScr1[50];
	char astsOnScr2[50]; 
	char astsHit[50];
	char hrStr[50];

	sprintf(bulletsFiredStr, "Bullets Fired: %3d", bulletsFired);
	sprintf(astsOnScr1, "%s", "Asteroids on "); 
	sprintf(astsOnScr2, "Screen: %3d", (int)asteroidBelt.size()); 
	sprintf(astsHit, "Asteroids Hit: %4d", bulletsHit);
	sprintf(hrStr, "Hit Ratio:  %5.2f %%", hitRatio);

	glColor3f(0.2, 0.5, 0.0);
	
	drawString(20, 30, bulletsFiredStr);
	drawString(20, 70, astsOnScr1);
	drawString(20, 55, astsOnScr2);
	
	drawString(480, 30, astsHit);
	drawString(480, 65, hrStr);
}

void printGameOver(void){
               

		char gameOver[25];
                setFont(GLUT_BITMAP_TIMES_ROMAN_24);
               
               sprintf(gameOver, "%s", "GAME OVER");
   
		//sprintf();

                drawString(225, 320, gameOver);
}

void printYouWin(void){
	char youWin[25];
	//setFont(GLUT_BITMAP_9_BY_15);
	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	sprintf(youWin, "%s", "YOU WIN!!!");
	drawString(235, 320, youWin);
}


void drawString(GLuint x, GLuint y, const char* string)
{
	const char *c;

	glRasterPos2i(x, y);
	//glColor3f(1.0, 0.0, 0.0);
	for(c=string; *c!='\0'; c++)
		glutBitmapCharacter(currentfont, *c);	
}

void calculateFPS()
{
	/*if (paused)
	{
		FPS=60;
		return;
	}*/
		
	frames++;
	timeC = glutGet(GLUT_ELAPSED_TIME);
	FPS = 1000.0/(double)(timeC - timeP);
	avgFPS= ((avgFPS*(frames-1))+FPS)/frames;
	timeP = timeC;
}

void debugDisplay()
{
	//display FPS
	char FPSStr[50];
	char avgFPSStr[50];
	
	sprintf(FPSStr, "FPS : %4.3f", FPS);
	sprintf(avgFPSStr, "avgFPS : %4.3f", avgFPS);

	drawString(20, WORLD_COORDINATE_MAX_Y-20, FPSStr);
	drawString(20, WORLD_COORDINATE_MAX_Y-35, avgFPSStr);

#ifdef LOGGING/*
	generalLogger.open( GENERAL_LOG_PATH, ofstream::out|ofstream::app);
	generalLogger << FPSStr << endl;
	generalLogger << avgFPSStr << endl;*/
#endif 
	// Count Asteroid Triangles

	int triCount = 0;

	char triCountStr[50];

	for (int i = 0; i < asteroidBelt.size(); i++)
	{
		triCount += asteroidBelt[i].getTess().size();
	}

//Display Triangle Count
	sprintf(triCountStr, "Triangles On Screen : %3d", triCount);
	drawString(20, WORLD_COORDINATE_MAX_Y-50, triCountStr);
#ifdef LOGGING/*
	generalLogger << triCountStr << endl;
	generalLogger.close();*/
#endif
}

/*
 * Main Display Fucntion
 * Displays everything from the Asteroids to the Bullets to the Scoreboard 
 */

 // Q: Why is this a method? - Ted
 // A: Because it is the Main Game Display Fucntion - Jonathan
 // R: Hmm, I see - Ted
void gameView()
{
	//output game to window
	calculateFPS();				// Calculate the interval between this frame and the last.
								// We use this to make game speed independent of framerate.
    glColor3f (0.1, 0.5, 0.0); 	// Set draw color to green
	glPointSize(4.0);			// Set the Point size to 4
	drawOctogon();				// Draw the Octogon on Screen 
	//Draw the asteroids

	//printGameOver();
	if (asteroidBelt.size()==0)
		printYouWin();
	if (gameOver)
	{
		printGameOver();
		paused = true;
	}
		
	switch(filled)
	{
		// If not filled
		case 0:
    			for (int i = 0; i < (asteroidBelt.size()); i++)
    			{
				vector<point> a = asteroidBelt.at(i).getRealPoints();
				//point b = asteroidBelt.at(i).getCenter();
				for (int j = 0; j < (a.size()); j++)
        			{
					glBegin (GL_LINES);
						glVertex2d(a[j].x, a[j].y);
						glVertex2d( a.at((j+1)%a.size()).x , a.at((j+1)%a.size()).y);
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
					glEnd ();         
        			}
			}
			break;
		// If filled == 2
		case 2: 
			for (int i = 0; i < (asteroidBelt.size()); i++)
	    		{
				vector<triangle> a = asteroidBelt.at(i).getTess();
				point b = asteroidBelt.at(i).getCenter();
				for (int j = 0; j < (a.size()); j++)
				{
					glBegin (GL_LINES);
						glVertex2d(a.at(j).a.x + b.x, a.at(j).a.y + b.y);
						glVertex2d(a.at(j).b.x + b.x, a.at(j).b.y + b.y);
						glVertex2d(a.at(j).b.x + b.x, a.at(j).b.y + b.y);
						glVertex2d(a.at(j).c.x + b.x, a.at(j).c.y + b.y);
						glVertex2d(a.at(j).c.x + b.x, a.at(j).c.y + b.y);
						glVertex2d(a.at(j).a.x + b.x, a.at(j).a.y + b.y);
					glEnd();
				}
			}
	}
	
	// Draw the ship
	drawShip(enterprise);		

	// Draw the bullets.
	glColor3f(1.0, 1.0, 0.0);
	for(int i = 0; i < bullets.size(); i++)
		drawBullet(bullets[i]);

	displayScore();

#ifdef DEBUG
	debugDisplay();
#endif

	// Swap the buffers.
	glutSwapBuffers();
}

void gameLoop()
{
	if (!paused){
	// Open the Ship Log file to record debug information.
#ifdef LOGGING/*
	shipLogger.open(SHIP_LOG_PATH, ofstream::out|ofstream::app);*/
#endif
	// If the right arrow key has been pressed rotate the ship
	// Starting at 1 degree then moving to 10 degrees at a time.
	if (rightKeyPressed && !paused) 
	{
		if (deltaRot < 10.0 && !rightReached10)
		{
			deltaRot *= 1.1;		// Multiply deltaRot by 1.1.

			if (deltaRot >= 10) 		// If deltaRot reached or 
			{				// went above 10 reset it 
				rightReached10 = true;	// to 10.
				deltaRot = 10;
			}			
		}
		

		// Decrement ship rotation by deltaRot (counterclockwise)
		enterprise.rotation = ((int)(enterprise.rotation-(deltaRot*(60/FPS)))%360);
		
		// Increment Timekey pressed
		timeKeyPressed++;

		// Log Changes
#ifdef LOGGING/*
		shipLogger << endl << "Ship Rotation : " << enterprise.rotation << endl; 
		shipLogger << "Delta Rot : " << deltaRot << endl;
		shipLogger << "Time Right Arrow Pressed = " << timeKeyPressed;*/
#endif
	}

	// If the left arrow key has been pressed rotate the ship
	// Starting at 1 degree then moving to 10 degrees at a time.
	if (leftKeyPressed && !paused)
	{
		if (deltaRot < 10.0 && !leftReached10)
		{
			deltaRot *= 1.1;		// Multiply deltaRot by 1.1.
			
			if (deltaRot >= 10)		// If deltaRot reached o
			{				// went above 10 reset it
				leftReached10 = true;	// to 10.
				deltaRot = 10;
			}		
		}
		
		// Decrement ship rotation by deltaRot (counterclockwise)
		enterprise.rotation = ((int)(enterprise.rotation+(deltaRot*(60/FPS)))%360);

		// Increment Timekey pressed
		timeKeyPressed++;

		// Log Changes
#ifdef LOGGING/*
		shipLogger << endl << "Ship Rotation : " << enterprise.rotation << endl; 
		shipLogger << "Delta Rot : " << deltaRot << endl;
		shipLogger << "Time Right Arrow Pressed = " << timeKeyPressed << endl;*/
#endif
	}
	
	//Close the ship logger to save changes.
#ifdef LOGGING/*
	shipLogger.close();*/
#endif
#ifdef LOGGING
		collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::app);
		collisionLogger << "\nRunning Collision Detection checks\n";
		collisionLogger << asteroidBelt.size() << endl;
		collisionLogger.close();
#endif
	for (int i = 0; i < asteroidBelt.size(); i++)
	{

		detectCollision(i);
	}

	// Iterate through and Increment each bullet's location
	for(int i=0; i < bullets.size();i++)
	{
		// We use sine and cosine because we need to tesslate them 
		// along the direction they need to be going or the direction
		// they were shot. We are moving them by 2 each time.

		bullets.at(i).location.x += 2.0 * cos(bullets.at(i).theta)*(60/FPS); 
		bullets.at(i).location.y += 2.0 * sin(bullets.at(i).theta)*(60/FPS);
		if(!insideOctogon(bullets[i].location) && bullets.size() > 1 && i <bullets.size())
		{
			bullets.erase(bullets.begin() + i);
		}
	}

	// Iterate through and Increment each asteroid's location
	for(int i=0; i <asteroidBelt.size();i++)
	{
		// We use use a function here be cause asteroids are objects
		// and their center, or the location of their left bottom corner
		// is protected. see this function in asteroids.cpp for more information 
		asteroidBelt.at(i).incrementLocation();
	}

	
	}
	glutPostRedisplay();
}

/* 
 * This is supposed to build game window dependencies. Like the scoreboard  
 * and other variables that would need to be initiallized. It is currently empty
 */
void initiateGameDisplay()
{
	//build window dependencies
}

/*
 * This function intitiates the number of asteroids that are supposed to be displayed.
 * It generates that set number and logs the information about the asteroids into the 
 * asteroid log file.
 */
void initiateAsteroids()
{
	// Open log file, record number of asteroids we are going to gnerate, then close to 
	// save changes.
#ifdef LOGGING
	asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
	asteroidLogger << "\nGenerating " << NUMBER_OF_ASTEROIDS << " asteroids\n\n";
	asteroidLogger.close();
#endif
	//Generate Asteroids
	int i = 0;
	while (i < NUMBER_OF_ASTEROIDS)
	{	
		// Open log file, record the asteroid we are on, then close to save changes.
#ifdef LOGGING
		asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
		asteroidLogger << "Asteroid #" << i << endl;
		asteroidLogger.close();
#endif
		// Create an asteroid then push it into the asteroidBelt.
		asteroid a = asteroid();
		asteroidBelt.push_back(a);
		i++;
	}

	// Open log file, record that we have generated asteroidBelt.size() asteroids,
	// then close to save changes.
#ifdef LOGGING	
	asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
	asteroidLogger << "\nGenerated " << asteroidBelt.size() << " asteroids\n";
	asteroidLogger.close();
#endif
}

/*
 * This function initiates the window. 
 */
void initiateWindow(int argc, char** argv)
{
	//build window
   	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_MAX_X, WINDOW_MAX_Y); /* set pixel window */
	glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
	glutCreateWindow("Asteroids: RETURN OF METEOR");
}

/*
 * This funtion also initiates the window. Primarily sets the interior.  
 */
void initiateGL(void)
{
	glClearColor(0.0,0.0,0.0,1.0); /* black background */

    	glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
	gluOrtho2D(WORLD_COORDINATE_MIN_X, WORLD_COORDINATE_MAX_X,
        WORLD_COORDINATE_MIN_Y, WORLD_COORDINATE_MAX_Y);
	glMatrixMode(GL_MODELVIEW);
}

/*
 * We draw the octogon here.
 */
void initiateOctogon(void)
{
	// Clear the buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// create a vector to hold the points.
	vector<point> pts; 

	// Set the first point, rotate it then push it to the vector of points.
	point p = {WORLD_COORDINATE_MIN_X ,WORLD_COORDINATE_MAX_Y / 2,0,1};
	point c = {WORLD_COORDINATE_MAX_X / 4, WORLD_COORDINATE_MAX_Y / 2, 0,1};	


	rotatePoint(p,45.0/2.0);
	rotatePoint(c,45.0/2.0);

	octogon.push_back(p);
	clipPts.push_back(c);
	
	for (int i = 0; i < 7; i++)
	{
		rotatePoint(p,-45);
		rotatePoint(c,-45);

		octogon.push_back(p);
		clipPts.push_back(c);
	}	

	noOctogon = 0;
}

void drawOctogon(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.1,0.5,0.0);
	
	glBegin(GL_LINES);
		for(int i = 0; i < octogon.size(); i ++)
		{
			glVertex2f(octogon[i].x, octogon[i].y);
			glVertex2f(octogon[(i+1)%octogon.size()].x, octogon[(i+1)%octogon.size()].y);
		}
	glEnd();
}

void debugMe(int x, int y)
{
	point p = {x,y,0,1};
	int result = insideOctogon(p);
	if (result) printf("        ");

}

/*
 * Keyboard Functions
 */
void keyboard(unsigned char key, int x, int y)
{	
	// start game
	if((key == 's' || key == 'S') && !gameOver)
		paused = false;

	// pause movement
	if((key == 'p' || key == 'P') && !gameOver)
	{
		if (paused)
			paused = false;
		else
			paused = true;
	}
	// pause movement
	if(key == 'r' || key == 'R')
	{
		asteroidBelt.clear();
		bullets.clear();
		initiateAsteroids();
		bulletsFired=0;
		paused=true;
		gameOver = false;
		enterprise.rotation=0;
		bulletsHit = 0;
	}


	// Exits the game.
	if(key == 'q' || key == 'Q')
		exit(0);

	// Shows tessellation lines for every asteroid
	if(key == 't' || key == 'T')
	{
		if(filled != 2)
			filled = 2;
		else
			filled = 0;
	}

	// Fills the asteroids.
	if(key == 'f' || key == 'F')
	{
		if(filled != 1)
			filled = 1;
		else
			filled = 0;
	}

	// Fires a bullet.
	if(key == ' ' && !paused)
	{
		glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
		if(!spacePressed)
		{
			spacePressed = true;
			bullet shot = createBullet();
			bullets.push_back(shot);
			bulletsFired++;
		}
	}

#ifdef DEBUG	
	if(key == 'b')
	{
		vector<asteroid> temp = asteroidBelt.at(0).breakupAsteroid();
		for (int i = 0; i < temp.size(); i++)
		{
			asteroidBelt.push_back(temp.at(i));
		}
		asteroidBelt.erase(asteroidBelt.begin());
		// REMOVE LATER
		bulletsHit++;
	}
#endif
}


// Handles the firing of bullets.
void keyReleased(unsigned char key, int x, int y)
{
	// When the space key is released after being tapped, fire a bullet.
	if(key == ' ')
	{
		glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
		spacePressed = false;
	}
}

// Handles the rotation of the ship.
void specialKeys(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_RIGHT:
			rightKeyPressed = true;
			//glutIdleFunc(gameLoop);
			break;

		case GLUT_KEY_LEFT:
			leftKeyPressed = true;
			//glutIdleFunc(gameLoop);
			break;

		default: break;
	}
}
void specialKeyReleased(int key, int x, int y)
{
	switch(key)
	{
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
void mouse(int button, int state, int x, int y){
        if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		{
                       
        }
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
                       debugMe(x,y);
        }
}

int main(int argc, char** argv)
{
#ifdef LOGGING
	asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::trunc);
	asteroidLogger << "Asteroid Logging Started" << endl;
	asteroidLogger.close();
	shipLogger.open(SHIP_LOG_PATH, ofstream::out|ofstream::trunc);
	shipLogger << "Ship Logger Started" << endl;
	shipLogger.close();
	generalLogger.open(GENERAL_LOG_PATH, ofstream::out|ofstream::trunc);
	generalLogger << "General Logging Started " << endl;
	generalLogger.close();
	collisionLogger.open(COLLISION_LOG_PATH, ofstream::out|ofstream::trunc);
	collisionLogger << "Collision Logging Started " << endl;
	collisionLogger.close();
#endif
	initiateWindow(argc, argv); /* Set up Window */
	initiateGL();
	initiateOctogon();
	initiateAsteroids();
	initiateGameDisplay();
	glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyReleased);
	glutSpecialFunc(specialKeys); 
	glutSpecialUpFunc(specialKeyReleased);
	glutDisplayFunc(gameView);
	glutIdleFunc(gameLoop);
	glutMainLoop();
}


// temporary cold storage.
/*

*/

