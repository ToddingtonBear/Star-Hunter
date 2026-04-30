#pragma once
#include "player.h"
#include "controller.h"

class Level {
public:
    Player player;
    Controller controller;

    Level();
    void Update();
    void Draw();
};