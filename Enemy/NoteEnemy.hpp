// NoteEnemy.hpp
#ifndef NOTE_ENEMY_HPP
#define NOTE_ENEMY_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Engine/Sprite.hpp"

class NoteEnemy : public Engine::Sprite {
public:
    int lane;
    float appearTime;
    bool scored = false;

    NoteEnemy(int lane, float appearTime);
    void Update(float deltaTime) override;
};

#endif

