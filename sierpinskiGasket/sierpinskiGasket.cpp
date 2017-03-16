#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include <glut.h>
#else
#include <GL/glut.h>
#endif


void myInit(void){

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);

}

void myDisplay(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	glFlush();
}

class GLintPoint{
public:
	GLint x, y;
};
void drawDot(int x, int y){
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

int random(int m){
	return rand() % m;
}
void Sierpinski(GLintPoint *corners){
	GLintPoint T[3];
	for (int i = 0; i < 3; i++){
		T[i] = corners[i];
	}
	int index = random(3);
	GLintPoint point = T[index];
	drawDot(point.x, point.y);
	for (int i = 0; i < 1000; i++)
	{
		index = random(3);
		if (index == 0)
			glColor3f(1.0, 0.0, 0.0);
		else if (index == 1)
			glColor3f(0.0, 1.0, 0.0);
		else
			glColor3f(0.0, 0.0, 1.0);
		point.x = (point.x + T[index].x) / 2;
		point.y = (point.y + T[index].y) / 2;
		drawDot(point.x, point.y);
		glFlush();
	}

}
void myMouse(int button, int state, int x, int y)
{
	glClear(GL_COLOR_BUFFER_BIT);
	int screenHeight = 480;
	static GLintPoint corners[3];
	static int numCorners = 0;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		corners[numCorners].x = x;
		corners[numCorners].y = screenHeight - y;
		if (++numCorners == 3){
			Sierpinski(corners);
			numCorners = 0;
		}
	}
}
int main(int argc, char** agrv){
	glutInit(&argc, agrv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("MY FIRST ATTEMPT");
	glutDisplayFunc(myDisplay);
	glutMouseFunc(myMouse);
	myInit();
	glutMainLoop();
}

