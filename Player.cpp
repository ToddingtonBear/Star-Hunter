#include "Player.h"
#include "raylib.h"
#include "melee_weapon_component.h"
#include"ranged_weapon_component.h"
#include <cmath>

Player::Player(float x, float y, SpriteType type, AnimationType animType, float spd, int hp,
    std::vector<Actor*>& actors, std::vector<Projectile*>& projectiles)
    : Actor(x, y, type, animType, spd, hp),
    isMoving(false),
    meleeRange(30.0f),
    isAttacking(false),
    attackCooldown(0.5f),
    attackTimer(0.0f),
    currentState(PlayerState::IDLE),
    aimingDirection({ 1.0f, 0.0f }),
    actors(&actors),
    projectiles(&projectiles) {
    // Initialize default weapons
    meleeWeapon = new MeleeWeaponComponent(MeleeWeaponType::KNIFE);
    rangedWeapon = new RangedWeaponComponent(RangedWeaponType::PISTOL);
}

Player::~Player() {
    // Weapons are deleted in Actor destructor
}

void Player::Update() {
    // --- Aiming Direction ---
    Vector2 mousePos = GetMousePosition();
    Vector2 toMouse = { mousePos.x - position.x, mousePos.y - position.y };
    float length = sqrt(toMouse.x * toMouse.x + toMouse.y * toMouse.y);
    if (length > 0) {
        aimingDirection = { toMouse.x / length, toMouse.y / length };
        // Set facing direction based on mouse position (left/right)
        SetFacingDirection(toMouse.x > 0);
    }

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
        SetState(PlayerState::WALKING);
    }
    else if (!isAttacking && meleeWeapon && meleeWeapon->cooldownTimer <= 0.0f) {
        SetState(PlayerState::IDLE);
    }

    // Update base class (animation)
    Actor::Update();
}

void Player::Draw() {
    Actor::Draw(); // Delegate to Actor::Draw() (handles sprite flipping/animation)
    // Optional: Draw aiming line for debugging
    Vector2 mousePos = GetMousePosition();
    DrawLine(position.x, position.y, mousePos.x, mousePos.y, RED);
}

void Player::Melee(std::vector<Actor*>& enemies) {
    if (!isAttacking || !meleeWeapon) return;
    meleeWeapon->Attack(this, enemies);
}

void Player::Shoot() {
    if (!rangedWeapon) return;
    rangedWeapon->Shoot(this, *projectiles, aimingDirection);
}

void Player::SetState(PlayerState newState) {
    currentState = newState;
    // Update animation based on state
    switch (newState) {
    case PlayerState::IDLE:         SetAnimation(AnimationType::IDLE); break;
    case PlayerState::WALKING:      SetAnimation(AnimationType::WALK); break;
    case PlayerState::MELEE_ATTACK: SetAnimation(AnimationType::MELEE); break;
    case PlayerState::SHOOTING:     SetAnimation(AnimationType::SHOOT); break;
    }
}