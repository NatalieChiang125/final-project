#include <allegro5/base.h>
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <string>

#include "Bullet/TurretFire.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"
#include "ShieldTurret.hpp"
#include "Scene/PlayScene.hpp"

const int ShieldTurret::Price = 300;
ShieldTurret::ShieldTurret(float x, float y) 
    : Turret("play/tower-base.png", "play/turret-5.png", x, y, 400, Price, 0.5), 
      shieldSprite("play/Shield.png",x,y) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
    shieldSprite.Tint = al_map_rgba(255, 255, 255, 180);
    shieldSprite.Anchor = Engine::Point(0.5,0.5);
}
void ShieldTurret::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    //Engine::Point normal = Engine::Point(-normalized.y, normalized.x);
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new TurretFire(Position + normalized * 36, diff, rotation, this));
    //getPlayScene()->BulletGroup->AddNewObject(new LaserBullet(Position + normalized * 36 + normal * 6, diff, rotation, this));
    AudioHelper::PlayAudio("laser.wav");
}

void ShieldTurret::NotDamage(){
    if(shield>0){
        shield--;
        AudioHelper::PlayAudio("missile.wav");
    } else{
        getPlayScene()->TowerGroup->RemoveNewObject(this);
    }
}

void ShieldTurret::Draw() const{
    Turret::Draw();
    if(shield>0){
        al_draw_circle(Position.x, Position.y, CollisionRadius + 5, al_map_rgba(135, 206, 250, 180), 4);         
        const_cast<Engine::Sprite&>(shieldSprite).Position = Position;
        if(shield<8)
            shieldSprite.Draw(); 
    }
}
