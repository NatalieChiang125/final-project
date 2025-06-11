#ifndef QUIZSCENE_HPP
#define QUIZSCENE_HPP
#include "Engine/IScene.hpp"
#include <allegro5/allegro_audio.h>
#include <memory>

struct Question {
    std::string questionText;
    std::vector<std::string> options;
    int correctIndex;
};
namespace Engine{
    class Label;
}

class QuizScene final : public Engine::IScene {
private:
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    std::vector<Question> questionPool;
    std::vector<Question> questions;
    int currentQuestionIndex = 0;
    bool answered = false;
    bool correct = false;
    int correctNum;
    float timeLeft;
    float timeLimit = 8.0f;
    float timeWait = 2.0f;
    Engine::Label *UITime;
    enum State {
        ANSWERING = 0,
        ANSWERED = 1,
        FINISHED = 2,

    };
    State CurrentState = ANSWERING;


public:
    explicit QuizScene() = default;
    void Initialize() override;
    void Terminate() override;
    void BackOnClick(int stage);
    void Update(float deltaTime) override;
    void OptionOnClick(int index);
    void NextQuestion();
    void ClearUI();
    void drawTime(float time);
};

#endif