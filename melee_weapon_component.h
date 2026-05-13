#pragma once
#include <vector>
#include <unordered_map>

class Actor; // Forward declaration

enum class MeleeWeaponType {
    HAND,
    KNIFE
};

struct MeleeWeaponProperties {
    int damage;
    float range;    
    float cooldown; 
};

class MeleeWeaponComponent {
public:
    MeleeWeaponType type;          // Current melee weapon type
    float cooldownTimer;            // Tracks cooldown for this instance

    MeleeWeaponComponent(MeleeWeaponType type);
    ~MeleeWeaponComponent();

    // Change the melee weapon type (e.g., switch from SWORD to AXE)
    void SetWeaponType(MeleeWeaponType newType);

    // Attack all targets within range
    void Melee(Actor* attacker, std::vector<Actor*>& targets);

    float GetRange() const {
        return meleeWeaponProperties.at(type).range;
    }

private:
    // Static lookup table for melee weapon properties (shared across all instances)
    static const std::unordered_map<MeleeWeaponType, MeleeWeaponProperties> meleeWeaponProperties;
};