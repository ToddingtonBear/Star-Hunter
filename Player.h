#pragma once
#include "Actor.h"

class Player : public Actor {
public:

    Player(float x, float y, const std::string& sprPath, float s);
    virtual ~Player();
    void Update() override;
    void Draw() override;
};