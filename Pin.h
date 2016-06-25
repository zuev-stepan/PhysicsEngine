#include "Rect.h"
#include "Particle.h"
#include <algorithm>

using std::min;
using std::max;

class Pin {
public:
	Particle *p;
	Vector2d pos;

	Pin() {}
	Pin(Particle* a, float x, float y) : p(a), pos(x, y) {}
	Pin(Particle* a, Vector2d p) : p(a), pos(p)  {}

	
};
