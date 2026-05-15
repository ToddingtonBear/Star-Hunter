#include "Controller.h"
#include "raylib.h"
#include <iostream>

Controller::Controller(Player* p) : player(p) {}

void Controller::HandleInput() {
    if (!player) return;

    // --- Movement Input ---
    player->isMoving = false;
    if (IsKeyDown(KEY_D)) {     // RIGHT
        player->position.x += player->speed;
        player->isMoving = true;
        //player->SetFacingDirection(true);
    }
    if (IsKeyDown(KEY_A)) {     // LEFT
        player->position.x -= player->speed;
        player->isMoving = true;
        //player->SetFacingDirection(false);
    }
    if (IsKeyDown(KEY_W)) {     // UP
        player->position.y -= player->speed;
        player->isMoving = true;
    }
    if (IsKeyDown(KEY_S)) {  // DOWN
        player->position.y += player->speed;
        player->isMoving = true;
    }

    // --- Aiming Direction ---
    Vector2 mousePos = GetMousePosition();
    Vector2 toMouse = { mousePos.x - player->position.x, mousePos.y - player->position.y };
    float length = sqrt(toMouse.x * toMouse.x + toMouse.y * toMouse.y);
    if (length > 0) {
        player->aimingDirection = { toMouse.x / length, toMouse.y / length };
        // Set facing direction based on mouse position (left/right)
        player->SetFacingDirection(toMouse.x > 0);
    }

    // --- Attack Input ---
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        std::cout << "MELEE pressed" << std::endl;
        player->Melee();
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        player->Shoot(player->aimingDirection);
    }
}