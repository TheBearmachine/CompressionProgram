#include "Vector2.h"
#include <cmath>

Vector2::Vector2() :
	x(0.0f), y(0.0f)
{
}

Vector2::Vector2(float x, float y) :
	x(x), y(y)
{
}

Vector2::Vector2(const Vector2 & v) :
	x(v.x), y(v.y)
{
}

std::string Vector2::toString() const
{
	std::string str = "X: " + std::to_string(x) + ", Y: " + std::to_string(y);
	return str;
}

float Vector2::magnitude() const
{
	return std::sqrtf(magnitudeSquared());
}

float Vector2::magnitudeSquared() const
{
	return (pow(x, 2) + pow(y, 2));
}

void Vector2::normalize()
{
	float m = magnitude();
	if (m < 0.01) return; // Cannot divide by zero
	x = x / m;
	y = y / m;
}

Vector2 Vector2::normalize(const Vector2 & v)
{
	float m = v.magnitude();
	if (m < 0.01) return Vector2(); // Cannot divide by zero
	Vector2 newVec = v;
	newVec.x /= m;
	newVec.y /= m;

	return newVec;
}

float Vector2::dotProduct(const Vector2 & v)
{
	return (x * v.x + y* v.y);
}

float Vector2::dotProduct(const Vector2 & v1, const Vector2 & v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

float Vector2::angleBetweenVectors(const Vector2 & v1, const Vector2 & v2)
{
	float l1 = v1.magnitude(), l2 = v2.magnitude();
	return acosf(dotProduct(v1, v2) / (l1*l2));
}

Vector2 Vector2::project(const Vector2 & v)
{
	if (v == Vector2(0.0f, 0.0f))return Vector2(0.0f, 0.0f);
	Vector2 newVec = v;
	newVec = newVec * (dotProduct(newVec) / newVec.magnitudeSquared());
	return newVec;
}

Vector2 operator+(const Vector2 &v1, const Vector2 &v2)
{
	return Vector2(v1.x + v2.x, v1.y + v2.y);
}

Vector2& operator+=(Vector2 &v1, const Vector2 &v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	return v1;
}

Vector2 operator-(const Vector2 &v1, const Vector2 &v2)
{
	return Vector2(v1.x - v2.x, v1.y - v2.y);
}

Vector2& operator-=(Vector2 &v1, const Vector2 &v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	return v1;
}

Vector2 operator*(const Vector2 &v, const float &f)
{
	return Vector2(v.x * f, v.y * f);
}

Vector2& operator*=(Vector2 &v, const float &f)
{
	v.x *= f;
	v.y *= f;
	return v;
}

Vector2 operator/(const Vector2 &v, const float &f)
{
	if (f == 0.0f) return Vector2();
	return Vector2(v.x / f, v.y / f);
}

Vector2& operator/=(Vector2 &v, const float &f)
{
	if (f == 0.0f) return v;
	v.x /= f;
	v.y /= f;
	return v;
}

bool operator!=(const Vector2 & v1, const Vector2 & v2)
{
	return (v1.x != v2.x || v1.y != v2.y);
}

bool operator==(const Vector2 & v1, const Vector2 & v2)
{
	return (v1.x == v2.x && v1.y == v2.y);
}
