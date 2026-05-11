#include "player.h"
#include "raylib.h"
#include "sprite_types.h"
#include "melee_weapon_component.h"
#include "ranged_weapon_component.h"
#include <cmath>

Player::Player(float x, float y, SpriteType spriteType, AnimationType animType, float spd, int hp, int dmg)
    : Actor(x, y, spriteType, animType, spd, hp, dmg), 
    isMoving(false),
    meleeRange(30.0f), 
    isAttacking(false), 
    attackCooldown(0.5f), 
    attackTimer(0.0f),
    currentState(PlayerState::IDLE),
    aimingDirection({ 1.0f, 0.0f }) { // Default: facing right
    meleeWeapon = new MeleeWeaponComponent(MeleeWeaponType::KNIFE);
    rangedWeapon = new RangedWeaponComponent(RangedWeaponType::PISTOL);
}

void Player::Update() {

    // Calculate aiming direction (from player to mouse)
    Vector2 mousePos = GetMousePosition();
    Vector2 toMouse = { mousePos.x - position.x, mousePos.y - position.y };
    float length = sqrt(toMouse.x * toMouse.x + toMouse.y * toMouse.y);
    if (length > 0) {
        aimingDirection = { toMouse.x / length, toMouse.y / length };
    }

    // move player if appropriate key is pressed 
    if (IsKeyDown(KEY_D)) {position.x += speed; isMoving = true;}  // Right
    if (IsKeyDown(KEY_A)) {position.x -= speed; isMoving = true;}   // Left
    if (IsKeyDown(KEY_W)) {position.y -= speed; isMoving = true;}     // Up
    if (IsKeyDown(KEY_S)) {position.y += speed; isMoving = true;}   // Down
    // If no movement key pressed, player is not moving
    if(!IsKeyDown(KEY_D) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_W) && !IsKeyDown(KEY_S)) isMoving = false;

    // Handle melee attack (right mouse button)
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && meleeWeapon) {
        //meleeWeapon->Attack(this, *actors);
        SetState(PlayerState::MELEE_ATTACK);
    }

    // Handle ranged attack (left mouse button)
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && rangedWeapon) {
        // Calculate direction from player to mouse
        Vector2 mousePos = GetMousePosition();
        Vector2 direction = {
            mousePos.x - position.x,
            mousePos.y - position.y
        };
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0) {
            direction.x /= length;
            direction.y /= length;
        }

        //rangedWeapon->Shoot(this, *projectiles, direction);
        SetState(PlayerState::SHOOTING);
    }

    // Handle state updates for animations
    if (isMoving) {
        SetState(PlayerState::WALKING);
    }
    else if (!isAttacking && attackTimer <= 0.0f) {
        SetState(PlayerState::IDLE);
    }

    // Update cooldown timers for attack components
    if (meleeWeapon) {
        meleeWeapon->cooldownTimer -= GetFrameTime();
        if (meleeWeapon->cooldownTimer < 0.0f) meleeWeapon->cooldownTimer = 0.0f;
    }
    if (rangedWeapon) {
        rangedWeapon->cooldownTimer -= GetFrameTime();
        if (rangedWeapon->cooldownTimer < 0.0f) rangedWeapon->cooldownTimer = 0.0f;
    }

    Actor::Update(); // Call base class Update() for animation
}

void Player::Draw() {
    Actor::Draw(); // Draw the player sprite

    // Draw melee attack range (for debugging)
    if (isAttacking) {
        DrawCircle(position.x, position.y, meleeRange, RED);
    }

    // Draw aiming line (faint line from player to mouse)
    Vector2 mousePos = GetMousePosition();
    DrawLineEx(
        { position.x , position.y },
        mousePos,
        2.0f,
        Fade(RED, 0.3f) // (30% opacity)
    );
}

void Player::MeleeAttack(std::vector<Actor*>& enemies) {
    if (!isAttacking) return;

    for (Actor* enemy : enemies) {
        if (enemy->IsAlive()) {
            float dx = enemy->position.x - position.x;
            float dy = enemy->position.y - position.y;
            float distance = sqrt(dx * dx + dy * dy);

            if (distance <= meleeRange) {
                enemy->TakeDamage(meleeDamage); // Use the Actor::TakeDamage method
            }
        }
    }
}

//void Player::Shoot(std::vector<Projectile*>& projectiles) {
//    // Spawn projectile slightly offset from player in the aiming direction
//    Vector2 spawnPos = {
//        position.x + aimingDirection.x * 20,
//        position.y + aimingDirection.y * 20
//    };
//
//    Projectile* projectile = new Projectile(
//        spawnPos.x, spawnPos.y,
//        "assets/Sprites/Projectiles/Bullet.png",
//        15.0f, // Speed
//        10,    // Damage
//        aimingDirection
//    );
//    projectiles.push_back(projectile);
//}

void Player::SetState(PlayerState newState) {
    if (currentState == newState) return;

    currentState = newState;

    // Update animation based on state
    switch (newState) {
    case PlayerState::IDLE:
        SetAnimation(AnimationType::IDLE);
        break;
    case PlayerState::WALKING:
        SetAnimation(AnimationType::WALK);
        break;
    case PlayerState::MELEE_ATTACK:
        SetAnimation(AnimationType::MELEE);
        break;
    case PlayerState::SHOOTING:
        SetAnimation(AnimationType::SHOOT);
        break;
    }
}

Player::~Player() {
    delete meleeWeapon;
    delete rangedWeapon;
}