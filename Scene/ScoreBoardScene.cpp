#include "ScoreBoardScene.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/ImageButton.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

void ScoreBoardScene::Initialize() {

    scores.clear();
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int halfW = w / 2;

    // 讀取 scores.txt
    //std::ifstream fin("Resource/scoreboard.txt");
    std::string scorePath = "scoreboard.txt";
    std::ifstream fin(scorePath);
    if (!fin.is_open()) {
        std::cerr << "Error: Cannot open " << scorePath << "!" << std::endl;
        return;
    }
    std::string name, datatime;
    float time;
    AddNewObject(new Engine::Label("Leaderboard", "pirulen.ttf", 48, halfW, 50, 255, 255, 255, 255, 0.5, 0.5));

    while (fin >> name >> time) {
        std::getline(fin, datatime);
        if (!datatime.empty() && datatime[0] == ' ') datatime.erase(0,1);
        scores.push_back({name, time, datatime});
    }
    fin.close();

    // 排序
    std::sort(scores.begin(), scores.end(), [](const ScoreRecord& a, const ScoreRecord& b) {
        return a.time < b.time;
    });

    
    

    /*for (int i = 0; i < std::min(5, (int)scores.size()); ++i) {
        std::stringstream ss;
        ss << i + 1 << ". " << scores[i].first << " - " << scores[i].second << "s";
        AddNewObject(new Engine::Label(ss.str(), "pirulen.ttf", 32, halfW, 120 + i * 50, 255, 255, 200, 255, 0.5, 0.5));
    }*/

    page=0;

    ReadPage();

    // Prev Button
    Engine::ImageButton* prevBtn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 250, 550, 150, 60);
    prevBtn->SetOnClickCallback([this]() {
        if (page > 0) {
            --page;
            ReadPage();
        }
    });
    AddNewControlObject(prevBtn);
    AddNewObject(new Engine::Label("Prev", "pirulen.ttf", 32, halfW - 175, 580, 0, 0, 0, 255, 0.5, 0.5));

    // Next Button
    Engine::ImageButton* nextBtn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW + 100, 550, 150, 60);
    nextBtn->SetOnClickCallback([this]() {
        if ((page + 1) * scoresPerPage < scores.size()) {
            ++page;
            ReadPage();
        }
    });
    AddNewControlObject(nextBtn);
    AddNewObject(new Engine::Label("Next", "pirulen.ttf", 32, halfW + 175, 580, 0, 0, 0, 255, 0.5, 0.5));


    // 返回按鈕
    Engine::ImageButton* btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, 650, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::BackOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, 700, 0, 0, 0, 255, 0.5, 0.5));

    bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
}

void ScoreBoardScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}

void ScoreBoardScene::BackOnClick(int) {
    Engine::GameEngine::GetInstance().ChangeScene("start");
}

void ScoreBoardScene::ReadPage(){
    for(auto label:scoreLabels){
       RemoveNewObject(label);
    }
    scoreLabels.clear();
    int halfW = Engine::GameEngine::GetInstance().GetScreenSize().x / 2;
    int startIndex = page * scoresPerPage;
    int endIndex = std::min((int)scores.size(), startIndex + scoresPerPage);

    for (int i = startIndex; i < endIndex; ++i) {
        std::stringstream ss;
        ss << i + 1 << ". " << scores[i].name << " - " << scores[i].time << "s";
        auto label = new Engine::Label(ss.str(), "pirulen.ttf", 32, halfW, 120 + (i - startIndex) * 50, 255, 255, 200, 255, 0.5, 0.5);
        scoreLabels.push_back(label);
        AddNewObject(label);
        int y = 120 + (i - startIndex) * 50;
        auto timeLabel = new Engine::Label("        (" + scores[i].datatime + ")", "pirulen.ttf", 24, halfW + 220, y, 180, 180, 255, 255, 0.0, 0.5);
        scoreLabels.push_back(timeLabel);
        AddNewObject(timeLabel);
    }
}
