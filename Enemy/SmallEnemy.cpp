#include <string>
#include <cmath>
#include "SmallEnemy.hpp"
#include "Scene/PlayScene.hpp"

SmallEnemy::SmallEnemy(int x, int y,Turret* target)
    : Enemy("play/ghost.png", x, y, 10, 50, 5, 5), target(target) {
}

void SmallEnemy::Update(float deltaTime){
    if(!target) return;
    float dx=target->Position.x - Position.x;
    float dy=target->Position.y - Position.y; 
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance > 1e-6) {
        float vx = speed * dx / distance;
        float vy = speed * dy / distance;
        Position.x += vx * deltaTime;
        Position.y += vy * deltaTime;
    }

    Rotation = std::atan2(dy, dx);
}
    