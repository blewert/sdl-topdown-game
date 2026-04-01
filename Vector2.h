#pragma once
#include <string>
#include "SDL.h"

class Vector2
{
public:
	float x, y;

	Vector2(float x = 0, float y = 0) : x(x), y(y) { }
	Vector2(const Vector2& rhs);

	std::string ToString() const
	{
		std::string strX = std::to_string(x);
		std::string strY = std::to_string(y);

		return "V(" + strX + ", " + strY + ")";
	}

	Vector2 operator+(const Vector2& rhs) const;
	Vector2 operator-(const Vector2& rhs) const;

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

	Vector2& operator=(const Vector2& rhs);

	SDL_FPoint ToFPoint();
	SDL_Rect ToRenderRect(int width, int height);

	static Vector2 zero;
	static Vector2 up;
	static Vector2 down;
	static Vector2 left;
	static Vector2 right;
};

