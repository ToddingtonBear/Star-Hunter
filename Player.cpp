#include "Player.h"
#include "raylib.h"
#include "melee_weapon_component.h"
#include"ranged_weapon_component.h"
#include <cmath>

Player::Player(Level* l, float x, float y, SpriteType type, AnimationType animType, float spd, int hp)
    : Actor(l, x, y, type, animType, spd, hp, ActorTeam::SURVIVOR),
    isMoving(false),
    meleeRange(30.0f),
    isAttacking(false),
    attackCooldown(0.5f),
    attackTimer(0.0f),
    aimingDirection({ 1.0f, 0.0f }){
    // Initialize default weapons
    meleeWeapon = new MeleeWeaponComponent(MeleeWeaponType::KNIFE);
    rangedWeapon = new RangedWeaponComponent(RangedWeaponType::PISTOL);
}

Player::~Player() {
    // Weapons are deleted in Actor destructor
}

void Player::Update() {
    
    // --- Update Cooldown Timers ---
    if (meleeWeapon) {
        meleeWeapon->cooldownTimer -= GetFrameTime();
        if (meleeWeapon->cooldownTimer < 0.0f) meleeWeapon->cooldownTimer = 0.0f;
    }
    if (rangedWeapon) {
        rangedWeapon->cooldownTimer -= GetFrameTime();
        if (rangedWeapon->cooldownTimer < 0.0f) rangedWeapon->cooldownTimer = 0.0f;
    }

    // --- Update State and Animation ---
    if (isMoving) {
        SetState(ActorState::WALKING);
    }
    else if (!isAttacking && meleeWeapon && meleeWeapon->cooldownTimer <= 0.0f) {
        SetState(ActorState::IDLING);
    }

    // Update base class (animation)
    Actor::Update();
}

void Player::Draw() {
    Actor::Draw(); // Delegate to Actor::Draw() (handles sprite flipping/animation)
    Vector2 mousePos = GetMousePosition();
    DrawLine(position.x, position.y, mousePos.x, mousePos.y, RED);
}

