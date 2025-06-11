#include "DailyScene.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/ImageButton.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/PlayerStat.hpp"
#include "Scene/PlayScene.hpp"

#include "fstream"
#include "ctime"
#include <iostream>
#include <ostream>
#include <cmath>

DailyScene::DailyScene() : currentDay(0), totalMoney(150), checkedIn(7, false) {}

void DailyScene::Initialize() {

    LoadStatus();
    
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    
    // 顯示標題與金額
    AddNewObject(new Engine::Label("Daily Check-In", "pirulen.ttf", 64, halfW, 80, 255, 255, 255, 255, 0.5, 0.5));
    //AddNewObject(new Engine::Label("Total Coins: " + std::to_string(totalMoney), "pirulen.ttf", 32, halfW, 140, 255, 255, 0, 255, 0.5, 0.5));
    //coinLabel = std::make_shared<Engine::Label>("Total Coins: " + std::to_string(totalMoney), "pirulen.ttf", 32, halfW, 140, 255, 255, 0, 255, 0.5, 0.5);
    //AddNewObject(coinLabel.get());
    coinLabel = new Engine::Label("Total Coins: " + std::to_string(totalMoney),
                              "pirulen.ttf", 32, halfW, 140, 255, 255, 0, 255, 0.5, 0.5);
    AddNewObject(coinLabel);


    // 打卡格 + 按鈕
    for (int i = 0; i < 7; ++i) {
        int boxX = 150 + i * 180;
        int boxY = 250;

        // 顯示第幾天
        AddNewObject(new Engine::Label("Day " + std::to_string(i + 1), "pirulen.ttf", 24, boxX + 50, boxY - 25, 255, 255, 255, 255, 0.5, 0.5));

        // 打卡狀態
        std::string img = checkedIn[i] ? "stage-select/checked.png" : "stage-select/unchecked.png";
        AddNewObject(new Engine::Image(img, boxX, boxY+50, 100, 100));

        // 打卡按鈕
        Engine::ImageButton* btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", boxX-20, boxY + 200, 140, 50);
        btn->SetOnClickCallback([=]() {
            this->OnCheckInClick(i);
        });
        AddNewControlObject(btn);
        AddNewObject(new Engine::Label("Check-In", "pirulen.ttf", 20, boxX + 50, boxY + 225, 0, 0, 0, 255, 0.5, 0.5));
    }

    // 返回按鈕
    auto backBtn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 100, h - 100, 200, 60);
    backBtn->SetOnClickCallback(std::bind(&DailyScene::BackOnClick, this));
    AddNewControlObject(backBtn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 28, halfW, h - 70, 0, 0, 0, 255, 0.5, 0.5));
}

void DailyScene::OnCheckInClick(int day) {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    if (day != currentDay){
        AddNewObject(new Engine::Label("You have checked in today!", "pirulen.ttf", 28, halfW, h -200, 255, 255, 255, 255, 0.5, 0.5));
        return;
    }
    if (checkedIn[day]){
        AddNewObject(new Engine::Label("You have checked in today!", "pirulen.ttf", 28, halfW, h -200, 255, 255, 255, 255, 0.5, 0.5));
        std::cout << "Already checked in today." << std::endl;
        return;
    }

    // 打卡成功
    checkedIn[day] = true;
    totalMoney += day+1;
    PlayerStat::totalMoney=totalMoney;
    /*PlayScene* playScene = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
    if (playScene) {
        playScene->EarnMoney(day + 1);
    }*/
    //PlayScene::EarnMoney(int(day+1));
    //currentDay = (currentDay + 1) % 7; // 第8天回到第1天
    coinLabel->Text = "Total Coins: " + std::to_string(totalMoney);
    SaveStatus();
    Engine::GameEngine::GetInstance().ChangeScene("daily"); // 重整畫面
}

void DailyScene::SaveStatus() {
    std::ofstream out("daily_status.txt");
    if (!out) return;
    out << totalMoney << '\n';
    out << currentDay << '\n';
    time_t now = time(0);
    out << now << '\n';
    for (bool c : checkedIn)
         out << (c ? 1 : 0) << '\n';
    out.close();
    PlayerStat::totalMoney = totalMoney;

    //std::filesystem::path p = std::filesystem::absolute("daily_status.txt");
    //std::cout << "Saving to: " << p << std::endl;
}

void DailyScene::LoadStatus() {
    std::ifstream in("daily_status.txt");
    if (!in.is_open()) {
        // 檔案不存在，建立並初始化一份
        std::ofstream out("daily_status.txt");
        out << 150 << '\n'; // totalMoney
        out << 0 << '\n'; // currentDay
        time_t now = time(0);
        out << now << '\n';
        for (int i = 0; i < 7; ++i) {
            out << 0 << '\n'; // checkedIn (bools)
        }
        //out << '\n';
        out.close();
        // 重新讀取剛建立的檔案
        in.open("daily_status.txt");
        if (!in.is_open()) return; // 若仍失敗，就回傳
    }
    time_t lastTime;
    in >> totalMoney;
    PlayerStat::totalMoney = totalMoney;
    in >> currentDay;
    in >> lastTime;
    for (int i = 0; i < 7; ++i) {
        //in >> checkedIn[i];
        int temp;
        in >> temp;
        checkedIn[i] = temp != 0;
    }

    //checkedIn[currentDay] = false;
    // 檢查是否隔日
    time_t now = time(0);
    tm nowTm = *localtime(&now);
    tm lastTm = *localtime(&lastTime);

    if (nowTm.tm_year != lastTm.tm_year || nowTm.tm_yday != lastTm.tm_yday) {
        currentDay = (currentDay + 1) % 7;
        if (currentDay == 0)
            checkedIn = std::vector<bool>(7, false);
        else
            checkedIn[currentDay] = false;
        SaveStatus();
    }


    in.close();
    std::cout << "currentDay: " << currentDay << ", checkedIn: ";
    for (bool b : checkedIn) std::cout << b << ' ';
    std::cout << std::endl;
}

void DailyScene::BackOnClick() {
    Engine::GameEngine::GetInstance().ChangeScene("start");
}

void DailyScene::Terminate() {
    IScene::Terminate();
}