#include "melee_weapon_component.h"
#include "actor.h"
#include <cmath>

// Lookup table for melee weapon properties
const std::unordered_map<MeleeWeaponType, MeleeWeaponProperties> MeleeWeaponComponent::meleeWeaponProperties = {
    {MeleeWeaponType::HAND, {5, 5.0f, 0.5f}}, // Damage, range, cooldown
    {MeleeWeaponType::KNIFE,   {20, 7.0f, 0.6f}},
};

MeleeWeaponComponent::MeleeWeaponComponent(MeleeWeaponType type)
    : type(type), cooldownTimer(0.0f) {
}

MeleeWeaponComponent::~MeleeWeaponComponent() {}

void MeleeWeaponComponent::SetWeaponType(MeleeWeaponType newType) {
    type = newType;
    // Reset cooldown when switching weapons (optional)
    cooldownTimer = 0.0f;
}

void MeleeWeaponComponent::Attack(Actor* attacker, std::vector<Actor*>& targets) {
    if (cooldownTimer > 0.0f) return; // Still on cooldown

    // Get weapon properties from the lookup table
    const MeleeWeaponProperties& props = meleeWeaponProperties.at(type);

    // Check all targets for hits
    for (Actor* target : targets) {
        if (target == attacker || !target->IsAlive()) continue;

        float dx = target->position.x - attacker->position.x;
        float dy = target->position.y - attacker->position.y;
        float distance = sqrt(dx * dx + dy * dy);

        if (distance <= props.range) {
            target->TakeDamage(props.damage);
        }
    }

    cooldownTimer = props.cooldown; // Reset cooldown
}