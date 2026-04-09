#include "Vector2.h"
#include "Math.h"
#include "Time.h"
#include <memory>

Vector2 Vector2::zero = Vector2(0, 0);
Vector2 Vector2::up = Vector2(0, 1);
Vector2 Vector2::down = Vector2(0, -1);
Vector2 Vector2::left = Vector2(-1, 0);
Vector2 Vector2::right = Vector2(1, 0);

Vector2::Vector2(const Vector2& rhs)
{
    this->x = rhs.x;
    this->y = rhs.y;
}

Vector2 Vector2::FromPolar(float angleDegrees, float distance)
{
    float x = SDL_cosf(angleDegrees * Math::degToRad) * distance;
    float y = SDL_sinf(angleDegrees * Math::degToRad) * distance;

    return Vector2(x, y);
}

float Vector2::Distance(const Vector2& a, const Vector2& b)
{
    return (b - a).Magnitude();
}

Vector2 Vector2::MoveTowards(const Vector2& from, const Vector2& to, float maxDelta)
{
    maxDelta *= Time::deltaTime;

    float xLerped = Math::MoveTowards(from.x, to.y, maxDelta);
    float yLerped = Math::MoveTowards(from.x, to.y, maxDelta);

    return Vector2(xLerped, yLerped);
}

Vector2 Vector2::operator+(const Vector2& rhs) const
{
    return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
    return Vector2(x - rhs.x, y - rhs.y);
}

Vector2 Vector2::operator-() const
{
    return Vector2(-x, -y);
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

float Vector2::Magnitude()
{
    return sqrtf(powf(x, 2) + powf(y, 2));
}

Vector2& Vector2::Normalize()
{
    float mag = Magnitude();

    if (Math::Approximately(mag, 0))
        return *this;

    this->x /= mag;
    this->y /= mag;

    return *this;
}

Vector2 Vector2::Normalized()
{
    Vector2 tmp(*this);
    return tmp.Normalize();
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

void swap(Vector2& a, Vector2& b) noexcept
{
    using std::swap;
    swap(a.x, b.x);
    swap(a.y, b.y);
}

Vector2& Vector2::operator=(Vector2 rhs)
{
    //The same thing? If so, don't change
    if (&rhs == this)
        return *this;

    Vector2 tmp(rhs);
    swap(*this, rhs);
    return *this;
}

SDL_FPoint Vector2::ToFPoint()
{
    return SDL_FPoint{ x = this->x, y = this->y };
}

SDL_Rect Vector2::ToRenderRect(int width, int height)
{
    return SDL_Rect{ (int)x, (int)y, width, height };
}


