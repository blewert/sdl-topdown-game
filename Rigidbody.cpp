#include "Rigidbody.h"
#include "GameObject.h"
#include "Time.h"
#include "Math.h"

Rigidbody::Rigidbody(GameObject* parent) : Component(parent)
{
    //Set defaults
    this->SetVelocity(Vector2(0, 0));
    this->dragFactor = 0;
    this->isStatic = false;
    this->isKinematic = false;
}

Rigidbody::~Rigidbody()
{
    SDL_Log("Rigidbody dtor");
}

void Rigidbody::Update()
{
    if (!isStatic)
    {
        Vector2 newPos = this->parent->GetPosition();
        Vector2 dragForce = (-velocity.Normalized() * dragFactor);

        //Calculate new pos via euler integration
        newPos += (velocity + dragForce) * Time::deltaTime;

        //Set new pos
        this->parent->SetPosition(newPos);
    }
}

void Rigidbody::SetVelocity(const Vector2& velocity)
{
    this->velocity = velocity;
}

void Rigidbody::SetStatic(const bool status)
{
    this->isStatic = status;
}

void Rigidbody::SetKinematic(const bool status)
{
    this->isKinematic = status;
}

inline Vector2 Rigidbody::GetVelocity() const
{
    return velocity;
}

inline bool Rigidbody::IsStatic() const
{
    return isStatic;
}

inline bool Rigidbody::IsKinematic() const
{
    return isKinematic;
}

bool Rigidbody::IsCollidingAABB(Rigidbody& a, Rigidbody& b)
{
    SDL_Rect aBounds = a.parent->renderer->GetBounds();
    SDL_Rect bBounds = b.parent->renderer->GetBounds();

    return Collision::AABB(aBounds, bBounds);
}
