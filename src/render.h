#pragma once

#ifndef __RENDER_H__
#define __RENDER_H__



#include <GL/glut.h>
#include <stdlib.h>
#include <vector>
#include "structs.h"
#include "windowProperties.h"




class render
{
	public:
		void drawString(GLuint x, GLuint y, const char* string); 
		void initOctogon();
		int insideOctogon(point p);
		int insidePlayArea(point P);
		void drawPlayArea();
		void drawOctogon();
		void setFont(void * font);

		void *currentfont;				// Bit map font pointer.
		std::vector<point> octogon;
		std::vector<point> playArea;
};



#endif