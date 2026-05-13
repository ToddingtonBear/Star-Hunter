#pragma once
#include "Actor.h"
#include "Projectile.h"
#include <vector>

class Player : public Actor {
public:
    // --- Player-Specific State ---
    bool isMoving;               // Whether the player is moving
    float meleeRange;            // Range for melee attacks
    bool isAttacking;            // Whether the player is currently attacking
    float attackCooldown;        // Cooldown time between attacks
    float attackTimer;           // Timer for attack cooldown
    //PlayerState currentState;    // Current state (e.g., IDLE, WALKING)
    Vector2 aimingDirection;     // Direction the player is aiming (normalized)

    // --- References to Game-Wide Vectors ---
    std::vector<Actor*>* actors;          // Pointer to the game's actors vector
    std::vector<Projectile*>* projectiles; // Pointer to the game's projectiles vector

    // --- Constructor/Destructor ---
    Player(Level* l, float x, float y, SpriteType type, AnimationType animType, float spd, int hp,
        std::vector<Actor*>& actors, std::vector<Projectile*>& projectiles);
    ~Player();

    // --- Player-Specific Methods ---
    void Update() override;               // Handle input, movement, and attacks
    void Draw() override;                 // Delegate to Actor::Draw() (handles flipping/animation)
    //void Melee(std::vector<Actor*>& enemies); // Attack nearby enemies
    //void Shoot();                        // Fire a projectile
};