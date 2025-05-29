#ifndef TURRETFIRE_HPP
#define TURRETFIRE_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
    struct Point;
}   // namespace Engine

class TurretFire : public Bullet {
public:
    explicit TurretFire(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret *parent);
    void OnExplode(Enemy *enemy) override;
};
#endif   // TURRETFIRE_HPP
