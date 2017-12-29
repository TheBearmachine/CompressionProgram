#pragma once
#include <string>

// A 2D representation of a vector
class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	Vector2(const Vector2 &v);

	std::string toString() const;

	float magnitude() const;
	float magnitudeSquared() const;
	void normalize();
	static Vector2 normalize(const Vector2 &v);
	float dotProduct(const Vector2 &v);
	static float dotProduct(const Vector2 &v1, const Vector2 &v2);

	static float angleBetweenVectors(const Vector2 &v1, const Vector2 &v2);

	Vector2 project(const Vector2 &v);


	float x, y;
};
Vector2 operator+(const Vector2 &v1, const Vector2 &v2);
Vector2& operator+=(Vector2 &v1, const Vector2 &v2);

Vector2 operator-(const Vector2 &v1, const Vector2 &v2);
Vector2& operator-=(Vector2 &v1, const Vector2 &v2);

Vector2 operator*(const Vector2 &v, const float &f);
Vector2& operator*=(Vector2 &v, const float &f);

Vector2 operator/(const Vector2 &v, const float &f);
Vector2& operator/=(Vector2 &v, const float &f);

bool operator!=(const Vector2 &v1, const Vector2 &v2);
bool operator==(const Vector2 &v1, const Vector2 &v2);
