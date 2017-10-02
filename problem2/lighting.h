// lightingtest.cpp
//
// LIACS Computer Graphics
//
// This sample code is for using and exploring OpenGL Lighting and Materials
//

//#include "stdafx.h"
#include <stdlib.h>
#include "GL/glut.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>

bool materialsOn = true;
bool diffuseOn = true;
bool ambientOn = true;

//angle of rotation
GLfloat angle = 0.0;

//diffuse light color variables
GLfloat dlr = 1.0;
GLfloat dlg = 1.0;
GLfloat dlb = 1.0;

//ambient light color variables
GLfloat alr = 1.0;
GLfloat alg = 1.0;
GLfloat alb = 1.0;

//light position variables
GLfloat lx = 0.0; // normal physics y axis
GLfloat ly = 15.0; // up (normal physics z axis)
GLfloat lz = 1.0; // normal physics x axis
GLfloat lw = 1.0; // normal physics x axis

//interface lighting flags
int aflag = 0;
int dflag = 1;
int mflag = 0;

//commonly used material values
//r,g,b,alpha
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat default_ambient[] = {0.2, 0.2, 0.2, 1.0};
GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
GLfloat default_diffuse[] = {0.8, 0.8, 0.8, 1.0};
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};

GLfloat no_shininess[] = { 0.0 };
GLfloat low_shininess[] = { 5.0 };
GLfloat high_shininess[] = { 100.0 };

void initLighting(){
  glEnable(GL_DEPTH_TEST); //enable the depth testing
  glEnable(GL_LIGHTING); //enable the lighting
  glEnable(GL_LIGHT0); //enable LIGHT0, our Diffuse Light
  glEnable(GL_LIGHT1); //enable LIGHT1, our Ambient Light
  glShadeModel(GL_SMOOTH); //set the shader to smooth shader
}

void updateLights(){
	//update lighting
	GLfloat DiffuseLight[] = {dlr, dlg, dlb}; //set DiffuseLight[] to the specified values
	GLfloat AmbientLight[] = {alr, alg, alb}; //set AmbientLight[] to the specified values
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight); //change the light accordingly
	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight); //change the light accordingly

	//set the LightPosition, if last element is 1: base, diffuse and specular 
	//lighting calculations on the actual location of the light in eye coordinates,

	GLfloat LightPosition[] = {lx, ly, lz, lw}; 
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition); //change the light accordingly

}

void drawWell(){
	glPushMatrix();
	glTranslatef(0, 50, 0);
	glScalef(3, 3, 3);
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLE_STRIP);
	// triangle 1
	glVertex3f(-0.5, 0.0, 0.5); // A
	glVertex3f(0.0, 0.0, -0.5); // B
	glVertex3f(0.0, 1.0, 0.0); // top
	// triangle 2
	glVertex3f(0.5, 0.0, 0.5); // C
	// triangle 3
	glVertex3f(-0.5, 0.0, 0.5); // A again
	// triangle 4 (bottom)
	glVertex3f(0.0, 0.0, -0.5); // B again
	glEnd();
	glPopMatrix();
}

void drawGroundPlane(){

	glPushMatrix(); //start new translation and rotation session
	
	glBegin(GL_QUADS);// cannon base

	glVertex3f(-5.0, 0.0, -5.0);
	glVertex3f(-5.0, 0.0, 5.0);
	glVertex3f(5.0, 0.0, 5.0);
	glVertex3f(5.0, 0.0, -5.0);
	glEnd();//draw the objects

	glBegin(GL_LINE_STRIP);// ground plane
	glVertex3f(-40.0, 0.0, -40.0);
	glVertex3f(-40.0, 0.0, 40.0);
	glVertex3f(40.0, 0.0, 40.0);
	glVertex3f(40.0, 0.0, -40.0);
	glVertex3f(-40.0, 0.0, -40.0);
	glEnd();//draw the objects

	glPopMatrix(); 
}

void drawLightSource(){
	glPushMatrix(); //start new translation and rotation session

	GLfloat ambient[4] = {1,1,1,1};
	GLfloat diffuse[4] = {0,0,0,0};
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

	glTranslatef(lx, ly, lz);
	glScalef(3, 3, 3);
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLE_STRIP);
	// triangle 1
	glVertex3f(-0.5, 0.0, 0.5); // A
	glVertex3f(0.0, 0.0, -0.5); // B
	glVertex3f(0.0, 1.0, 0.0); // top
	// triangle 2
	glVertex3f(0.5, 0.0, 0.5); // C
	// triangle 3
	glVertex3f(-0.5, 0.0, 0.5); // A again
	// triangle 4 (bottom)
	glVertex3f(0.0, 0.0, -0.5); // B again
	glEnd();
	glPopMatrix(); 

	//restore default colors
	glMaterialfv(GL_FRONT, GL_AMBIENT, default_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, default_diffuse);
}

void drawTestParticle(){
	glPushMatrix(); //start new translation and rotation session

/*	GLfloat ambient[4] = {1,1,1,1};*/
/*	GLfloat diffuse[4] = {0,0,0,0};*/
/*	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);*/
/*	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);*/

	glTranslatef(0, 10, 0);
	glutSolidSphere(1,60,60); 
	glPopMatrix(); 

/*	//restore default colors*/
/*	glMaterialfv(GL_FRONT, GL_AMBIENT, default_ambient);*/
/*	glMaterialfv(GL_FRONT, GL_DIFFUSE, default_diffuse);*/
}

void crossProduct(GLfloat vec1[3], GLfloat vec2[3], GLfloat result[3]) {
  result[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
  result[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
  result[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
}

void setNormalVec(GLfloat p3[3], GLfloat p2[3], GLfloat p1[3]) {
  GLfloat vect1[3], vect2[3], normalVec[3];
	float len;
  
	//calc X vec along vertice
  vect1[0] = p1[0] - p2[0];
  vect2[0] = p2[0] - p3[0];

  vect1[1] = p1[1] - p2[1];
  vect2[1] = p2[1] - p3[1];

  vect1[2] = p1[2] - p2[2];
  vect2[2] = p2[2] - p3[2];
  
  crossProduct(vect1, vect2, normalVec);
  len = sqrt(pow(normalVec[0], 2) + pow(normalVec[1], 2) + pow(normalVec[2], 2));

  normalVec[0] /= len;
  normalVec[1] /= len;
  normalVec[2] /= len;
  
  glNormal3fv(normalVec);
}

void drawBox_WithoutFloor(float dx, float dy, float dz){
	GLfloat vertex[10][3] = 
			{{-dx, -dy, dz}, //1 front bottem left
			{-dx, dy, dz},		//2 front top left
	    {dx, -dy, dz}, //3 front bottem right
			// triangle 2
	    {dx, dy, dz}, //4 front top right
			// triangle 3
	    {dx, -dy, -dz}, //5 back bottem right
			// triangle 4
	    {dx, dy, -dz}, //6 back top right
			// triangle 5
	    {-dx, -dy, -dz}, //7 back bottem left
			// triangle 6
	    {-dx, dy, -dz}, //8 back top left
			// triangle 6
	    {-dx, -dy, dz}, //9 front bottem left
			// triangle 6
	    {-dx, dy, dz}}; //9 front top left


	glBegin(GL_TRIANGLE_STRIP);

	glVertex3fv(vertex[0]);
	glVertex3fv(vertex[1]);
	for(int i=2; i<10; i++){
		setNormalVec(vertex[i], vertex[i-1], vertex[i-2]);
		glVertex3fv(vertex[i]);
	}
	glEnd();
}


void drawBox(float dx, float dy, float dz){
	/*using the cube strip from "Optimising Tringle Strips for Fast Rendering"
	  by Francine Evans, Steven Skiena and Amitabh Varshney. 
	  State University of New York Oktober 1996

		modified for cubes with variable vertices
	*/
	GLfloat vertex[14][3] = 
		{{-dx, dy, dz},  //4 front top left
		{dx, dy, dz},  //3 front top right
		{-dx, -dy, dz},  //7 front bottom left
		{dx, -dy, dz},  //8 front bottom right
		{dx, -dy, -dz},  //5 back bottom right
		{dx, dy, dz},  //3 front top right
		{dx, dy, -dz},  //1 back top right
		{-dx, dy, dz},  //4 front top left
		{-dx, dy, -dz},  //2 back top left
		{-dx, -dy, dz},  //7 front bottom left
		{-dx, -dy, -dz},  //6 back bottom left
		{dx, -dy, -dz},  //5 back bottom right
		{-dx, dy, -dz},  //2 back top left
		{dx, dy, -dz}};  //1 back top right

	glBegin(GL_TRIANGLE_STRIP);

	for(int i=2; i<14; i++){
		setNormalVec(vertex[i], vertex[i-1], vertex[i-2]);
		glVertex3fv(vertex[i]);
	}
	glEnd();		
}

void drawWindMillBase(float baseWith, float baseHeight){
	glPushMatrix(); //start new translation and rotation session
	glTranslatef(0, baseHeight/2, 0);	
	drawBox_WithoutFloor(baseWith/2, baseHeight/2, baseWith/2);
	glPopMatrix(); 
}

void drawWindMillBlades(float length, float with, float thickness){
	glPushMatrix(); //start new translation and rotation session

	//draw top blade
	glTranslatef(0, length/2+with/2, 0); 
	drawBox(with/2,length/2,thickness/2);
	//draw bottem blade
	glTranslatef(0, -1*length-with, 0); //= -length/2 -with/2 relative to origin
	drawBox(with/2,length/2,thickness/2);

	//draw right blade
	glTranslatef(length/2+with/2, +length/2+with/2, 0);
	drawBox(length/2,with/2,thickness/2); 
	//draw right blade
	glTranslatef(-length-with, 0, 0); 
	drawBox(length/2,with/2,thickness/2); 
	glPopMatrix(); 
}

void drawWindMill(){
	constexpr float length = 10, with = 4, thickness = 1;
	constexpr float baseWith = 5, baseHeight=20;	
	glPushMatrix();
	drawWindMillBase(baseWith, baseHeight);
	glTranslatef(0,baseHeight, baseWith/2);
	drawWindMillBlades(length, with, thickness);
	glPopMatrix(); 
}
