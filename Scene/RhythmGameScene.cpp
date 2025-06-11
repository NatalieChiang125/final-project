#include "RhythmGameScene.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/LOG.hpp"
#include "Engine/PlayerStat.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "Enemy/NoteEnemy.hpp"
#include "RhythmGameConfig.hpp"
#include <cmath>
#include <allegro5/allegro_primitives.h>
#include <fstream>     
#include <random>     
#include <sstream>
#include <vector>

void RhythmGameScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    NoteGroup = new Engine::Group();
    AddNewObject(NoteGroup);

    AddNewObject(new Engine::Label(" Rhythm Game ", "pirulen.ttf", 48, halfW, halfH / 3, 255, 255, 255, 255, 0.5, 0.5));


    score = 0;
    scoreLabel = new Engine::Label("Score: 0", "pirulen.ttf", 28, 100, 50, 255, 255, 255, 255);
    AddNewObject(scoreLabel);

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
    bgmInstance = AudioHelper::PlaySample("rhythm.ogg", false, AudioHelper::BGMVolume);
    if (bgmInstance && bgmInstance.get()) {
        al_set_sample_instance_position(bgmInstance.get(), 0);
    } else {
        Engine::LOG(Engine::ERROR) << "[ERROR] bgmInstance 播放失敗！";
    }

    noteData.clear();
    nextNote = 0;
    const float fallTime = ((TARGET_Y - NOTE_START_Y) / NOTE_SPEED) * 1000.0f;
    std::ifstream fin("Resource/beatmap.txt");
    if (!fin) {
        Engine::LOG(Engine::ERROR) << "[ERROR] beatmap.txt 無法開啟！";
        return;
    }

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> laneDist(0, 2);

    std::string line;
    while (std::getline(fin, line)) {
        std::stringstream ss(line);
        int hitTime;
        if (ss >> hitTime) {
            int lane = laneDist(rng);
            float appearTime = hitTime - fallTime;
            Engine::LOG(Engine::INFO) << "[NOTE SPAWN] hitTime = " << hitTime 
                                  << ", appearTime = " << appearTime 
                                  << ", fallTime = " << fallTime;
            noteData.emplace_back(appearTime, lane);
        }
    }
    if (recordMode) {
        recordOut.open("recorded_beatmap.txt");
        if (!recordOut) {
            Engine::LOG(Engine::ERROR) << "[ERROR] 無法開啟 recorded_beatmap.txt";
            recordMode = false;
        }
    }

}

void RhythmGameScene::Update(float deltaTime) {
    IScene::Update(deltaTime);

    float currentTime = al_get_sample_instance_position(bgmInstance.get()) * 1000.0f; 

    // 檢查是否要生成新的 note
    while (nextNote < noteData.size() && noteData[nextNote].time <= currentTime) {
        auto& note = noteData[nextNote];
        //Engine::LOG(Engine::INFO) << "[SPAWN] Note lane = " << note.lane << ", time = " << note.time;
        
        NoteGroup->AddNewObject(new NoteEnemy(note.lane, note.time));
        nextNote++;
    }
    if (nextNote >= noteData.size() && NoteGroup->GetObjects().empty()) {
        Engine::LOG(Engine::INFO) << "[END] All notes cleared.";
    }
}

void RhythmGameScene::OnKeyDown(int keyCode) {
    int lane = -1;
    if (keyCode == ALLEGRO_KEY_A) lane = 0;
    else if (keyCode == ALLEGRO_KEY_S) lane = 1;
    else if (keyCode == ALLEGRO_KEY_D) lane = 2;
    if (lane == -1) return;

    float hitTime = GetCurrentTime() / 1000.0f; // 抓下按的當下時間（毫秒）
    bool hit = false;
    if (recordMode && recordOut.is_open()) {
        recordOut << static_cast<int>(hitTime) << '\n';
        Engine::LOG(Engine::INFO) << static_cast<int>(hitTime) / 20.0f;
        return;
    }

    const auto& objects = NoteGroup->GetObjects();

    for (auto it = objects.begin(); it != objects.end(); ++it) {
        auto* note = dynamic_cast<NoteEnemy*>(*it);
        if (!note) continue;
        if (note->scored || note->lane != lane) continue;

        float diffY = fabs(note->Position.y - TARGET_Y);
        if (diffY <= JUDGE_THRESHOLD) {
            note->Visible = false;
            note->scored = true;

            score += 100;
            scoreLabel->Text = "Score: " + std::to_string(score);
            Engine::LOG(Engine::INFO) << ">> HIT! [lane " << lane << ", time " << static_cast<int>(hitTime) << "]";
            hit = true;
            break;
        }
    }

    if (!hit) {
        Engine::LOG(Engine::INFO) << ">> MISS! [lane " << lane << ", time " << static_cast<int>(hitTime) << "]";
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
    if (recordOut.is_open()) {
        recordOut.close();
    }
}

void RhythmGameScene::BackOnClick(int stage) {

    PlayerStat::playerY += 80;
    Engine::GameEngine::GetInstance().ChangeScene("play");
    
}
