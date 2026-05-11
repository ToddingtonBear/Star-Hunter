#pragma once
#include "sprite_types.h"
#include <string>
#include <unordered_map>

struct AnimationMetadata {
    std::string path;      // File path for the animation sprite sheet
    int frameCount;        // Number of frames in the sprite sheet
};

struct SpriteMetadata {
    std::string basePath;  // Base path for the sprite 
    std::unordered_map<AnimationType, AnimationMetadata> animations; // Map animation type to animation metadata
};

class SpriteMetadataDB {
public:
    static const std::unordered_map<SpriteType, SpriteMetadata> metadata; // Map sprite type to sprite metadata
};