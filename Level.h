#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Controller.h"
#include "Projectile.h"
#include <vector>

class Level {
public:
    Player* player;                 // Pointer to the player (for easy access)
    std::vector<Actor*> actors;      // All actors (player, enemies)
    std::vector<Projectile*> projectiles; // All projectiles
    Controller controller;          // Handles player input

    Level();
    ~Level();
    void Update();
    void Draw();
    void CheckCollisions();
};


//
//: player(new Player(400, 225, SpriteType::SOLDIER_1, AnimationType::IDLE, 2.0f, 100, 20)),
//controller(*player) {  // Initialize controller with *player (dereference the pointer)
//    actors.push_back(player);
//
//    // Add enemies
//    actors.push_back(new Enemy(200, 200, SpriteType::ZOMBIE_MAN, AnimationType::IDLE, 2.0f, player, 50, 10));
//    actors.push_back(new Enemy(600, 300, SpriteType::ZOMBIE_WOMAN, AnimationType::IDLE, 2.5f, player, 60, 15));
//    actors.push_back(new Enemy(750, 600, SpriteType::WILD_ZOMBIE, AnimationType::IDLE, 1.5f, player, 60, 15));
