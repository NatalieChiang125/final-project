#include <functional>
#include <string>
#include <algorithm>
#include <random> 

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "QuizScene.hpp"
#include "PlayScene.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "Player/Player.hpp"
#include "Engine/PlayerStat.hpp"

#include <iostream>


void QuizScene::Initialize() {
    /*int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton *btn;
    btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&QuizScene::BackOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));*/
    //bgmInstance = AudioHelper::PlaySample("astronomia.ogg", false, AudioHelper::BGMVolume, PlayScene::DangerTime);
    questionPool = {
        {"How many turbo engines does Lake Cheng Kong have?", {"3", "4", "6", "8"}, 3},
        {"What is the formula of differentiation?", {"dx^n/dx = nx^(n-1)", "xy+x'z+yz=xy+x'z", "e = mc^2", "NaCl -> Na + 1/2Cl2"}, 0},
        {"What does CPU do", {"Cooks popcorn", "Translates cat meows", "Executes instructions", "Controls the moon’s orbit"}, 2},
        {"Which gas do plants absorb?", {"O2", "CO2", "H2", "N2"}, 1},
        {"What is the capital of France?", {"London", "Berlin", "Paris", "Rome"}, 2}
    };
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(questionPool.begin(), questionPool.end(), rng);
    questions.assign(questionPool.begin(), questionPool.begin() + 2);
    
    currentQuestionIndex = 0;
    answered = false;
    correct = false;
    correctNum=0;
    CurrentState = ANSWERING;
    timeLeft = timeLimit;
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
   

    NextQuestion();
}

void QuizScene::NextQuestion() {
    std::cout << "current index = [" << currentQuestionIndex << "]\n";
    ClearUI(); // 自訂函式：清除前一題的物件
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    UITime = new Engine::Label("AAAAA", "pirulen.ttf", 40, w / 2, 140, 0, 255, 255, 255, 0.5, 0.5);
    AddNewObject(UITime);
    timeLeft = timeLimit;
    CurrentState = ANSWERING;
    if (currentQuestionIndex >= questions.size()) {

        if(correctNum==2){
            PlayScene* scene = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene()); // 呼叫這個成員函式
            if (scene) {
                Player* player = scene->GetPlayer();
                if (player) {
                    player->AddHP(3);
                }
            }
            PlayerStat::totalMoney+=20;
        }

        AddNewObject(new Engine::Label("Finish", "pirulen.ttf", 48, w / 2, h / 3, 255, 255, 255, 255, 0.5, 0.5));

        Engine::ImageButton* btn;
        btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", w / 2 - 200, h * 2 / 3 - 50, 400, 100);
        btn->SetOnClickCallback(std::bind(&QuizScene::BackOnClick, this, 2));
        AddNewControlObject(btn);
        AddNewObject(new Engine::Label("BACK", "pirulen.ttf", 48, w / 2, h * 2 / 3 + 10, 0, 0, 0, 255, 0.5, 0.5));
        return;
    }

    const Question& q = questions[currentQuestionIndex];
    

    AddNewObject(new Engine::Label(q.questionText, "pirulen.ttf", 36, w / 2, h / 4, 255, 255, 0, 255, 0.5, 0.5));

    for (int i = 0; i < q.options.size(); ++i) {
        Engine::ImageButton* btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", w / 2 - 400, h / 3 + i * 100, 800, 80);
        btn->SetOnClickCallback(std::bind(&QuizScene::OptionOnClick, this, i));
        AddNewControlObject(btn);
        AddNewObject(new Engine::Label(q.options[i], "pirulen.ttf", 28, w / 2, h / 3 + i * 100 + 40, 0, 0, 0, 255, 0.5, 0.5));
    }
}

void QuizScene::OptionOnClick(int index) {
    if (answered) return;

    answered = true;
    const Question& q = questions[currentQuestionIndex];
    correct = (index == q.correctIndex);

    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;

    CurrentState = ANSWERED; 
    if (correct) {
        AudioHelper::PlaySample("correct.wav");
        AddNewObject(new Engine::Label("Correct!", "pirulen.ttf", 40, w / 2, h - 140, 0, 255, 0, 255, 0.5, 0.5));
        correctNum++;
    } else {
        AudioHelper::PlaySample("wrong.wav");
        AddNewObject(new Engine::Label("Wrong！", "pirulen.ttf", 40, w / 2+25, h - 140, 255, 0, 0, 255, 0.5, 0.5));
    }

    if (currentQuestionIndex + 1 >= questions.size()){
        timeLeft = timeWait;
        return;
    }

    // 下一題按鈕
    Engine::ImageButton* btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", w / 2 - 150, h - 80, 300, 60);
    btn->SetOnClickCallback([this]() {
        currentQuestionIndex++;
        answered = false;
        correct = false;
        NextQuestion();
    });
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Next", "pirulen.ttf", 28, w / 2, h - 50, 0, 0, 0, 255, 0.5, 0.5));
}

void QuizScene::Update(float deltaTime){
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    drawTime(timeLeft);
    //std::cout << "time=[" << timeLeft << "]\n";
    if (CurrentState == ANSWERING){
        if (timeLeft > 0){
            timeLeft -= deltaTime;
            
        } else {  // answer time limit exceeded->wrong answer
            answered = true;
            correct = false;
            CurrentState = ANSWERED;
            
            UITime->Text = "";
            //currentQuestionIndex++;
            if (currentQuestionIndex+1 >= questions.size()) { // if all questions finished 
                timeLeft = timeWait;
                AddNewObject(new Engine::Label("Wrong Answer", "pirulen.ttf", 40, w / 2, h - 140, 0, 255, 0, 255, 0.5, 0.5));
                return;
            }
            else { // next question
                Engine::ImageButton* btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", w / 2 - 150, h - 80, 300, 60);
                btn->SetOnClickCallback([this]() {
                    currentQuestionIndex++;
                    answered = false;
                    correct = false;
                    NextQuestion();
                });
                AddNewControlObject(btn);
                AddNewObject(new Engine::Label("Next", "pirulen.ttf", 28, w / 2, h - 50, 0, 0, 0, 255, 0.5, 0.5));
                
                AddNewObject(new Engine::Label("Wrong Answer", "pirulen.ttf", 40, w / 2, h - 140, 0, 255, 0, 255, 0.5, 0.5));
            }

                    
        }
    }else if (CurrentState == ANSWERED){
        if (currentQuestionIndex+1 >= questions.size()){ 
            if (timeLeft > 0){
                timeLeft -= deltaTime;
            } else {
                CurrentState = FINISHED;
                if(correctNum == 2){ // win
                    PlayScene* scene = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene()); // 呼叫這個成員函式
                    if (scene) {
                        Player* player = scene->GetPlayer();
                        if (player) {
                            player->AddHP(3);
                        }
                    }
                    PlayerStat::totalMoney+=20;
                }

                // 關卡結算畫面
                ClearUI();
                AddNewObject(new Engine::Label("Finish", "pirulen.ttf", 48, w / 2, h / 3, 255, 255, 255, 255, 0.5, 0.5));

                Engine::ImageButton* btn;
                btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", w / 2 - 200, h * 2 / 3 - 50, 400, 100);
                btn->SetOnClickCallback(std::bind(&QuizScene::BackOnClick, this, 2));
                AddNewControlObject(btn);
                AddNewObject(new Engine::Label("BACK", "pirulen.ttf", 48, w / 2, h * 2 / 3 + 10, 0, 0, 0, 255, 0.5, 0.5));
            }
        }
    }

}

void QuizScene::drawTime(float time){
    if (CurrentState != ANSWERING){
        UITime->Text = "";
        return;
    }
    int tiledTime = int(time);
    UITime->Text = std::to_string(tiledTime);

}

void QuizScene::Terminate() {
    //AudioHelper::StopSample(bgmInstance);
    //bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}
void QuizScene::BackOnClick(int stage) {
    // Change to select scene.
    PlayerStat::playerY += 180;
    Engine::GameEngine::GetInstance().ChangeScene("play");
}

void QuizScene::ClearUI() {
    //objects.clear();
    //controlObjects.clear();
    IScene::Terminate();
}
