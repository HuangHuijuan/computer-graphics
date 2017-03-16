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
	glFlush();
}
class GLintPoint{
public:
	GLint x, y;
};
void checkerboard(GLintPoint *corner){
	int x1 = corner[0].x;
	int y1 = corner[0].y;
	int x2 = corner[1].x;
	int y2 = corner[1].y;

	int width = (x2 - x1) / 8;
	int height = (y2 - y1) / 8;

	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			if ((i + j) % 2 == 0)
				glColor3f(0.6, 0.6, 0.6);
			else
				glColor3f(0.2, 0.2, 0.2);
			glRecti(x1 + i*width, y1 + j*height, x1 + (i + 1)*width, y1 + (j + 1)*height);
			glFlush();
		}
	}

}
/*
void checkerboard(int x, int y, int size){

for (int i = 0; i < 8; i++){
for (int j = 0; j < 8; j++){
if ((i + j) % 2 == 0)
glColor3f(0.6, 0.6, 0.6);
else
glColor3f(0.2, 0.2, 0.2);
glRecti(x + i*size, y + j*size, x + (i + 1)*size, y + (j + 1)*size);
glFlush();
}
}

}
*/
void myMouse(int button, int state, int x, int y)
{
	glClear(GL_COLOR_BUFFER_BIT);
	int screenHeight = 480;
	static GLintPoint corners[2];
	static int numCorners = 0;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){

		/*	checkerboard(x,480-y,20);*/

		corners[numCorners].x = x;
		corners[numCorners].y = screenHeight - y;
		if (++numCorners == 2){
			checkerboard(corners);
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

