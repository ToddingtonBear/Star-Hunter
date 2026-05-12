#include "Projectile.h"
#include "raylib.h"
#include <cmath> // For sqrt()

Projectile::Projectile(float x, float y, SpriteType type, AnimationType animType, float spd, int dmg, Vector2 dir)
    : Entity(x, y, type, animType),
    damage(dmg),
    isActive(true),
    direction(dir),
    speed(spd) {
    // Normalize the direction vector
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0) {
        direction = { direction.x / length, direction.y / length };
    }
}

void Projectile::Update() {
    // Move the projectile in its direction
    position.x += direction.x * speed;
    position.y += direction.y * speed;

    // Deactivate if it goes off-screen
    if (position.x < 0 || position.x > GetScreenWidth() ||
        position.y < 0 || position.y > GetScreenHeight()) {
        isActive = false;
    }
}

void Projectile::Draw() {
    // Use Entity::Draw() to handle sprite flipping and animation
    Entity::Draw();
}

bool Projectile::IsActive() const {
    return isActive;
}