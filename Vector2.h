#pragma once
#include <string>

class Vector2
{
public:
	float x, y;

	Vector2(float x = 0, float y = 0) : x(x), y(y) { }

	std::string ToString() const
	{
		std::string strX = std::to_string(x);
		std::string strY = std::to_string(y);

		return "V(" + strX + ", " + strY + ")";
	}

	static Vector2 zero;
	static Vector2 up;
	static Vector2 down;
	static Vector2 left;
	static Vector2 right;
};

