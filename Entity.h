#pragma once
#include "raylib.h"       // For Vector2, Texture2D, DrawTexturePro, etc.
#include "sprite_types.h" // For SpriteType and AnimationType enums

class Entity {
public:
    // --- Core Properties ---
    Vector2 position;       // Position in the game world
    Texture2D sprite;        // Sprite texture
    SpriteType spriteType;   // Type of sprite (e.g., PLAYER, ZOMBIE_1)
    AnimationType currentAnimType; // Current animation (e.g., IDLE, WALK)

    // --- Animation Properties ---
    int currentFrame = 0;    // Current frame in the animation
    int frameCount = 4;      // Total number of frames in the sprite sheet
    int frameWidth;          // Width of a single frame
    int frameHeight;         // Height of a single frame
    float frameDelay = 0.5f; // Time (in seconds) between animation frames
    float frameTimer = 0.0f; // Timer for animation frame updates

    // --- Sprite Direction ---
    bool facingRight = true; // Tracks whether the sprite is facing right (default: true)

    // --- Constructor/Destructor ---
    Entity(float x, float y, SpriteType type, AnimationType animType);
    virtual ~Entity();

    // --- Core Methods ---
    virtual void Update();  // Update animation frame
    virtual void Draw();    // Draw the current sprite frame (with flipping support)
    virtual void SetAnimation(AnimationType animType); // Change the current animation

    // --- Sprite Direction ---
    void SetFacingDirection(bool right); // Set whether the sprite is facing right
};