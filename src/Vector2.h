#pragma once
#include <string>
#include "SDL.h"

class Vector2
{
public:
	float x, y;
	Vector2(float x = 0, float y = 0) : x(x), y(y) {};
	Vector2(const Vector2& rhs);

	Vector2(const SDL_FPoint& point) : Vector2(point.x, point.y) {};

	std::string ToString() const
	{
		std::string strX = std::to_string(x);
		std::string strY = std::to_string(y);

		return "V(" + strX + ", " + strY + ")";
	}

	static Vector2 FromPolar(float angleDegrees, float distance);
	static float Distance(const Vector2& a, const Vector2& b);
	static Vector2 MoveTowards(const Vector2& from, const Vector2& to, float maxDelta);

	Vector2 operator+(const Vector2& rhs) const;
	Vector2 operator-(const Vector2& rhs) const;
	Vector2 operator-() const;

	Vector2 operator*(const float& rhs) const;
	Vector2 operator/(const float& rhs) const;

	Vector2& operator+=(const Vector2& rhs);
	Vector2& operator-=(const Vector2& rhs);
	Vector2& operator*=(const float& rhs);
	Vector2& operator/=(const float& rhs);

	float Magnitude();
	Vector2& Normalize();
	Vector2 Normalized();

	bool operator==(const Vector2& rhs) const;
	bool operator!=(const Vector2& rhs) const;

	Vector2& operator=(Vector2 rhs);

	friend void swap(Vector2& a, Vector2& b) noexcept;

	SDL_FPoint ToFPoint();
	SDL_FRect ToRenderRect(int width, int height);

	static Vector2 zero;
	static Vector2 up;
	static Vector2 down;
	static Vector2 left;
	static Vector2 right;
};

