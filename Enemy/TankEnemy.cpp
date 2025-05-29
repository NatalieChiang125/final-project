#include <allegro5/base.h>
#include <random>
#include <string>

#include "Engine/Point.hpp"
#include "TankEnemy.hpp"
#include "Turret/Turret.hpp"
#include "Turret/ShieldTurret.hpp"
#include "Bullet/Bullet.hpp"
#include "Bullet/Rocket.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Scene/PlayScene.hpp"

TankEnemy::TankEnemy(int x, int y)
    : Enemy("play/enemy-3.png", x, y, 20, 20, 100, 50),
      head("play/enemy-3-head.png", x, y), targetRotation(0) {
}
void TankEnemy::Draw() const {
    Enemy::Draw();
    head.Draw();
}
/*void TankEnemy::Update(float deltaTime) {
    Enemy::Update(deltaTime);
    head.Position = Position;
    // Choose arbitrary one.
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist(0.0f, 4.0f);
    float rnd = dist(rng);
    if (rnd < deltaTime) {
        // Head arbitrary rotation.
        std::uniform_real_distribution<> distRadian(-ALLEGRO_PI, ALLEGRO_PI);
        targetRotation = distRadian(rng);
    }
    head.Rotation = (head.Rotation + deltaTime * targetRotation) / (1 + deltaTime);
}*/

void TankEnemy::Update(float deltaTime) {
    Enemy::Update(deltaTime);
    head.Position = Position;

    PlayScene* scene = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());

    if (bulletCooldown > 0)
        bulletCooldown -= deltaTime;
    // 找最近的砲台
    Turret* targetTurret = nullptr;
    float minDistance = INFINITY;
    for (auto& obj : scene->TowerGroup->GetObjects()) {
        Turret* turret = dynamic_cast<Turret*>(obj);
        if (!turret) continue;
        float dist = (turret->Position - Position).Magnitude();
        if (dist < minDistance) {
            minDistance = dist;
            targetTurret = turret;
        }
    }

    this->targetTurret = targetTurret; 

    if (targetTurret) {
        // 轉頭部朝向砲台
        Engine::Point diff = targetTurret->Position - Position;
        float desiredRotation = atan2(diff.y, diff.x);

        // 平滑旋轉（你可以調整轉動速度）
        float rotateSpeed = 2 * ALLEGRO_PI; // 每秒可旋轉一圈
        float rotationDiff = desiredRotation - head.Rotation;
        // 確保角度在 -PI 到 PI 之間
        while (rotationDiff > ALLEGRO_PI) rotationDiff -= 2 * ALLEGRO_PI;
        while (rotationDiff < -ALLEGRO_PI) rotationDiff += 2 * ALLEGRO_PI;
        float maxRotate = rotateSpeed * deltaTime;
        if (std::abs(rotationDiff) <= maxRotate)
            head.Rotation = desiredRotation;
        else
            head.Rotation += (rotationDiff > 0 ? 1 : -1) * maxRotate;

        // 判斷是否對準：誤差範圍內可以射擊
        if (std::abs(rotationDiff) < 0.1f && bulletCooldown <= 0) {
            
            ShootBullet();
            //bulletCooldown=20.0f;
        }
    }
}

void TankEnemy::ShootBullet(){
    if(!targetTurret) return;
    Engine::Point direction = (targetTurret->Position - Position).Normalize();
    Engine::Point velocity = direction * 30;  // 控制子彈速度
    Engine::Point startPosition = Position + direction * 8;

    //PlayScene* scene = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());

    //scene->BulletGroup->AddNewObject(new FireBullet(startPosition, velocity, head.Rotation, nullptr));
    //scene->TowerGroup->RemoveNewObject(targetTurret);

    /*ShieldTurret* shieldTurret = dynamic_cast<ShieldTurret*>(targetTurret);
    if (shieldTurret) {
        shieldTurret->NotDamage();
    } else {
        getPlayScene()->TowerGroup->RemoveNewObject(targetTurret);
    }*/

    getPlayScene()->BulletGroup->AddNewObject(new Rocket(startPosition, velocity, head.Rotation, targetTurret));
    //getPlayScene()->TowerGroup->RemoveNewObject(targetTurret);
    bulletCooldown = 5.0f;
    // 可選播放音效
    AudioHelper::PlayAudio("gun.wav");
}
