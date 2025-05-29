#ifndef SMALLENEMY_HPP
#define SMALLENEMY_HPP
#include "Enemy.hpp"
#include "Turret/Turret.hpp"

class Turrent;

class SmallEnemy : public Enemy {
protected:
    Turret* target;
public:
    
    SmallEnemy(int x, int y,Turret* target);
    void Update(float deltaTime) override;
};

#endif  // SMALLENEMY_HPP
