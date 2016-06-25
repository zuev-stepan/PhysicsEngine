#ifndef PARTICLE
#define PARTICLE

#include "Rect.h"
#include "Vector2d.h"

class Particle {
public:
	float m, r;
	int mask;
	Vector2d pos;
	Vector2d prev;
	Vector2d a;
	Vector2d f;

	Particle() : m(1), r(3), mask(1) {}
	Particle(Vector2d pos) : m(1), r(3), mask(1), pos(pos), prev(pos) {}
	Particle(Vector2d pos, float r) : m(1), r(r), mask(1), pos(pos), prev(pos) {}
	Particle(Vector2d pos, float m, float r, int mask) : m(m), r(r), mask(mask), pos(pos), prev(pos) {}
	Particle(float x, float y, float m, float r, int mask) : m(m), r(r), mask(mask), pos(x, y), prev(x, y)  {}
	Rect getBox() {
		return Rect(pos.x - r, pos.y - r, pos.x + r, pos.y + r);
	}
};
#endif PARTICLE
