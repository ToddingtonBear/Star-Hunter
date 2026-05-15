#pragma once
#include "Actor.h"
#include "Level.h"
#include "melee_weapon_component.h" 
#include "ranged_weapon_component.h"
#include <iostream>

Actor::Actor(Level* l, float x, float y, SpriteType type, AnimationType animType, float spd, int hp, ActorTeam t)
    : Entity(x, y, type, animType),
    level(l),
    health(hp),
    speed(spd),
    team(t),
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
    std::cout << "Actor took damage. " << health << " health remaining." << std::endl;
    if (health <= 0) {
        health = 0; // Clamp health to 0
        std::cout << "Target died" << std::endl;
        SetState(ActorState::DYING);
    }
}

bool Actor::IsAlive() const {
    return health > 0;
}

ActorTeam Actor::GetTeam() const {
    return team;
}

void Actor::Melee() {
    if (meleeWeapon) { 

        meleeWeapon->Melee(this, level->GetActors()); 
    }
}

void Actor::Shoot(Vector2 direction) {
    if (rangedWeapon) {
        Projectile* projectile = rangedWeapon->CreateProjectile(this, direction);
        if (projectile) { 
            level->AddProjectile(projectile); 
            SetState(ActorState::SHOOTING);
        }
    }
}