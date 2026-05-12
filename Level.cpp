#include "Level.h"
#include "raylib.h"
#include <cmath>

Level::Level() {
    // Create the player and add to actors
    player = new Player(400, 225, SpriteType::SOLDIER_1, AnimationType::IDLE, 5.0f, 100, actors, projectiles);
    actors.push_back(player);

    // Initialize the controller with the player pointer
    controller = Controller(player);

    // Add enemies (pass the player pointer for AI targeting)
    actors.push_back(new Enemy(200, 200, SpriteType::DESTROYER, AnimationType::IDLE, 2.0f, 50, player));
    actors.push_back(new Enemy(600, 300, SpriteType::INFANTRYMAN, AnimationType::IDLE, 2.5f, 60, player));
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
    player->Melee(actors);

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
    for (Actor* actor : actors) {
        if (actor != player && actor->IsAlive() && player->IsAlive()) {
            float dx = player->position.x - actor->position.x;
            float dy = player->position.y - actor->position.y;
            float distance = sqrt(dx * dx + dy * dy);
            if (distance < 20.0f) { // Collision threshold
                player->TakeDamage(10); // Fixed damage for now (or use actor->damage if available)
            }
        }
    }

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