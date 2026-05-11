#include "ranged_weapon_component.h"
#include "actor.h"
#include "projectile.h"
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

void RangedWeaponComponent::Shoot(Actor* attacker, std::vector<Actor*>& projectiles, Vector2 direction) {
    if (cooldownTimer > 0.0f) return; // Still on cooldown

    // Get weapon properties from the lookup table
    RangedWeaponProperties properties = rangedWeaponProperties.at(type);

    // Spawn projectile slightly offset from attacker
    Vector2 spawnPos = {
        attacker->position.x + direction.x * 20,
        attacker->position.y + direction.y * 20
    };

    //Projectile* projectile = new Projectile(
    //    spawnPos.x, spawnPos.y,
    //    "assets/Sprites/Projectiles/Bullet.png",
    //    properties.projectileSpeed,
    //    properties.damage,
    //    direction
    //);
    //projectiles.push_back(projectile);

    cooldownTimer = properties.cooldown; // Reset cooldown
}