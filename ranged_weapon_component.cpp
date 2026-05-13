#include "ranged_weapon_component.h"
#include "actor.h"
#include "projectile.h"
#include "Level.h"
#include <cmath>
#include <unordered_map>


//lookup table for weapon properties
const std::unordered_map<RangedWeaponType, RangedWeaponProperties> RangedWeaponComponent::rangedWeaponProperties = {
    {RangedWeaponType::PISTOL,   {50, 10, 15.0f, 0.3f, 0}},
    {RangedWeaponType::ASSAULT,   {80, 15, 18.0f, 0.1f, 5}},
    {RangedWeaponType::SHOTGUN,  {20, 20, 12.0f, 0.8f, 45}},
    {RangedWeaponType::SNIPER,   {100,30, 20.0f, 1.5f, 0}},
};

RangedWeaponComponent::RangedWeaponComponent(RangedWeaponType type)
    : type(type), cooldownTimer(0.0f) {
}

void RangedWeaponComponent::SetWeaponType(RangedWeaponType newType) {
    type = newType;
}

Projectile* RangedWeaponComponent::CreateProjectile(Actor* attacker, Vector2 direction) {
    if (cooldownTimer > 0.0f) return nullptr;

    const RangedWeaponProperties& props = rangedWeaponProperties.at(type);

    // Spawn projectile slightly offset from attacker
    Vector2 spawnPos = {
        attacker->position.x + direction.x * 20,
        attacker->position.y + direction.y * 20
    };

    Projectile* projectile = new Projectile(
        spawnPos.x, spawnPos.y,
        SpriteType::SOLDIER_3,  // Replace with your projectile sprite type
        AnimationType::IDLE,    // Replace with your projectile animation type
        props.projectileSpeed,
        props.damage,
        direction
    );

    cooldownTimer = props.cooldown;
    return projectile;
}