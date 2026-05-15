#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "raylib.h"
#include <cmath>

Level::Level() {
    // Create the player and add to actors
    player = new Player(this, 400, 225, SpriteType::SOLDIER_1, AnimationType::IDLE, 5.0f, 100);
    actors.push_back(player);

    // Initialize the controller with the player pointer
    controller = Controller(player);

    // Add enemies (pass the player pointer for AI targeting)
    
    actors.push_back(new Enemy(this, 200, 200, SpriteType::DESTROYER, AnimationType::IDLE, 2.0f, 50, ActorTeam::HUNTER));
    actors.push_back(new Enemy(this, 600, 300, SpriteType::INFANTRYMAN, AnimationType::IDLE, 2.5f, 60, ActorTeam::HUNTER));
}

Level::~Level() {
    // Clean up actors
    for (Actor* actor : actors) {
        delete actor;
    }
    actors.clear();

    // Clean up projectiles
    for (Projectile* projectile : projectiles) {
        delete projectile;
    }
    projectiles.clear();
}

void Level::Update() {
    // Handle player input
    controller.HandleInput();

    // Player-specific attacks
    //player->Melee(actors);

    // Update all actors (player, enemies)
    for (Actor* actor : actors) {
        actor->Update();
    }

    // Update all projectiles
    for (Projectile* projectile : projectiles) {
        projectile->Update();
    }

    // Check for collisions
    CheckCollisions();
}

void Level::Draw() {
    // Draw all actors
    for (Actor* actor : actors) {
        actor->Draw();
    }

    // Draw all projectiles
    for (Projectile* projectile : projectiles) {
        projectile->Draw();
    }
}

void Level::CheckCollisions() {
    // --- Player vs. Enemies ---
    //for (Actor* actor : actors) {
    //    if (actor != player && actor->IsAlive() && player->IsAlive()) {
    //        float dx = player->position.x - actor->position.x;
    //        float dy = player->position.y - actor->position.y;
    //        float distance = sqrt(dx * dx + dy * dy);
    //        if (distance < 20.0f) { // Collision threshold
    //            player->TakeDamage(10); // Fixed damage for now (or use actor->damage if available)
    //        }
    //    }
    //}

    // --- Projectiles vs. Actors ---
    for (size_t i = 0; i < projectiles.size(); ) {
        Projectile* projectile = projectiles[i];
        if (!projectile->IsActive()) {
            // Remove inactive projectiles
            delete projectile;
            projectiles.erase(projectiles.begin() + i);
            continue; // Skip the rest of the loop for this iteration
        }

        for (Actor* actor : actors) {
            if (actor->IsAlive() && projectile->IsActive()) {
                float dx = projectile->position.x - actor->position.x;
                float dy = projectile->position.y - actor->position.y;
                float distance = sqrt(dx * dx + dy * dy);
                if (distance < 20.0f) { // Collision threshold
                    actor->TakeDamage(projectile->damage);
                    projectile->isActive = false; // Deactivate the projectile
                }
            }
        }
        i++; // Only increment if we didn't erase
    }
}

void Level::AddProjectile(Projectile* projectile) {
    projectiles.push_back(projectile);
}

Actor* Level::FindClosestEnemy(Actor* self) const {
    Actor* closestEnemy = nullptr;
    float closestDistance = std::numeric_limits<float>::max();

    for (Actor* actor : actors) {
        // Skip self, dead actors, or teammates
        if (actor == self || !actor->IsAlive() || actor->GetTeam() == self->GetTeam()) {
            continue;
        }

        // Calculate distance
        float dx = actor->position.x - self->position.x;
        float dy = actor->position.y - self->position.y;
        float distance = sqrt(dx * dx + dy * dy);

        if (distance < closestDistance) {
            closestDistance = distance;
            closestEnemy = actor;
        }
    }
    return closestEnemy; // Returns nullptr if no enemy found
}

std::vector<Actor*>& Level::GetActors() {
    return actors;
}