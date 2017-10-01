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

void drawWindMill(){
	glPushMatrix(); //start new translation and rotation session
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
