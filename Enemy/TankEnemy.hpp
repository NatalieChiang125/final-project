#ifndef TANKENEMY_HPP
#define TANKENEMY_HPP
#include "Enemy.hpp"
#include "Engine/Sprite.hpp"
#include "Turret/Turret.hpp"

class TankEnemy : public Enemy {
private:
    Sprite head;
    float targetRotation;
    Turret* targetTurret = nullptr;
    float reload = 0;
    float bulletCooldown = 0.0f;

public:
    TankEnemy(int x, int y);
    void Draw() const override;
    void Update(float deltaTime) override;
    void ShootBullet();
};
#endif   // TANKENEMY_HPP
