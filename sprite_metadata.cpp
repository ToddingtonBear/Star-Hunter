#include "sprite_metadata.h"

const std::unordered_map<SpriteType, SpriteMetadata> SpriteMetadataDB::metadata = {
    {
        //Players
        SpriteType::SOLDIER_1,
        {
            "assets/Sprites/Players/Soldier_1/",
            {
                {AnimationType::IDLE,   {"Idle.png", 7}},
                {AnimationType::WALK,   {"Walk.png", 7}},
                {AnimationType::RUN,    {"Run.png", 8}},
                {AnimationType::JUMP,   {"Run.png", 8}},
                {AnimationType::MELEE,  {"Attack.png", 3}},
                {AnimationType::SHOOT,  {"Shot_1.png", 4}},
                {AnimationType::HURT,   {"Hurt.png", 3}},
                {AnimationType::DEAD,   {"Dead.png", 4}}
            }
        }
    },
    {
        SpriteType::SOLDIER_2,
        {
            "assets/Sprites/Players/Soldier_2/",
            {
                {AnimationType::IDLE,   {"Idle.png", 9}},
                {AnimationType::WALK,   {"Walk.png", 8}},
                {AnimationType::RUN,    {"Run.png", 8}},
                {AnimationType::JUMP,   {"Run.png", 8}},
                {AnimationType::MELEE,  {"Attack.png", 4}},
                {AnimationType::SHOOT,  {"Shot_1.png", 4}},
                {AnimationType::HURT,   {"Hurt.png", 3}},
                {AnimationType::DEAD,   {"Dead.png", 4}}
            }
        }
    },
    {
        SpriteType::SOLDIER_3,
        {
            "assets/Sprites/Players/Soldier_3/",
            {
                {AnimationType::IDLE,   {"Idle.png", 7}},
                {AnimationType::WALK,   {"Walk.png", 7}},
                {AnimationType::RUN,    {"Run.png", 8}},
                {AnimationType::JUMP,   {"Run.png", 8}},
                {AnimationType::MELEE,  {"Attack.png", 3}},
                {AnimationType::SHOOT,  {"Shot_1.png", 4}},
                {AnimationType::HURT,   {"Hurt.png", 3}},
                {AnimationType::DEAD,   {"Dead.png", 4}}
            }
        }
    },
    // Enemies
    {
        SpriteType::ZOMBIE_MAN,
        {
            "assets/Sprites/Enemies/Zombie Man/",
            {
                {AnimationType::IDLE,   {"Idle.png", 8}},
                {AnimationType::WALK,   {"Walk.png", 8}},
                {AnimationType::RUN,    {"Run.png", 7}},
                {AnimationType::JUMP,   {"Jump.png", 8}},
                {AnimationType::MELEE,  {"Bite.png", 11}},
                {AnimationType::SHOOT,  {"Attack_1.png", 5}},
                {AnimationType::HURT,   {"Hurt.png", 3}},
                {AnimationType::DEAD,   {"Dead.png", 5}}
            }
        }
    },
    {
        SpriteType::ZOMBIE_WOMAN,
        {
            "assets/Sprites/Enemies/Zombie Woman/",
            {
                {AnimationType::IDLE,   {"Idle.png", 5}},
                {AnimationType::WALK,   {"Walk.png", 7}},
                {AnimationType::RUN,    {"Run.png", 7}},
                {AnimationType::JUMP,   {"Jump.png", 6}},
                {AnimationType::MELEE,  {"Attack_1.png", 11}},
                {AnimationType::SHOOT,  {"Scream.png", 6}},
                {AnimationType::HURT,   {"Hurt.png", 3}},
                {AnimationType::DEAD,   {"Dead.png", 5}}
            }
        }
    },
    {
        SpriteType::WILD_ZOMBIE,
        {
            "assets/Sprites/Enemies/Wild Zombie/",
            {
                {AnimationType::IDLE,   {"Idle.png", 9}},
                {AnimationType::WALK,   {"Walk.png", 10}},
                {AnimationType::RUN,    {"Run.png", 8}},
                {AnimationType::JUMP,   {"Jump.png", 6}},
                {AnimationType::MELEE,  {"Attack_2.png", 4}},
                {AnimationType::SHOOT,  {"Attack_1.png", 4}},
                {AnimationType::HURT,   {"Hurt.png", 5}},
                {AnimationType::DEAD,   {"Dead.png", 5}}
            }
        }
    },
    {
        SpriteType::DESTROYER,
        {
            "assets/Sprites/Enemies/Destroyer/",
            {
                {AnimationType::IDLE,   {"Idle.png", 5}},
                {AnimationType::WALK,   {"Walk.png", 8}},
                {AnimationType::RUN,    {"Walk.png", 8}},
                {AnimationType::JUMP,   {"Attack_2.png", 3}},
                {AnimationType::MELEE,  {"Attack_1.png", 3}},
                {AnimationType::SHOOT,  {"Shot_1.png", 8}},
                {AnimationType::HURT,   {"Hurt.png", 3}},
                {AnimationType::DEAD,   {"Dead.png", 7}}
            }
        }
    },
    {
        SpriteType::INFANTRYMAN,
        {
            "assets/Sprites/Enemies/Infantryman/",
            {
                {AnimationType::IDLE,   {"Idle.png", 6}},
                {AnimationType::WALK,   {"Walk.png", 6}},
                {AnimationType::RUN,    {"Walk.png", 6}},
                {AnimationType::JUMP,   {"Attack_2.png", 3}},
                {AnimationType::MELEE,  {"Attack_1.png", 17}},
                {AnimationType::SHOOT,  {"Shot_1.png", 11}},
                {AnimationType::HURT,   {"Hurt.png", 4}},
                {AnimationType::DEAD,   {"Dead.png", 5}}
            }
        }
    },
    {
        SpriteType::SWORDSMAN,
        {
            "assets/Sprites/Enemies/Swordsman/",
            {
                {AnimationType::IDLE,   {"Idle.png", 5}},
                {AnimationType::WALK,   {"Pick_Up.png", 8}},
                {AnimationType::RUN,    {"Pick_Up.png", 8}},
                {AnimationType::JUMP,   {"Attack_2.png", 2}},
                {AnimationType::MELEE,  {"Attack_1.png", 4}},
                {AnimationType::SHOOT,  {"Attack_4.png", 2}},
                {AnimationType::HURT,   {"Hurt.png", 3}},
                {AnimationType::DEAD,   {"Dead.png", 4}}
            }
        }
    },
};