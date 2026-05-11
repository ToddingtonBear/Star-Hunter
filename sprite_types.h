#pragma once

// Sprite types (e.g., Player, Zombie1, Zombie2)
enum class SpriteType {
    // Players
    SOLDIER_1,
    SOLDIER_2,
    SOLDIER_3,

    // Enemies
    DESTROYER,
    INFANTRYMAN,
    SWORDSMAN,
    ZOMBIE_MAN,
    ZOMBIE_WOMAN,
    WILD_ZOMBIE
};

// Animation types (e.g., Idle, Walk, Attack)
enum class AnimationType {
    IDLE,
    WALK,
    RUN,
    JUMP,
    MELEE,
    SHOOT,
    HURT,
    DEAD
};