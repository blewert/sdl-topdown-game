#include "Rigidbody.h"
#include "GameObject.h"
#include "Time.h"
#include "Math.h"
#include "InputManager.h"

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
        Vector2 movement = InputManager::Instance().Find2DAxisByName("WASD")->GetValueInvertedY();
        
        if(movement != Vector2::zero)
            velocity = movement * 50;

        Vector2 newPos = this->parent->GetPosition();

        //Calculate new pos via euler integration
        newPos += velocity * Time::deltaTime;

        //Apply drag
        velocity *= (1 - dragFactor * Time::deltaTime);

        SDL_Log("%s", velocity.ToString().c_str());

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

void Rigidbody::SetDragFactor(const float factor)
{
    dragFactor = factor;
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
