#ifndef WORLD_H
#define WORLD_H
#include <list>
#include "Vector2d.h"
#include "Connection.h"
#include "Particle.h"
#include "Pin.h"
#include "QuadTree.h"

using std::list;
class ShapeFactory;
class World {
public:
	list<Particle> particles;
	list<Connection> connections;
	list<Connection> lenConnections;
	list<Pin> pins;
	Vector2d g, border1, border2, tmp;
	bool collision = false;
	QuadTree* qt = new QuadTree(Rect(0, 0, 1000, 1000));

	int iter = 2;
	float dt = 1;

	World() {
		border1 = Vector2d(0, 0);
		border2 = Vector2d(900, 900);
	}


	void step(float dt) {
		//applyForces();
		(*this).dt = dt;
		collision = false;
		moveBodies();
		for (int i = 0; i < iter; i++) {
			solveConnections();
			solveCollisions();
		}
		applyForces();
	}

	void buildTree() {
		qt->clear();
		for (Particle &p : particles) {
			if (p.r > 1e-6)
				qt->insert(&p);
		}
		for (Connection &c : connections) {
			if (c.p1->r + c.p2->r > 1e-6)
				qt->insert(&c);
		}
	}

	void applyForces() {
		for(Particle &p : particles) {
			p.a = g;
		}
	}

	void moveBodies() {
		for (Particle &p : particles) {
			Vector2d v = p.pos - p.prev + p.a * (dt * dt);
			p.prev = p.pos;
			p.pos += v;
		}
	}

	void solveConnections() {
		for (Pin &pin : pins) {
			pin.p->pos = pin.pos;
		}
		for (Connection &connection : connections) {
			Vector2d normal = connection.p1->pos - connection.p2->pos;
			normal *= ((connection.l * connection.l / (normal * normal + connection.l * connection.l) - 0.5f) * connection.s);
			connection.p1->pos += normal;
			connection.p2->pos -= normal;
		}
		for (Connection &connection : lenConnections) {
			Vector2d normal = connection.p1->pos - connection.p2->pos;
			connection.broken |= (normal * normal) / sqr(connection.l) > 6;
			if (connection.broken)
				continue;
			normal *= ((connection.l * connection.l / (normal * normal + connection.l * connection.l) - 0.5f) * connection.s);
			connection.p1->pos += normal;
			connection.p2->pos -= normal;
		}
	}

	void check(Particle *p, QuadTree *t) {
		if (t->b.dontTouch(p->getBox()))
			return;
		for (Connection* &c : t->c) {
			solveConnection(p, c);
		}
		for (Particle* &p1 : t->p) {
			solveParticle(p, p1);
		}
		if (t->lt != NULL) {
			check(p, t->lt);
			check(p, t->rt);
			check(p, t->lb);
			check(p, t->rb);
		}
	}

	void solveCollisions() {
		for (Particle &particle : particles) {
			particle.pos = Vector2d::maxV(Vector2d::minV(particle.pos, border2, particle.r), border1, particle.r);
		}
		buildTree();
		for (Particle &p : particles) {
			check(&p, qt);
		}
	}

	bool solveConnection(Particle* &p, Connection* &c) {
		if (p == c->p1 || p == c->p2)
			return false;
		if ((p->mask & c->mask) == 0)
			return false;
		float r = p->r + c->r;
		if (r < 1e-9)
			return false;
		int x = Vector2d::ptToLine(c->p1->pos, c->p2->pos, p->pos, tmp);
		if (x == 0) {
			return false;
		}
		else {
			Vector2d add = p->pos - tmp;
			if (add * add > r * r)
				return false;
			float dl = r - add.len();
			add = add.norm() * (dl / 2);
			//p.prev = p.pos;
			p->pos += add;
			float f = (c->p1->pos - tmp).len() / c->l;
			//p1.prev = p1.pos;
			c->p1->pos -= (add * (1 - f));
			//p2.prev = p2.pos;
			c->p2->pos -= (add * f);
			return true;
		}
	}

	bool solveParticle(Particle* &p1, Particle* &p2) {
		float r = p1->r + p2->r;
		if (r < 1e-9)
			return false;
		if ((p1->pos - p2->pos) * (p1->pos - p2->pos) > r * r)
			return false;
		if ((p1->mask & p2->mask) == 0)
			return false;

		Vector2d add = p1->pos - p2->pos;
		add *= (r * r / (add * add + r * r) - 0.5f);
		p1->pos += add;
		p2->pos -= add;

		return true;
	}

	float sqr(float x) {
		return x * x;
	}

	Connection* createConnection(Particle* a, Particle* b) {
		connections.push_back(Connection(a, b, (a->pos - b->pos).len()));
		return &connections.back();
	}
	Connection* createConnection(Particle* a, Particle* b, float len) {
		connections.push_back(Connection(a, b, len));
		return &connections.back();
	}
	Connection* createConnection(Particle* a, Particle* b, float len, float s) {
		connections.push_back(Connection(a, b, len, s));
		return &connections.back();
	}
	Connection* createLenConnection(Particle* a, Particle* b) {
		lenConnections.push_back(Connection(a, b, (a->pos - b->pos).len()));
		return &lenConnections.back();
	}
	Connection* createLenConnection(Particle* a, Particle* b, float len) {
		lenConnections.push_back(Connection(a, b, len));
		return &lenConnections.back();
	}

	Connection* createLenConnection(Particle* a, Particle* b, float len, float s) {
		lenConnections.push_back(Connection(a, b, len, s));
		return &lenConnections.back();
	}
	Particle* createParticle(float x, float y) {
		particles.push_back(Particle(Vector2d(x, y)));
		return &particles.back();
	}
	Particle* createParticle(float x, float y, float r) {
		particles.push_back(Particle(x, y, 1, r, 1));
		return &particles.back();
	}
	Particle* createParticle(float x, float y, float m, float r) {
		particles.push_back(Particle(x, y, m, r, 1));
		return &particles.back();
	}
	Particle* createParticle(float x, float y, float m, float r, int mask) {
		particles.push_back(Particle(x, y, m, r, mask));
		return &particles.back();
	}
	Pin* createPin(Particle *p, float x, float y) {
		pins.push_back(Pin(p, x, y));
		return &pins.back();
	}

};

#endif WORLD_H
