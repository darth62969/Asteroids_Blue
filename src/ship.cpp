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

	// Begin at vertex 0.

/*	while (temp.size()>3)
	{
		point l1;
		l1.x = A.x - B.x;
		l1.y = A.y - B.y;

		point l2;
		l2.x = C.x - B.x;
		l2.y = C.y - c.x;

		double z = l1.x*l2.y = l2.x*l2.y
	}
*/
	int i = 0;
	// While there are more than three vertices left in points, run the following code.
	while(temp.size() > 3)
	{
		//cout << intersect (temp[0], temp[1], A, B) << endl;

		bool insect = false;
		for (int i1  = 0; i1 < temp.size(); i1++)
		{
			switch (i1)
			{
				case 0:
					if(intersect(temp[i1], temp[temp.size()-1], A, B))
						insect=true;
					break;
				default:
					if (intersect(temp[i1], temp[i1-1], A, B))
					{
						cout	<< " A->B intersects (" << temp[i1].x << " , " 
								<< temp[i1].y << " ),( " << temp[i1-1].x << " , "
								<< temp[i1-1].y << " )" << endl;
						insect = true;
					}
					break;
			}
			if(insect)
			{	
				break;
			}
		}
		for (int i1  = 0; i1 < temp.size(); i1++)
		{
			switch (i1)
			{
				case 0:
					if(intersect(temp[i1], temp[temp.size()-1], B, C))
						insect = true;
					break;
				default:
					if (intersect(temp[i1], temp[i1-1], B, C))
					{
						cout	<< " B->C intersects (" << temp[i1].x << " , " 
							<< temp[i1].y << " ),( " << temp[i1-1].x << " , "
							<< temp[i1-1].y << " )" << endl;
						insect = true;
					}
					break;
			}
			if(insect)
				break;
		}
		for (int i1  = 0; i1 < temp.size(); i1++)
		{
			switch (i1)
			{
				case 0:
					if(intersect(temp[i1], temp[temp.size()-1], C, A))
						insect = true;
					break;
				default:
					if (intersect(temp[i1], temp[i1-1], C, A))
					{
						cout	<< "C->A intersects (" << temp[i1].x << " , " 
							<< temp[i1].y << " ),( " << temp[i1-1].x << " , "
							<< temp[i1-1].y << " )" << endl;
						insect = true;
					}
					break;
			}
			if(insect)
				break;
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
		/*
		// Set the middle vertex as the vertex immediately following i. Set the third vertex as the vertex immediately following j.
		int j=i+1;
		int k=j+1;
		// If j is vertex 0, set j to 0 and k to 1. 
		if(j == temp.size())
		{
			j = 0;
			k = 1;
		}
		// If k is vertex 0, set k to 0.
		else if(k == temp.size())
			k = 0;	
	
		float l1_x = temp.at(i).x - temp.at(j).x;
		float l1_y = temp.at(i).y - temp.at(j).y;
		float l2_x = temp.at(k).x - temp.at(j).x;
		float l2_y = temp.at(k).y - temp.at(j).y;	
		// z is the z component of the cross product of l1 (i to j) and l2 (k to j).
		z = l1_x*l2_y - l2_x*l1_y;
		cout << " z = " << z << endl;
		// If CW winding occurs, set the starting vertex to j.
		if(z > 0.0)
			i = j;
		// If the middle point lies on a line segment connecting the first and third points, erase it.
		else if(z == 0.0)
			temp.erase(temp.begin() + j);
		// If CCW winding occurs, run the following code.
		else if(z < 0.0)
		{*/
			/*
			 * In the special circumstance that k is vertex 2, determine if all the remaining vertices 
			 * would cause concavity. Determine the z component of the cross product of l1 (k to each 
			 * remaining vertex) and l2 (i to each remaining vertex).
			 *//*
			float z2 = -1.0;
			if(k == 2)
			{	
				for(int m=3; m<temp.size(); m++)
				{	
					float l1_x = temp.at(k).x - temp.at(m).x;
					float l1_y = temp.at(k).y - temp.at(m).y;
					float l2_x = temp.at(i).x - temp.at(m).x;
					float l2_y = temp.at(i).y - temp.at(m).y;
					z2 = l1_x*l2_y - l2_x*l1_y;
					// If the angle is convex or the points lie on a line, break out of the loop.
					if(z2 <= 0.0)
						break;
				}
			}

			// Declare and initialize the boolean intersection as false.
			bool intersection = false;

			// Check if the newly created diagonal intersects with any formed line segment.
			for(int n=0; n<temp.size()-1; n++)
			{
				bool v = intersect(temp.at(i), temp.at(k), temp.at(n), temp.at(n+1));
				if(v)
					intersection = true;
			}

			// Check if the newly created diagonal intersects with the last line segment.
			bool v = intersect(temp.at(i), temp.at(k), temp.back(), temp.front());
			if(v)
				intersection = true;

			// If no intersection has occurred and no CW winding occurs in the special circumstance, run the following code.
			if(!intersection && z2 <= 0.0)
			{
				// Declare and initalize a triangle holding the three vertices, i, j, and j+1.
				triangle t;
				t.a = temp.at(i);
				t.b = temp.at(j);
				t.c = temp.at(k);
				shptris.push_back(t);

				// Erase the middle vertex.
				temp.erase(temp.begin() + j);

				// If i is not at 0, reset it to 0.
				if(i != 0)
					i = 0;
			}
			// If an intersection has occurred or CW winding occurs in the special circumstance, set the starting vertex to j.
			else
				i = j;
		}
	}
	// Create the final triangle with the remaining three vertices in points.	
	triangle t;
	t.a = temp.front();
	t.b = temp.at(1);
	t.c = temp.back();
	shptris.push_back(t);	*/

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
