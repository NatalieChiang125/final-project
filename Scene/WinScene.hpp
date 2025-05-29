#ifndef WINSCENE_HPP
#define WINSCENE_HPP
#include "Engine/IScene.hpp"
#include "UI/Component/Label.hpp"
#include <allegro5/allegro_audio.h>
#include <string>
//#include "Engine/TextInput.hpp"

class WinScene final : public Engine::IScene {
private:
    float ticks;
    bool submitted=false;
    //float gameTime;
    ALLEGRO_SAMPLE_ID bgmId;
    //std::shared_ptr<Engine::TextInput> nameInput;
    std::string playerName; // 玩家名字
    Engine::Label* nameDisplay = nullptr; // 顯示輸入名字的Label

public:
    //explicit WinScene(float gameTime=0);
    explicit WinScene()=default;
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void BackOnClick(int stage);
    void SubmitName();
    void OnKeyDown(int keyCode) override;
};

#endif   // WINSCENE_HPP
