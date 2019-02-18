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

#define _USE_MATH_DEFINES


#include <fstream>
#include <dlfcn.h>
#include "headers.h"
#include "mode.h"
#include "structs.h"
#include "windowProperties.h"


#ifdef WINDOWS
#include "mingw.thread.h"
#endif

#define SPACEBAR 32

// User Modes
std::vector<mode *> usrModes;
mode * curMode;

//Global Variables

//The Ship

//enterprise player = enterprise();

//std::vector<point> octogon; 
bool noOctogon = 1;
std::vector<point> clipPts;


render * r = new render();
//Runtime Variables
//std::vector<asteroid> asteroidBelt; 	// Holds all asteroids
//std::vector<bullet> bullets; 	// Holds all bullets
//std::vector<ship> enemies;

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

int bottomFifth = WORLD_COORDINATE_MIN_Y+((WORLD_COORDINATE_MAX_Y-WORLD_COORDINATE_MIN_Y)/5);

int menuLevel = 0;
int menuSelection = 0;
int menuOptions = 0;
std::vector<int> selections;



//void initiateOctogon();			// Function to construct the Octagonal game screen.
//void drawOctogon(void);			// Function to draw the octogon.
//void initiateAsteroids();
//void generateShips();

// Function to set up draw strings on screen at a particular x and y. 

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

void setGameMode(int i)
{

	if (i < usrModes.size())
	{
		curMode=usrModes[i];
	}
}

void DisplayPause()
{
	// set up the charstrings.
	std::string pausedString = "ASTEROIDS: Return of Meteor";
	std::vector<std::string> items;
	char ToggleGameMode[50];
	char menu[50];
	sprintf(menu, "Menu level = %d and menuSelection = %d",  menuLevel, menuSelection);

	r->setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	r->drawString(-200, 220, pausedString.c_str());

	if (selections.empty())
	{
		
		items.push_back("Modes");
		items.push_back("Options");
		items.push_back("Controls");
		items.push_back("Quit");
		menuOptions=items.size();
		r->setFont(GLUT_BITMAP_HELVETICA_18);
		for(int i = 0; i < items.size(); i++)
		{
			if(i==menuSelection)
			{
				glColor3f (1, 1, 0.1);
				r->drawString(-120, 0+(-20*i),items[i].c_str());
				glColor3f (0.1, 1, 0.1);
			}
			else
			{
				r->drawString(-120, 0+(-20*i),items[i].c_str());
			}
		}
	}
	else
	{
		switch(selections.size())
		{
			case 0:
				items.push_back("Modes");
				items.push_back("Options");
				items.push_back("Controls");
				items.push_back("Quit");

				r->setFont(GLUT_BITMAP_HELVETICA_18);
				for(int i = 0; i < items.size(); i++)
				{
					if(i==menuSelection)
					{
						glColor3f (1, 1, 0.1);
						r->drawString(-120, 0+(-20*i),items[i].c_str());
						glColor3f (0.1, 1, 0.1);
					}
					else
					{
						r->drawString(-120, 0+(-20*i),items[i].c_str());
					}
				}
				break;

			case 1:
				switch(selections[0])
				{
					case 0:
						for(mode * m : usrModes)
						{
							items.push_back(m->getName());
						}
						/*
						items.push_back("Normal");
						items.push_back("Endless");
						items.push_back("Invaders");
						items.push_back("Bullet Hell");*/
						
						menuOptions=items.size();

						r->setFont(GLUT_BITMAP_HELVETICA_18);
						
						for(int i = 0; i < items.size(); i++)
						{
							if(i==menuSelection)
							{
								glColor3f (1, 1, 0.1);
								r->drawString(-120, 0+(-20*i),items[i].c_str());
								glColor3f (0.1, 1, 0.1);
							}
							else
							{
								r->drawString(-120, 0+(-20*i),items[i].c_str());
							}
						}
						break;	

					case 2:
						menuOptions=0;
						items.push_back("S = Start Game");
						items.push_back("P = Pause Game");
						items.push_back("Space = Fire Missiles");
						items.push_back("Arrow Keys = Rotate player");
						items.push_back("R = Restart Game");
						items.push_back("F = Filled Asteroids");
						items.push_back("M = Toggle between endless and normal");

						r->setFont(GLUT_BITMAP_HELVETICA_12);
						for (int i = 0; i<items.size(); i++)
						{
							r->drawString(-120, 0+(-20*i),items[i].c_str());
						}

					break;
					
					case 3:
						exit(0);
						break;

				}
				break;
			case 2:
				switch(selections[0])
				{
					case 0:
						setGameMode(selections[1]);
						selections.clear();
						gamestate=1;
						break;
				}
		}
	}
}

// Function to display the score.

// Function to print game over on screen.
void printGameOver(void)
{
	//Set font
	r->setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	
	//Prep Charsting for printing
	char gameOver[25];
    sprintf(gameOver, "%s", "GAME OVER");

	//Draw the string
    r->drawString(25, 50, gameOver);
}

// Function to print "you win" on screen.
void printYouWin(void)
{
	// Set font
	r->setFont(GLUT_BITMAP_TIMES_ROMAN_24);

	// Prep You win CharString
	char youWin[25];
	sprintf(youWin, "%s", "YOU WIN!!!");
	
	// Draw the string.
	r->drawString(25, 50, youWin);
}

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
			if(curMode)
			{
				curMode->drawAll();
			}
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
	glutSwapBuffers();
	
}


void gameLoop()
{
	timeC2 = glutGet(GLUT_ELAPSED_TIME);

	switch (gamestate)
	{
		case 1:
			curMode->step();
			break;
	
	}
	timeP2 = glutGet(GLUT_ELAPSED_TIME);
		
	//sleep thread for for a time.
	if(timeP2-timeC2<16)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(16-(timeP2-timeC2)));
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

bool intersect(point v1, point v2, point v3, point v4)
{
	float ua_num = ((v3.x - v1.x) * -(v4.y - v3.y)) - (-(v4.x - v3.x) * (v3.y - v1.y));
	float den = ((v2.x - v1.x) * -(v4.y - v3.y)) - (-(v4.x - v3.x) * (v2.y - v1.y));

	float ub_num = ((v2.x - v1.x) * (v3.y - v1.y)) - ((v3.x - v1.x) * (v2.y - v1.y));

	float ua = ua_num / den;
	float ub = ub_num / den;

	if((ua > 0.0) && (ua < 1.0) && (ub > 0.0) && (ub < 1.0))
	{
		return true;
	}

	return false;
}


void drawOctogon(void)
{
}

void debugMe(int x, int y)
{
	point p = {x, y, 0, 1};
	//std::cout << insideOctogon(p);
}

/*
 * Keyboard Functions
 */
void keyboard(unsigned char key, int x, int y)
{	
	if(curMode)
	{
		curMode->keyboardFunc(key, x, y);
	}
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
			//asteroidBelt.clear();
			//bullets.clear();
			initiateAsteroids();
			bulletsFired=0;
			paused=true;
			gameOver = false;

			#ifdef SHIPTEST
				//player.setRotation(0);
				//player.resetShip();
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
			//asteroidBelt.clear();
			//bullets.clear();
			bulletsFired=0;
			paused=true;
			gameOver = false;
			//player.setHealth(100);

			int x, y;

			bulletsHit = 0;
			break;
			
		case 13 :
			if(menuOptions>0)
			{
				selections.push_back(menuSelection);
				menuSelection=0;
				menuLevel++;
			}
			break;

		case 8 :
			if(menuLevel>0)
			{
				menuLevel--;
				selections.erase(selections.begin()+menuLevel);
				menuSelection=0;
			}
			break;
	}
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
	switch (gamestate)
	{
		case 0:
			switch (key)
			{
				case GLUT_KEY_UP:
					menuSelection=(menuSelection-1)%menuOptions;
					break;
				case GLUT_KEY_DOWN:
					menuSelection=(menuSelection+1)%menuOptions;
					break;
			}
	}
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

/* The Mouse Function gets button input and forwards it
 * it to the current mode.
 */
		
void mouse(int button, int state, int x, int y)
{
	if(curMode)
	{
		curMode->mouseFunc(button, state, x, y);
	}
}

/* The Passive Mouse Function finds where in the world 
 * the mouse is and then forwards that information to
 * the current mode for processing.
 */
void passiveMouse(int x, int y)
{
	int x2 = WinWidth/2-x;
	int y2 = y-WinHeight/2;
	point temp ={x, y, 0, 1};
	point pnt;
	double bearing;
	if(curMode)
	{
		curMode -> passiveMouseFunc(x2, y2);
	}
}

typedef mode* create_t();

void initModes()
{/*
	mode * temp = new mode();
	usrModes.push_back(temp);
	curMode = temp;*/
	std::fstream in("libraries.txt", std::fstream::in);
	while (in)
	{
		std::string str;
		std::getline(in, str);
		//in >> str;
		std::cout << str << std::endl;
		

		//typedef mode * (create_t)();
		//std::cout << "created function pointer\n";
		//void *handle = dlopen(str.c_str(), RTLD_NOW);
		void *handle = dlopen("./normal.mode", RTLD_NOW);
		if(!handle)
		{
			std::cout << "ERROR " << dlerror() <<std::endl;
		}
		if (handle)
		{
			std::cout << "found library\n";
		}

		create_t* create = dlsym(handle,"create");

		
//		destroy_t* destroy=(destroy_t*)dlsym(handle,"destroy");
		if (!create)
		{
			std::cout << "Error: %s" << dlerror() << std::endl;
		}

/*		if (!destroy)
		{
			std::cout << "Error: %s" << dlerror();
		}*/

		mode * temp = create();
		temp -> init();
		usrModes.push_back(temp);
		curMode = temp;
		//destroy(tst);
		//return 0;

	}
}

int main(int argc, char** argv)
{
	std::cout << "Starting Game\n";
	std::cout << "Seeding Generator\n";
	std::chrono::high_resolution_clock::time_point s = 
		std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::duration d = 
		std::chrono::high_resolution_clock::now()-s;
	unsigned s2 = d.count();
	generator.seed(s2);
	std::cout << "initiating window\n";
	initiateWindow(argc, argv); 				/* Set up Window 					*/
	std::cout << "Initiating Modes\n";
	initModes();

	initiateGL();								/* Initiate GL   					*/
	glutReshapeFunc(WindowResizeHandler);		/* Reshapes window					*/
	glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);		/* Set Key Repeat on 				*/
	glutMouseFunc(mouse);						/* Set a Mouse funtion				*/
	glutPassiveMotionFunc(passiveMouse);		/* Forwards input to the mode		*/
	glutKeyboardFunc(keyboard);					/* Set a keyboard Funcitons			*/
	glutKeyboardUpFunc(keyReleased);			
	glutSpecialFunc(specialKeys); 
	glutSpecialUpFunc(specialKeyReleased);

	glutDisplayFunc(gameView);					/* Set loop for The game rendering	*/
	glutIdleFunc(gameLoop);						/* Set loop for the game processing	*/

	
	
	glutMainLoop();								/* Start the main loop				*/
}
