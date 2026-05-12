#pragma once
#include "Entity.h"

// Forward declarations
class MeleeWeaponComponent;
class RangedWeaponComponent;

class Actor : public Entity {
public:
    // --- Game Logic Properties ---
    int health;                     // Health points
    float speed;                    // Movement speed

    // --- Weapon Components ---
    MeleeWeaponComponent* meleeWeapon;   // Optional melee weapon
    RangedWeaponComponent* rangedWeapon; // Optional ranged weapon

    // --- Constructor/Destructor ---
    Actor(float x, float y, SpriteType type, AnimationType animType, float spd, int hp);
    virtual ~Actor();

    // --- Game Logic Methods ---
    virtual void Update();          // Update game logic (e.g., cooldowns)
    virtual void Draw();            // Delegate to Entity::Draw() (handles flipping/animation)
    virtual void TakeDamage(int amount); // Reduce health
    bool IsAlive() const;           // Check if health > 0
};