#ifndef ROCKET_HPP
#define ROCKET_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
    struct Point;
}   // namespace Engine

class Rocket : public Bullet {
protected:
    Turret* targetTurret;
public:
    //Turret* targetTurret;
    explicit Rocket(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret *parent);
    void OnExplode(Turret* turret);
    void Update(float deltaTime);
};
#endif   // FIREBULLET_HPP
