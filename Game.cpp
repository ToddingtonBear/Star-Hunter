#include "game.h"

void Game::Run() {
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        level.Update();
        BeginDrawing();
        ClearBackground(BLACK);
        level.Draw();
        EndDrawing();
    }

    CloseWindow();
}