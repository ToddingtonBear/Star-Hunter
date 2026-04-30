#include "player.h"
#include <iostream>

Player::Player(float x, float y, const std::string& spritePath, float s)
    : Actor(x, y, spritePath, s){
}

void Player::Update() {
    // move player if appropriate key is pressed 
    if (IsKeyDown(KEY_RIGHT)) position.x += speed;
    if (IsKeyDown(KEY_LEFT)) position.x -= speed;
    if (IsKeyDown(KEY_UP)) position.y -= speed;
    if (IsKeyDown(KEY_DOWN)) position.y += speed;

    // Call the base class Update() to handle animation
    Actor::Update();
}


void Player::Draw() {
    Actor::Draw(); // Call the base class Draw() to render the sprite
}

Player::~Player() {
    // Texture is unloaded in the base Actor destructor
}