#include "Vector2.h"
#include "Math.h"

Vector2 Vector2::zero = Vector2(0, 0);
Vector2 Vector2::up = Vector2(0, 1);
Vector2 Vector2::down = Vector2(0, -1);
Vector2 Vector2::left = Vector2(-1, 0);
Vector2 Vector2::right = Vector2(1, 0);

Vector2::Vector2(const Vector2& rhs)
{
}

Vector2 Vector2::operator+(const Vector2& rhs) const
{
    return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
    return Vector2(x - rhs.x, y - rhs.y);
}

Vector2 Vector2::operator*(const float& rhs) const
{
    return Vector2(x * rhs, y * rhs);
}

Vector2 Vector2::operator/(const float& rhs) const
{
    if (Math::Approximately(rhs, 0))
        return Vector2::zero;

    return Vector2(x / rhs, y / rhs);
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
    this->x += rhs.x;
    this->y += rhs.y;

    return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
    this->x -= rhs.x;
    this->y -= rhs.y;
    
    return *this;
}

Vector2& Vector2::operator*=(const float& rhs)
{
    this->x *= rhs;
    this->y *= rhs;

    return *this;
}

Vector2& Vector2::operator/=(const float& rhs)
{
    if (Math::Approximately(rhs, 0))
        return Vector2::zero;

    this->x /= rhs;
    this->y /= rhs;

    return *this;
}

bool Vector2::operator==(const Vector2& rhs) const
{
    bool xEqual = Math::Approximately(this->x, rhs.x);
    bool yEqual = Math::Approximately(this->y, rhs.y);

    return xEqual && yEqual;
}

bool Vector2::operator!=(const Vector2& rhs) const
{
    return !(*this == rhs);
}

Vector2& Vector2::operator=(const Vector2& rhs)
{
    //The same thing? If so, don't change
    if (&rhs == this)
        return *this;

    //Otherwise copy and swap
    Vector2 tmp(*this);
    tmp.x = rhs.x;
    tmp.y = rhs.y;
    std::swap(*this, tmp);
}

SDL_FPoint Vector2::ToFPoint()
{
    return SDL_FPoint{ x = this->x, y = this->y };
}

SDL_Rect Vector2::ToRect(int width, int height)
{
    return SDL_Rect{ (int)x, (int)y, width, height };
}
