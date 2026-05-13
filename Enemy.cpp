#include "Enemy.h"
#include "raylib.h"
#include "Player.h"
#include "melee_weapon_component.h"
#include "ranged_weapon_component.h"
#include <cmath> 

Enemy::Enemy(Level* l, float x, float y, SpriteType type, AnimationType animType, float spd, int hp, Player* player)
    : Actor(l, x, y, type, animType, spd, hp),
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

            SetState(ActorState::WALKING);

            // Set facing direction based on movement (left/right)
            SetFacingDirection(dx > 0);
        }

        // --- Attacks (Enemy targets ONLY the player) ---
        //if (meleeWeapon && distance < meleeWeapon->GetRange()) { 
        //    Melee({ player }); // Pass ONLY the player as a target
        //}
        if (rangedWeapon && distance < rangedWeapon->GetRange()) { 
            Vector2 direction = { dx / distance, dy / distance };
            Shoot(direction); // Shoot toward player
        }
    }

    // Update base class (animation)
    Actor::Update();
}

void Enemy::Draw() {
    Actor::Draw(); // Delegate to Actor::Draw() (handles sprite flipping/animation)
}