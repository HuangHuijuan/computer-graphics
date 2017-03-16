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

Canvas cvs(700, 700, "Snow Flakes"); // create a global canvas object
bool loop = true;

void flakeMotif(){
	Point2 A[] = { Point2(8, 5), Point2(100, 5), Point2(130, 60), Point2(135, 50), Point2(108, 5), Point2(180, 5), Point2(210, 50), Point2(215, 40), Point2(188, 5), Point2(250, 5), Point2(255, 0) };
	for (int i = 0; i < 11; i++)
	{
		if (i == 0) cvs.moveTo(A[i].getX(), A[i].getY());
		else cvs.lineTo(A[i].getX(), A[i].getY());
	}
//	glutSwapBuffers();
}

void drawFlake()
{
//	cvs.clearScreen();
//	int r = rand() % 700;
//	cvs.setWindow(-300-r, 300+r, 300+r, -300-r);
///	cvs.setViewport(x,x+300,y, y+300);
	cvs.setWindow(-1000, 1000, 1000, -1000);
//	cvs.setViewport(0, 300, 0, 300);
	for (int count = 0; count < 6; count++) // draw a snowflake
	{
		flakeMotif();
		cvs.scale2D(1.0, -1.0);
		flakeMotif();
		cvs.scale2D(1.0, -1.0);
		cvs.rotate2D(60.0); // concatenate a 60 degree rotation
	}
//	glutSwapBuffers();
	glFlush();
}
void randomDraw(){
	drawFlake();
	Sleep(2000);
	cvs.clearScreen();
	cvs.setBackgroundColor(0.0, 1.0, 1.0);
	for (int i = 0; i < 100;i++)
	{
		cvs.initCT();
//		double r = 1-rand() % 100 * 0.01;
		double scales[] = { 0.1, 0.2, 0.3 };
		int rotations[] = { 0, 10, 20, 30, 40, 50 };
		double scale = scales[rand() % 3];
		int rotation = rotations[rand() % 6];
		cvs.translate2D(-700 + rand() % 1400, -700+rand() % 1400);
		cvs.scale2D(scale,scale);
		cvs.rotate2D(rotation/(2*3.1415));
		drawFlake();
		Sleep(100);
	}
//	glutSwapBuffers();
}
void myDisplay(void)
{
	cvs.clearScreen();
//	drawFlake();
	randomDraw();
	glFlush();
}


void main(int argc, char** argv)
{
	// the window has already been opened in the Canvas constructor
	cvs.setBackgroundColor(0.0, 1.0, 1.0); // background is white
	cvs.setColor(1.0, 1.0, 1.0); // set drawing color
	glutDisplayFunc(myDisplay);
	glutMainLoop();
}

