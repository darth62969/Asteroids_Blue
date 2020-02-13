#define _USE_MATH_DEFINES

#include "render.h"

#include <cmath>

void *currentfont;
std::vector<point> octogon;

void render::drawString(GLuint x, GLuint y, const char* string)
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

void render::initOctogon()
{
	
	point p;
	p.x = WORLD_COORDINATE_MIN_X*cos(M_PI_4/2)-0*sin(M_PI_4/2);
	p.y = WORLD_COORDINATE_MIN_X*sin(M_PI_4/2)+0*cos(M_PI_4/2);

	octogon.push_back(p);

	for (int i = 0; i < 7; i++)
	{
		point t_p;
		t_p.x = p.x*cos(-M_PI_4)-p.y*sin(-M_PI_4);
		t_p.y = p.x*sin(-M_PI_4)+p.y*cos(-M_PI_4);
		p=t_p;

		octogon.push_back(p);
	}
}

int render::insideOctogon(point p)
{
	double slope, line;

	int in = 1;
	if (p.x < octogon[0].x) in *= 0;// x less then 22
	if (p.x > octogon[5].x) in *= 0;// x greater then 577
	if (p.y > octogon[2].y) in *= 0;// y greater then 577
	if (p.y < octogon[7].y) in *= 0;// y less then 22

	//calculating slope bottom left
	slope = (octogon[7].y - octogon[0].y) / (octogon[7].x - octogon[0].x);
	line = slope*(p.x - octogon[0].x)+ octogon[0].y;
	if (p.y < line) in *= 0;
	
	slope = (octogon[6].y - octogon[5].y) / (octogon[6].x - octogon[5].x);
	line = slope*(p.x - octogon[6].x)+ octogon[6].y;
	if (p.y < line) in *= 0;
	
	slope = (octogon[4].y - octogon[3].y) / (octogon[4].x - octogon[3].x);
	line = slope*(p.x - octogon[3].x)+ octogon[3].y;
	if (p.y > line) in *= 0;

	slope = (octogon[2].y - octogon[1].y) / (octogon[2].x - octogon[1].x);
	line = slope*(p.x - octogon[2].x)+ octogon[2].y;
	if (p.y > line) in *= 0;

	return in;
}

int render::insidePlayArea(point P)
{
	int rtn;
	for (int i = 0; i < playArea.size(); i++)
	{
		point a = playArea[i];
		point b = playArea[(i+1)%playArea.size()];
		/*switch (a.x-b.x)
		{
			case 0:
				break;
		}*/
	}
}

void render::drawOctogon()
{
	glColor3f(0.1,0.5,0.0);
	
	glBegin(GL_LINE_LOOP);
		for(int i = 0; i < octogon.size(); i ++)
		{
			glVertex2f(octogon[i].x, octogon[i].y);
		}
	glEnd();
}

void render::setFont(void * font)
{
	currentfont=font;
}