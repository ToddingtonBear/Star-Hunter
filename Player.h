#pragma once
#include "actor.h"
#include "Projectile.h"
#include <vector>
#include <string>

enum class PlayerState {
    IDLE,
    WALKING,
    MELEE_ATTACK,
    SHOOTING
};

class Player : public Actor {
public:
    bool isMoving;
    float meleeRange;
    bool isAttacking;
    float attackCooldown;
    float attackTimer;
    PlayerState currentState;
    Vector2 aimingDirection; // Direction the player is aiming (normalized)


    Player(float x, float y, SpriteType spriteType, AnimationType animType, float spd, int hp, int dmg);
    void Update() override;
    void Draw() override;
    void MeleeAttack(std::vector<Actor*>& enemies);
    //void Shoot(std::vector<Projectile*>& projectiles);
    void SetState(PlayerState newState);
    ~Player();
};