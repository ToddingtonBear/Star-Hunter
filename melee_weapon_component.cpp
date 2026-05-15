#include "melee_weapon_component.h"
#include "actor.h"
#include <cmath>
#include <iostream>

// Lookup table for melee weapon properties
const std::unordered_map<MeleeWeaponType, MeleeWeaponProperties> MeleeWeaponComponent::meleeWeaponProperties = {
    {MeleeWeaponType::HAND, {5, 120.0f, 0.5f}}, // Damage, range, cooldown
    {MeleeWeaponType::KNIFE,   {20, 150.0f, 0.6f}},
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

void MeleeWeaponComponent::Melee(Actor* attacker, std::vector<Actor*>& targets) {
    std::cout << "COOLDOWN check" << std::endl;
    if (cooldownTimer > 0.0f) return; // Still on cooldown

    attacker->SetState(ActorState::MELEEING);

    // Get weapon properties from the lookup table
    const MeleeWeaponProperties& props = meleeWeaponProperties.at(type);

    ActorTeam friendlyTeam = attacker->GetTeam();
    // Check all targets for hits
    for (Actor* target : targets) {
        // If target is dead, on the same team as attacker, or is the attacker, skip
        if (!target->IsAlive() || target->GetTeam() == friendlyTeam || target == attacker ) continue;

        float dx = target->position.x - attacker->position.x;
        float dy = target->position.y - attacker->position.y;
        float distance = sqrt(dx * dx + dy * dy);

        if (distance <= props.range) {
            target->TakeDamage(props.damage);
        }
    }

    cooldownTimer = props.cooldown; // Reset cooldown
    std::cout << "MELEE!!!!!!!!!!!!!!!" << std::endl;
}
