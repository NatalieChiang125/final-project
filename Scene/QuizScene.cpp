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
#include "Engine/GameMoney.hpp"

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
        {"Which planet is the Earth?", {"1", "2", "3", "4"}, 2},
        {"What is the chemical formula of water?", {"H2O", "CO2", "O2", "NaCl"}, 0},
        {"How many legs does a spider have?", {"4", "6", "8", "10"}, 2},
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

    NextQuestion();
}

void QuizScene::NextQuestion() {
    ClearUI(); // 自訂函式：清除前一題的物件
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    if (currentQuestionIndex >= questions.size()) {

        if(correctNum==2){
            PlayScene* scene = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene()); // 呼叫這個成員函式
            if (scene) {
                Player* player = scene->GetPlayer(); // 如果你有實作 GetPlayer()
                if (player) {
                    player->AddHP(3); // 正確呼叫
                }
            }
            GameMoney::totalMoney+=20;
        }

        AddNewObject(new Engine::Label("Finish", "pirulen.ttf", 48, w / 2, h / 3, 255, 255, 255, 255, 0.5, 0.5));

        Engine::ImageButton* btn;
        btn=new Engine::ImageButton("win/dirt.png", "win/floor.png", w / 2 - 200, h * 2 / 3 - 50, 400, 100);
        btn->SetOnClickCallback(std::bind(&QuizScene::BackOnClick, this, 2));
        AddNewControlObject(btn);
        AddNewObject(new Engine::Label("BACK", "pirulen.ttf", 48, w / 2, h * 2 / 3 + 10, 0, 0, 0, 255, 0.5, 0.5));
        return;
    }

    const Question& q = questions[currentQuestionIndex];
    

    AddNewObject(new Engine::Label(q.questionText, "pirulen.ttf", 36, w / 2, h / 4, 255, 255, 0, 255, 0.5, 0.5));

    for (int i = 0; i < q.options.size(); ++i) {
        Engine::ImageButton* btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", w / 2 - 150, h / 3 + i * 100, 300, 80);
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

    if (correct) {
        AudioHelper::PlaySample("correct.wav");
        AddNewObject(new Engine::Label("Correct!", "pirulen.ttf", 40, w / 2, h - 140, 0, 255, 0, 255, 0.5, 0.5));
        correctNum++;
    } else {
        AudioHelper::PlaySample("wrong.wav");
        AddNewObject(new Engine::Label("Wrong！", "pirulen.ttf", 40, w / 2+25, h - 140, 255, 0, 0, 255, 0.5, 0.5));
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

void QuizScene::Terminate() {
    //AudioHelper::StopSample(bgmInstance);
    //bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}
void QuizScene::BackOnClick(int stage) {
    // Change to select scene.
    Engine::GameEngine::GetInstance().ChangeScene("start");
}

void QuizScene::ClearUI() {
    //objects.clear();
    //controlObjects.clear();
    IScene::Terminate();
}