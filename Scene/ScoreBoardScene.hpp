#ifndef SCOREBOARD_SCENE_HPP
#define SCOREBOARD_SCENE_HPP

#include "Engine/IScene.hpp"
#include "UI/Component/Label.hpp"
#include <vector>
#include <string>
#include <allegro5/allegro_audio.h>

struct ScoreRecord{
    std::string name;
    float time;
    std::string datatime;
};

class ScoreBoardScene final : public Engine::IScene {
private:
    //std::vector<std::pair<std::string, float>> scores;
    std::vector<ScoreRecord> scores;
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    std::vector<Engine::Label*> scoreLabels;
    int page = 0;
    const int scoresPerPage = 5;
    
    

public:
    void Initialize() override;
    void Terminate() override;
    void BackOnClick(int stage);
    void ReadPage();
};

#endif // SCOREBOARD_SCENE_HPP
