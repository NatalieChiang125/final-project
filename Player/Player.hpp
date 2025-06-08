#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <allegro5/base.h>
#include <list>
#include <string>
#include <set>

#include "Engine/Sprite.hpp"

class Enemy;
class PlayScene;

class Player : public Engine::Sprite {
protected:
   
    float hp;
   
    PlayScene *getPlayScene();
    // Reference: Design Patterns - Factory Method.
public:
    Player(std::string imgPlayer, float x, float y, int spriteW, int spriteH);
    void Update(float deltaTime) override;
    void Draw() const override;
    void OnKeyDown(int keyCode);
    void OnKeyUp(int keyCode);
private:
    std::set<int> keyDown; //記錄目前被按著的按鍵
    float speed = 128.0f; //移動速度
    enum Direction {
        DIR_DOWN = 0,
        DIR_LEFT = 1,
        DIR_RIGHT = 2,
        DIR_UP = 3
    };

    Direction direction = DIR_DOWN;
    float walkTime = 0;          // 動畫速度
    int currentFrame = 0;        // 目前的動畫幀
    float frameDuration = 0.15f; // 每幀持續多久
    int frameCount = 3;          // 每方向幀數
    int spriteWidth = 64;        // 單格寬度
    int spriteHeight = 66;       // 單格高度

};
#endif   // TURRET_HPP
