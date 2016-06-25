#ifndef DRAWER_H
#define DRAWER_H

#include <glut.h>
#include <cmath>

const float pi = 3.1415926535897932;
const float cosX[] = {
	1.000000,
	0.923880,
	0.707107,
	0.382683,
	- 0.000000,
	- 0.382684,
	- 0.707107,
	- 0.923880,
	- 1.000000,
	- 0.923880,
	- 0.707107,
	- 0.382683,
	0.000000,
	0.382684,
	0.707107,
	0.923880
};
const float sinX[] = {
	0.000000,
	0.382683,
	0.707107,
	0.923880,
	1.000000,
	0.923880,
	0.707107,
	0.382683,
	-0.000000,
	-0.382683,
	-0.707107,
	-0.923880,
	-1.000000,
	-0.923879,
	-0.707107,
	-0.382683
};

class Drawer {
public:
	static void init(int argc, char** argv, int width, int height) {
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
		glutInitWindowSize(width, height);
		glutInitWindowPosition(100, 100);
		glutCreateWindow("322");

		glClearColor(0, 0, 0, 1);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, width, -height, 0, -1, 1);
	}

	static void startLoop() {
		glutMainLoop();
	}


	static void clear() {
		glClear(GL_COLOR_BUFFER_BIT);
	}
	static void drawLine(float x1, float y1, float x2, float y2) {
		glBegin(GL_LINES);
		glVertex2f(x1, -y1);
		glVertex2f(x2, -y2);
		glEnd();
	}
	static void drawCircle(float x, float y, float r) {
		glBegin(GL_POLYGON);
		for (int i = 0; i < 16; i++) {
			glVertex2f(r * cosX[i] + x, -r * sinX[i] - y);
		}
		glEnd();
	}
	static void update() {
		glutSwapBuffers();
	}
};

#endif DRAWER_H