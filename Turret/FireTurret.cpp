#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Bullet/BoomBullet.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"
#include "FireTurret.hpp"
#include "Scene/PlayScene.hpp"

const int FireTurret::Price = 250;
FireTurret::FireTurret(float x, float y) 
    : Turret("play/tower-base.png", "play/turret-3.png", x, y, 400, Price, 0.5) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}
void FireTurret::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    //Engine::Point normal = Engine::Point(-normalized.y, normalized.x);
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new BoomBullet(Position + normalized * 36, diff, rotation, this));
    //getPlayScene()->BulletGroup->AddNewObject(new LaserBullet(Position + normalized * 36 + normal * 6, diff, rotation, this));
    AudioHelper::PlayAudio("laser.wav");
}

