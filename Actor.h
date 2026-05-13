#pragma once
#include "Entity.h"
#include "Projectile.h"

// Forward declarations
class Level;
class MeleeWeaponComponent;
class RangedWeaponComponent;

enum class ActorState {
    IDLING,
    WALKING,
    RUNNING,
    JUMPING,
    MELEEING,
    SHOOTING,
    HURTING,
    DYING
};

class Actor : public Entity {
protected: 
    Level* level;
public:
    // --- Game Logic Properties ---
    int health;                     // Health points
    float speed;                    // Movement speed

    ActorState currentState;    // Current state (e.g., IDLE, WALKING)

    // --- Weapon Components ---
    MeleeWeaponComponent* meleeWeapon;   // Optional melee weapon
    RangedWeaponComponent* rangedWeapon; // Optional ranged weapon

    // --- Constructor/Destructor ---
    Actor(Level* l, float x, float y, SpriteType type, AnimationType animType, float spd, int hp);
    virtual ~Actor();

    // --- Game Logic Methods ---
    virtual void Update();          // Update game logic (e.g., cooldowns)
    virtual void Draw();            // Delegate to Entity::Draw() 
    void SetState(ActorState newState); // Update the actor's state and animation
    virtual void TakeDamage(int amount); // Reduce health
    bool IsAlive() const;           // Check if health > 0

    // --- Attack Methods ---
    //void Melee(std::vector<Actor*>& targets);
    void Shoot(Vector2 direction);
};