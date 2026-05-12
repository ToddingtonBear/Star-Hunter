#include "game.h"
#include <filesystem>
#include <iostream>

void Game::Run() {
    SetTargetFPS(60);
    std::cout << "Working directory: " << std::filesystem::current_path() << std::endl;
    while (!WindowShouldClose()) {
        level.Update();
        BeginDrawing();
        ClearBackground(WHITE);
        level.Draw();
        EndDrawing();
    }

    CloseWindow();
}