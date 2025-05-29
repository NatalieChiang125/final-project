#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <allegro5/base.h>
#include <list>
#include <string>

#include "Engine/Sprite.hpp"

class Enemy;
class PlayScene;

class Player : public Engine::Sprite {
protected:
   
    float hp;
   
    PlayScene *getPlayScene();
    // Reference: Design Patterns - Factory Method.
public:
    Player(std::string imgPlayer, float x, float y);
    void Update(float deltaTime) override;
    void Draw() const override;
    void OnKeyDown(int keyCode);
};
#endif   // TURRET_HPP
