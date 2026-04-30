#pragma once
#include "actor.h"
#include "player.h"
#include <string>

class Enemy : public Actor {
public:
    int health;
    int damage;
    Player* target; // Pointer to the player for chasing

    Enemy(float x, float y, const std::string& sprPath, float spd, Player* t, int hp, int dmg);
    void Update() override;
    void Draw() override;
    void TakeDamage(int amount);
    bool IsAlive() const;
};