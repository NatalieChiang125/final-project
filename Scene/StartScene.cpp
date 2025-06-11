//
// Created by Hsuan on 2024/4/10.
//

#include "StartScene.h"
#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "PlayScene.hpp"
#include "Scene/StartScene.h"
#include "Scene/ScoreBoardScene.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/Slider.hpp"

// TODO HACKATHON-2 (1/3): You can imitate the 2 files: 'StartScene.hpp', 'StartScene.cpp' to implement your SettingsScene.(okay)
void StartScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton *btn;

    AddNewObject(new Engine::Label("Tower Defense", "pirulen.ttf", 120, halfW, halfH / 3 + 50, 10, 255, 255, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH / 2 + 200, 400, 100);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Play", "pirulen.ttf", 48, halfW, halfH / 2 + 250, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2 - 80, 400, 100);
    btn->SetOnClickCallback(std::bind(&StartScene::SettingsOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Settings", "pirulen.ttf", 48, halfW, halfH * 3 / 2 - 30, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 235, halfH * 3 / 2 + 50, 480, 100);
    btn->SetOnClickCallback(std::bind(&StartScene::ScoreBoardOnClick, this, 3));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("ScoreBoard", "pirulen.ttf", 48, halfW, halfH * 3 / 2 + 100, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 500, halfH -375, 200, 50);
    btn->SetOnClickCallback(std::bind(&StartScene::DailyOnClick, this, 4));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Reward", "pirulen.ttf", 25, halfW+600, halfH-350, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 500, halfH -375, 200, 50);
    btn->SetOnClickCallback(std::bind(&StartScene::QuizOnClick, this, 4));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Quiz", "pirulen.ttf", 25, halfW-400, halfH-350, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 500, halfH - 300, 200, 50);
    btn->SetOnClickCallback(std::bind(&StartScene::RhythmOnClick, this, 5));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Rhythm", "pirulen.ttf", 25, halfW + 600, halfH - 275, 0, 0, 0, 255, 0.5, 0.5));

}
void StartScene::Terminate() {
    IScene::Terminate();
}
void StartScene::PlayOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
void StartScene::SettingsOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("settings");
}
void StartScene::ScoreBoardOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("scoreBoard");
}

void StartScene::DailyOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("daily");
}

void StartScene::QuizOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("quiz");
}
void StartScene::RhythmOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("rhythm");
}