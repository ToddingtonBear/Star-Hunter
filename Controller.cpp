#include "controller.h"

Controller::Controller(Player& p) : player(p) {}

void Controller::HandleInput() {
    player.Update();
}