#include "ProgressScene.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Image.hpp"
#include "Engine/Sprite.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Engine/PlayerStat.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <iostream>



void ProgressScene::Initialize() {

    int halfW = Engine::GameEngine::GetInstance().GetScreenSize().x/2;
    int halfH = Engine::GameEngine::GetInstance().GetScreenSize().y/2;
    //
    AddNewObject(new Engine::Label("Academy", "pirulen.ttf", 36, halfW - 200, 200, 255, 255, 255, 255, 0.5, 0.5));

    // 返回按鈕
    Engine::ImageButton* btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, 650, 400, 100);
    btn->SetOnClickCallback(std::bind(&ProgressScene::BackOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, 700, 0, 0, 0, 255, 0.5, 0.5));

    int pA = PlayerStat::progressA, pB = PlayerStat::progressB, pC = PlayerStat::progressC;
    //Engine::Sprite *images[3][3]; // 用sprite來改變顏色
    // 支線一 進度
    
    // for (int i=0;i<3;i++){

    //     images[0][i] = new Engine::Sprite("play/enemy-1.png",halfW - 200 + 200 * i, 200);
    //     int color = i<pA ? 255 : 0;
    //     images[0][i]->Tint = al_map_rgb(color,color,color);
    //     al_draw_bitmap(images[0][i]->bmp.get(),images[0][i]->Position.x,images[0][i]->Position.y, 0);
    // }
    Engine::Image *images[3][3];

    AddNewObject(new Engine::Label("Academy", "pirulen.ttf", 36, halfW - 200, 200, 255, 255, 255, 255, 0.5, 0.5));
    for (int i=0;i<3;i++){
        AddNewObject(new Engine::Label("Level " + std::to_string(i+1), "pirulen.ttf", 24, halfW + 200 * i, 150, 255, 255, 255, 255, 0.5, 0.5));
        if (i < pA) // 關卡顏色與遊戲進度的關係
            AddNewObject(images[0][i] = new Engine::Image("play/enemy-1.png", halfW + 200 * i, 200, 0, 0, 0.5, 0.5));
        else AddNewObject(images[0][i] = new Engine::Image("play/turret-1.png", halfW + 200 * i, 200, 0, 0, 0.5, 0.5));
    }
    

    // 支線二
    AddNewObject(new Engine::Label("Romance", "pirulen.ttf", 36, halfW - 200, 350, 255, 255, 255, 255, 0.5, 0.5));
    for (int i=0;i<3;i++){
        AddNewObject(new Engine::Label("Level " + std::to_string(i+1), "pirulen.ttf", 24, halfW + 200 * i, 300, 255, 255, 255, 255, 0.5, 0.5));
        if (i < pA) // 關卡顏色與遊戲進度的關係
            AddNewObject(images[1][i] = new Engine::Image("play/enemy-1.png", halfW + 200 * i, 350, 0, 0, 0.5, 0.5));
        else AddNewObject(images[1][i] = new Engine::Image("play/turret-1.png", halfW + 200 * i, 350, 0, 0, 0.5, 0.5));
    }

    // 支線三
    AddNewObject(new Engine::Label("Club", "pirulen.ttf", 36, halfW - 200, 500, 255, 255, 255, 255, 0.5, 0.5));
    for (int i=0;i<3;i++){
        AddNewObject(new Engine::Label("Level " + std::to_string(i+1), "pirulen.ttf", 24, halfW + 200 * i, 450, 255, 255, 255, 255, 0.5, 0.5));
        if (i < pA) // 關卡顏色與遊戲進度的關係
            AddNewObject(images[2][i] = new Engine::Image("play/enemy-1.png", halfW + 200 * i, 500, 0, 0, 0.5, 0.5));
        else AddNewObject(images[2][i] = new Engine::Image("play/turret-1.png", halfW + 200 * i, 500, 0, 0, 0.5, 0.5));
    }

}
void ProgressScene::Draw() const {
    IScene::Draw();
    int halfW = Engine::GameEngine::GetInstance().GetScreenSize().x/2;
    int halfH = Engine::GameEngine::GetInstance().GetScreenSize().y/2;
    Engine::Sprite img("play/playerMove.png",0,0);
    al_draw_scaled_bitmap(
        img.bmp.get(), // 來自 Engine::Sprite 裡的 ALLEGRO_BITMAP*
        0,  // x
        0, // y
        62,                  // width
        64,                 // height
        halfW - 700,
        halfH - 200,
        62 * 5,
        64 * 5,
        0
    );
    
}

void ProgressScene::Terminate() {
    IScene::Terminate();
}

void ProgressScene::BackOnClick() {
    Engine::GameEngine::GetInstance().ChangeScene("start");
}



// void ScoreBoardScene::ReadPage(){
//     for(auto label:scoreLabels){
//        RemoveNewObject(label);
//     }
//     scoreLabels.clear();
//     int halfW = Engine::GameEngine::GetInstance().GetScreenSize().x / 2;
//     int startIndex = page * scoresPerPage;
//     int endIndex = std::min((int)scores.size(), startIndex + scoresPerPage);

//     for (int i = startIndex; i < endIndex; ++i) {
//         std::stringstream ss;
//         ss << i + 1 << ". " << scores[i].name << " - " << scores[i].time << "s";
//         auto label = new Engine::Label(ss.str(), "pirulen.ttf", 32, halfW, 120 + (i - startIndex) * 50, 255, 255, 200, 255, 0.5, 0.5);
//         scoreLabels.push_back(label);
//         AddNewObject(label);
//         int y = 120 + (i - startIndex) * 50;
//         auto timeLabel = new Engine::Label("        (" + scores[i].datatime + ")", "pirulen.ttf", 24, halfW + 220, y, 180, 180, 255, 255, 0.0, 0.5);
//         scoreLabels.push_back(timeLabel);
//         AddNewObject(timeLabel);
//     }
// }
