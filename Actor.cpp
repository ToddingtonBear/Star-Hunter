#pragma once
#include "Actor.h"
#include "Level.h"
#include "melee_weapon_component.h" 
#include "ranged_weapon_component.h"

Actor::Actor(Level* l, float x, float y, SpriteType type, AnimationType animType, float spd, int hp)
    : Entity(x, y, type, animType),
    level(l),
    health(hp),
    speed(spd),
    meleeWeapon(nullptr),
    rangedWeapon(nullptr),
    currentState(ActorState::IDLING){
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

void Actor::SetState(ActorState newState) {
    currentState = newState;
    // Update animation based on state
    switch (newState) {
    case ActorState::IDLING:    SetAnimation(AnimationType::IDLE); break;
    case ActorState::WALKING:   SetAnimation(AnimationType::WALK); break;
    case ActorState::MELEEING:  SetAnimation(AnimationType::MELEE); break;
    case ActorState::SHOOTING:  SetAnimation(AnimationType::SHOOT); break;
    }
}

void Actor::TakeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0; // Clamp health to 0
}

bool Actor::IsAlive() const {
    return health > 0;
}

//void Actor::Melee(std::vector<Actor*>& targets) {
//    if (meleeWeapon) meleeWeapon->Melee(this, targets);
//}
void Actor::Shoot(Vector2 direction) {
    if (rangedWeapon) {
        Projectile* projectile = rangedWeapon->CreateProjectile(this, direction);
        if (projectile) { 
            level->AddProjectile(projectile); 
            SetState(ActorState::SHOOTING);
        }
    }
}