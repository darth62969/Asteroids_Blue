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
#include <thread>
#include <chrono>
#include <unistd.h>
#include <string.h>

#define SPACEBAR 32

//Global Variables

//The Ship
#ifndef SHIPTEST
ship enterprise = createShip();
#endif

#ifdef SHIPTEST
ship enterprise = ship(0);
#endif

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
vector<ship> enemies;

float deltaRot = 1.0; 		// For use in the accelleration of ship rotation 

double FPS = 0.0;	// FPS calcuatitions 
double avgFPS;
double origin = (WORLD_COORDINATE_MAX_X / 2);

double aspectRatio;
int WinHeight, WinWidth;
int coordinateXoffset, coordinateYoffset;

bool rightKeyPressed = false;	// These are for the ship rotation functions
bool rightReached10 = false;	// right rotation reached 10
bool leftKeyPressed = false;	// Also for ship rotation, tells us if the ship's
bool leftReached10 = false;		// left rotation reached 10
bool spacePressed = false;		// This is for firing bullets.
bool paused = true;				// For pause screen 
bool gameOver = false;

int GameMode = 0;				// 0 Normal, 1 Endless
int gamestate = 0; 				// 0 Paused, 1 Play, 2 Game Over, 3 Win!!
int gametick = 0;
int timeKeyPressed = 0;			// Iterator for Debug reasons
int filled = 0;					// 0 if lines should be drawn, 1 if filled (asteroids)   
int Level = 1;

int frames = 0;					// How many frames have been counted.
int timeC = 0;					// Time the last was frame drawn
int timeP = 0;					// Time of the current frame draw
int timeC2 = 0;					// Time since start of game loop
int timeP2 = 0;					// Time of at the end of the game loop

int bulletsFired = 0;			// The number of bullets fired
int bulletsHit = 0;				// The number of bullets hit
std::mt19937_64 generator;

/*std::binomial_distribution<int> numsidesdist(ASTEROID_MIN_SIZE, ASTEROID_MAX_SIZE);
std::uniform_real_distribution<double> dirdist(0, 2*M_PI);
std::uniform_real_distribution<double> xlocdist(WORLD_COORDINATE_MIN_X, WORLD_COORDINATE_MAX_X);
std::uniform_real_distribution<double> ylocdist(WORLD_COORDINATE_MIN_Y, WORLD_COORDINATE_MAX_Y);
std::uniform_real_distribution<double> spddist(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED);
std::uniform_int_distribution<int> sizedist(ASTEROID_MIN_SIZE, ASTEROID_MAX_SIZE);*/


//double EndGameAnimation =2;

void *currentfont;				// Bit map font pointer.

void initiateOctogon();			// Function to construct the Octagonal game screen.
void drawOctogon(void);			// Function to draw the octogon.

// Function to set up draw strings on screen at a particular x and y. 

void drawString(GLuint x, GLuint y, const char* string); //THIS IS NOT DRAW A FUCKING SHIP!! YOU MORON!!!

// Function to set the font to a specific font
void setFont(void *font)
{
	currentfont = font;
}

void WindowResizeHandler(int windowWidth, int windowHeight)
{
	aspectRatio = (double) windowWidth/(double)windowHeight;
	WinHeight=windowHeight;
	WinWidth=windowWidth;

	int cxo	= WORLD_COORDINATE_MAX_X-WORLD_COORDINATE_MIN_X;
	int cyo = WORLD_COORDINATE_MAX_Y-WORLD_COORDINATE_MIN_Y;
	
	
	double xSpan=1;
	double ySpan=1;
	glViewport(0,0,WinWidth,WinHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(aspectRatio>1)
	{
		xSpan*=aspectRatio;
	}
	else
	{
		ySpan = xSpan/aspectRatio;
	}

	glOrtho(xSpan*WORLD_COORDINATE_MIN_X, xSpan*WORLD_COORDINATE_MAX_X, 
		ySpan*WORLD_COORDINATE_MIN_Y, ySpan*WORLD_COORDINATE_MAX_Y, 1.0, -1.0);
	


}



void DisplayPause()
{
	// set up the charstrings.
	string pausedString = "ASTEROIDS: Return of Meteor";
	string Startgame = "S = Start Game";
	char PauseGame[50];
	char FireBullets[50];
	char MoveEnterprise[50];
	char ReloadAsteroids[50];
	char ToggleTeslation[50];
	char ToggleGameMode[50];
	
	// Input the information into the char strings
	//sprintf(pausedString, "%s", "ASTEROIDS: Return of Meteor");
	//sprintf(Startgame, "%s", "S = Start Game");
	sprintf(PauseGame, "%s", "P = Pause Game");
	sprintf(FireBullets, "%s", "Space = Fire Misiles");
	sprintf(MoveEnterprise, "%s", "Arrow Keys = Rotate Enterprise");
	sprintf(ReloadAsteroids, "%s", "R = Restart Game");
	sprintf(ToggleTeslation, "%s", "F = Filled Asteroids");
	sprintf(ToggleGameMode, "%s", "M = Toggle between endless and normal");

	//set font draw "paused on screen"
	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	drawString(-200, 220, pausedString.c_str());

	//set font draw help on screen
	setFont(GLUT_BITMAP_HELVETICA_12);
	drawString(-120, -275, Startgame.c_str());
	drawString(-120, -255, PauseGame);
	drawString(-120, -235, FireBullets);
	drawString(-120, -215, MoveEnterprise);
	drawString(-120, -195, ReloadAsteroids);
	drawString(-120, -175, ToggleTeslation);
	drawString(-120, -155, ToggleGameMode);
}

// Function to display the score.
void displayScore(void)
{
	// We calculate the hit ratio (I spot some optmization stuff!!)
	double hitRatio;
	
	switch (bulletsHit)
	{
		default:
			hitRatio = (double)bulletsHit/(double)bulletsFired*100.0;
			break;
		case 0:
			hitRatio = 0;
			break;
	}
	// set the faunt to Helvetica, size 12
	setFont(GLUT_BITMAP_HELVETICA_12);

	// Set up needed charstrings.
	char bulletsFiredStr[50];	
	char astsOnScr1[50];
	char astsOnScr2[50]; 
	char astsHit[50];
	char hrStr[50];
	char mode[50];
	char lvlstr[50];
	char health[50];

	// Place the text into the charstrings.
	switch(GameMode)
	{
		case 0:
			sprintf(mode, "Game Mode: %s", "Normal");
			sprintf(lvlstr, "                       ");
			break;
		case 1:
			sprintf(mode, "Game Mode: %s", "Endless");
			sprintf(lvlstr, "Level : %d", Level);
			break;
		case 2: 
			sprintf(mode, "Game Mode: %s", "Invasion");
			sprintf(lvlstr, "Level : %d", Level);
			break;
		default:
			sprintf(mode, "Game Mode: %s", "Undefined");
			break;
	}
	sprintf(bulletsFiredStr, "Bullets Fired: %3d", bulletsFired);
	sprintf(astsOnScr1, "%s", "Asteroids on "); 
	sprintf(astsOnScr2, "Screen: %3d", (int)asteroidBelt.size()); 
	sprintf(astsHit, "Asteroids Hit: %4d", bulletsHit);
	sprintf(hrStr, "Hit Ratio:  %5.2f %%", hitRatio);
	sprintf(health, "Health: %%%d", enterprise.getHealth() );

	//Set color to green.
	glColor3f(0.2, 0.5, 0.0);
	
	//Draw the strings, left side
	drawString(-280, -230, bulletsFiredStr);
	drawString(-280, -270, astsOnScr1);
	drawString(-280, -255, astsOnScr2);
	
	// draw the strings, right side.
	drawString(180, 30, astsHit);
	drawString(180, 15, mode);
	drawString(180, 65, hrStr);
	
	drawString(-280, 265, health);
	drawString(-280, 250, lvlstr);
	
}

// Function to print game over on screen.
void printGameOver(void)
{
	//Set font
	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	
	//Prep Charsting for printing
	char gameOver[25];
    sprintf(gameOver, "%s", "GAME OVER");

	//Draw the string
    drawString(25, 50, gameOver);
}

// Function to print "you win" on screen.
void printYouWin(void)
{
	// Set font
	setFont(GLUT_BITMAP_TIMES_ROMAN_24);

	// Prep You win CharString
	char youWin[25];
	sprintf(youWin, "%s", "YOU WIN!!!");
	
	// Draw the string.
	drawString(25, 50, youWin);
}

//Function to draw strings.
void drawString(GLuint x, GLuint y, const char* string)
{
	
	// create a pointer to the character
	const char *c;

	//position the drawing pointer
	glRasterPos2i(x, y);
	//glColor3f(1.0, 0.0, 0.0);

	// Print each letter using the font pointer and the character pointer.
	for(c=string; *c!='\0'; c++)
		glutBitmapCharacter(currentfont, *c);	
}

#ifdef SHIPTEST
void generateShips()
{ 
	point world;
	world.x = WORLD_COORDINATE_MAX_X-WORLD_COORDINATE_MIN_X;
	world.y = WORLD_COORDINATE_MAX_Y-WORLD_COORDINATE_MIN_Y;
	int x, y;
	switch(Level)
	{
		case 1:
			for (int i = 0; i < 9; i++)
			{
				enemies.push_back(ship(1));
				x=WORLD_COORDINATE_MAX_X-world.x/10*(i+1);
				y=WORLD_COORDINATE_MIN_Y+world.y/10*9;
				enemies[i].setLocation(x, y);
				enemies[i].setRotation(3*M_PI_2);
			}
			break;
		case 2:
			for (int i = 0; i < 9; i++)
			{
				switch(i%8)
				{
					case 0:
						enemies.push_back(ship(2));
						break;
					default:
						enemies.push_back(ship(1));
						break;
				}
				x=WORLD_COORDINATE_MAX_X-world.x/10*(i+1);
				y=WORLD_COORDINATE_MIN_Y+world.y/10*9;
				enemies[i].setLocation(x, y);
				enemies[i].setRotation(3*M_PI_2);
			}
			break;
	}
}
#endif
// Here we calculate the FPS of the game. (Technically the FrameTime)
void calculateFPS()
{
	// Increment frame count
	frames++;

	// Set current time
	timeC = glutGet(GLUT_ELAPSED_TIME);
	
	// Calculate FrameTime, 1000 because this is in seconds and glut measures time in miliseconds
	FPS = 1000.0/(double)(timeC - timeP);
	
	// Average Frame time calculated by 
	avgFPS = ((avgFPS*(frames-1))+FPS)/frames;

	// Set current time to the time from the previous frame.
	timeP = timeC;
}


// Fucntion to display debug information like frame time
void debugDisplay()
{
	//prep frame time charstrings
	char FPSStr[50];
	char avgFPSStr[50];

	sprintf(FPSStr, "FPS : %4.3f", FPS);
	sprintf(avgFPSStr, "avgFPS : %4.3f", avgFPS);

	// Draw frame time strings.
	drawString(20, WORLD_COORDINATE_MAX_Y-20, FPSStr);
	drawString(20, WORLD_COORDINATE_MAX_Y-35, avgFPSStr);

#ifdef LOGGING
/*	generalLogger.open( GENERAL_LOG_PATH, ofstream::out|ofstream::app);
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

#ifdef LOGGING
/*	generalLogger << triCountStr << endl;
	generalLogger.close();*/
#endif
}

/*
 * Main Display Fucntion
 * Displays everything from the Asteroids to the Bullets to the Scoreboard 
 */
void gameView()
{


		calculateFPS();					// Calculate the interval between this frame and the last.
									// We use this to make game speed independent of framerate. *not anymore
    	glColor3f (0.1, 1, 0.1); 		// Set draw color to green
		glPointSize(4.0);				// Set the Point size to 4
		glClear(GL_COLOR_BUFFER_BIT);	// Clear the buffer bit for some reason...?
	switch(gamestate)	
	{

	
		case 1:
		//output game to window

		drawOctogon();					// Draw the Octogon on Screen 
		clipMeDaddy();					//Draw the asteroids, Why is this "clipMeDaddy?"

		// Print you win if asteroid belt is empty.
		
		// Print Game over if "gameOver" has been set

		
		// This is where we decide if we need to draw asteroids one way or the other.	
		switch(filled)
		{
		// If not filled
			case 0:
				// For each asteroid...
    			for (int i = 0; i < (asteroidBelt.size()); i++)
    			{
					// Get the Location of the lower left corner of the asteroid
					point loc = asteroidBelt.at(i).getCenter();

					// get the location of the points on the asteroid grid
					vector<point> pnt = asteroidBelt.at(i).getPoints();

					for (int j = 0; j < (pnt.size()); j++)
        			{
						glBegin (GL_LINES);
							glVertex2d(pnt[j].x+loc.x, pnt[j].y+loc.y);
							glVertex2d( pnt.at((j+1)%pnt.size()).x + loc.x , pnt.at((j+1)%pnt.size()).y + loc.y);
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
					// Get the pre formated triangles.
					vector<triangle> a = asteroidBelt.at(i).getTess();

					// get the center point
					point b = asteroidBelt.at(i).getCenter();

					// draw the triangles, and the tesselations.
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
		if (paused)
		{
			
		}
		// Draw the ship

		#ifndef SHIPTEST
			drawShip(enterprise);		
		#endif

		#ifdef SHIPTEST
			enterprise.renderShip();
			switch(GameMode)
			{
				case 2:
					for (int i = 0; i < enemies.size(); i++)
					{
						enemies[i].renderShip();
					}
					break;
			}

		#endif
		// Draw the bullets.
		glColor3f(1.0, 1.0, 0.0);
		for(int i = 0; i < bullets.size(); i++)
		{
			#ifndef SHIPTEST
				drawBullet(bullets[i]);
			#endif
			#ifdef SHIPTEST
				bullets[i].drawBullet();
			#endif
		}
	
		switch (GameMode)
		{
			case 0:
			case 1:
				clipMeDaddy(); // Why is this "clip me daddy... i will have to fix this..."

			// draw the octogon
				drawOctogon();
				break;

			case 2:
				break;
		}
	
	//display the score;

		displayScore();
		break;

	case 0:
		DisplayPause();
		break;
	case 2:
		printGameOver();
		break;
	case 3:
		printYouWin();
		break;
	}

	#ifdef DEBUG
		debugDisplay();
	#endif
	// Swap the buffers.
	glutSwapBuffers();
	
}


void gameLoop()
{
	switch (gamestate)
	{
		case 1:
			switch(GameMode)
			{
				case 0:
					if (asteroidBelt.size()==0)
						gamestate=3;
					break;
				case 2:
					if (enemies.size()==0)
					{
						Level++;
						generateShips();
					}

					break;
			}

			timeC2 = glutGet(GLUT_ELAPSED_TIME);
			// If the right arrow key has been pressed rotate the ship
			// Starting at 1 degree then moving to 10 degrees at a time.
			/*
			if (rightKeyPressed && !paused) 
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
				enterprise.rotation = ((int)(enterprise.rotation-(deltaRot*(60/FPS)))%360);
		
				// Increment Timekey pressed
				timeKeyPressed++;
			}

			// If the left arrow key has been pressed rotate the ship
			// Starting at 1 degree then moving to 10 degrees at a time.
			if (leftKeyPressed && !paused)
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
				enterprise.rotation = ((int)(enterprise.rotation+(deltaRot*(60/FPS)))%360);
			
				// Increment Timekey pressed
				timeKeyPressed++;
			}*/
			
			switch (GameMode)
			{	
				case 1:
					if (asteroidBelt.size() == 0)
					{
						Level++;
						for (int i = 0; i < Level; i++)
						{
							asteroid a = asteroid();
							asteroidBelt.push_back(a);
						}
					}
					break;
				case 2:
					switch(gametick)
					{
						case 0:
							for (int i =0; i < enemies.size(); i++)
							{
								enemies[i].iterateAction();
							}
							gametick++;
							break;
						case 5:
							gametick=0;
							break;
						default:
							gametick++;
							break;
					}
			}

		// detect colitions with each asteroid in the belt.
		switch(GameMode)
		{
			case 0:
			case 1:
				for (int i = 0; i < asteroidBelt.size(); i++)
				{
					detectCollision(i);
					for (int j = 0; j<bullets.size(); j++)
					{
						switch((int)(abs(asteroidBelt[i].getCenter().x-bullets[j].getLocation().x)/30)
								-(int)(abs(asteroidBelt[i].getCenter().y-bullets[j].getLocation().y)/30))
						{
							case 0:
								switch(detectCollision(asteroidBelt[i], bullets[j]))
								{
									case 0:
										vector<asteroid> tmp = asteroidBelt[i].breakupAsteroid();
									asteroidBelt.erase(asteroidBelt.begin()+i);

									for (asteroid a : tmp)
									{
										asteroidBelt.push_back(a);
									}
								
									bullets.erase(bullets.begin()+j);
									break;
								}
						}

					}
				}
				break;
				
			case 2:
				for (int i = 0; i < enemies.size(); i++)
				{
					for (int j =0;  j < bullets.size(); j++ )
					{
						switch((int)(abs(enemies[i].getLocation().x-bullets[j].getLocation().x)/50)
							-(int)(abs(enemies[i].getLocation().y-bullets[j].getLocation().y)/50))
						{
							case 0:
								switch (detectCollision(enemies[i], bullets[j]))
								{
									case 0:
										bullets.erase(bullets.begin()+j);
										if(enemies[i].damageHealth(bullets[i].getDamage())<=0)
											enemies.erase(enemies.begin()+i);
										break;
								}
						}
					}
				}
					//detectCollision(i);

				for (int i = 0; i < bullets.size(); i++)
				{
					switch((int)(abs(enterprise.getLocation().x-bullets[i].getLocation().x)/50)
							-(int)(abs(enterprise.getLocation().y-bullets[i].getLocation().y)/50))
					{
						case 0:
							switch(detectCollision(enterprise, bullets[i]))
							{
								case 0:
									bullets.erase(bullets.begin()+i);
									if (enterprise.damageHealth(bullets[i].getDamage())<=0)
										gamestate=2;
									break;
							}
					}
				}
		
		}
	
		// Iterate through and Increment each bullet's location
			for (int i=0; i < bullets.size(); i++)
			{
			// We use sine and cosine because we need to tesslate them 
			// along the direction they need to be going or the direction
			// they were shot. We are moving them by 2 each time.
				//bullets.at(i).location.x += 2.0 * cos(bullets.at(i).theta)/**(60/FPS)*/; 
				//bullets.at(i).location.y += 2.0 * sin(bullets.at(i).theta)/**(60/FPS)*/;
				bullets[i].increment();
				if(!insideOctogon(bullets[i].getLocation()) && bullets.size() > 1 && i <bullets.size())
					bullets.erase(bullets.begin() + i);
			}

		// Iterate through and Increment each asteroid's location
			for (int i=0; i < asteroidBelt.size(); i++)
			{
			// We use use a function here be cause asteroids are objects
			// and their center, or the location of their left bottom corner
			// is protected. see this function in asteroids.cpp for more information 
				asteroidBelt.at(i).incrementLocation();
			}	
		// get the time since thing started.
			timeP2 = glutGet(GLUT_ELAPSED_TIME);
		
		//sleep thread for for a time.
			if(timeP2-timeC2>0)
			{
				this_thread::sleep_for(chrono::milliseconds(18-(timeP2-timeC2)));
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
	//Generate Asteroids
	switch (GameMode)
	{
		case 0:
			for (int i =0; i < NUMBER_OF_ASTEROIDS; i++)
			{	
				// Create an asteroid then push it into the asteroidBelt.
				asteroid a = asteroid();
				asteroidBelt.push_back(a);
			}
			break;
		case 1:
			asteroid a = asteroid();
			asteroidBelt.push_back(a);
			break;
	}

	// Open log file, record that we have generated asteroidBelt.size() asteroids,
	// then close to save changes.
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
	point p = { WORLD_COORDINATE_MIN_X , 0, 0, 1};
	point c = {-WORLD_COORDINATE_MAX_X , 0, 0, 1};	

	point tempp;
	tempp.x = p.x*cos(M_PI_4/2)-p.y*sin(M_PI_4/2);
	tempp.y = p.x*sin(M_PI_4/2)+p.y*cos(M_PI_4/2);
	p = tempp;
	
	tempp.x = c.x*cos(M_PI_4/2)-c.y*sin(M_PI_4/2);
	tempp.y = c.x*sin(M_PI_4/2)+c.y*cos(M_PI_4/2);
	c = tempp;


	octogon.push_back(p);
	clipPts.push_back(c);

	for (int i = 0; i < 7; i++)
	{
		tempp.x = p.x*cos(-M_PI_4)-p.y*sin(-M_PI_4);
		tempp.y = p.x*sin(-M_PI_4)+p.y*cos(-M_PI_4);
		p = tempp;

		tempp.x = c.x*cos(-M_PI_4)-c.y*sin(-M_PI_4);
		tempp.y = c.x*sin(-M_PI_4)+c.y*cos(-M_PI_4);
		c = tempp;

		octogon.push_back(p);
		clipPts.push_back(c);
	}
	noOctogon = 0;
}

void drawOctogon(void)
{
	
	glColor3f(0.1,0.5,0.0);
	
	glBegin(GL_LINE_LOOP);
		for(int i = 0; i < octogon.size(); i ++)
		{
			glVertex2f(octogon[i].x, octogon[i].y);
		}
	glEnd();
}

void debugMe(int x, int y)
{
	point p = {x, y, 0, 1};
	std::cout << insideOctogon(p);
}

/*
 * Keyboard Functions
 */
void keyboard(unsigned char key, int x, int y)
{	
	// start game
	switch (key)
	{
		//starts game
		case 'S':
		case 's':
			switch(gamestate)
			{
				case 0:
					gamestate=1;
					paused=false;
					break;
				case 1:
					break;
			}
			break;

		//pauses game
		case 'P':
		case 'p':
			switch(gamestate)
			{
				case 0:
					gamestate=1;
					paused=false;
					break;
				case 1:
					gamestate=0;
					paused=true;
					break;
			}
			break;
		
		//reloads asteroids and pauses game.
		case 'r':
		case 'R':
			Level=1;
			gamestate=0;
			asteroidBelt.clear();
			bullets.clear();
			initiateAsteroids();
			bulletsFired=0;
			paused=true;
			gameOver = false;
#ifndef SHIPTEST
			enterprise.rotation=0;		
			resetShip();
#endif
#ifdef SHIPTEST
			enterprise.setRotation(0);
			enterprise.resetShip();
#endif
			bulletsHit = 0;	
			break;
		//quits game
		case 'q':
		case 'Q':
			exit(0);
			break;
		//toggles fill state
		case 'f':
		case 'F':
			switch (filled)
			{
				case 0:
					filled = 1;
					break;
				case 1:
					filled = 2;
					break;
				case 2: 
					filled = 0;
					break;
			}
			break;

		//Fires Bullet once;
		case ' ':
			switch (gamestate)
			{
				case 1:
					glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
					if(!spacePressed)
					{/*
						spacePressed = true;
						bullet shot = createBullet();
						bullets.push_back(shot);
						bulletsFired++;*/
					}	
					break;
			}
			break;

		case 'm':
		case 'M':
			gamestate=0;
			asteroidBelt.clear();
			bullets.clear();
			bulletsFired=0;
			paused=true;
			gameOver = false;

#ifndef SHIPTEST
			enterprise.rotation=0;		
#endif

			int x, y;

			bulletsHit = 0;	
			switch (GameMode)
			{
				case 0:
					GameMode=1;
					initiateAsteroids();
#ifdef SHIPTEST
					enterprise.setRotation(0);
#endif
					break;
				case 1:
					GameMode=2;
#ifdef SHIPTEST
					enterprise.setLocation(WORLD_COORDINATE_MAX_X/2, WORLD_COORDINATE_MAX_Y/5);
					enterprise.setRotation(M_PI_2);
					generateShips();
#endif
					break;
				case 2:
					GameMode=0;
					initiateAsteroids();
#ifdef SHIPTEST
					enterprise.setRotation(0);
#endif
					break;
			}
			break;


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
		
void mouse(int button, int state, int x, int y)
{
        if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		{
        }
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			switch(gamestate)
			{
				case 1:
#ifndef SHIPTEST
					spacePressed = true;
					bullet shot = createBullet();
					bullets.push_back(shot);
					bulletsFired++;
#endif
#ifdef SHIPTEST
					enterprise.fire();
#endif
					break;
			}          
        }
}
void passiveMouse(int x, int y)
{
	//cout<< "mouse at ( " << x << " , " << y << " )\n";
	int x2 = WinWidth/2-x;
	int y2 = y-WinHeight/2;
	point temp ={x, y, 0, 1};
	point pnt;
	double bearing;
	#ifndef SHIPTEST
		double bearing =-1( atan2f(enterprise.aLocation.y-y2, enterprise.aLocation.x-x2)); //* (180 / M_PI))+180;
		enterprise.rotation=bearing;
	#endif

	#ifdef SHIPTEST
	switch(GameMode)
	{
		case 0:
		case 1:
			pnt = enterprise.getAtkPnts()[0];
			bearing =(atan2f(pnt.y-y2, pnt.x-x2));
			enterprise.setRotation(bearing);
			break;

		case 2:
			enterprise.setLocation(-1*x2, WORLD_COORDINATE_MIN_Y+((WORLD_COORDINATE_MAX_Y-WORLD_COORDINATE_MIN_Y)/5));
			break;
	}

	#endif
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
	chrono::high_resolution_clock::time_point s = chrono::high_resolution_clock::now();
	chrono::high_resolution_clock::duration d = chrono::high_resolution_clock::now()-s;
	unsigned s2 = d.count();
	generator.seed(s2);
	initiateWindow(argc, argv); 				/* Set up Window 					*/
	initiateGL();								/* Initiate GL   					*/
	initiateOctogon();							/* Initiate The Game View 			*/
	initiateAsteroids();						/* Generate Asteroids				*/
	initiateGameDisplay();						/* Does nothing 					*/
	glutReshapeFunc(WindowResizeHandler);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);		/* Set Key Repeat on 				*/
	glutMouseFunc(mouse);						/* Set a Mouse funtion				*/
	glutPassiveMotionFunc(passiveMouse);
	glutKeyboardFunc(keyboard);					/* Set a keyboard Funcitons			*/
	glutKeyboardUpFunc(keyReleased);			
	glutSpecialFunc(specialKeys); 
	glutSpecialUpFunc(specialKeyReleased);
#ifdef MULTIT
	thread Render (glutDisplayFunc, gameView);
	thread Idle (glutIdleFunc, gameLoop);
#endif
#ifndef MULTIT
	glutDisplayFunc(gameView);					/* Set loop for The game rendering	*/
	glutIdleFunc(gameLoop);						/* Set loop for the game processing	*/
#endif
	glutMainLoop();								/* Start the main loop				*/
}
