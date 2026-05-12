#pragma once
#include "Entity.h"  
#include "raylib.h"  // For Vector2

class Projectile : public Entity {
public:
    int damage;          // Damage dealt by the projectile
    bool isActive;       // Whether the projectile is active (not off-screen or destroyed)
    Vector2 direction;   // Direction of movement (normalized)
    float speed;         // Speed of movement

    // Constructor: x, y, sprite type, animation type, speed, damage, direction
    Projectile(float x, float y, SpriteType type, AnimationType animType, float spd, int dmg, Vector2 dir);

    // Override Entity methods
    void Update() override;  // Move the projectile and check for off-screen
    void Draw() override;    // Draw the projectile (uses Entity::Draw for flipping)
    bool IsActive() const;  // Check if the projectile is active
};