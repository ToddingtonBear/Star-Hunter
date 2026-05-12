#pragma once
#include "Actor.h"

class Player; // Forward declaration (to avoid circular dependency)

class Enemy : public Actor {
public:
    Player* player; // Pointer to the player for AI (chasing)

    // Constructor: x, y, sprite type, animation type, speed, health, target player
    Enemy(float x, float y, SpriteType type, AnimationType animType, float spd, int hp, Player* player);
    void Update() override; // Chase the player and update AI
    void Draw() override;   // Delegate to Actor::Draw() (handles flipping/animation)
};