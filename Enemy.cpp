#include "Level.h"
#include "Enemy.h"
#include "raylib.h"
#include "melee_weapon_component.h"
#include "ranged_weapon_component.h"
#include <cmath> 

Enemy::Enemy(Level* l, float x, float y, SpriteType type, AnimationType animType, float spd, int hp, ActorTeam t)
    : Actor(l, x, y, type, animType, spd, hp, t){
}

void Enemy::Update() {
    Actor* target = level->FindClosestEnemy(this);

    if (target) {
        // Calculate direction to the target
        float dx = target->position.x - position.x;
        float dy = target->position.y - position.y;
        float distance = sqrt(dx * dx + dy * dy);

        if (distance > 0) {
            // Move toward the player
            position.x += (dx / distance) * speed;
            position.y += (dy / distance) * speed;

            SetState(ActorState::WALKING);

            // Set facing direction based on movement (left/right)
            SetFacingDirection(dx > 0);
        }

        // Melee if can and in range
        if (meleeWeapon && distance < meleeWeapon->GetRange()) { 
            Melee();
        }

        // Shoot if can and in range
        if (rangedWeapon && distance < rangedWeapon->GetRange()) { 
            Vector2 direction = { dx / distance, dy / distance };
            Shoot(direction); // Shoot toward target
        }
    }

    // Update base class (animation)
    Actor::Update();
}

void Enemy::Draw() {
    Actor::Draw(); // Delegate to Actor::Draw() (handles sprite flipping/animation)
}