#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define WINDOW_MAX 700
#define WINDOW_MIN 0
#define VIEWPORT_MAX 600
#define VIEWPORT_MIN 100
#define MAX 100

typedef struct vertex {
	float x;
	float y;
	float z;
	float w;
} vertex;

float DELTA_SPIN = 0.0;
float SPIN = 0.0;

float SCALE = 1.0;

float RESET = false;

bool filled = false;

bool reflect = false;

bool cw = true;

int xPos = 0, yPos = 0;

vector<triangle> triVect;

void beginCallback(GLenum which){
	glBegin(which);
}

void vertexCallback(void *data){
	glVertex3dv((GLdouble *) data);
}

void endCallback(void){
	glEnd();
}

void Pipeline(vector<vertex>& vertVect){
	triVect.clear();
	
	glTranslatef(WINDOW_MAX/2 + xPos, WINDOW_MAX/2 + yPos, 0.0);

	if(reflect == true){
		glScalef(1.0, -1.0, 1.0);
	} 

	glScalef(SCALE, SCALE, SCALE);

	glRotatef(SPIN, 0.0, 0.0, 1.0);

	glTranslatef(-(WINDOW_MAX/2 + xPos), -(WINDOW_MAX/2 + yPos), 0.0);
}

void defineArrow(vector<vertex>& aVerts){
	vertex v;
	
	v.x = 250.0; v.y = 300.0; v.z = 0.0; v.w = 1.0;
	aVerts.push_back(v);

	v.x = 450.0; v.y = 300.0;
	aVerts.push_back(v);

	v.x = 400.0; v.y = 250.0;
	aVerts.push_back(v);

	v.x = 550.0; v.y = 350.0;
	aVerts.push_back(v);

	v.x = 400.0; v.y = 450.0;
	aVerts.push_back(v);

	v.x = 450.0; v.y = 400.0;
	aVerts.push_back(v);

	v.x = 250.0; v.y = 400.0;
	aVerts.push_back(v);
}

void drawArrow(vector<vertex> aVerts, bool filled){
	int i;

	if(filled){
		GLdouble coords[aVerts.size()][3];
		for (i=0; i<aVerts.size(); i++){
			coords[i][0] = aVerts[i].x;
			coords[i][1] = aVerts[i].y;
			coords[i][2] = aVerts[i].z;
		}

		GLUtesselate* tobj = gluNewTess();
	
		gluTessCallback(tobj, GLU_TESS_VERTEX, (GLvoid (*)()) &vertexCallback);
		gluTessCallback(tobj, GLU_TESS_BEGIN, (GLvoid (*)()) &beginCallback);
		gluTessCallback(tobj, GLU_TESS_END, endCallback);

		gluTessBeginPolygon(tobj, NULL);
		gluTessBeginContour(tobj);
		for (i=0; i<aVerts.size(); i++){
			gluTessVertex(tobj, coords[i], coords[i]);
		}
		gluTessEndContour(tobj);
		gluTessEndPolygon(tobj);
		gluDeleteTess(tobj);
		glFlush();
		}
		else{
			glBegin(GL_LINE_LOOP);
			for(i=0; i<aVerts.size(); i++)
				glVertex2f(aVerts[i].x, aVerts[i].y);
			glEnd();
		}
	}
}

void myinit(void){
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glPointSize(1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (float) WINDOW_MAX, 0.0, (float) WINDOW_MAX);
	glMatrixMode(GL_MODELVIEW);	
}

void display(void){
	vector<vertex> aVerts;
	vector<vertex> inVerts;

	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);

	glRecti(VIEWPORT_MIN, VIEWPORT_MIN, VIEWPORT_MAX, VIEWPORT_MAX);

	glScissor(VIEWPORT_MIN, VIEWPORT_MIN, 500, 500);
	glPopMatrix();
	
	glEnable(GL_SCISSOR_TEST);
	glPushMatrix();
		defineArrow(aVerts);

	if(RESET != true)
		Pipeline(aVerts);

	RESET = false;

	glColor3f(1.0, 0.0, 0.0);
		glEnable(GL_SCISSOR_TEST);

	if(!filled){
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
	}
	
	if(aVerts.size()!=0){
		drawArrow(aVerts, filled);		
	}	
	glPopMatrix();

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);

	glDisable(GL_SCISSOR_TEST);

	glutSwapBuffers();
}

void SpinDisplay(void){
	SPIN = SPIN + DELTA_SPIN;
	if(SPIN > 360.0) SPIN = SPIN - 360.0;
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y){
	
}
