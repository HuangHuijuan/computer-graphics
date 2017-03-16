#include <stdlib.h>
#include <iostream>
#include <math.h>
#include<windows.h>
#ifdef __APPLE__
#include <glut.h>
#else
#include <GL/glut.h>
#include "Canvas.h"
#endif

Canvas cvs(760, 630, "Tweening Animation"); // create a global canvas object
bool loop = true;
void myDisplay(void)
{
	cvs.clearScreen();
	cvs.draw();
//	cvs.drawHouse();
//	cvs.drawT();
	glFlush();
}

void myidle(void){
	if (loop)
		cvs.draw();
}
void myMouse(int button, int state, int x, int y)
{
	glClear(GL_COLOR_BUFFER_BIT);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		loop = true;
		glutIdleFunc(myidle);
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		loop = false;
	}
}


void main(int argc, char** argv)
{
	// the window has already been opened in the Canvas constructor
	cvs.setBackgroundColor(1.0, 1.0, 1.0); // background is white
	cvs.setColor(1.0, 0.0, 0.0); // set drawing color
	glutDisplayFunc(myDisplay);
	glutMouseFunc(myMouse);
	glutMainLoop();
}