#include "stdafx.h"
#include <cmath>
#include <stdio.h>
#include <iostream>
#include "World.h"
#include "Drawer.h"
#include "ShapeFactory.h"
#include <time.h>

World w;
ShapeFactory sf(w);
Vector2d tmp;
float onRight = 0;
float onLeft = 0;
bool leftPressed = false;
int mx, my;

void Draw() {
	if (leftPressed) for (Particle &p : w.particles) {
		tmp = (Vector2d(mx, my) - p.pos);
		if (tmp * tmp < 10000)
			p.a += tmp.norm() * 100;
	}

	w.step(0.1);

	Drawer::clear();
	//Drawer::drawCircle(0, 0, i);
	for (Particle &p : w.particles) {
		Drawer::drawCircle(p.pos.x, p.pos.y, p.r);
	}
	for (Connection &c : w.connections) {
		Drawer::drawLine(c.p1->pos.x, c.p1->pos.y, c.p2->pos.x, c.p2->pos.y);
	}
	for (Connection &c : w.lenConnections) {
		if (!(c.broken))
			Drawer::drawLine(c.p1->pos.x, c.p1->pos.y, c.p2->pos.x, c.p2->pos.y);
	}
	Drawer::update();
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y) {
	mx = x, my = y;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		onLeft = clock();
		leftPressed = true;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		onLeft = clock();
		leftPressed = false;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		onRight = clock();
		sf.createGum(mx, my, 10);
	}
}

void SetXY(int x, int y) {
	mx = x, my = y;
}

int _tmain(int argc, char** argv)
{
	
	w.g.y = 10;
	
	//sf.createGum(300, 300);
	Drawer::init(argc, argv, 900, 900);
	glutDisplayFunc(Draw);
	glutMouseFunc(Mouse);
	glutMotionFunc(SetXY);
	Drawer::startLoop();
	return 0;
}

