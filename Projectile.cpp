//#include "projectile.h"
//#include "raylib.h"
//
//Projectile::Projectile(float x, float y, const std::string& sprPath, float spd, int dmg, Vector2 dir)
//    : Actor(x, y, SpriteType::SOLDIER_3, AnimationType::IDLE, spd, 1, dmg), // Health=1, damage=dmg
//    damage(dmg), isActive(true), direction(dir) {
//    // Normalize direction
//    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
//    if (length > 0) {
//        direction = { direction.x / length, direction.y / length };
//    }
//}
//
//void Projectile::Update() {
//    // Move the projectile
//    position.x += direction.x * speed;
//    position.y += direction.y * speed;
//
//    // Deactivate if it goes off-screen
//    if (position.x < 0 || position.x > GetScreenWidth() ||
//        position.y < 0 || position.y > GetScreenHeight()) {
//        isActive = false;
//    }
//
//    Actor::Update();
//}
//
//void Projectile::Draw() {
//    Actor::Draw();
//}
//
//bool Projectile::IsActive() const {
//    return isActive;
//}