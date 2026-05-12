#include "Enemy.h"
#include "raylib.h"
#include "Player.h"
#include <cmath> 

Enemy::Enemy(float x, float y, SpriteType type, AnimationType animType, float spd, int hp, Player* player)
    : Actor(x, y, type, animType, spd, hp),
    player(player) {
}

void Enemy::Update() {
    if (player) {
        // Calculate direction to the player
        float dx = player->position.x - position.x;
        float dy = player->position.y - position.y;
        float distance = sqrt(dx * dx + dy * dy);

        if (distance > 0) {
            // Move toward the player
            position.x += (dx / distance) * speed;
            position.y += (dy / distance) * speed;

            // Set facing direction based on movement (left/right)
            SetFacingDirection(dx > 0);
        }
    }

    // Update base class (animation)
    Actor::Update();
}

void Enemy::Draw() {
    Actor::Draw(); // Delegate to Actor::Draw() (handles sprite flipping/animation)
}