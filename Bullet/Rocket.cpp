#include <allegro5/base.h>
#include <random>
#include <string>
#include <iostream>

#include "Enemy/Enemy.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"
#include "Rocket.hpp"
#include "Scene/PlayScene.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "Turret/ShieldTurret.hpp"

class Turret;

Rocket::Rocket(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret *parent)
     : Bullet("play/bullet-10.png", 500, 1, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
        targetTurret=parent;
}
void Rocket::OnExplode(Turret* turret) {
    if (turret == targetTurret) {
        ShieldTurret* shieldTurret = dynamic_cast<ShieldTurret*>(turret);
        if (shieldTurret) {
            shieldTurret->NotDamage();
        } else {
            getPlayScene()->TowerGroup->RemoveNewObject(turret);

        }
        getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-1.png", 10, turret->Position.x, turret->Position.y));
    }
}

void Rocket::Update(float deltaTime){
    // 更新子彈位置
    Sprite::Update(deltaTime);
    Position.x += Velocity.x * deltaTime;
    Position.y += Velocity.y * deltaTime;

    // 檢查是否撞到目標砲台
    if (targetTurret && (Position - targetTurret->Position).Magnitude() <= CollisionRadius + targetTurret->CollisionRadius) {
        OnExplode(targetTurret); // 自定義行為：可能刪除砲台或觸發效果
        getPlayScene()->BulletGroup->RemoveNewObject(this); // 移除子彈
        return;
    }

    // 如果飛出地圖邊界，也移除自己
    if (Position.x < 0 || Position.x > PlayScene::BlockSize * PlayScene::MapWidth ||
        Position.y < 0 || Position.y > PlayScene::BlockSize * PlayScene::MapHeight) {
        getPlayScene()->BulletGroup->RemoveNewObject(this);
    }
}
