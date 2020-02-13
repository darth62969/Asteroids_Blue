#include "headers.h"
#include "structs.h"
#include "globals.h"
#include "object.h"
#include "prototypes.h"

void object::doAction(mode * md)
{
	return;
}

bool intersect(point v1, point v2, point v3, point v4)
{
	float ua_num = ((v3.x - v1.x) * -(v4.y - v3.y)) - (-(v4.x - v3.x) * (v3.y - v1.y));
	float den = ((v2.x - v1.x) * -(v4.y - v3.y)) - (-(v4.x - v3.x) * (v2.y - v1.y));

	float ub_num = ((v2.x - v1.x) * (v3.y - v1.y)) - ((v3.x - v1.x) * (v2.y - v1.y));

	float ua = ua_num / den;
	float ub = ub_num / den;

	if((ua > 0.0) && (ua < 1.0) && (ub > 0.0) && (ub < 1.0))
	{
		return true;
	}

	return false;
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
void voidFunc(double frac_1, double frac_2)
{
	
}

bool object::collides(object * other)
{
	std::vector<point> a_pnt = getBounds();
	std::vector<point> b_pnt = other->getBounds();
	for (int i = 0; i < a_pnt.size(); i++)
	{
		for (int j = 0; j < b_pnt.size(); j++)
		{
			point v1 = a_pnt[i];
			point v2 = a_pnt[(i+1)%a_pnt.size()];
			point v3 = b_pnt[j];
			point v4 = b_pnt[(j+1)%b_pnt.size()];

			double num_1 = ((v3.x - v1.x) * -(v4.y - v3.y)) - (-(v4.x - v3.x) * (v3.y - v1.y));
			double num_2 = ((v2.x - v1.x) * (v3.y - v1.y)) - ((v3.x - v1.x) * (v2.y - v1.y));
			double den =((v2.x - v1.x) * -(v4.y - v3.y)) - (-(v4.x - v3.x) * (v2.y - v1.y));

			double frac_1 = num_1 / den;
			double frac_2 = num_2 / den;

			if((frac_1>0.0)&&(frac_1<1.0)&&(frac_2>0.0)&&(frac_2<1.0))
				return true;
		}
	}
	return false;
}
bool object::collides(std::shared_ptr<object> other)
{
	std::vector<point> a_pnt = getBounds();
	std::vector<point> b_pnt = other->getBounds();
	for (int i = 0; i < a_pnt.size(); i++)
	{
		for (int j = 0; j < b_pnt.size(); j++)
		{
			point v1 = a_pnt[i];
			point v2 = a_pnt[(i+1)%a_pnt.size()];
			point v3 = b_pnt[j];
			point v4 = b_pnt[(j+1)%b_pnt.size()];

			double num_1 = ((v3.x - v1.x) * -(v4.y - v3.y)) - (-(v4.x - v3.x) * (v3.y - v1.y));
			double num_2 = ((v2.x - v1.x) * (v3.y - v1.y)) - ((v3.x - v1.x) * (v2.y - v1.y));
			double den =((v2.x - v1.x) * -(v4.y - v3.y)) - (-(v4.x - v3.x) * (v2.y - v1.y));

			double frac_1 = num_1 / den;
			double frac_2 = num_2 / den;

			if((frac_1>0.0)&&(frac_1<1.0)&&(frac_2>0.0)&&(frac_2<1.0))
				return true;
		}
	}
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
std::vector<triangle> object::getTess()
{
	std::vector<triangle> temp = lyrs[0].tris;
	for (int i =0; i < temp.size(); i++)
	{
		point a[3] = {temp[i].a, temp[i].b, temp[i].c};
		for (int j = 0; j < 3; j++ )
		{
			a[j].x += location.x;
			a[j].y += location.y;
		}
		temp[i].a = a[0];
		temp[i].b = a[1];
		temp[i].c = a[2];
	}
	return temp;
}

float object::getVectorLength(object * other)
{
	return sqrt(pow(abs(location.x-other->getLocation().x),2)+pow(abs(location.y-other->getLocation().y),2));
}

float object::getVectorLength(std::shared_ptr<object> other)
{
	return sqrt(pow(abs(location.x-other->getLocation().x),2)+pow(abs(location.y-other->getLocation().y),2));
}