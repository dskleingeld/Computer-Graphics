// cannon.cpp : Defines the entry point for the console application.
//
// Pre-Workshop
//
// Goal: Get to know the code you will start with for Workshop 1
//
// The workshops are timed problem sessions where your solutions
// must be turned in at the end of the workshop (like an exam).
//
// You are encouraged to received advice and tips from the teaching assistant
// and other students, but the source code must be written by you
//
// The workshops are typically done with 2 students per computer.
//
// For workshops, note that each and every student must make their
// own submission on the LML Course Manager.  If John and Mary do the
// workshop together then John must make a submission and also Mary
// must make a submission.  Late submissions are subject to the late penalty.
// If Mary assumes that John's submission includes hers, and does not
// make her own submission, her grade will be zero.
//
// See class notes for explanation of functions
//

//#include "stdafx.h"
#include <stdlib.h>
#include "GL/glut.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <cstdio>

#include "lighting.h"

#define MAXPARTICLES 100
int WELLMASS = 100;
float g_posX = 0.0, g_posY = 25.0, g_posZ = 50.0;
float g_orientation = 15.0; // y axis
float g = 0.0;
float G = -6.67408; //NON PHYSICAL MISSES AN e-11 (but lets have pitty on the pc)

bool wellOn = false;
bool fired = true;

void updateCamera();
void drawObjects();

struct pinfo{
	float width;
	float x, y, z;
	float v_x, v_y, v_z;
	float a_x, a_y, a_z;
	GLfloat ambient[4];
	GLfloat diffuse[4];
	void setParticleColor(float r, float g , float b){
		ambient[0] = r;
		ambient[1] = g;
		ambient[2] = b;
		ambient[3] = 1;

		diffuse[0] = r;
		diffuse[1] = g;
		diffuse[2] = b;
		diffuse[3] = 1;
	}
} particles[MAXPARTICLES];

void fireCannon()
{
	unsigned int i;
	for (i = 0; i < MAXPARTICLES; i = i + 1){
		particles[i].width = 2* ((rand() / (float)RAND_MAX) + 1.0)*0.5;
		particles[i].x = 0.0;
		particles[i].y = 0.0;
		particles[i].z = 0.0;
		particles[i].v_x = 1.0 * ((rand() / (float)RAND_MAX) - 0.5);
		particles[i].v_y = 3.0 * ((rand() / (float)RAND_MAX) + 1.0); // always upwards
		particles[i].v_z = 1.0 * ((rand() / (float)RAND_MAX) - 0.5);

		particles[i].setParticleColor(1.0 * (rand() / (float)RAND_MAX),  //r
		                              1.0 * (rand() / (float)RAND_MAX),  //g
		                              1.0 * (rand() / (float)RAND_MAX)); //b

		particles[i].a_x = 0;
		particles[i].a_y = 0;
		particles[i].a_z = 0;
	}
	glutGet(GLUT_ELAPSED_TIME);
}

void fireworks()
{
	unsigned int i;
	float startAlt = 50.0*(rand() / (float)RAND_MAX) + 10.0;
	float r = 1.0 * (rand() / (float)RAND_MAX);
	float g = 1.0 * (rand() / (float)RAND_MAX);
	float b = 1.0 * (rand() / (float)RAND_MAX);
	for (i = 0; i < MAXPARTICLES; i = i + 1){
		particles[i].width =  0.5* (rand() / (float)RAND_MAX);
		particles[i].x = 0.0;
		particles[i].y = startAlt;
		particles[i].z = 0.0;
		particles[i].v_x = 5.0 * (rand() / (float)RAND_MAX) - 2.5;
		particles[i].v_y = 5.0 * (rand() / (float)RAND_MAX) - 2.5; // always upwards
		particles[i].v_z = 5.0 * (rand() / (float)RAND_MAX) - 2.5;
		particles[i].setParticleColor(r, g, b);

		particles[i].a_x = 0;
		particles[i].a_y = 0;
		particles[i].a_z = 0;
	}
	glutGet(GLUT_ELAPSED_TIME);
}


void drawOneParticle(unsigned int i){
	//set material properties (needs to be done before drawing)

	glMaterialfv(GL_FRONT, GL_AMBIENT, particles[i].ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, particles[i].diffuse);

	//draw a sphere (radius, number of subdivisions around the Z axis, 
	//number of subdivisions along the Z axis)
	glutSolidSphere(particles[i].width ,60,60); 
}

void drawParticles()
{	
	if(materialsOn){
		 glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		 glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		 glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	}
	else{
   glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
   glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
   glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	}

	unsigned int i;
	for (i = 0; i < MAXPARTICLES; i = i + 1){
		glPushMatrix();
		glTranslatef(particles[i].x, particles[i].y, particles[i].z);
		drawOneParticle(i);
		glPopMatrix();
	}

	//restore default colors
	glMaterialfv(GL_FRONT, GL_AMBIENT, default_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, default_diffuse);
}

void keyboard(unsigned char key, int x, int y){
	switch (key) {
		case 's': // up
			g_posY = g_posY + 1.0;
			break;
		case 'x': // down
			g_posY = g_posY - 1.0;
			break;
		case 'j': // left
			g_orientation = g_orientation - 15.0;
			break;
		case 'l': // right
			g_orientation = g_orientation + 15.0;
			break;
		case 'i': // forwards in direction of movement
			g_posX = g_posX + sin(g_orientation / 180.0 * M_PI);
			g_posZ = g_posZ - cos(g_orientation / 180.0 * M_PI);
			break;
		case 'k': // backwards in direction of movement
			g_posX = g_posX - sin(g_orientation / 180.0 * M_PI);
			g_posZ = g_posZ + cos(g_orientation / 180.0 * M_PI);
			break;
		case 'h': // reset
			g_posX = 0.0;
			g_posY = 25.0;
			g_posZ = 50.0;
			g_orientation = 15.0; // y axis
			lx = 0;
			ly = 0;
			lz = 0;		
			break;
		case 'g':
			if (g == 0.0)
				g = 9.81;
			else
				g = 0.0;
			break;
		case 'w':
			if(wellOn){
				wellOn = false;
				printf("turned well off\n");
			}
			else{
				wellOn = true;
				printf("turned well on\n");
			}
			break;
		case 'f': // fire
			fireCannon();
			break;
//		case 'r': // fireworks
//			fireworks();
//			break;
		case '4': // light up
			ly += 0.2;;
			break;
		case 'r': // light down
			ly -= 0.2;
			break;
		case 'e': // light left
			lx -= 0.2;
			break;
		case 't': // light right
			lx += 0.2;
			break;
		case 'q': // exit
			exit(0);
			break;
		case 'd':
			if(diffuseOn){
				printf("disabled diffuse lighting\n");
				diffuseOn = false; 
				glDisable(GL_LIGHT0);
			}
			else{
				printf("enabled diffuse lighting\n");				
				diffuseOn = true; 
				glEnable(GL_LIGHT0);
			}
			break;
		case 'a':
			if(ambientOn){
				printf("disabling ambient lighting\n");						
				ambientOn = false; 
				glDisable(GL_LIGHT1);
			}
			else{
				printf("enabling ambient lighting\n");				
				ambientOn = true; 
				glEnable(GL_LIGHT1);
			}
			break;
		case 'm':
			if(materialsOn){
				printf("disabling material lighting\n");					
				materialsOn = false;
			}
			else{
				printf("enabling material lighting\n");					
				materialsOn = true;
			}
			break;
	}
	glutPostRedisplay();
}

void update(){
	glClearColor (0.0,0.0,0.0,1.0); //clear the screen to black
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
  glLoadIdentity(); //replaces the current matrix with the identity matrix

	updateCamera();

	//update lighting
	updateLights();

	drawObjects(); //call the object drawing function
	glutSwapBuffers(); //swap the buffers
}

void updateCamera(){
	glRotatef(g_orientation, 0.0, 1.0, 0.0); // rotate in y axis
	glTranslatef(-g_posX, -g_posY, -g_posZ);
}

void drawObjects(){
	drawGroundPlane();
	drawLightSource();
	//drawTestParticle();
	//drawWindMill();
	
	if(wellOn) //indicate gravity well with single particle
		drawWell();
	if(fired)
		drawParticles();
}

void gravity(float time){
	float F, a, r2, r;
	float xRatio, yRatio, zRatio;
	float x, y, z, m;
	float x_w, y_w, z_w;
	int m_w;

	for(int currentP = 0; currentP < MAXPARTICLES; currentP ++){
		x = particles[currentP].x;
		y = particles[currentP].y;
		z = particles[currentP].z;
		m = 0.1;

		x_w = 0;
		y_w = 50;
		z_w = 0;
		m_w = WELLMASS;

		r2 = (pow(x-x_w,2)+pow(y-y_w,2)+pow(z-z_w,2));
		r = sqrt(r2);

		//get direction of vector without sin/cos etc
		xRatio = (x-x_w)/r;
		yRatio = (y-y_w)/r;
		zRatio = (z-z_w)/r;

		//calc force and accelleration
		F= m*m_w*G/r2;
		a= F/m;

		//store acceleration
		particles[currentP].a_x = a*xRatio;
		particles[currentP].a_y = a*yRatio;
		particles[currentP].a_z = a*zRatio;

		particles[currentP].v_x += particles[currentP].a_x*time;
		particles[currentP].v_y += particles[currentP].a_y*time;
		particles[currentP].v_z += particles[currentP].a_z*time;

		particles[currentP].x += particles[currentP].v_x*time;
		particles[currentP].y += particles[currentP].v_y*time;
		particles[currentP].z += particles[currentP].v_z*time;
	}
}

void timer(int value){
	static int lastTime;
	int thisTime;
	float time;
	thisTime = glutGet(GLUT_ELAPSED_TIME);
	time = (thisTime - lastTime) / 500.0;
	lastTime = thisTime;

	if(wellOn){
		gravity(time);
	}
	else{//Do grav + floor
		for(int i = 0; i < MAXPARTICLES; i++){
			if (particles[i].y < 0.0) {
				particles[i].v_x = 0.0;
				particles[i].v_y = 0.0;
				particles[i].v_z = 0.0;
			}
			else
				particles[i].v_y -= g*time;
			particles[i].x += particles[i].v_x*time;
			particles[i].y += particles[i].v_y*time;
			particles[i].z += particles[i].v_z*time;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(50, &timer, 0);
}

void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
    glMatrixMode (GL_PROJECTION); //set the matrix to projection

    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100.0); //set the perspective (angle of sight, width, height, , depth)
    glMatrixMode (GL_MODELVIEW); //set the matrix back to model

}

int main(int argc, char *argv[]){
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize (500, 500); //set the window size
	glutInitWindowPosition (100, 100); //set the position of the window
	glutCreateWindow("Particle Cannon");

	initLighting(); //initialise lighting
	glutDisplayFunc(&update); //use the display function to draw everything
	glutIdleFunc(&update); //set the function to execute when no window events are happening
  glutReshapeFunc(&reshape); //reshape the window accordingly
	glutKeyboardFunc(&keyboard); //check the keyboard
	glutTimerFunc(50, &timer, 0);
	glutMainLoop();
	return 0;
}
