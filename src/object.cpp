#include "headers.h"
#include "structs.h"
#include "globals.h"
#include "object.h"
#include "prototypes.h"

void object::doAction(mode * md)
{
	return;
}

void object::tessellate(layer* lyr)
{
	std::vector<point> temp = lyr->pnts;
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
		for (int i1  = 0; i1 < lyr->pnts.size(); i1++)
		{
			switch (i1)
			{
				case 0:
					if(intersect(lyr->pnts[i1], lyr->pnts[lyr->pnts.size()-1], A, B))
						insect=true;
					if(intersect(lyr->pnts[i1], lyr->pnts[lyr->pnts.size()-1], B, C))
						insect = true;
					if(intersect(lyr->pnts[i1], lyr->pnts[lyr->pnts.size()-1], C, A))
						insect = true;
					break;
				default:
					if (intersect(lyr->pnts[i1], lyr->pnts[i1-1], A, B))
						insect = true;
					if (intersect(lyr->pnts[i1], lyr->pnts[i1-1], B, C))
						insect = true;
					if (intersect(lyr->pnts[i1], lyr->pnts[i1-1], C, A))
						insect = true;
					break;
			}
			if(insect)
			{	
				break;
			}
		}

		for (int i1  = 0; i1 < lyr->tris.size(); i1++)
		{
			point temp1[3] = {lyr->tris[i1].a, lyr->tris[i1].b, lyr->tris[i1].c};
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
				lyr->tris.push_back(tri);

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

	for (int i = 0; i < lyr->tris.size(); i++)
	{
	}
}

bool object::collides(object * other)
{
	point a = other->getLocation();
	if (getVectorLength(other)>100)
		return false;

	std::vector<point> a_pnt= getBounds();
	std::vector<point> b_pnt= other->getBounds();
	for (int i = 0; i < a_pnt.size(); i++)
	{
		for (int j = 0; j < b_pnt.size(); j++)
		{
			if(intersect(a_pnt[i], a_pnt[(i+1)%a_pnt.size()], 
				b_pnt[j], b_pnt[(j+1)%b_pnt.size()]))
				{
					return true;
				}
		}
	}

		/*if ((a.x-location.x) < 50 && (a.y-location.y)<50)
		{
			std::vector<point> a_pnt= getBounds();
			std::vector<point> b_pnt= other->getBounds();
			for (int i = 0; i < a_pnt.size(); i++)
			{

			}
		}
		else
		{
			return false;
		}*/
	
	
	return false;
}

/*
 * Getters and setters, for security and other reasons. 
 * Most of this stuff shouldn't be public.
 */



point object::getLocation()
{
	return location;
}

void object::setLocation(double x, double y)
{
	location.x = x;
	location.y = y;
}
void object::setLocation(point loc)
{
	location = loc;
}

double object::getRotation()
{
	return location.angle;
}

void object::setRotation(double rot)
{
	location.angle = rot;
}

std::vector<point> object::getBounds()
{
	return lyrs[0].pnts;
}

float object::getVectorLength(object * other)
{
	return sqrt(pow(abs(location.x-other->getLocation().x),2)+pow(abs(location.y-other->getLocation().y),2));
}