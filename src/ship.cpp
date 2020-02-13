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

#include "ship.h"
#include "globals.h"

double EndGameAnimation=7;
double WinGameAnimation=0;
point shipRender;

int type;

ship::ship()
{

}


ship::ship(int tp, std::vector<point> pnts)
{
	type=tp;
	switch(type)
	{
		case 0:  //Enterprise class ship, this is the player ship
			//set Location of the ship
			location = {WORLD_COORDINATE_MAX_X/2, WORLD_COORDINATE_MAX_Y/2, 0, 1, 0};
			
			//Generate the Enterprise
			lyrs[0].pnts.push_back(point{0, 5, 0, 1});
			lyrs[0].pnts.push_back(point{-1, 2, 0, 1});
			lyrs[0].pnts.push_back(point{-3, 2, 0, 1});
			lyrs[0].pnts.push_back(point{-3, -5, 0, 1});
			lyrs[0].pnts.push_back(point{-1, -5, 0, 1});
			lyrs[0].pnts.push_back(point{-1, -1, 0, 1});
			lyrs[0].pnts.push_back(point{1, -1, 0, 1});
			lyrs[0].pnts.push_back(point{1, -5, 0, 1});
			lyrs[0].pnts.push_back(point{3, -5, 0, 1});
			lyrs[0].pnts.push_back(point{3, 2, 0, 1});
			lyrs[0].pnts.push_back(point{1, 2, 0, 1});
			
			//Generate Trangles
			std::cout << "teslating ship" << std::endl;
			tessilateShip();

			//set attack points (i.e. where it shoots from)
			atkpnts.push_back(point{0, 5, 0, 1});

			actionSet = 0;
			health = 100;
			cycle = 0;

			break;
		case 5:
			lyrs[0].pnts=pnts;
			break;
	}

	
}
ship::ship(int tp)
{
	//set the type.
	type=tp;
	std::vector<point> temp;
	layer lyr;
	//based on the type generate the ship.
	switch(type)
	{
		case 0:  //Enterprise class ship, this is the player ship
			//set Location of the ship
			location = {0, 0, 0, 1, 0};
			
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

			lyrs.push_back(lyr);

			//set attack points (i.e. where it shoots from)
			atkpnts.push_back(point{ 5,  0, 0, 1});

			
			temp.push_back(point { 3, -1, 0, 1});
			temp.push_back(point { 3,  1, 0, 1});
			temp.push_back(point { 1,  2, 0, 1});
			temp.push_back(point {-3,  2, 0, 1});
			temp.push_back(point {-3, -2, 0, 1});
			temp.push_back(point { 1, -2, 0, 1});

			blt = bullet(temp, 10, 2);

			actionSet = 0;
			health = 100;
			cycle = 0;
			EndGameAnimation = 5;

			break;
		case 1:
			lyr.pnts.push_back(point{ 3,  0, 0, 1});
			lyr.pnts.push_back(point{ 1,  1, 0, 1});
			lyr.pnts.push_back(point{ 0,  1, 0, 1});
			lyr.pnts.push_back(point{-1,  2, 0, 1});
			lyr.pnts.push_back(point{-1,  3, 0, 1});
			lyr.pnts.push_back(point{-3,  3, 0, 1});
			lyr.pnts.push_back(point{-3,  1, 0, 1});
			lyr.pnts.push_back(point{-2,  1, 0, 1});
			lyr.pnts.push_back(point{-2, -1, 0, 1});
			lyr.pnts.push_back(point{-3, -1, 0, 1});
			lyr.pnts.push_back(point{-3, -3, 0, 1});
			lyr.pnts.push_back(point{-1, -3, 0, 1});
			lyr.pnts.push_back(point{-1, -2, 0, 1});
			lyr.pnts.push_back(point{ 0, -1, 0, 1});
			lyr.pnts.push_back(point{ 1, -1, 0, 1});
			
			tessellate(&lyr);
			
			lyrs.push_back(lyr);

			atkpnts.push_back(point{ 3,  0, 0, 1});

			temp.push_back(point { 3, -1, 0, 1});
			temp.push_back(point { 3,  1, 0, 1});
			temp.push_back(point { 1,  2, 0, 1});
			temp.push_back(point {-3,  2, 0, 1});
			temp.push_back(point {-3, -2, 0, 1});
			temp.push_back(point { 1, -2, 0, 1});

			blt = bullet(temp, 5, 2);

			actionSet = 1;
			health = 20;
			cycle = 25;

			break;

		case 2:
			lyr.pnts.push_back(point{ 3,  0, 0 ,1});
			lyr.pnts.push_back(point{ 0,  1, 0 ,1});
			lyr.pnts.push_back(point{-2,  3, 0 ,1});
			lyr.pnts.push_back(point{-2, -3, 0 ,1});
			lyr.pnts.push_back(point{ 0, -1, 0 ,1});
			
			tessellate(&lyr);
			
			lyrs.push_back(lyr);

			atkpnts.push_back(point{ 3,  0, 0, 1});

			temp.push_back(point { 3, -1, 0, 1});
			temp.push_back(point { 3,  1, 0, 1});
			temp.push_back(point { 1,  2, 0, 1});
			temp.push_back(point {-3,  2, 0, 1});
			temp.push_back(point {-3, -2, 0, 1});
			temp.push_back(point { 1, -2, 0, 1});

			blt = bullet(temp, 10, 2);

			actionSet = 2;
			health = 20;
			cycle = 25;
			
			break;
		
		case 3:
			lyr.pnts.push_back(point { 1, 3});

			
	}
}
std::vector<point> ship::getBounds()
{
 	std::vector<point> temp = lyrs[0].pnts;
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
std::vector<point> ship::getPoints()
{
	std::vector<point> temp = lyrs[0].pnts;
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
	std::vector<triangle> temp = lyrs[0].tris;
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
	std::vector<point> temp = atkpnts;
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

int  ship::getHealth()
{
	return health;
}
void ship::setHealth(int dmg)
{
	health=dmg;
}


void ship::fire(mode* md)
{
	std::vector<point> temp=getAtkPnts();
	for (int i = 0; i < temp.size(); i++)
	{
		std::cout << "ship fire method" << std::endl;
		temp[i].x+=sin(location.angle);
		temp[i].y+=cos(location.angle);
		bullet * shot = blt.fireBullet(temp[i].x, temp[i].y, location.angle);
	//	shot.location= temp[i];
	//	shot.theta = location.angle;
		md->addToOnScreen(shot);
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
					//fire();
					break;
			}
			break;
		case 2:
			cycle++;

			break;

	}		
}

int ship::damageHealth(int dmg)
{
	health-=dmg;
	return health;
}
int ship::addHealth(int dmg)
{
	health+=dmg;
	return health;
}

void ship::resetShip()
{
	switch (type)
	{
		case 0:
			location = {0, 0, 0, 1, 0};
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
	// Create a temporary std::vector with the ship's Triangles
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
		switch (/*filled*/0)
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
void ship::render()
{
	// Create a temporary std::vector with the ship's Triangles
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
		
	for(int i = 0; i<temp.size(); i++)
	{    
		switch (/*filled*/0)
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
	std::vector<point> temp = lyrs[0].pnts;
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
		//cout << intersect (temp[0], temp[1], A, B) << std::endl;

		bool insect = false;
		for (int i1  = 0; i1 < lyrs[0].pnts.size(); i1++)
		{
			switch (i1)
			{
				case 0:
					if(intersect(lyrs[0].pnts[i1], lyrs[0].pnts[lyrs[0].pnts.size()-1], A, B))
						insect=true;
					if(intersect(lyrs[0].pnts[i1], lyrs[0].pnts[lyrs[0].pnts.size()-1], B, C))
						insect = true;
					if(intersect(lyrs[0].pnts[i1], lyrs[0].pnts[lyrs[0].pnts.size()-1], C, A))
						insect = true;
					break;
				default:
					if (intersect(lyrs[0].pnts[i1], lyrs[0].pnts[i1-1], A, B))
						insect = true;
					if (intersect(lyrs[0].pnts[i1], lyrs[0].pnts[i1-1], B, C))
						insect = true;
					if (intersect(lyrs[0].pnts[i1], lyrs[0].pnts[i1-1], C, A))
						insect = true;
					break;
			}
			if(insect)
			{	
				break;
			}
		}

		for (int i1  = 0; i1 < lyrs[0].tris.size(); i1++)
		{
			point temp1[3] = {lyrs[0].tris[i1].a, lyrs[0].tris[i1].b, lyrs[0].tris[i1].c};
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

			bool within = false;
			for (int i =0; i < temp.size(); i ++)
			{
				if(PointInTriangle(temp[i], A, B, C) && Ai!=i && Bi!=i && Ci!=i)
					within = true;
			}

			if (z<0 && !within)
			{
				tri.a = A;
				tri.b = B;
				tri.c = C;
				lyrs[0].tris.push_back(tri);

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

	for (int i = 0; i < lyrs[0].tris.size(); i++)
	{
	}
}

