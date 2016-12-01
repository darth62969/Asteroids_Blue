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
ship enterprise = createShip();

//Log Writers

ofstream asteroidLogger;
ofstream shipLogger;
ofstream collisionLogger;
ofstream bulletLogger;
ofstream transformationLogger;

char* ASTEROID_LOG_PATH = "asteroid_log.txt";
char* SHIP_LOG_PATH = "ship_log.txt";
char* COLLISION_LOG_PATH = "collision_log.txt";
char* BULLET_LOG_PATH = "bullet_log.txt";
char* TRANSFORMATION_LOG_PATH = "transformation_log.txt";

//Runtime Variables go here
vector<asteroid> asteroidBelt;

vector<bullet> bullets;

float deltaRot = 1.0;

bool rightKeyPressed = false;
bool rightReached10 = false;

bool leftKeyPressed = false;
bool leftReached10 = false;

int timeKeyPressed = 0;
//float shipRotation = 0.0;

int filled = 0;
int tess = 0;

void initiateOctogon(void);

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

void gameView()
{
	//output game to window
		initiateOctogon();  // Clear display window
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

	switch(tess)
	{
		case 1:
		for (int i = 0; i < (asteroidBelt.size()); i++)
    		{
			vector<triangle> a = asteroidBelt.at(i).getTess();
			point b = asteroidBelt.at(i).getCenter();
			for (int j = 0; j < (a.size()); j++)
        		{
				glBegin (GL_LINES);
						glVertex2d(a.at(j).a.x + b.x, a.at(j).a.y + b.y);
						glVertex2d(a.at(j).b.x + b.x, a.at(j).b.y + b.y);
						glVertex2d(a.at(j).c.x + b.x, a.at(j).c.y + b.y);
						glVertex2d(a.at(j).a.x + b.x, a.at(j).a.y + b.y);
//					glVertex2d(a.at(j).a.x + b.x, a.at(j).a.y + b.y);
//					glVertex2d(a.at(j).b.x + b.x, a.at(j).b.y + b.y);
//					glVertex2d(a.at(j).b.x + b.x, a.at(j).b.y + b.y);
//					glVertex2d(a.at(j).c.x + b.x, a.at(j).c.y + b.y);
//					glVertex2d(a.at(j).c.x + b.x, a.at(j).c.y + b.y);
//					glVertex2d(a.at(j).b.x + b.x, a.at(j).b.y + b.y);
				glEnd();
			}
		}
	}
	
	drawShip(enterprise);		

	glColor3f(1.0, 1.0, 0.0);
	for(int i = 0; i < bullets.size(); i++){
			drawBullet(bullets[i]);
		
	}
#ifdef DEBUG
	debugDisplay();
#endif

	glutSwapBuffers();


}


void gameLoop()
{
	shipLogger.open(SHIP_LOG_PATH, ofstream::out|ofstream::app);
	if (rightKeyPressed) 
	{
		if (deltaRot < 10.0 && !rightReached10)
		{
			deltaRot *= 1.1;
			if (deltaRot >= 10)
			{
				rightReached10 = true;
				deltaRot = 10;
			}
			
		}

		enterprise.rotation = (int)(enterprise.rotation-deltaRot)%360;
		
		timeKeyPressed++;

		shipLogger << endl << "Ship Rotation : " << enterprise.rotation << endl; 
		shipLogger << "Delta Rot : " << deltaRot << endl;
		shipLogger << "Time Right Arrow Pressed = " << timeKeyPressed;

		
	}
	if (leftKeyPressed)
	{
		if (deltaRot < 10.0 && !leftReached10)
		{
			deltaRot *= 1.1;
			if (deltaRot >= 10)
			{
				leftReached10 = true;
				deltaRot = 10;
			}
			
		}

		enterprise.rotation = (int)(enterprise.rotation+deltaRot)%360;

		timeKeyPressed++;

		shipLogger << endl << "Ship Rotation : " << enterprise.rotation << endl; 
		shipLogger << "Delta Rot : " << deltaRot << endl;
		shipLogger << "Time Right Arrow Pressed = " << timeKeyPressed << endl;
	}
	

	
	for(int i=0; i <bullets.size();i++)
	{
		bullets.at(i).location.x += 2.0* cos(bullets.at(i).theta);
		bullets.at(i).location.y += 2.0*sin(bullets.at(i).theta);
	}
	for(int i=0; i <asteroidBelt.size();i++)
	{
		asteroidBelt.at(i).incrementLocation();
	}
	glutPostRedisplay();
	shipLogger.close();
}

void initiateGameDisplay()
{
	//build window dependencies
}


void initiateAsteroids()
{
	asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
	asteroidLogger << "Generating " << NUMBER_OF_ASTEROIDS << " asteroids\n\n";
	asteroidLogger.close();
	//Generate Asteroids
	int i= 0;
	while (i<NUMBER_OF_ASTEROIDS)
	{	
		asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
		asteroidLogger << "Asteroid #" << i << endl;
		asteroidLogger.close();
		asteroid a = asteroid();
		asteroidBelt.push_back(a);
		i++;
	}
	asteroidLogger.open(ASTEROID_LOG_PATH, ofstream::out|ofstream::app);
	asteroidLogger << "\nGenerated " << asteroidBelt.size() << " asteroids\n";
	asteroidLogger.close();
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

	if(key == 't' || key == 'T'){
		filled = 0;
		if(tess == 0)
			tess = 1;
		else
			tess = 0;
		glutIdleFunc(gameLoop);
	}

	if(key == 'f' || key == 'F'){
		if(filled == 0)
			filled = 1;
		else
			filled = 0;
		tess = 0;
		glutIdleFunc(gameLoop);
	}

	if(key == 'a' || key == 'A'){
		enterprise.rotation += 2.5;
		glutIdleFunc(gameLoop);
	}		

	if(key == 'd' || key == 'D'){
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
