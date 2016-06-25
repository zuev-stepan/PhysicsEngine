#ifndef RECT_H
#define RECT_H
class Rect {
public:
	float x1, y1, x2, y2;
	Rect(){}
	Rect(float a, float b, float c, float d) {
		x1 = a;
		x2 = c;
		y1 = b;
		y2 = d;
	}

	bool inside(Rect &r) {
		return r.x1 >= x1 && r.x2 <= x2 && r.y1 >= y1 && r.y2 <= y2;
	}
	bool dontTouch(Rect &r) {
		return (r.x2 < x1 || r.x1 > x2 || r.y2 < y1 || r.y1 > y2);
	}
};

#endif RECT_H
