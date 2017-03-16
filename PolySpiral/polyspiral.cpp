#include <stdlib.h>
#include <math.h>
#include<windows.h>
#ifdef __APPLE__
#include <glut.h>
#else
#include <GL/glut.h>
#endif
#include"canvas.h"


Canvas cvs(700, 700, "try out Canvas"); // create a global canvas object

void polySpiral(int n, float cx, float cy, float rotAngle)
{
	if (n < 3)return;		//bad number of sides
	double angle = rotAngle*3.14159265 / 180;		//the initial angle
	double angleInc = 2 * 3.14159265 / 5;		//the delta_angle
	double radius = 5;		//the radius
	double radiusInc = 1;	//radius increment
	cvs.moveTo(radius*cos(angle) + cx, radius*sin(angle) + cy);
	for (int k = 0; k < n; k++)
	{
		angle += angleInc + 0.02;
		radius += radiusInc;
		cvs.lineTo(radius * cos(angle) + cx, radius*sin(angle) + cy);
	}
	glFlush();
	glutSwapBuffers();
}
void zoomIn(int NumFrames){
	RealRect window = cvs.getWindow();
	float cx = 350, cy = 350;//center of the window
	float  H = window.getT() - window.getB(), W = window.getR() - window.getL(), aspect = 1; // window properties
	for (int frame = 0; frame < NumFrames; frame++) // for each frame
	{
		cvs.clearScreen();
		W *= 0.8; // reduce the window width
		H = W * aspect; // maintain the same aspect ratio
		cvs.setWindow(cx - W / 2, cx + W / 2, cy - H / 2, cy + H / 2); //set the next window
		polySpiral(250, 350, 350, 0);// draw the object
		Sleep(100);
	}
}
void zoomOut(int NumFrames){
	RealRect window = cvs.getWindow();
	float cx = 350, cy = 350;//center of the window
	float  H = window.getT() - window.getB(), W = window.getR() - window.getL(), aspect = 1; // window properties
	for (int frame = 0; frame < NumFrames; frame++) // for each frame
	{
		cvs.clearScreen();
		W *= 1.1; // reduce the window width
		H = W * aspect; // maintain the same aspect ratio
		cvs.setWindow(cx - W / 2, cx + W / 2, cy - H / 2, cy + H / 2); //set the next window
		polySpiral(250, 350, 350, 0);// draw the object
		Sleep(100);
	}

}
void roam(float h, float v){
	cvs.clearScreen();
	RealRect window = cvs.getWindow();
	cvs.setWindow(window.getL() + h, window.getR() + h, window.getB() + v, window.getT() + v);
	polySpiral(250, 350, 350, 0);
	Sleep(100);
}
void zoomKeyboard(unsigned char theKey, int mx, int my)
{
	switch (theKey)
	{
	case '+':
		zoomIn(3);
		break;
	case '-':
		zoomOut(3);
		break;
	default:
		break;

	}
}
void roamKeyboard(int theKey, int mx, int my)
{
	switch (theKey){
	case GLUT_KEY_UP:
		roam(0, 10);
		break;
	case GLUT_KEY_DOWN:
		roam(0, -10);
		break;
	case GLUT_KEY_LEFT:
		roam(-10, 0);
		break;
	case GLUT_KEY_RIGHT:
		roam(10, 0);
		break;
	default:
		break;

	}
}
void myDisplay(void)
{
	cvs.clearScreen();
	polySpiral(250, 350, 350, 0);
	Sleep(2000);
	zoomIn(20);
	//lrbt
	cvs.clearScreen();
	cvs.setWindow(200, 500, 200, 500);
	polySpiral(250, 350, 350, 0);

	Sleep(2000);
	for (int i = 0; i < 30; i++)
		roam(0, -10);

	cvs.clearScreen();
	cvs.setWindow(0, 700, 0, 700);
	polySpiral(250, 350, 350, 0);

	glFlush();
}

void main(int argc, char** argv)
{

	// the window has already been opened in the Canvas constructor
	cvs.setBackgroundColor(1.0, 0.0, 0.0); // background is white
	cvs.setColor(1.0, 1.0, 0.0); // set drawing color
	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(zoomKeyboard);
	glutSpecialFunc(roamKeyboard);
	glutMainLoop();
}