#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <cmath>
#include <algorithm>
#include <stdlib.h>

using std::swap;
using std::min;
using std::max;

class Vector2d {
public:
	float x, y;
	Vector2d() : x(0), y(0) {
	}
	Vector2d(float x, float y) : x(x), y(y) {
	}
	Vector2d operator +(Vector2d b) {
		return Vector2d(x + b.x, y + b.y);
	}
	Vector2d operator -(Vector2d b) {
		return Vector2d(x - b.x, y - b.y);
	}
	float operator *(Vector2d b) {
		return x * b.x + y * b.y;
	}
	Vector2d operator *(float b) {
		return Vector2d(x * b, y * b);
	}
	Vector2d operator /(float b) {
		return Vector2d(x / b, y / b);
	}
	void operator =(Vector2d b) {
		x = b.x;
		y = b.y;
	}
	void operator +=(Vector2d b) {
		x += b.x; y += b.y;
	}
	void operator -=(Vector2d b) {
		x -= b.x; y -= b.y;
	}
	void operator *=(float b) {
		x *= b; y *= b;
	}

	
	float len() {
		return (float) sqrt(x * x + y * y);
	}
	Vector2d norm() {
		float tmp = len();
		if (tmp == 0)
			return *this;
		return Vector2d(x / tmp, y / tmp);
	}
	static int ptToLine(Vector2d &t1, Vector2d &t2, Vector2d &p, Vector2d &p0) {
		Vector2d v1 = p - t1;
		Vector2d v2 = t2 - t1;
		Vector2d tmp = t1 + (v2 * ((v1 * v2) / (v2 * v2)));
		p0.x = tmp.x; p0.y = tmp.y;
		if ((v1 * v2 >= 0.0f) && ((v1 * v1)) / (v2 * v2) <= 1.0f)
			return 1;
		else
			return 0;
	}

	static bool int1(float a, float b, float c, float d) {
		float tmp;
		if (a > b)  { swap(a, b); }
		if (c > d)  { swap(c, d); }
		return max(a, c) <= min(b, d);
	}

	static bool intRect(Vector2d &r11, Vector2d &r12, Vector2d &r21, Vector2d &r22) {
		return int1(r11.x, r12.x, r21.x, r22.x) && int1(r11.y, r12.y, r21.y, r22.y);
	}

	static Vector2d minV(Vector2d &a, Vector2d &b) {
		return Vector2d(min(a.x, b.x), min(a.y, b.y));
	}
	static Vector2d maxV(Vector2d &a, Vector2d &b) {
		return Vector2d(max(a.x, b.x), max(a.y, b.y));
	}
	static Vector2d minV(Vector2d &a, Vector2d &b, float r) {
		return Vector2d(min(a.x, b.x - r), min(a.y, b.y - r));
	}
	static Vector2d maxV(Vector2d &a, Vector2d &b, float r) {
		return Vector2d(max(a.x, b.x + r), max(a.y, b.y + r));
	}

	static Vector2d convert(Vector2d &source, Vector2d &x) {
		//float n = (source.x * x.y - source.y * x.x);// / source.len2(); //(== 1 when .norm())
		//float k = (source.y * x.y + source.x * x.x);// / source.len2();
		//float n = source.x * x.y - source.y *
		float n = (source.y * x.x - source.x * x.y);// / source.len2(); //(== 1 when .norm())
		float k = (source.y * x.y + source.x * x.x);// / source.len2();
		return Vector2d(k, n);
	}

	static Vector2d back(Vector2d &source, Vector2d &x) {
		return Vector2d(source.x * x.x - source.y * x.y, source.x * x.y + source.y * x.x);
	}
};
#endif VECTOR2D_H
