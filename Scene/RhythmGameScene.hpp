#ifndef RHYTHM_GAME_SCENE_HPP
#define RHYTHM_GAME_SCENE_HPP

#include <memory>
#include <vector>
#include <allegro5/allegro_audio.h>
#include "Engine/IScene.hpp"
#include "Engine/Group.hpp"
#include "UI/Component/Label.hpp"
#include <fstream>

class RhythmGameScene final : public Engine::IScene {
private:
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;

    struct Note {
        float time;
        int lane;
        Note(int t, int l) : time(t), lane(l) {} 
    };
    std::vector<Note> noteData;
    size_t nextNote = 0;
    Engine::Group* NoteGroup;

    int score = 0;
    Engine::Label* scoreLabel = nullptr;

public:
    void Initialize() override;
    void Terminate() override;
    void BackOnClick(int stage);
    void Update(float deltaTime) override;
    void OnKeyDown(int keyCode) override;
    void Draw() const override;
    float GetCurrentTime() const {
        if (!bgmInstance) return 0;
        return al_get_sample_instance_position(bgmInstance.get()) * 1000.0f;
    }
    bool recordMode = false;
    std::ofstream recordOut;
};

#endif
