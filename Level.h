#pragma once
#include "player.h"
#include "enemy.h"
#include "controller.h"
#include <vector>

class Level {
public:
    Player* player;
    Controller controller;
    std::vector<Actor*> actors; // All actors (player, enemies)
    //std::vector<Projectile*> projectiles;

    Level();
    ~Level();
    void Update();
    void Draw();
    void CheckCollisions();
};