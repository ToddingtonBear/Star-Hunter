#pragma once
#include "raylib.h"
#include <string>

class Actor {
public:
    // Graphics
    Vector2 position;
    Texture2D sprite;
    std::string spritePath;

    // Stats
    int health;
    int meleeDamage; 
    float speed;

    // Animation members
    int currentFrame = 0;
    int frameCount = 4;
    int frameWidth;
    int frameHeight;
    float frameDelay = 0.1f;
    float frameTimer = 0.0f;

    Actor(float x, float y, const std::string& sprPath, float spd, int hp, int dmg);
    virtual ~Actor();
    virtual void Update();
    virtual void Draw();
    virtual void TakeDamage(int amount);
    bool IsAlive() const;
};