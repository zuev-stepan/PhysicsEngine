#include <vector>

using std::vector;

class QuadTree {
public:
	int capacity = 4;
	Rect b;
	QuadTree *lt, *rt, *lb, *rb;
	vector<Particle*> p;
	vector<Connection*> c;
	QuadTree(){ lt = rt = lb = rb = NULL; }
	QuadTree(Rect br) {
		lt = rt = lb = rb = NULL;
		b = br;
	}
	
	bool insert(Particle* x) {
		if (!b.inside(x->getBox())) {
			return false;
		}
		if (p.size() + c.size() < capacity) {
			p.push_back(x);
			return true;
		}
		if (!lt) {
			divide();
		}
		if (lt->insert(x)) return true;
		if (rt->insert(x)) return true;
		if (lb->insert(x)) return true;
		if (rb->insert(x)) return true;
		p.push_back(x);
		return true;
	}

	bool insert(Connection* x) {
		if (!b.inside(x->getBox())) {
			return false;
		}
		if (p.size() + c.size() < capacity) {
			c.push_back(x);
			return true;
		}
		if (!lt) {
			divide();
		}
		if (lt->insert(x)) return true;
		if (rt->insert(x)) return true;
		if (lb->insert(x)) return true;
		if (rb->insert(x)) return true;
		c.push_back(x);
		return true;
	}

	void divide() {
		lt = new QuadTree(Rect(b.x1, b.y1, (b.x1 + b.x2) / 2, (b.y1 + b.y2) / 2));
		rt = new QuadTree(Rect((b.x1 + b.x2) / 2, b.y1, b.x2, (b.y1 + b.y2) / 2));
		lb = new QuadTree(Rect(b.x1, (b.y1 + b.y2) / 2, (b.x1 + b.x2) / 2, b.y2));
		rb = new QuadTree(Rect((b.x1 + b.x2) / 2, (b.y1 + b.y2) / 2, b.x2, b.y2));
	}

	void clear() {
		p.clear();
		c.clear();
		if (lt) {
			lt->clear();
			rt->clear();
			lb->clear();
			rb->clear();
		}
	}
};
