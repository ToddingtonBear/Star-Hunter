#include "level.h"
#include "raylib.h"
#include <cmath>

Level::Level()
    : player(new Player(400, 225, SpriteType::SOLDIER_1, AnimationType::IDLE, 2.0f, 100, 20)),
    controller(*player) {  // Initialize controller with *player (dereference the pointer)
    actors.push_back(player);

    // Add enemies
    actors.push_back(new Enemy(200, 200, SpriteType::ZOMBIE_MAN, AnimationType::IDLE, 2.0f, player, 50, 10));
    actors.push_back(new Enemy(600, 300, SpriteType::ZOMBIE_WOMAN, AnimationType::IDLE, 2.5f, player, 60, 15));
    actors.push_back(new Enemy(750, 600, SpriteType::WILD_ZOMBIE, AnimationType::IDLE, 1.5f, player, 60, 15));
}

Level::~Level() {
    for (Actor* actor : actors) {
        delete actor;
    }
    actors.clear();

    //for (Projectile* projectile : projectiles) {
    //    delete projectile;
    //}
    //projectiles.clear();
}

void Level::Update() {
    controller.HandleInput();
    player->MeleeAttack(actors); // Pass all actors to check for melee hits

    // Update all actors
    for (Actor* actor : actors) {
        actor->Update();
    }

    //// Update projectiles
    //for (auto it = projectiles.begin(); it != projectiles.end(); ) {
    //    (*it)->Update();
    //    if (!(*it)->IsActive()) {
    //        delete* it;
    //        it = projectiles.erase(it);
    //    }
    //    else {
    //        ++it;
    //    }
    //}

    CheckCollisions();
}

void Level::Draw() {
    for (Actor* actor : actors) {
        actor->Draw();
    }

    //for (Projectile* projectile : projectiles) {
    //    projectile->Draw();
    //}
}

void Level::CheckCollisions() {
    // Player vs. Enemies
    for (Actor* actor : actors) {
        if (actor != player && actor->IsAlive() && player->IsAlive()) {
            float dx = player->position.x - actor->position.x;
            float dy = player->position.y - actor->position.y;
            float distance = sqrt(dx * dx + dy * dy);

            if (distance < 20.0f) { // Collision threshold
                player->TakeDamage(actor->meleeDamage); // Use actor->damage instead of actor->meleeDamage
            }
        }
    }

    //// Projectiles vs. Enemies
    //for (auto it = projectiles.begin(); it != projectiles.end(); ) {
    //    Projectile* projectile = *it;
    //    bool hit = false;

    //    for (Actor* actor : actors) {
    //        if (actor != player && actor->IsAlive() && projectile->IsActive()) {
    //            float dx = projectile->position.x - actor->position.x;
    //            float dy = projectile->position.y - actor->position.y;
    //            float distance = sqrt(dx * dx + dy * dy);

    //            if (distance < 20.0f) { // Collision threshold
    //                actor->TakeDamage(projectile->damage);
    //                hit = true;
    //                break;
    //            }
    //        }
    //    }

    //    if (hit) {
    //        delete projectile;
    //        it = projectiles.erase(it);
    //    }
    //    else {
    //        ++it;
    //    }
    //}
}