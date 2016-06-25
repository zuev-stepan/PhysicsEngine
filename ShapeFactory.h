#ifndef SHAPEFACTORY
#define SHAPEFACTORY

#include "World.h"

class ShapeFactory {
public:
	World* w;
	ShapeFactory(World &world) {
		w = &world;
	}

	void createRagdoll(float x, float y) {
		Particle* head = w->createParticle(x, y, 20);
		Particle* neck = w->createParticle(x, y + 35, 10);
		Particle* lh1 = w->createParticle(x - 30, y + 35, 10);
		Particle* lh2 = w->createParticle(x - 60, y + 35, 10);
		Particle* rh1 = w->createParticle(x + 30, y + 35, 10);
		Particle* rh2 = w->createParticle(x + 60, y + 35, 10);
		Particle* ass = w->createParticle(x, y + 95, 10);
		Particle* ll1 = w->createParticle(x - 30, y + 120, 10);
		Particle* ll2 = w->createParticle(x - 60, y + 145, 10);
		Particle* rl1 = w->createParticle(x + 30, y + 120, 10);
		Particle* rl2 = w->createParticle(x + 60, y + 145, 10);

		w->createConnection(head, neck);
		w->createConnection(neck, lh1);
		w->createConnection(lh1, lh2);
		w->createConnection(neck, rh1);
		w->createConnection(rh1, rh2);
		w->createConnection(neck, ass);
		w->createConnection(ass, ll1);
		w->createConnection(ll1, ll2);
		w->createConnection(ass, rl1);
		w->createConnection(rl1, rl2);

		w->createLenConnection(neck, lh2);
		w->createLenConnection(neck, rh2);
		w->createLenConnection(ass, ll2);
		w->createLenConnection(ass, rl2);
		w->createLenConnection(neck, ll1);
		w->createLenConnection(neck, rl1);
		w->createLenConnection(ass, lh1);
		w->createLenConnection(ass, rh1);
	}

	void createTriangle(float x, float y) {
		Particle* p1 = w->createParticle(x, y, 10);
		Particle* p2 = w->createParticle(x + 30, y + 50, 10);
		Particle* p3 = w->createParticle(x - 30, y + 50, 10);

		w->createConnection(p1, p2);
		w->createConnection(p2, p3);
		w->createConnection(p3, p1);
	}

	void createCube(float x, float y) {
		Particle* p1 = w->createParticle(x - 50, y - 50, 10);
		Particle* p2 = w->createParticle(x + 50, y - 50, 10);
		Particle* p3 = w->createParticle(x + 50, y + 50, 10);
		Particle* p4 = w->createParticle(x - 50, y + 50, 10);

		w->createConnection(p1, p2);
		w->createConnection(p2, p3);
		w->createConnection(p3, p4);
		w->createConnection(p4, p1);

		w->createLenConnection(p1, p3);
		w->createLenConnection(p2, p4);
	}

	void createGum(float x, float y, int h) {
		Particle* p[100][100];
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < h; j++) {
				p[i][j] = w->createParticle(x + j * 30, y + i * 30, 10);
				if (j > 0)
					w->createLenConnection(p[i][j], p[i][j - 1]);
				if (i > 0)
					w->createLenConnection(p[i][j], p[i - 1][j]);
				if (i > 0 && j > 0)
					w->createLenConnection(p[i][j], p[i - 1][j - 1]);
			}
		}
	}
	void createCloth(float x, float y, int h) {
		Particle* p[100][100];
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < h; j++) {
				p[i][j] = w->createParticle(x + j * 30, y + i * 30, 1);
				p[i][j]->mask = 0;
				if (j > 0)
					w->createLenConnection(p[i][j], p[i][j - 1])->s = 0.002;
				if (i > 0)
					w->createLenConnection(p[i][j], p[i - 1][j])->s = 0.002;
			}
		}
		for (int i = 0; i < h; i++)
			w->createPin(p[0][i], x + i * 30, y);
	}
	void createGish(float x, float y) {
		Particle* p[50];
		float r = 100;
		for (int i = 0; i < 50; i++) {
			p[i] = w->createParticle(x + r * cos(pi / 25 * i), y + r * sin(pi / 25 * i));
			if (i > 0)
				w->createConnection(p[i], p[i - 1]);
			if (i == 49)
				w->createConnection(p[i], p[0]);
		}
		for (int i = 0; i < 25; i++)
			w->createLenConnection(p[i], p[i + 25], (p[i]->pos - p[i + 25]->pos).len(), 0.0002);
	} 
};

#endif SHAPEFACTORY