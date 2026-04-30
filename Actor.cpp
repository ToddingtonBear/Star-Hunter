#include "actor.h"
#include <iostream>

Actor::Actor(float x, float y, const std::string& sprPath, float spd, int hp, int dmg)
    : position({ x, y }), speed(spd), spritePath(sprPath), health(hp), meleeDamage(dmg) {
    sprite = LoadTexture(sprPath.c_str());
    if (sprite.id == 0) {
        std::cerr << "Failed to load sprite: " << sprPath << std::endl;
        frameWidth = 10;
        frameHeight = 10;
    }
    else {
        frameWidth = sprite.width / frameCount;
        frameHeight = sprite.height;
    }
}

Actor::~Actor() {
    UnloadTexture(sprite);
}

void Actor::Update() {
    // Update animation frame
    frameTimer += GetFrameTime();
    if (frameTimer >= frameDelay) {
        frameTimer = 0.0f;
        currentFrame = (currentFrame + 1) % frameCount;
    }
}

void Actor::Draw() {
    if (sprite.id != 0) {
        Rectangle sourceRect = {
            (float)currentFrame * frameWidth,
            0,
            (float)frameWidth,
            (float)frameHeight
        };
        Vector2 destPos = {
            position.x - frameWidth / 2,
            position.y - frameHeight / 2
        };
        DrawTextureRec(sprite, sourceRect, destPos, WHITE);
    }
    else {
        DrawCircle(position.x, position.y, 10, RED);
    }
}

void Actor::TakeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

bool Actor::IsAlive() const {
    return health > 0;
}