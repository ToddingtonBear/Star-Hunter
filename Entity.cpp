#include "Entity.h"
#include "sprite_metadata.h"
#include <iostream>

// Constructor: Initialize position and load the sprite
Entity::Entity(float x, float y, SpriteType type, AnimationType animType)
    : position({ x, y }), spriteType(type), currentAnimType(animType), facingRight(true) {

    // Look up the sprite metadata
    const SpriteMetadata& spriteMeta = SpriteMetadataDB::metadata.at(spriteType);
    // Look up the animation metadata
    const AnimationMetadata& animMeta = spriteMeta.animations.at(animType);

    // Combine base path and animation path
    std::string fullPath = spriteMeta.basePath + animMeta.path;
    sprite = LoadTexture(fullPath.c_str());

    if (sprite.id == 0) {
        // Fallback if the sprite fails to load
        std::cerr << "Failed to load sprite: " << fullPath << std::endl;
        frameWidth = 10;
        frameHeight = 10;
    }
    else {
        // Calculate frame dimensions (assume sprite sheet is horizontal)
        frameCount = animMeta.frameCount;
        frameWidth = sprite.width / frameCount;
        frameHeight = sprite.height;
        std::cout << "Sprite loaded: " << animMeta.path
            << " (Frames: " << frameCount
            << ", Frame size: " << frameWidth << "x" << frameHeight << ")" << std::endl;
    }
}

Entity::~Entity() {
    UnloadTexture(sprite);
}

void Entity::Update() {
    // Update animation frame timer
    frameTimer += GetFrameTime();
    if (frameTimer >= frameDelay) {
        frameTimer = 0.0f;
        currentFrame = (currentFrame + 1) % frameCount; // Loop back to 0
    }
}

void Entity::Draw() {
    if (sprite.id != 0) {
        Rectangle sourceRect = {
            static_cast<float>(currentFrame * frameWidth),
            0,
            static_cast<float>(frameWidth),
            static_cast<float>(frameHeight)
        };
        Rectangle destRect = {
            position.x - frameWidth / 2,
            position.y - frameHeight / 2,
            static_cast<float>(frameWidth),
            static_cast<float>(frameHeight)
        };
        Vector2 origin = { 0, 0 };
        float rotation = 0.0f;
        Color tint = WHITE;

        // Flip the sprite horizontally if facing left
        if (!facingRight) {
            //destRect.width = -destRect.width; // Negative width flips the sprite
            sourceRect.width = -sourceRect.width; // Negative width flips the sprite
        }

        DrawTexturePro(sprite, sourceRect, destRect, origin, rotation, tint);
    }
    else {
        // Fallback: Draw a red circle if the sprite failed to load
        DrawCircle(position.x, position.y, 10, RED);
    }
}

void Entity::SetAnimation(AnimationType animType) {
    if (currentAnimType == animType) return; // Skip if no change

    currentAnimType = animType;
    currentFrame = 0; // Reset to the first frame

    // Reload the sprite for the new animation
    const SpriteMetadata& spriteMeta = SpriteMetadataDB::metadata.at(spriteType);
    const AnimationMetadata& animMeta = spriteMeta.animations.at(animType);
    std::string fullPath = spriteMeta.basePath + animMeta.path;

    // Unload the old sprite
    if (sprite.id != 0) {
        UnloadTexture(sprite);
    }

    // Load the new sprite
    sprite = LoadTexture(fullPath.c_str());
    if (sprite.id == 0) {
        std::cerr << "Failed to load sprite for animation: " << fullPath << std::endl;
        frameWidth = 10;
        frameHeight = 10;
    }
    else {
        frameCount = animMeta.frameCount;
        frameWidth = sprite.width / frameCount;
        frameHeight = sprite.height;
    }
}

void Entity::SetFacingDirection(bool right) {
    facingRight = right;
    std::cout << "Facing: " << (facingRight ? "RIGHT" : "LEFT") << std::endl;
}