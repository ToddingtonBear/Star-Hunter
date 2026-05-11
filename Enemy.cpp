#include "enemy.h"
#include "raylib.h"
#include <cmath>

Enemy::Enemy(float x, float y, SpriteType spriteType, AnimationType animType, float spd, Player* p, int hp, int dmg)
    : Actor(x, y, spriteType, animType, spd, hp, dmg), player(p) {
}

void Enemy::Update() {
    // Simple chase AI: Move toward the player
    if (player && player->IsAlive()) {
        float dx = player->position.x - position.x;
        float dy = player->position.y - position.y;
        float distance = sqrt(dx * dx + dy * dy);

        if (distance > 0) {
            position.x += (dx / distance) * speed;
            position.y += (dy / distance) * speed;
        }
    }

    Actor::Update(); // Call base class Update() for animation
}

void Enemy::Draw() {
    Actor::Draw(); // Draw the enemy sprite
}