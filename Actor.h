#pragma once
#include "raylib.h"
#include "sprite_types.h"
#include "melee_weapon_component.h"
#include "ranged_weapon_component.h"
#include <string>

class MeleeWeaponComponent;
class RangedWeaponComponent;

class Actor {
public:
    // Graphics
    Vector2 position;
    Texture2D sprite;
    SpriteType spriteType;
    AnimationType currentAnimType;

    // Stats
    int health;
    int meleeDamage; 
    float speed;

    // Attack components
    MeleeWeaponComponent* meleeWeapon;
    RangedWeaponComponent* rangedWeapon;

    // Animation members
    int currentFrame = 0;
    int frameCount = 4;
    int frameWidth;
    int frameHeight;
    float frameDelay = 0.1f;
    float frameTimer = 0.0f;

    Actor(float x, float y, SpriteType type, AnimationType animType, float spd, int hp, int dmg);
    virtual ~Actor();
    virtual void Update();
    virtual void Draw();
    virtual void SetAnimation(AnimationType animType);
    virtual void TakeDamage(int amount);
    bool IsAlive() const;
};