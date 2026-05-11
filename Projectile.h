/*#pragma once
#include "Actor.h"
#include <string>

class Projectile : public Actor {
public:
    int damage;
    bool isActive;
    Vector2 direction;

    Projectile(float x, float y, const std::string& sprPath, float spd, int dmg, Vector2 dir);
    void Update() override;
    void Draw() override;
    bool IsActive() const;
};*/