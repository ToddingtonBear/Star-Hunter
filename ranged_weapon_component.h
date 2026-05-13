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
    Projectile* CreateProjectile(Actor* attacker, Vector2 direction);

    float GetRange() const {
        return rangedWeaponProperties.at(type).range;
    }

private:
    static const std::unordered_map<RangedWeaponType, RangedWeaponProperties> rangedWeaponProperties;
};