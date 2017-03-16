#include <stdlib.h>
#include <math.h>
#include<windows.h>
#ifdef __APPLE__
#include <glut.h>
#else
#include <GL/glut.h>
#endif

class Point2
{
public:
	Point2(){ x = 0.0f; y = 0.0f; }
	Point2(float xx, float yy){
		x = xx;
		y = yy;
	}
	void set(float xx, float yy){
		x = xx;
		y = yy;
	}
	float getX(){
		return x;
	}
	float getY(){
		return y;
	}
	void draw(void){
		glBegin(GL_POINTS);
		glVertex2f((GLfloat)x, (GLfloat)y);
		glEnd();
	}
private:
	float x, y;
};

class IntRect
{
public:
	IntRect(){
		l = 0; r = 100; b = 0; t = 100;
	}
	IntRect(int left, int right, int bottom, int top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void set(int left, int right, int bottom, int top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void draw(void);
	int getL(){
		return l;
	}
	int getR(){
		return r;
	}
	int getB(){
		return b;
	}
	int getT(){
		return t;
	}
private:
	int l, r, b, t;
};

class RealRect
{
public:
	RealRect(){
		l = 0; r = 100; b = 0; t = 100;
	}
	RealRect(float left, float right, float bottom, float top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void set(float left, float right, float bottom, float top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void draw(void);
	float getL(){
		return l;
	}
	float getR(){
		return r;
	}
	float getB(){
		return b;
	}
	float getT(){
		return t;
	}
private:
	float l, r, b, t;
};

class Canvas {
public:
	Canvas(int width, int height, char* windowTitle); // constructor
	void setWindow(float l, float r, float b, float t);
	void setViewport(int l, int r, int b, int t);
	IntRect getViewport(void); // divulge the viewport data
	RealRect getWindow(void); // divulge the window data
	float getWindowAspectRatio(void);
	void clearScreen();
	void setBackgroundColor(float r, float g, float b);
	void setColor(float r, float g, float b);
	void lineTo(float x, float y);
	void lineTo(Point2 p);
	void moveTo(float x, float y);
	void moveTo(Point2 p);
	void moveRel(float dx, float dy);
	void lineRel(float dx, float dy);
	void turnTo(float angle);
	void turn(float angle);
	void forward(float dist, int isVisible);
	void initCT(void);
	void scale2D(double sx, double sy);
	void translate2D(double dx, double dy);
	void rotate2D(double angle);

private:
	Point2 CP; // current position in the world
	IntRect viewport; // the current window
	RealRect window; // the current viewport
	float CD;
};

Canvas::Canvas(int width, int height, char* windowTitle)
{
	char* argv[1]; // dummy argument list for glutInit()
	char dummyString[8];
	argv[0] = dummyString; // hook up the pointer
	int argc = 1; // to satisfy glutInit()
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 0);
	glutCreateWindow(windowTitle); // open the screen window
	//	setWindow(0, 100, 0, 100);
	setWindow(0, (float)width, 0, (float)height); //default world window
	setViewport(0, width, 0, height); // default viewport
	CP.set(0.0f, 0.0f); // initialize the CP to (0, 0)
}

void Canvas::moveTo(float x, float y)
{
	CP.set(x, y);
}

void Canvas::lineTo(float x, float y)
{
	glBegin(GL_LINES);
	glVertex2f((GLfloat)CP.getX(), (GLfloat)CP.getY());
	glVertex2f((GLfloat)x, (GLfloat)y); // draw the line
	glEnd();
	CP.set(x, y); // update the CP
	glFlush();
}
IntRect Canvas::getViewport(void){
	return viewport;
}
RealRect Canvas::getWindow(void){
	return window;
}
void Canvas::setWindow(float l, float r, float b, float t)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D((GLdouble)l, (GLdouble)r, (GLdouble)b, (GLdouble)t);
	window.set(l, r, b, t);
}
void Canvas::setBackgroundColor(float r, float g, float b){
	glClearColor(r, g, b, 0.0);
	//glColor3f(r, g, b);
}
void Canvas::setColor(float r, float g, float b){
	glColor3f(r, g, b);
};
void Canvas::clearScreen(){
	glClear(GL_COLOR_BUFFER_BIT);
};
void Canvas::setViewport(int left, int right, int bottom, int top)
{
	glViewport(left, bottom, right - left, top - bottom);
}

void Canvas::moveRel(float dx, float dy)
{
	CP.set(CP.getX() + dx, CP.getY() + dy);
}
void Canvas::lineRel(float dx, float dy)
{
	float x = CP.getX() + dx, y = CP.getY() + dy;
	lineTo(x, y);
	CP.set(x, y);
}
void Canvas::forward(float dist, int isVisible)
{
	const float RadPerDeg = 0.017453393; //radians per degree
	float x = CP.getX() + dist * cos(RadPerDeg * CD);
	float y = CP.getY() + dist * sin(RadPerDeg * CD);
	if (isVisible)
		lineTo(x, y);
	else
		moveTo(x, y);
}
void Canvas::turnTo(float angle) { CD = angle; }
void Canvas::turn(float angle){ CD += angle; }
void Canvas::initCT(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // set CT to the identity matrix
}
//<<<<<<<<<<<<<< scale2D >>>>>>>>>>>>>>>>>>>>
void Canvas::scale2D(double sx, double sy)
{
	glMatrixMode(GL_MODELVIEW);
	glScaled(sx, sy, 1.0); // set CT to CT * (2D scaling)
}
//<<<<<<<<<<<<<<< translate2D >>>>>>>>>>>>>>>>>
void Canvas::translate2D(double dx, double dy)
{
	glMatrixMode(GL_MODELVIEW);
	glTranslated(dx, dy, 1.0); // set CT to CT * (2D translation)
}
//<<<<<<<<<<<<<<<< rotate2D >>>>>>>>>>>>>>>>>>>>
void Canvas::rotate2D(double angle)
{
	glMatrixMode(GL_MODELVIEW);
	glRotated(angle, 0.0, 0.0, 1.0); // set CT to CT * (2D rotation)
}





