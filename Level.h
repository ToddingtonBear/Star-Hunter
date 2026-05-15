#pragma once
#include "Controller.h"
#include "Projectile.h"
#include <vector>

class Actor;
class Player;

class Level {

private:
    Player* player;                 // Pointer to the player (for easy access)
    std::vector<Actor*> actors;      // All actors (player, enemies)
    std::vector<Projectile*> projectiles; // All projectiles
    Controller controller;          // Handles player input
public:

    Level();
    ~Level();
    void Update();
    void Draw();
    void CheckCollisions();

    void AddProjectile(Projectile* projectile);
    Actor* FindClosestEnemy(Actor* self) const;
    std::vector<Actor*>& GetActors();
};
