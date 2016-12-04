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
vector<point> octogon; bool noOctogon = 1;
vector<point> clipPts;

//Runtime Variables go here
vector<asteroid> asteroidBelt;

vector<bullet> bullets;

bool newRotate = false;

//float shipRotation = 0.0;

bool filled = false;

void drawOctogon(void);

void Pipeline(void){
	//apply transformations
		//ship
		if(newRotate){
			rotateShip(enterprise);
			newRotate = false;
		}
		//asteroids
		//bullets		
		//collision detection

		//clipping
		
		//tesselation
	//
}

void debugDisplay(void)
{
	drawOctogon();  // Clear display window
    	glColor3f ( 0.1, 0.5, 0.0 );      // Set line segment color to green
	glPointSize(4.0);

	Pipeline();
   
	//clip();
 
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

	
	drawShip(enterprise);		


	glColor3f(1.0, 1.0, 0.0);
	for(int i = 0; i < bullets.size(); i++){
			drawBullet(bullets[i]);
		
	}

	glutSwapBuffers();
}

void gameView()// Why is this a method? - Ted
{
	//output game to window
	debugDisplay();

}


void gameLoop()
{
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

	point p = {WORLD_COORDINATE_MIN_X ,WORLD_COORDINATE_MAX_Y / 2,0,1};
	point c = {WORLD_COORDINATE_MAX_X / 4, WORLD_COORDINATE_MAX_Y / 2, 0,1};	
	rotatePoint(p,45.0/2.0);
	rotatePoint(c,45.0/2.0);

	octogon.push_back(p);
	clipPts.push_back(c);
	
	for (int i = 0; i < 7; i++){
		rotatePoint(p,-45);
		rotatePoint(c,-45);

		octogon.push_back(p);
		clipPts.push_back(c);
	}	

	noOctogon = 0;
}

void drawOctogon(void){
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POLYGON);
		for(int i = 0; i < octogon.size(); i ++){
			glVertex2f( octogon[i].x , octogon[i].y);
		}
	glEnd();
}
void debugMe(int x, int y){
	point p = {x,y,0,1};

	int result = insideOctogon(p);
	
	if (result) printf("        ");
}
void keyboard(unsigned char key, int x, int y){
	
	//if(key == 's' || key == 'S')
		// start game

	//if(key == 'p' || key == 'P')
		//pause movement

	if(key == 'q' || key == 'Q')
		exit(0);

	if(key == 't' || key == 'T'){
		filled = false;
		glutIdleFunc(gameLoop);
	}

	if(key == 'f' || key == 'F'){
		filled = true;	
		glutIdleFunc(gameLoop);
	}

	if(key == 'w' || key == 'W'){
		enterprise.rotation += 2.5;
		newRotate = true;
		glutIdleFunc(gameLoop);
	}		

	if(key == 's' || key == 'S'){
		enterprise.rotation -= 2.5;
		newRotate = true;
		glutIdleFunc(gameLoop);
	}

	if(key == ' ')
	{
		bullet shot = createBullet();
		bullets.push_back(shot);
		fireBullet(shot);
		glutIdleFunc(gameLoop);
	}

		

}

void specialKeys(int key, int x, int y){
	switch(key){
		case GLUT_KEY_RIGHT:
			enterprise.rotation -= 2.5;
			newRotate = true;
			glutIdleFunc(gameLoop);
			break;

		case GLUT_KEY_LEFT:
			enterprise.rotation += 2.5;
			newRotate = true;
			glutIdleFunc(gameLoop);
			break;	

		case SPACEBAR:
			//fire missiles
			bullet shot = createBullet();
			bullets.push_back(shot);
			fireBullet(shot);
			glutIdleFunc(gameLoop);
			break;		

		//default: break;
	}
}

void mouse(int button, int state, int x, int y){
        if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
                       
        }
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
                       debugMe(x,y);
        }
}

int main(int argc, char** argv)
{
	initiateWindow(argc, argv); /* Set up Window */
	initiateGL();
	if (noOctogon) {initiateOctogon();}
	drawOctogon();
	initiateShip();
	initiateAsteroids();
	initiateGameDisplay();
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys); 
	glutDisplayFunc(gameView);
	glutIdleFunc(gameLoop);
	glutMainLoop();
}
