#include "enemy.h"
#include "raylib.h"
#include <cmath>

Enemy::Enemy(float x, float y, const std::string& sprPath, float spd, Player* t, int hp, int dmg)
    : Actor(x, y, sprPath, spd), target(t), health(hp), damage(dmg) {
}

void Enemy::Update() {
    // Simple chase AI: Move toward the player
    if (target) {
        float dx = target->position.x - position.x;
        float dy = target->position.y - position.y;
        float distance = sqrt(dx * dx + dy * dy);

        if (distance > 0) {
            position.x += (dx / distance) * speed;
            position.y += (dy / distance) * speed;
        }
    }

    // Call the base class Update() to handle animation
    Actor::Update();
}

void Enemy::Draw() {
    Actor::Draw(); // Draw the enemy sprite
}

void Enemy::TakeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

bool Enemy::IsAlive() const {
    return health > 0;
}