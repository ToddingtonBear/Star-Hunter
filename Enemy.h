#pragma once
#include "actor.h"
#include "player.h"
#include "sprite_types.h"
#include <string>

class Enemy : public Actor {
public:
    Player* player; // Pointer to the player for chasing

    Enemy(float x, float y, SpriteType spriteType, AnimationType animType, float spd, Player* p, int hp, int dmg);
    void Update() override;
    void Draw() override;
};


