#ifndef SHIELDTURRET_HPP
#define SHIELDTURRET_HPP
#include "Turret.hpp"
#include "Engine/Sprite.hpp"



class ShieldTurret : public Turret {
public:
    Engine::Sprite shieldSprite;
    static const int Price;
    int shield=8;
    ShieldTurret(float x, float y);
    void CreateBullet() override;
    void Draw() const override;
    void NotDamage();
};
#endif   // SHIELDTURRET_HPP
