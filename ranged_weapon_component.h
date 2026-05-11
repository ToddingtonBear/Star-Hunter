#pragma once
#include "raylib.h"
#include <vector>
#include "projectile.h"
#include <unordered_map>


class Actor; // Forward declaration

enum class RangedWeaponType {
    PISTOL, 
    ASSAULT,
    SHOTGUN,
    SNIPER
};

struct RangedWeaponProperties {
    float range;
    int damage;
    float projectileSpeed;
    float cooldown;
    float spread;
};

class RangedWeaponComponent {
public:
    RangedWeaponType type;
    float cooldownTimer;

    RangedWeaponComponent(RangedWeaponType type);
    void SetWeaponType(RangedWeaponType newType);
    void Shoot(Actor* attacker, std::vector<Actor*>& projectiles, Vector2 direction);

private:
    static const std::unordered_map<RangedWeaponType, RangedWeaponProperties> rangedWeaponProperties;
};