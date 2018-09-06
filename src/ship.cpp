/* 
 * Ship Operations for Asteroids: RETURN OF METEOR
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

double EndGameAnimation=7;
double WinGameAnimation=0;
point shipRender;

#ifndef SHIPTEST
ship createShip(void)
{
	/* 
	 * Create a ship, enterprise, in the middle of the window.
	 */

	// Create Ship
	ship temp;

	// Set the values to the ship's grid, these don't get changed.
	temp.body.a.x = 2;
	temp.body.a.y = 0.0;
	temp.body.b.x = -2.0;
	temp.body.b.y = -1.0;
	temp.body.c.x = -2;
	temp.body.c.y = 1.0;

	shipRender = {WORLD_COORDINATE_MAX_X/2, WORLD_COORDINATE_MAX_Y/2, 0, 1};
	
	// Rotation will be changed if the user presses the left or right arrow keys.
	temp.rotation = 0.0;

	return temp;
}

// This is the function that draws the ship. 
void drawShip(ship a)
{
	/*
	 * Here we create a temporary point that we use to preform operations on and to draw the ship.
	 * We scale the this point and then rotate it so that it is the proper size for it to show properly
	 * Then we translate these points directly by the half the Max size of the World Coordinates  
	 */

	//Create Point to hold temperary points to draw the ship
	point b[3];

	//Copy the points in the ship (a) to b
	b[0] = {a.body.a.x, a.body.a.y, a.body.a.z, a.body.a.w, a.body.a.angle};
	b[1] = {a.body.b.x, a.body.b.y, a.body.b.z, a.body.b.w, a.body.b.angle};
	b[2] = {a.body.c.x, a.body.c.y, a.body.c.z, a.body.c.w, a.body.c.angle};

	//Now we want to scale each point then rotate it into position
	for (int i = 0; i < 3; i++)
	{
		switch (gamestate)
		{
			case 2:
				scalePoint(b[i], EndGameAnimation);
				EndGameAnimation*=0.99;
				break;
			default:
				scalePoint(b[i], 7);
		}
		//scalePoint(b[i], 7);
		rotatePoint(b[i], a.rotation);
	}

	//We want to save the location of the nose of the ship for use with the positioning of bullets later on
	enterprise.aLocation = {b[0].x+WORLD_COORDINATE_MAX_X/2, b[0].y+WORLD_COORDINATE_MAX_Y/2} ;

	switch(gamestate)
	{
		case 3:
			WinGameAnimation = (WinGameAnimation+.01)*1.01;
			shipRender.x += WinGameAnimation*sin(a.rotation*(180/M_PI)+(M_PI));
			shipRender.y += WinGameAnimation*cos(a.rotation*(180/M_PI)+(M_PI));
	}

	///Now we want to draw the ship.
	glBegin(GL_TRIANGLES);
		for(int i = 0; i<3; i++)
		{    
			glVertex2d(b[i].x + shipRender.x, b[i].y + shipRender.y);
		}
	glEnd();
}

void resetShip()
{
	EndGameAnimation=7;
	shipRender = {WORLD_COORDINATE_MAX_X/2, WORLD_COORDINATE_MAX_Y/2, 0, 1};
	WinGameAnimation=0;
}
#endif

#ifdef SHIPTEST

int type;


ship::ship(int tp, std::vector<point> pnts)
{
	type=tp;
	switch(type)
	{
		case 0:  //Enterprise class ship, this is the player ship
			//set Location of the ship
			location = {WORLD_COORDINATE_MAX_X/2, WORLD_COORDINATE_MAX_Y/2, 0, 1, 0};
			
			//Generate the Enterprise
			shppnts.push_back(point{0, 5, 0, 1});
			shppnts.push_back(point{-1, 2, 0, 1});
			shppnts.push_back(point{-3, 2, 0, 1});
			shppnts.push_back(point{-3, -5, 0, 1});
			shppnts.push_back(point{-1, -5, 0, 1});
			shppnts.push_back(point{-1, -1, 0, 1});
			shppnts.push_back(point{1, -1, 0, 1});
			shppnts.push_back(point{1, -5, 0, 1});
			shppnts.push_back(point{3, -5, 0, 1});
			shppnts.push_back(point{3, 2, 0, 1});
			shppnts.push_back(point{1, 2, 0, 1});
			
			//Generate Trangles
			cout << "teslating ship" << endl;
			tessilateShip();

			//set attack points (i.e. where it shoots from)
			atkpnts.push_back(point{0, 5, 0, 1});

			actionSet = 0;
			health = 100;
			cycle = 0;

			break;
		case 5:
			shppnts=pnts;
			break;
	}

	
}
ship::ship(int tp)
{
	//set the type.
	type=tp;

	//based on the type generate the ship.
	switch(type)
	{
		case 0:  //Enterprise class ship, this is the player ship
			//set Location of the ship
			location = {WORLD_COORDINATE_MAX_X/2, WORLD_COORDINATE_MAX_Y/2, 0, 1, 0};
			
			//Generate the Enterprise
			shppnts.push_back(point{ 5,  0, 0, 1});
			shppnts.push_back(point{ 2,  1, 0, 1});
			shppnts.push_back(point{ 2,  3, 0, 1});
			shppnts.push_back(point{-5,  3, 0, 1});
			shppnts.push_back(point{-5,  1, 0, 1});
			shppnts.push_back(point{ 0,  1, 0, 1});
			shppnts.push_back(point{ 0, -1, 0, 1});
			shppnts.push_back(point{-5, -1, 0, 1});
			shppnts.push_back(point{-5, -3, 0, 1});
			shppnts.push_back(point{ 2, -3, 0, 1});
			shppnts.push_back(point{ 2, -1, 0, 1});

			//Generate Trangles
			cout << "teslating ship" << endl;
			tessilateShip();

			//set attack points (i.e. where it shoots from)
			atkpnts.push_back(point{ 5,  0, 0, 1});

			actionSet = 0;
			health = 100;
			cycle = 0;
			EndGameAnimation = 5;

			break;
		case 1:
			shppnts.push_back(point{ 3,  0, 0, 1});
			shppnts.push_back(point{ 1,  1, 0, 1});
			shppnts.push_back(point{ 0,  1, 0, 1});
			shppnts.push_back(point{-1,  2, 0, 1});
			shppnts.push_back(point{-1,  3, 0, 1});
			shppnts.push_back(point{-3,  3, 0, 1});
			shppnts.push_back(point{-3,  1, 0, 1});
			shppnts.push_back(point{-2,  1, 0, 1});
			shppnts.push_back(point{-2, -1, 0, 1});
			shppnts.push_back(point{-3, -1, 0, 1});
			shppnts.push_back(point{-3, -3, 0, 1});
			shppnts.push_back(point{-1, -3, 0, 1});
			shppnts.push_back(point{-1, -2, 0, 1});
			shppnts.push_back(point{ 0, -1, 0, 1});
			shppnts.push_back(point{ 1, -1, 0, 1});
			
			tessilateShip();

			atkpnts.push_back(point{ 3,  0, 0, 1});

			actionSet = 1;
			health = 20;
			cycle = 25;

			break;
	}
}
std::vector<point> ship::getPoints()
{
	vector<point> temp = shppnts;
	for (int i =0; i < temp.size(); i++)
	{
			scalePoint(temp[i], 5);

			point tempp;

			tempp.x= temp[i].x*cos(location.angle)-temp[i].y*sin(location.angle);
			tempp.y= temp[i].x*sin(location.angle)+temp[i].y*cos(location.angle);
			
			temp[i] = tempp;
			temp[i].x += location.x;
			temp[i].y += location.y;
	}

	return temp;	
}

std::vector<triangle> ship::getTriangles()
{
	vector<triangle> temp = shptris;
	for (int i =0; i < temp.size(); i++)
	{
		point a[3] = {temp[i].a, temp[i].b, temp[i].c};
		for (int j = 0; j < 3; j++ )
		{
			scalePoint(a[j], 5);

			point tempp;

			tempp.x= a[j].x*cos(location.angle)-a[j].y*sin(location.angle);
			tempp.y= a[j].x*sin(location.angle)+a[j].y*cos(location.angle);
			
			a[j] = tempp;
			a[j].x += location.x;
			a[j].y += location.y;
		}
		temp[i].a = a[0];
		temp[i].b = a[1];
		temp[i].c = a[2];
	}
	return temp;
}
std::vector<point> ship::getAtkPnts()
{
	vector<point> temp = atkpnts;
	for (int i =0; i < temp.size(); i++)
	{
			scalePoint(temp[i], 5);

			point tempp;

			tempp.x= temp[i].x*cos(location.angle)-temp[i].y*sin(location.angle);
			tempp.y= temp[i].x*sin(location.angle)+temp[i].y*cos(location.angle);
			
			temp[i] = tempp;
			temp[i].x += location.x;
			temp[i].y += location.y;
	}

	return temp;	
}

point ship::getLocation()
{
	return location;
}
int  ship::getHealth()
{
	return health;
}

void ship::setRotation(double rot)
{
	location.angle=rot;
}
void ship::setLocation(double x, double y)
{
	location.x = x;
	location.y = y;
}

void ship::fire()
{
	vector<point> temp=getAtkPnts();
	for (int i = 0; i < temp.size(); i++)
	{
		//cout << temp[i].x << " " << temp[i].y << endl;
		temp[i].x+=sin(location.angle);
		temp[i].y+=cos(location.angle);
		bullet shot;
		shot.location= temp[i];
		shot.theta = location.angle;
		bullets.push_back(shot);
	}
}

void ship::iterateAction()
{
	switch(actionSet)
	{
		case 1:
			cycle++;
			switch(cycle/50)
			{
				case 0:
					location.x++;
					break;
				case 1:
					location.x--;
					break;
			}
			switch(cycle%50)
			{
				case 0:
					location.y-=10;
					break;

			}
			if (cycle >= 100)
			{
				cycle = 0;
			}
			switch(rand()%70)
			{
				case 0: 
					fire();
					break;
			}

	}		
}

int ship::damageHealth(int dmg)
{
	health-=dmg;
	return health;
}

void ship::resetShip()
{
	switch (type)
	{
		case 0:
			location = {WORLD_COORDINATE_MAX_X/2, WORLD_COORDINATE_MAX_Y/2, 0, 1, 0};
			EndGameAnimation=5;
			break;
		case 1:
			/*
			 * ToDo: 
			 *  - Create reset code for type 1 ships.
			 */
			break;
	}
}

void ship::renderShip()
{
	// Create a temporary vector with the ship's Triangles
	vector<triangle> temp = shptris;

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
void ship::tessilateShip()
{
	vector<point> temp = shppnts;
	point A = temp[0];
	point B = temp[1];
	point C = temp[2];
	int Ai = 0;
	int Bi = 1;
	int Ci = 2;
	triangle tri;
	double z;

	int i = 0;
	// While there are more than three vertices left in points, run the following code.
	while(temp.size() >= 3)
	{
		//cout << intersect (temp[0], temp[1], A, B) << endl;

		bool insect = false;
		for (int i1  = 0; i1 < shppnts.size(); i1++)
		{
			switch (i1)
			{
				case 0:
					if(intersect(shppnts[i1], shppnts[shppnts.size()-1], A, B))
						insect=true;
					if(intersect(shppnts[i1], shppnts[shppnts.size()-1], B, C))
						insect = true;
					if(intersect(shppnts[i1], shppnts[shppnts.size()-1], C, A))
						insect = true;
					break;
				default:
					if (intersect(shppnts[i1], shppnts[i1-1], A, B))
						insect = true;
					if (intersect(shppnts[i1], shppnts[i1-1], B, C))
						insect = true;
					if (intersect(shppnts[i1], shppnts[i1-1], C, A))
						insect = true;
					break;
			}
			if(insect)
			{	
				break;
			}
		}

		for (int i1  = 0; i1 < shptris.size(); i1++)
		{
			point temp1[3] = {shptris[i1].a, shptris[i1].b, shptris[i1].c};
			for (int j1=0; j1<3; j1++)
			{
				switch (j1)
				{
					case 0:
						if(intersect(temp1[j1], temp1[2], A, B))
							insect = true;
						if(intersect(temp1[j1], temp1[2], B, C))
							insect = true;
						if(intersect(temp1[j1], temp1[2], C, A))
							insect = true;
						break;
					default:
						if (intersect(temp1[j1], temp1[j1-1], A, B))
							insect = true;
						if (intersect(temp1[j1], temp1[j1-1], B, C))
							insect = true;
						if (intersect(temp1[j1], temp1[j1-1], C, A))
							insect = true;
						break;
				}
			}
			if(insect)
				break;
		}
		if (insect)
		{
			Ci++;
			if(Ci>=temp.size())
			{
				Bi++;
				if(Bi>=temp.size()-1)
				{
					temp.erase(temp.begin());
					Bi=Ai+1;
					Ci=Bi+1;
					A=temp[Ai];
					B=temp[Bi];
					C=temp[Ci];
					
					
				}
				else
				{
					Ci=Bi+1;
					B=temp[Bi];
					C=temp[Ci];
				}
			}
			else
			{
				C=temp[Ci];
			}
		}

		if(!insect)
		{
			point l1;
			l1.x = A.x - B.x;
			l1.y = A.y - B.y;

			point l2;
			l2.x = C.x - B.x;
			l2.y = C.y - B.y;

			z = l1.x*l2.y - l2.x*l1.y;

			//cout << " Index " << Ai << " A  ( "  << A.x << " , " << A.y << " )" << endl;
			//cout << " Index " << Bi << " B  ( "  << B.x << " , " << B.y << " )" << endl;
			//cout << " Index " << Ci << " C  ( "  << C.x << " , " << C.y << " )" << endl;
			//cout << " z = " << z << endl;

			bool within = false;
			for (int i =0; i < temp.size(); i ++)
			{
				if(PointInTriangle(temp[i], A, B, C) && Ai!=i && Bi!=i && Ci!=i)
					within = true;
			}

			if (z<0 && !within)
			{
				cout << " Index " << Ai << " A  ( "  << A.x << " , " << A.y << " )" << endl;
				cout << " Index " << Bi << " B  ( "  << B.x << " , " << B.y << " )" << endl;
				cout << " Index " << Ci << " C  ( "  << C.x << " , " << C.y << " )" << endl;
				tri.a = A;
				tri.b = B;
				tri.c = C;
				shptris.push_back(tri);

				Bi=Ci;
				B=temp[Bi];
				
				Ci++;
				C=temp[Ci];

			}
			else
			{
				Ci++;
				if(Ci>=temp.size())
				{
					Bi++;
					if(Bi>=temp.size()-1)
					{
						temp.erase(temp.begin());
						Bi=Ai+1;
						Ci=Bi+1;
						A=temp[Ai];
						B=temp[Bi];
						C=temp[Ci];

						cout << " Index " << Ai << " A  ( "  << A.x << " , " << A.y << " )" << endl;
				cout << " Index " << Bi << " B  ( "  << B.x << " , " << B.y << " )" << endl;
				cout << " Index " << Ci << " C  ( "  << C.x << " , " << C.y << " )" << endl;
					}
					else
					{
						Ci=Bi+1;
						B=temp[Bi];
						C=temp[Ci];
					}
				}
				else
				{
					C=temp[Ci];
				}
			}

		}
	}

	for (int i = 0; i < shptris.size(); i++)
	{
		cout << "Triangle " << i << endl;
		cout << "A ( " << shptris[i].a.x << " , " << shptris[i].a.y << " )" << endl;
		cout << "B ( " << shptris[i].b.x << " , " << shptris[i].b.y << " )" << endl;
		cout << "C ( " << shptris[i].c.x << " , " << shptris[i].c.y << " )" << endl;
		cout << endl;
	}
}
#endif
