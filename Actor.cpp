#include "actor.h"
#include "sprite_metadata.h"
#include <iostream>

Actor::Actor(float x, float y, SpriteType spriteType, AnimationType animType, float spd, int hp, int dmg)
    : position({ x, y }), speed(spd), spriteType(spriteType), currentAnimType(animType), health(hp), meleeDamage(dmg) {
    // Look up the sprite metadata
    const SpriteMetadata& spriteMeta = SpriteMetadataDB::metadata.at(spriteType);
    // Look up the animation metadata
    const AnimationMetadata& animMeta = spriteMeta.animations.at(animType);

    // Combine base path and animation path
    std::string fullPath = spriteMeta.basePath + animMeta.path;
    sprite = LoadTexture(fullPath.c_str());

    if (sprite.id == 0) {
        std::cerr << "Failed to load sprite: " << fullPath << std::endl;
        frameWidth = 10;
        frameHeight = 10;
    }
    else {
        frameCount = animMeta.frameCount;
        frameWidth = sprite.width / frameCount;
        frameHeight = sprite.height;
        std::cout << "Sprite loaded: " << fullPath
            << " (Frames: " << frameCount
            << ", Frame size: " << frameWidth << "x" << frameHeight << ")" << std::endl;
    }
}

void Actor::SetAnimation(AnimationType animType) {
    if (currentAnimType == animType) return; // No change needed

    // set incoming type as current type and fetch its data
    currentAnimType = animType;
    const SpriteMetadata& spriteMeta = SpriteMetadataDB::metadata.at(spriteType);
    const AnimationMetadata& animMeta = spriteMeta.animations.at(animType);

    // Reload the sprite for the new animation
    std::string fullPath = spriteMeta.basePath + animMeta.path;
    UnloadTexture(sprite);
    sprite = LoadTexture(fullPath.c_str());

    if (sprite.id != 0) {
        frameCount = animMeta.frameCount;
        frameWidth = sprite.width / frameCount;
        frameHeight = sprite.height;
        currentFrame = 0; // Reset to the first frame
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