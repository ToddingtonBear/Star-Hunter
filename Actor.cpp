#include "Actor.h"
#include "melee_weapon_component.h" 
#include "ranged_weapon_component.h"

Actor::Actor(float x, float y, SpriteType type, AnimationType animType, float spd, int hp)
    : Entity(x, y, type, animType),
    health(hp),
    speed(spd),
    meleeWeapon(nullptr),
    rangedWeapon(nullptr) {
}

Actor::~Actor() {
    delete meleeWeapon;   // Clean up melee weapon component
    delete rangedWeapon;  // Clean up ranged weapon component
}

void Actor::Update() {
    // Update animation (handled by Entity)
    Entity::Update();
}

void Actor::Draw() {
    // Delegate to Entity::Draw() (handles sprite flipping/animation)
    Entity::Draw();
}

void Actor::TakeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0; // Clamp health to 0
}

bool Actor::IsAlive() const {
    return health > 0;
}