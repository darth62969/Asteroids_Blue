/* 
 * Bullet Operations for Asteroids: RETURN OF METEOR
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

#include "structs.h"
#include "globals.h"
#include "prototypes.h"

#ifndef SHIPTEST
bullet createBullet()
{
	bullet shot;
#ifndef SHIPTEST
	// The bullet will originate at the front of the ship.
	shot.location = enterprise.aLocation;
	// Convert the rotation (float) of enterprise to radians.
	shot.theta = enterprise.rotation * M_PI / 180.0;
#endif
	return shot;
}

void drawBullet(bullet shot)
{
	glBegin(GL_POINTS);
		glVertex2f(shot.location.x, shot.location.y);
	glEnd();	
}

void fireBullet(bullet shot){
	
	//glTranslatef(shot.translation.x, shot.translation.y, 0.0);
 	point trans = shot.location;
	//rotatePoint(trans, shot.theta);
	glBegin(GL_POINTS);
		glVertex2f(trans.x, trans.y);
	glEnd();
	
	//drawBullet(shot);
}
#endif

#ifdef SHIPTEST

#include "bullet.h"

bullet::bullet(vector<point> pnts, int dmg, double vel)
{
	bltPnts = pnts;
	damage = dmg;
	location.w = vel;
	tesselate();
}
bullet::bullet()
{
	
}

bullet bullet::createBullet(int x, int y, double rot)
{
	bullet temp;
	temp.location.x = x;
	temp.location.y = y;
	temp.location.angle = rot;
	temp.location.w = location.w;
	temp.bltPnts = bltPnts;
	temp.bltTris = bltTris;
	temp.damage = damage;
	return temp;

}

void bullet::increment()
{
	location.x+=location.w*cos(location.angle);
	location.y+=location.w*sin(location.angle);
}

void bullet::drawBullet()
{
	vector<triangle> temp = bltTris;
	for (int i = 0; i < temp.size(); i++)
	{
		point b[3];
		b[0]=temp[i].a;
		b[1]=temp[i].b;
		b[2]=temp[i].c;
		for(int j=0; j<3; j++)
		{ 
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
}

int bullet::getDamage()
{
	return damage;
}

point bullet::getLocation()
{
	return location;
}

void bullet::tesselate()
{
	vector<point> temp = bltPnts;
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
		for (int i1  = 0; i1 < bltPnts.size(); i1++)
		{
			switch (i1)
			{
				case 0:
					if(intersect(bltPnts[i1], bltPnts[bltPnts.size()-1], A, B))
						insect=true;
					if(intersect(bltPnts[i1], bltPnts[bltPnts.size()-1], B, C))
						insect = true;
					if(intersect(bltPnts[i1], bltPnts[bltPnts.size()-1], C, A))
						insect = true;
					break;
				default:
					if (intersect(bltPnts[i1], bltPnts[i1-1], A, B))
						insect = true;
					if (intersect(bltPnts[i1], bltPnts[i1-1], B, C))
						insect = true;
					if (intersect(bltPnts[i1], bltPnts[i1-1], C, A))
						insect = true;
					break;
			}
			if(insect)
			{	
				break;
			}
		}

		for (int i1  = 0; i1 < bltTris.size(); i1++)
		{
			point temp1[3] = {bltTris[i1].a, bltTris[i1].b, bltTris[i1].c};
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
				tri.a = A;
				tri.b = B;
				tri.c = C;
				bltTris.push_back(tri);

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
}

#endif