#include "Rect.h"
#include "Particle.h"
#include <algorithm>

using std::min;
using std::max;

class Connection {
public:
	Particle *p1, *p2;
	int mask;
	float l, s, r;
	bool broken = false;

	Connection() {}
	Connection(Particle* a, Particle* b, float l) : mask(1), p1(a), p2(b), l(l), s(0.05), r(1) {}
	Connection(Particle* a, Particle* b, float l, float s) : mask(1), p1(a), p2(b), l(l), s(s), r(1)  {}

	Rect getBox() {
		float x1 = min(p1->pos.x - p1->r, p2->pos.x - p2->r);
		float y1 = min(p1->pos.y - p1->r, p2->pos.y - p2->r);
		float x2 = max(p1->pos.x + p1->r, p2->pos.x + p2->r);
		float y2 = max(p1->pos.y + p1->r, p2->pos.y + p2->r);
		return Rect(x1, y1, x2, y2);
	}
};
