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
#include "Scene/PlayScene.hpp"
#include "Player.hpp"


PlayScene *Player::getPlayScene() {
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}

Player::Player(std::string imgPlayer, float x, float y) : Sprite(imgPlayer, x, y){ 
    hp = 3;
}

void Player::Update(float deltaTime) {
    Sprite::Update(deltaTime);
    PlayScene *scene = getPlayScene(); 
}

void Player::OnKeyDown(int keyCode){

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
}

void Player::Draw() const {
    Sprite::Draw();
}