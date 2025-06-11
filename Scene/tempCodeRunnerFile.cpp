#include "RhythmGameScene.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/LOG.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/ImageButton.hpp"
#include "Enemy/NoteEnemy.hpp"
#include "RhythmGameConfig.hpp"
#include <cmath>
#include <allegro5/allegro_primitives.h>


void RhythmGameScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    NoteGroup = new Engine::Group();
    AddNewObject(NoteGroup);

    AddNewObject(new Engine::Label(" Rhythm Game ", "pirulen.ttf", 48, halfW, halfH / 3, 255, 255, 255, 255, 0.5, 0.5));

    // Back 按鈕
    Engine::ImageButton* btn = new Engine::ImageButton(
        "stage-select/dirt.png", "stage-select/floor.png",
        halfW - 200, halfH * 3 / 2, 400, 100
    );
    btn->SetOnClickCallback(std::bind(&RhythmGameScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 36, halfW, halfH * 3 / 2 + 50, 0, 0, 0, 255, 0.5, 0.5));

    // 判定線提示 Label
    //AddNewObject(new Engine::Label("?", "pirulen.ttf", 36, w / 2, TARGET_Y, 255, 255, 0, 255, 0.5, 0.5));

    // 播放背景音樂
    bgmInstance = AudioHelper::PlaySample("select.ogg", false, AudioHelper::BGMVolume);
    if (bgmInstance && bgmInstance.get()) {
        al_set_sample_instance_position(bgmInstance.get(), 0);
    } else {
        Engine::LOG(Engine::ERROR) << "[ERROR] bgmInstance 播放失敗！";
    }

    noteData = {
        {1000, 0},
        {1500, 1},
        {2000, 2},
        {2500, 1},
        {3000, 0},
    };
    nextNote = 0;
}

void RhythmGameScene::Update(float deltaTime) {
    IScene::Update(deltaTime);

    float currentTime = al_get_sample_instance_position(bgmInstance.get()) * 1000.0f;

    // 檢查是否要生成新的 note
    while (nextNote < noteData.size() && noteData[nextNote].time <= currentTime) {
        auto& note = noteData[nextNote];
        NoteGroup->AddNewObject(new NoteEnemy(note.lane, note.time));
        nextNote++;
    }
}

void RhythmGameScene::OnKeyDown(int keyCode) {
    int lane = -1;
    if (keyCode == ALLEGRO_KEY_Z) lane = 0;
    else if (keyCode == ALLEGRO_KEY_X) lane = 1;
    else if (keyCode == ALLEGRO_KEY_C) lane = 2;
    if (lane == -1) return;

    for (auto it = NoteGroup->GetObjects().begin(); it != NoteGroup->GetObjects().end(); ++it) {
        auto* note = dynamic_cast<NoteEnemy*>(*it);
        if (!note) continue;
        if (note->scored || note->lane != lane) continue;

        float diffY = abs(note->Position.y - TARGET_Y);
        if (diffY <= JUDGE_THRESHOLD) {
            note->Visible = false;
            note->scored = true;
            Engine::LOG(Engine::INFO) << ">> HIT!";
            break;
        }
    }
}
void RhythmGameScene::Draw() const {
    IScene::Draw(); 

    int screenW = Engine::GameEngine::GetInstance().GetScreenSize().x;
    al_draw_line(
        0, TARGET_Y,
        screenW, TARGET_Y,
        al_map_rgb(255, 0, 0),
        4.0f                   
    );
}

void RhythmGameScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}

void RhythmGameScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("start");
}
