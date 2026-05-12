#include "Controller.h"
#include "raylib.h"

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

    // --- Attack Input ---
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        player->Melee(*player->actors);
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        player->Shoot();
    }
}