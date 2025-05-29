#ifndef DAILYREWARDSCENE_H
#define DAILYREWARDSCENE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <string>
#include <vector>
#include "Engine/IScene.hpp"
#include "UI/Component/Label.hpp"

class DailyScene final : public Engine::IScene {
private:
    int currentDay;
    int totalMoney;
    std::vector<bool> checkedIn;
    

public:
    //std::shared_ptr<Engine::Label> coinLabel;
    Engine::Label* coinLabel;
    DailyScene();
    void Initialize() override;
    void Terminate() override;
    void LoadStatus();
    void SaveStatus();
    void OnCheckInClick(int day);
    void BackOnClick(); // 返回主畫面
};

#endif
