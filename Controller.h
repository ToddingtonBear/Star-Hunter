#pragma once
#include "player.h"

class Controller {
public:
    Player& player;

    Controller(Player& p);
    void HandleInput();
};