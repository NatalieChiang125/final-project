#ifndef BOOMBULLET_HPP
#define BOOMBULLET_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
    struct Point;
}   // namespace Engine

class BoomBullet : public Bullet {
public:
    explicit BoomBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret *parent);
    void OnExplode(Enemy *enemy) override;
};
#endif   // FIREBULLET_HPP
