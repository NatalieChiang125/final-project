// [main.cpp]
// This is the entry point of your game.
// You can register your scenes here, and start the game.
#include "Engine/GameEngine.hpp"
#include "Engine/LOG.hpp"
#include "Engine/GameTime.hpp"
#include "Engine/PlayerStat.hpp"
#include "Scene/LoseScene.hpp"
#include "Scene/PlayScene.hpp"
#include "Scene/StageSelectScene.hpp"
#include "Scene/WinScene.hpp"
#include "Scene/StartScene.h"
#include "Scene/SettingsScene.hpp"
#include "Scene/ScoreBoardScene.hpp"
#include "Scene/DailyScene.hpp"
#include "Scene/QuizScene.hpp"
#include "Scene/RhythmGameScene.hpp"
#include "Scene/ProgressScene.hpp"

void ReadProgress(std::string filename){

    // 讀取 progress.txt
    /*
    playerX playerY hp
    # item1 item2 item3
    money
    lvl progress A B C
    */
    //std::ifstream fin("Resource/scoreboard.txt");
    std::string progressPath = "scoreboard.txt";
    std::ifstream fin(progressPath);
    if (!fin.is_open()) {
        std::cerr << "Error: Cannot open " << progressPath << "!" << std::endl;
        return;
    }

    fin >> PlayerStat::playerX >> PlayerStat::playerY >> PlayerStat::health;
    fin >> PlayerStat::item1 >> PlayerStat::item2 >> PlayerStat::item3;
    fin >> PlayerStat::totalMoney;
    fin >> PlayerStat::progressA >> PlayerStat::progressB >> PlayerStat::progressC;
    
    fin.close();
}

int main(int argc, char **argv) {
	Engine::LOG::SetConfig(true);
	Engine::GameEngine& game = Engine::GameEngine::GetInstance();

	GameTime::Reset();
	//ReadProgress("Resource/progress.txt");
    // TODO HACKATHON-2 (2/3): Register Scenes here(okay)
	game.AddNewScene("start", new StartScene());
	game.AddNewScene("settings", new SettingsScene());
    game.AddNewScene("stage-select", new StageSelectScene());
	game.AddNewScene("scoreBoard", new ScoreBoardScene());
	game.AddNewScene("daily", new DailyScene());
	game.AddNewScene("quiz", new QuizScene());
	game.AddNewScene("rhythm", new RhythmGameScene());
	//game.AddNewScene("progress", new ProgressScene());
	
	game.AddNewScene("play", new PlayScene());
	game.AddNewScene("lose", new LoseScene());
	game.AddNewScene("win", new WinScene());

    // TODO HACKATHON-1 (1/1): Change the start scene (okay)
	game.Start("start", 60, 1600, 832);

	return 0;
}
