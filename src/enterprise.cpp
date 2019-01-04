#define _USE_MATH_DEFINES

#include "enterprise.h"
#include "globals.h"

enterprise::enterprise()
{
	location = {0, 0, 0, 1, 0};
	layer lyr;
	//Generate the Enterprise
	lyr.pnts.push_back(point{ 5,  0, 0, 1});
	lyr.pnts.push_back(point{ 2,  1, 0, 1});
	lyr.pnts.push_back(point{ 2,  3, 0, 1});
	lyr.pnts.push_back(point{-5,  3, 0, 1});
	lyr.pnts.push_back(point{-5,  1, 0, 1});
	lyr.pnts.push_back(point{ 0,  1, 0, 1});
	lyr.pnts.push_back(point{ 0, -1, 0, 1});
	lyr.pnts.push_back(point{-5, -1, 0, 1});
	lyr.pnts.push_back(point{-5, -3, 0, 1});
	lyr.pnts.push_back(point{ 2, -3, 0, 1});
	lyr.pnts.push_back(point{ 2, -1, 0, 1});

	//Generate Trangles
	tessellate(&lyr);

	lyr.clr = {0.95, 0.34, 0.67};

	lyrs.push_back(lyr);

	//set attack points (i.e. where it shoots from)
	atkpnts.push_back(point{ 5,  0, 0, 1});

	health = 100;
	cycle = 0;
	EndGameAnimation = 5;

	//generate bullet
	std::vector<point> temp;

	temp.push_back(point { 3, -1, 0, 1});
	temp.push_back(point { 3,  1, 0, 1});
	temp.push_back(point { 1,  2, 0, 1});
	temp.push_back(point {-3,  2, 0, 1});
	temp.push_back(point {-3, -2, 0, 1});
	temp.push_back(point { 1, -2, 0, 1});

	blt = bullet(temp, 5, 2);


}

void enterprise::fire(mode * md)
{
	//std::cout << "getting attack point" << std::endl;
	std::vector<point> temp=getAtkPnts();
	for (int i = 0; i < temp.size(); i++)
	{
	//	std::cout << "firing bullet" << std::endl;
		//temp[i].x+=sin(location.angle);
		//temp[i].y+=cos(location.angle);
		
		bullet * shot = blt.fireBullet(temp[i].x, temp[i].y, location.angle);
	//	shot.location= temp[i];
	//	shot.theta = location.angle;
		md->addToOnScreen(shot);
		bulletsFired++;
	}
}
void enterprise::resetShip()
{
	location = {0, 0, 0, 1, 0};
	EndGameAnimation=5;
}

void enterprise::render()
{
	// Create a temporary vector with the ship's Triangles
	//std::cout << "Trying to Render the Enterprise" << std::endl;
	std::vector<triangle> temp = lyrs[0].tris;

	//scale the points
	for (int i = 0; i < temp.size(); i++)
	{
		point b[3];
		b[0]=temp[i].a;
		b[1]=temp[i].b;
		b[2]=temp[i].c;
		for(int j=0; j<3; j++)
		{ 
			switch(gamestate)
			{
				//if end game we want to play the end animation
				case 2: 
					scalePoint(b[j], EndGameAnimation);
					EndGameAnimation*=0.999;
					break;
				// all other cases leave the ship alone
				default:
					scalePoint(b[j], 5);
					break;
			}

			point tempp;

			tempp.x= b[j].x*cos(location.angle)-b[j].y*sin(location.angle);
			tempp.y= b[j].x*sin(location.angle)+b[j].y*cos(location.angle);
			b[j] = tempp;
		}

		temp[i].a=b[0];
		temp[i].b=b[1];
		temp[i].c=b[2];
	}
	glColor3d(lyrs[0].clr.red, lyrs[0].clr.green, lyrs[0].clr.blue);	
	for(int i = 0; i<temp.size(); i++)
	{    
		switch (filled)
		{
			case 0:
			case 1:
				glBegin(GL_TRIANGLES);
					glVertex2d((temp[i].a.x)+(location.x), (temp[i].a.y)+(location.y));
					glVertex2d((temp[i].b.x)+(location.x), (temp[i].b.y)+(location.y));
					glVertex2d((temp[i].c.x)+(location.x), (temp[i].c.y)+(location.y));
				glEnd();
				break;
			case 2:
				glBegin (GL_LINES);
					glVertex2d((temp[i].a.x)+(location.x), (temp[i].a.y)+(location.y));
					glVertex2d((temp[i].b.x)+(location.x), (temp[i].b.y)+(location.y));
					glVertex2d((temp[i].b.x)+(location.x), (temp[i].b.y)+(location.y));
					glVertex2d((temp[i].c.x)+(location.x), (temp[i].c.y)+(location.y));
					glVertex2d((temp[i].c.x)+(location.x), (temp[i].c.y)+(location.y));
					glVertex2d((temp[i].a.x)+(location.x), (temp[i].a.y)+(location.y));
				glEnd();
		}
	}

	switch(gamestate)
	{
		case 3:
			WinGameAnimation = (WinGameAnimation+.01)*1.01;
			shipRender.x += WinGameAnimation*sin(location.angle*(180/M_PI)+(M_PI));
			shipRender.y += WinGameAnimation*cos(location.angle*(180/M_PI)+(M_PI));
	}

	///Now we want to draw the ship. 
	/*glBegin(GL_TRIANGLES);
		for(int i = 0; i<temp.size(); i++)
		{    
			
			glVertex2d(temp.at(i).a.x + location.x, temp.at(i).a.y + location.y);
			glVertex2d(temp.at(i).b.x + location.x, temp.at(i).b.y + location.y);
			glVertex2d(temp.at(i).c.x + location.x, temp.at(i).c.y + location.y);

		}
	glEnd();*/
}