#include "level.h"

std::string path = "C:\\Users\\Chris\\Documents\\Masters\\C++\\Project\\Star Hunter\\Sprites\\Destroyer\\Idle.png";

Level::Level() : player(400, 225, path, 1), controller(player) {}

void Level::Update() {
    controller.HandleInput();
}

void Level::Draw() {
    player.Draw();
}