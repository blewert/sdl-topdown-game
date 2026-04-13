#include "Rigidbody.h"
#include "GameObject.h"
#include "Time.h"
#include "Math.h"
#include "InputManager.h"

Rigidbody::Rigidbody(GameObject* parent, BoxCollider& collider) : Component(parent), colliderRef(collider)
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

        //SDL_Log("%s", velocity.ToString().c_str());

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

void Rigidbody::HandleCollisionEvents(Rigidbody& other, bool colliding)
{
    //Other object ID
    uint64_t otherId = other.parent->id;

    //These will be used to trigger collision events. These are
    //just the number of frames colliding with another object. If -1,
    //then it is currently not colliding with this object
    int oldState = -1;
    int newState = -1;

    //Get the old state for the other object
    oldState = collisionFrameMap[otherId];

    if (collisionFrameMap.find(otherId) == collisionFrameMap.end() && colliding)
    {
        //Not found and colliding? We've just started colliding
        collisionFrameMap[otherId] = newState = 0;
    }
    else if (!colliding)
    {
        //Otherwise, it was found -- and we're not colliding, so this is exit
        collisionFrameMap[otherId] = newState = -1;
    }
    else
    {
        //Otherwise, we are still colliding, increase collision frame count
        newState = ++collisionFrameMap[otherId];
    }

    //-----------

    //Stateful event triggers
    if (oldState < 0 && newState == 0)
    {
        //Collision enter: from -1 to 0
        this->parent->OnCollisionEnter(*this, other);
    }
    else if (oldState > 0 && newState < 0)
    {
        //Collision exit: from > 0 to -1
        this->parent->OnCollisionExit(*this, other);
    }
    else if (oldState > 0 && newState > 0)
    {
        //Collision stay: from > 0 to > 0
        this->parent->OnCollisionStay(*this, other);
    }
}

inline bool Rigidbody::IsCollidingWith(Rigidbody& other)
{
    //Couldn't find it? It hasn't encountered it yet
    if (collisionFrameMap.find(other.parent->id) == collisionFrameMap.end())
        return false;

    //This will be -1 if they are not colliding, and 0
    //or more if they are colliding currently
    return collisionFrameMap[other.parent->id] >= 0;
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
    return a.colliderRef.CollidingWith(b.colliderRef);
}
