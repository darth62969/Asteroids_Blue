//Sutherland Hodgeman Clipping Algorithm
//by Dr. Pounds, Mercer University
//

#include "headers.h"
#include "structs.h"
#include "globals.h"
#include "prototypes.h"

typedef point edge[2];
typedef point pointArray[200];        /* MAX is a declared constant */

void Intersect(point first, point second, point *clipBoundary,
                          point *intersectPt)
{


	if (clipBoundary[0].y == clipBoundary[1].y) {           /*horizontal*/
                intersectPt->y = clipBoundary[0].y;
                intersectPt->x = first.x + (clipBoundary[0].y - first.y) *
                        (second.x - first.x) / (second.y - first.y);
        } else if (clipBoundary[0].x == clipBoundary[1].x) {                                                                                        /*vertical*/
                intersectPt->x = clipBoundary[0].x;
                intersectPt->y = first.y + (clipBoundary[0].x - first.x) *
                        (second.y - first.y) / (second.x - first.x);
        }
	else{
	double a1, a2, b1, b2, c1, c2, det;

	a1 = clipBoundary[1].y - clipBoundary[0].y;
	b1 = clipBoundary[0].x - clipBoundary[1].x;
	c1 = a1*clipBoundary[0].x + b1*clipBoundary[0].y;

	a2 = second.y - first.y;
        b2 = first.x - second.x;
        c2 = a2*first.x + b2*first.y;
	
	det = a1*b2 - a2*b1;
	
	intersectPt->x = (b2*c1 -b1*c2)/det;
	intersectPt->y = (a1*c2 -a2*c1)/det;
	}	

 }

int insideOctogon(point p)
{
	double slope, line;

	int in = 1;
	if (p.x < octogon[0].x) in *= 0;
	if (p.x > octogon[5].x) in *= 0;
	if (p.y > octogon[2].y) in *= 0;
	if (p.y < octogon[7].y) in *= 0;

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

bool Inside(point p, point *clipBoundary)
{
	
       double slope, line;
	int in = 1;

	if(clipBoundary[0].x == octogon[0].x && clipBoundary[0].y == octogon[0].y){
		if (p.x < octogon[0].x) in *= 0;
	}
	if(clipBoundary[0].x == octogon[1].x && clipBoundary[0].y == octogon[1].y){
		slope = (octogon[2].y - octogon[1].y) / (octogon[2].x - octogon[1].x);
         	line = slope*(p.x - octogon[2].x)+ octogon[2].y;
        	if (p.y > line) in *= 0;

	}
	if(clipBoundary[0].x == octogon[2].x && clipBoundary[0].y == octogon[2].y){
		if (p.y > octogon[2].y) in *= 0;
	}
	if(clipBoundary[0].x == octogon[3].x && clipBoundary[0].y == octogon[3].y){
		slope = (octogon[3].y - octogon[4].y) / (octogon[3].x - octogon[4].x);
        	line = slope*(p.x - octogon[4].x)+ octogon[4].y;
        	if (p.y > line) in *= 0;
	}
	if(clipBoundary[0].x == octogon[4].x && clipBoundary[0].y == octogon[4].y){
		if (p.x > octogon[5].x) in *= 0;
	}
	if(clipBoundary[0].x == octogon[5].x && clipBoundary[0].y == octogon[5].y){
		slope = (octogon[6].y - octogon[5].y) / (octogon[6].x - octogon[5].x);
        	line = slope*(p.x - octogon[6].x)+ octogon[6].y;
	        if (p.y < line) in *= 0;

	}
	if(clipBoundary[0].x == octogon[6].x && clipBoundary[0].y == octogon[6].y){
		if (p.y < octogon[7].y) in *= 0;
	}
	if(clipBoundary[0].x == octogon[7].x && clipBoundary[0].y == octogon[7].y){
		slope = (octogon[7].y - octogon[0].y) / (octogon[7].x - octogon[0].x);
	        line = slope*(p.x - octogon[0].x)+ octogon[0].y;
        	if (p.y < line) in *= 0;
	}

	return in;


}

void Output(point newPoint, int *outLength, point *outPointArray)
{
        (*outLength)++;       outPointArray[*outLength - 1].x = newPoint.x;
        outPointArray[*outLength - 1].x = newPoint.x;
        outPointArray[*outLength - 1].y = newPoint.y;
}

void SutherlandHodgmanPolygonClip(point *inPointArray,
        point *outPointArray, int inLength, int *outLength, point *clip_boundary)
{
        point s, p, i;
        int j;

        *outLength = 0;
        s = inPointArray[inLength - 1];        /* Start with the last point in inPointArray */
        for (j = 0; j < inLength; j++) {
                p = inPointArray[j];   /* Now s and p correspond to the vertices in Fig.3.33 */
                if (Inside(p, clip_boundary)) { /* Cases 1 and 4 */
                        if (Inside(s, clip_boundary))
                                Output(p, outLength, outPointArray);   /* Case 1 */
                        else {                                                                          /* Case 4 */
                                Intersect(s, p, clip_boundary, &i);
                                Output(i, outLength, outPointArray);
                                Output(p, outLength, outPointArray);
                        }
                } else if(Inside(s, clip_boundary)) {                   /* Cases 2 and 3 */
                        Intersect(s, p, clip_boundary, &i);                     /* Case 2 */
                        Output(i, outLength, outPointArray);
                }                                                                                               /* No action for case 3 */
                s = p;                                  /* Advance to next pair of vertices */
        }
}

void vectorToArray(vector<point>& v,point *a){
	for(int i = 0; i < v.size(); i++){
		a[i] = v[i];
	}
}

void arrayToVector(vector<point>& v,point *a, int size){
	v.clear();
	for(int i = 0; i < size; i++){
		v.push_back(a[i]);
	}
}
void clip(vector<point>& v){
	pointArray in;
        pointArray out;
        int *outSize = new int;


        edge clipBounds;
        clipBounds[0] = octogon[0];
        clipBounds[1] = octogon[1];

        vectorToArray(v,in);

        SutherlandHodgmanPolygonClip(in,out,v.size(),outSize,clipBounds);

        clipBounds[0] = octogon[1]; clipBounds[1] = octogon[2];
        SutherlandHodgmanPolygonClip(out,in,*outSize,outSize,clipBounds);

        clipBounds[0] = octogon[2]; clipBounds[1] = octogon[3];
        SutherlandHodgmanPolygonClip(in,out,*outSize,outSize,clipBounds);

        clipBounds[0] = octogon[3]; clipBounds[1] = octogon[4];
        SutherlandHodgmanPolygonClip(out,in,*outSize,outSize,clipBounds);

        clipBounds[0] = octogon[4]; clipBounds[1] = octogon[5];
        SutherlandHodgmanPolygonClip(in,out,*outSize,outSize,clipBounds);

        clipBounds[0] = octogon[5]; clipBounds[1] = octogon[6];
        SutherlandHodgmanPolygonClip(out,in,*outSize,outSize,clipBounds);

        clipBounds[0] = octogon[6]; clipBounds[1] = octogon[7];
        SutherlandHodgmanPolygonClip(in,out,*outSize,outSize,clipBounds);

        clipBounds[0] = octogon[7]; clipBounds[1] = octogon[0];
        SutherlandHodgmanPolygonClip(out,in,*outSize,outSize,clipBounds);

        arrayToVector(v, in, *outSize);

}

void clipMeDaddy(){
	glColor3f(0.0,0.0,0.0);
	int p = 1;
	int q = 0;

	for(int i = 0; i < 8; i++){
		
		glBegin(GL_POLYGON);
			glVertex2f(octogon[p].x, octogon[p].y);		
			glVertex2f(octogon[q].x, octogon[q].y);	
			glVertex2f(clipPts[q].x, clipPts[q].y);	
			glVertex2f(clipPts[p].x, clipPts[p].y);		
		glEnd();
		p++;
		q++;
		if (p == 8) p = 0;
		if (q == 8) q = 0;
	}
	glColor3f (0.1, 0.5, 0.0); 


	/*allGood.clear();
	for (int i = 0; i < asteroidBelt.size(); i++){
		int total = 0;
		vector<point> a = asteroidBelt[i].getRealPoints();
		for(int j = 0; j < a.size(); j++) 
			total += insideOctogon(a[i]);

		if (total == 0);
		else if (total == a.size()) allGood.push_back(asteroid[i]);
		else {
			clip(asteroid[i]);
			allGood.push_back(a);
		}
				
	}*/
}


