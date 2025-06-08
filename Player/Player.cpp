#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <utility>
#include <iostream>

#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/map.hpp"
#include "Scene/PlayScene.hpp"
#include "Player.hpp"


PlayScene *Player::getPlayScene() {
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}

Player::Player(std::string imgPlayer, float x, float y, int spriteW, int spriteH) : 
    Sprite(imgPlayer, x, y), spriteWidth(spriteW), spriteHeight(spriteH),
    currentFrame(0), direction(DIR_DOWN), walkTime(0), frameDuration(0.2f), frameCount(3){ 
    hp = 10;
}

void Player::Update(float deltaTime) {
    Sprite::Update(deltaTime);
    PlayScene *scene = getPlayScene();
    Cam = scene->Camera;
    if (!scene || !scene->map) return;
    Engine::Point velocity(0, 0);
    if (keyDown.count(ALLEGRO_KEY_W)) velocity.y -= 1;
    if (keyDown.count(ALLEGRO_KEY_S)) velocity.y += 1;
    if (keyDown.count(ALLEGRO_KEY_A)) velocity.x -= 1;
    if (keyDown.count(ALLEGRO_KEY_D)) velocity.x += 1;

    if (velocity.x != 0 || velocity.y != 0) {
        // 進行 normalize 避免斜對角比單方向快
        float length = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        velocity.x = velocity.x / length * speed * deltaTime;
        velocity.y = velocity.y / length * speed * deltaTime;

        if (std::abs(velocity.x) > std::abs(velocity.y)) {
            direction = (velocity.x > 0) ? DIR_RIGHT : DIR_LEFT;
        } else {
            direction = (velocity.y > 0) ? DIR_DOWN : DIR_UP;
        }
        walkTime += deltaTime;
        if (walkTime >= frameDuration) {
            walkTime -= frameDuration;
            currentFrame = (currentFrame + 1) % frameCount;
        }

        Engine::Point newPos = Position + velocity;

        if(newPos.x<20) newPos.x=20;
        if(newPos.y<35) newPos.y=35;

        int mapWidth=(scene->map->GetWidth())*PlayScene::BlockSize;
        int mapHeight=(scene->map->GetHeight())*PlayScene::BlockSize;

        if(newPos.x > mapWidth*(2.25)-spriteWidth+10) newPos.x = mapWidth*(2.25)-spriteWidth+10;
        if(newPos.y > mapHeight*(2)-spriteHeight+20) newPos.y = mapHeight*(2)-spriteHeight+20;

        Engine::Point tilePos = scene->map->WorldToTile(newPos);
        //PlayScene* scene = getPlayScene();
        /*if (scene && scene->map) {
            Engine::Point tilePos = scene->map->WorldToTile(newPos);
            if (scene->map->isWalkable(scene->map->GetBlock(tilePos))) {
                Position = newPos;
            }
        }*/
       if (scene->map->isWalkable(scene->map->GetBlock(tilePos))) {
            Position = newPos;
        }
    }
    else{
        currentFrame=0;
    }
}

/*void Player::OnKeyDown(int keyCode){

    float moveDist = 32.0f; // tile 大小
    PlayScene* scene = getPlayScene();
    if (!scene) {
        std::cout << "Scene is null!\n";
        return;
    }
    if (!scene->map) {
        std::cout << "Map is null!\n";
        return;
    }
    
    Engine::Point newPos = Position;
    if (keyCode == ALLEGRO_KEY_A)
        newPos.x -= moveDist;
    else if (keyCode == ALLEGRO_KEY_D)
        newPos.x += moveDist;
    else if (keyCode == ALLEGRO_KEY_W)
        newPos.y -= moveDist;
    else if (keyCode == ALLEGRO_KEY_S)
        newPos.y += moveDist;

    Engine::Point tilePos = scene->map->WorldToTile(newPos);
    if (scene->map->isWalkable(scene->map->GetBlock(tilePos))) {
        Position = newPos;
    }
    //Position = newPos;
}*/
void Player::OnKeyDown(int keyCode){
    keyDown.insert(keyCode); // 記錄按下的鍵
}

void Player::OnKeyUp(int keyCode){
    keyDown.erase(keyCode); // 放開時移除
}

void Player::Draw() const {
    int dx = Position.x - Cam.x;
    int dy = Position.y - Cam.y;

    //if(dx<0) dx=0;
    //if(dy<0) dx=0;

    
    //Sprite::Draw();
    al_draw_bitmap_region(
        bmp.get(), // 來自 Engine::Sprite 裡的 ALLEGRO_BITMAP*
        currentFrame * spriteWidth,   // x
        direction * spriteHeight,     // y
        spriteWidth,                  // width
        spriteHeight,                 // height
        dx - Anchor.x * spriteWidth,
        dy - Anchor.y * spriteHeight,
        0
    );
}

void Player::AddHP(int amount){
    hp+=amount;
    if(hp>10) hp=10;
}

int Player::GetHP() const{
    return hp;
}

Engine::Point Player::getCam(){
    return Cam;
}