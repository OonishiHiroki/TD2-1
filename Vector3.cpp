#include "Vector3.h"
#include <cmath>

float Vector3::length()const {
	return sqrt(x * x) + (y * y) + (z * z);
}

Vector3& Vector3::normalize() {
	float len = length();
	if (len != 0) {
		return *this /= length();
	}
	return *this;
}

Vector3 Vector3::cross(const Vector3& v)const {
	Vector3 ans;

	ans = { (y * v.z) - (z * v.y),(z * v.x) - (x * v.z), (x * v.y) - (y * v.x) };

	return ans;
}



// Vector2 ƒNƒ‰ƒX‚É‘®‚³‚È‚¢ŠÖ”ŒQ
// 2€‰‰Zq
const Vector3 operator+(const Vector3& v1, const Vector3& v2) {
	Vector3 temp(v1);
	return temp += v2;
}

const Vector3 operator-(const Vector3& v1, const Vector3& v2) {
	Vector3 temp(v1);
	return temp -= v2;
}

const Vector3 operator*(const Vector3& v, float s) {
	Vector3 temp(v);
	return temp *= s;
}

const Vector3 operator*(float s, const Vector3& v) { return v * s; }

const Vector3 operator/(const Vector3& v, float s) {
	Vector3 temp(v);
	return temp /= s;
}
