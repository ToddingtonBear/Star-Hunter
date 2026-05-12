#pragma once
#include "Player.h"

class Controller {
public:
    Player* player; // Pointer to the player

    Controller() : player(nullptr) {}
    Controller(Player* p);

    void HandleInput(); // Handle ALL input (movement, attacks, etc.)
};