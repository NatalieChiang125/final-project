#include <functional>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <allegro5/allegro.h>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/GameTime.hpp"
#include "PlayScene.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "WinScene.hpp"
#include "ScoreBoardScene.hpp"
//#include "Engine/TextInput.hpp"

//WinScene::WinScene(float gameTime) : gameTime(gameTime) {}

void WinScene::Initialize() {
    ticks = 0;
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    AddNewObject(new Engine::Image("win/benjamin-sad.png", halfW, halfH, 0, 0, 0.5, 0.5));
    AddNewObject(new Engine::Label("You Win!", "pirulen.ttf", 48, halfW, halfH / 4 - 10, 255, 255, 255, 255, 0.5, 0.5));

    submitted=false;
    playerName.clear();
    //GameTime::gameTime=0.0f;
    //GameTime::Reset();

    std::stringstream ss;
    ss<<"Time: "<<GameTime::gameTime<<"s";
    AddNewObject(new Engine::Label(ss.str(), "pirulen.ttf", 32, halfW, halfH / 4 + 40, 200, 255, 200, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("Enter your name:", "pirulen.ttf", 28, halfW, halfH / 4 + 100, 255, 255, 255, 255, 0.5, 0.5));
    //nameInput = std::make_shared<Engine::TextInput>("", "pirulen.ttf", 28, halfW, halfH / 4 + 140, 255, 255, 255, 255, 0.5, 0.5);
    //nameInput->SetTextAlignment(Engine::TextInput::Alignment::Left);
    //AddNewControlObject(nameInput.get());

    nameDisplay = new Engine::Label("", "pirulen.ttf", 28, halfW+300, halfH / 4 + 100, 255, 255, 255, 255, 0.0, 0.5);
    AddNewObject(nameDisplay);

    Engine::ImageButton *btn;
    btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
    bgmId = AudioHelper::PlayAudio("win.wav");
}
void WinScene::Terminate() {
    IScene::Terminate();
    AudioHelper::StopBGM(bgmId);
}
void WinScene::Update(float deltaTime) {
    ticks += deltaTime;
    if (ticks > 4 && ticks < 100 &&
        dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
        ticks = 100;
        bgmId = AudioHelper::PlayBGM("happy.ogg");
    }
}
void WinScene::BackOnClick(int stage) {
    // Change to select scene.
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

/*void WinScene::OnKeyDown(int keyCode) {
    if (keyCode == ALLEGRO_KEY_ENTER) {
        std::string name = nameInput->GetText();
        if (name.empty()) return;

        // 存入檔案
        std::ofstream fout("scores.txt", std::ios::app);
        fout << name << " " << gameTime << "\n";
        fout.close();

        // 切換到排行榜畫面
        Engine::GameEngine::GetInstance().ChangeScene("score-board");
    }
}*/

void WinScene::OnKeyDown(int keyCode) {
    if(submitted) return;

    if (keyCode == ALLEGRO_KEY_BACKSPACE && !playerName.empty()) {
        playerName.pop_back();
    } else if (keyCode == ALLEGRO_KEY_ENTER) {
        SubmitName();
    } else {
        if ((keyCode >= ALLEGRO_KEY_A && keyCode <= ALLEGRO_KEY_Z) ||
            (keyCode >= ALLEGRO_KEY_0 && keyCode <= ALLEGRO_KEY_9) ||
            keyCode == ALLEGRO_KEY_SPACE) {
            if (playerName.size() < 20) {
                char ch = 0;
                if (keyCode >= ALLEGRO_KEY_A && keyCode <= ALLEGRO_KEY_Z)
                    ch = 'A' + (keyCode - ALLEGRO_KEY_A);  // 轉換為大寫字母
                else if (keyCode >= ALLEGRO_KEY_0 && keyCode <= ALLEGRO_KEY_9)
                    ch = '0' + (keyCode - ALLEGRO_KEY_0);
                else if (keyCode == ALLEGRO_KEY_SPACE)
                    ch = ' ';
                if (ch != 0)
                    playerName.push_back(ch);
            }
        }
    }

    // 更新Label顯示
    if (nameDisplay) {
        nameDisplay->Text=playerName;
    }

    // 傳遞按鍵事件給 TextInput
    /*if (nameInput)
        nameInput->OnKeyDown(keyCode);

    // 如果按下 Enter，就提交名字
    if (keyCode == ALLEGRO_KEY_ENTER) {
        playerName = nameInput->GetText();
        SubmitName();
    }*/
}

void WinScene::SubmitName() {
    if (playerName.empty()) return;
    //if (!nameInput) return;
    //std::string name = nameInput->GetText();
    //if (name.empty()) return;
    if(submitted) return;

    //playerName = name;
    
    std::string scorePath = "scoreboard.txt";
    std::ofstream fout(scorePath, std::ios::app);
    if (!fout.is_open()) {
        std::cerr << "Error: Cannot open scoreboard.txt!" << std::endl;
        return;
    }

    //if (fout.is_open()) 
    std::time_t now = std::time(nullptr);
    char timeStr[100];
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    fout << playerName << " " << GameTime::gameTime << " " << timeStr << "\n";
    fout.close();
   // }
    submitted=true;
    std::cout << "Successfully added " << playerName << " with time " << GameTime::gameTime << "s" << std::endl;

    Engine::GameEngine::GetInstance().ChangeScene("scoreBoard");
    GameTime::Reset();
}
/*#include <filesystem>
void WinScene::SubmitName() {
    if (playerName.empty()) return;
    if (submitted) return;

    submitted = true;

    // 印出當前工作目錄
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

    // 取得 scoreboard.txt 的完整絕對路徑
    std::string path = "Resource/scoreboard.txt";
    std::string absolutePath = std::filesystem::absolute(path).string();
    std::cout << "Attempting to write to: " << absolutePath << std::endl;

    // 開啟檔案（附加模式）
    std::ofstream fout(path, std::ios::app);
    if (!fout.is_open()) {
        std::cerr << "Error: Cannot open " << path << "!" << std::endl;
        return;
    }

    fout << playerName << " " << GameTime::gameTime << "\n";
    if (fout.fail()) {
        std::cerr << "Error: Failed to write to " << path << "!" << std::endl;
        fout.close();
        return;
    }

    fout.close();

    std::cout << "Successfully added " << playerName << " with time " << GameTime::gameTime << "s" << std::endl;

    // 切換場景與重設時間
    Engine::GameEngine::GetInstance().ChangeScene("scoreBoard");
    GameTime::Reset();
}*/
