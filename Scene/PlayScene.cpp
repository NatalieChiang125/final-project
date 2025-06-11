#include <algorithm>
#include <allegro5/allegro.h>
#include <cmath>
#include <fstream>
#include <functional>
#include <memory>
#include <queue>
#include <string>
#include <vector>

#include "Enemy/Enemy.hpp"
#include "Enemy/SoldierEnemy.hpp"
#include "Enemy/PlaneEnemy.hpp"
#include "Enemy/TankEnemy.hpp"
#include "Enemy/BoomEnemy.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/LOG.hpp"
#include "Engine/Resources.hpp"
#include "Engine/GameTime.hpp"
#include "Engine/PlayerStat.hpp"
#include "Engine/map.hpp"
#include "Player/Player.hpp"
#include "PlayScene.hpp"
#include "Turret/LaserTurret.hpp"
#include "Turret/MachineGunTurret.hpp"
#include "Turret/FireTurret.hpp"
#include "Turret/TurretButton.hpp"
#include "Turret/ShieldTurret.hpp"
#include "Turret/Shovel.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "UI/Animation/Plane.hpp"
#include "UI/Component/Label.hpp"

// TODO HACKATHON-4 (1/3): Trace how the game handles keyboard input.
// TODO HACKATHON-4 (2/3): Find the cheat code sequence in this file.(okay)
// TODO HACKATHON-4 (3/3): When the cheat code is entered, a plane should be spawned and added to the scene.
// TODO HACKATHON-5 (1/4): There's a bug in this file, which crashes the game when you win. Try to find it.(okay)
// TODO HACKATHON-5 (2/4): The "LIFE" label are not updated when you lose a life. Try to fix it.(okay)

bool PlayScene::DebugMode = false;
const std::vector<Engine::Point> PlayScene::directions = { Engine::Point(-1, 0), Engine::Point(0, -1), Engine::Point(1, 0), Engine::Point(0, 1) };
const int PlayScene::MapWidth = 50, PlayScene::MapHeight = 21;
const int PlayScene::BlockSize = 64;
const float PlayScene::DangerTime = 7.61;
const Engine::Point PlayScene::SpawnGridPoint = Engine::Point(-1, 0);
const Engine::Point PlayScene::EndGridPoint = Engine::Point(MapWidth, MapHeight - 1);
//the cheat code sequence
const std::vector<int> PlayScene::code = {
    ALLEGRO_KEY_UP, ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_DOWN,
    ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT,
    ALLEGRO_KEY_B, ALLEGRO_KEY_A, ALLEGRO_KEYMOD_SHIFT, ALLEGRO_KEY_ENTER
};
Engine::Point PlayScene::GetClientSize() {
    return Engine::Point(MapWidth * BlockSize, MapHeight * BlockSize);
}
void PlayScene::Initialize() {
    mapState.clear();
    keyStrokes.clear();
    ticks = 0;
    deathCountDown = -1;
    lives = 10;
    money = PlayerStat::totalMoney;
    SpeedMult = 1;
    //AddNewObject(EnemyGroup = new Group());
    map = new Map(); 
    map->loadMapFromFile("Resource/map1.txt");

    mapState = map->GetGrid();
    std::cerr << "[DEBUG] mapState initialized: " << mapState.size() << " rows, "
          << (mapState.empty() ? 0 : mapState[0].size()) << " cols.\n";
    
    screenH = Engine::GameEngine::GetInstance().GetScreenHeight();
    screenW = Engine::GameEngine::GetInstance().GetScreenWidth();
    TileMapGroup = new Group();
    TileMapGroup->AddNewObject(map);  // 可選，除非你有設計讓 Group 負責顯示地圖物件
    AddNewObject(TileMapGroup);
    // Add groups from bottom to top.
    //AddNewObject(TileMapGroup = new Group());
    AddNewObject(GroundEffectGroup = new Group());
    AddNewObject(DebugIndicatorGroup = new Group());
    //AddNewObject(TowerGroup = new Group());
    //不能刪，會潰堤
    AddNewObject(EnemyGroup = new Group());
    //AddNewObject(BulletGroup = new Group());
    AddNewObject(EffectGroup = new Group());
    // Should support buttons.
    AddNewControlObject(UIGroup = new Group());
    ReadMap();
    //map = new Map("Resource/map1.txt");
    
    player = new Player("play/playerOwn.png", PlayerStat::playerX, PlayerStat::playerY ,115,100);
    AddNewObject(player);
    //新增的
    //map = dynamic_cast<Map*>(TileMapGroup->GetObjects().front());
    ReadEnemyWave();
    mapDistance = CalculateBFSDistance();
    ConstructUI();
    imgTarget = new Engine::Image("play/target.png", 0, 0);
    imgTarget->Visible = false;
    preview = nullptr;
    UIGroup->AddNewObject(imgTarget);
    // Preload Lose Scene
    deathBGMInstance = Engine::Resources::GetInstance().GetSampleInstance("astronomia.ogg");
    Engine::Resources::GetInstance().GetBitmap("lose/benjamin-happy.png");
    // Start BGM.
    bgmId = AudioHelper::PlayBGM("play.ogg");
}
void PlayScene::Terminate() {
    AudioHelper::StopBGM(bgmId);
    AudioHelper::StopSample(deathBGMInstance);
    deathBGMInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
    //map->cleanup();
}
void PlayScene::Update(float deltaTime) {
    // If we use deltaTime directly, then we might have Bullet-through-paper problem.
    // Reference: Bullet-Through-Paper
    if (PlayerStat::health > 0) PlayerStat::health -= deltaTime ;

    map->update(deltaTime);
    Camera.x = player->Position.x - screenW / 2;
    Camera.y = player->Position.y - screenH / 2;
    if(Camera.x < -50) Camera.x = -50;
    if(Camera.y < 0) Camera.y = 0;

    int mapWidth=(map->GetWidth())*BlockSize;
    int mapHeight=(map->GetHeight())*BlockSize;

    if(Camera.x > mapWidth*2-MapWidth-100) Camera.x = mapWidth*2-MapWidth-100;
    if(Camera.y > mapHeight*2-MapHeight-340) Camera.y = mapHeight*2-MapHeight-340;

    //UIMoney->Text = std::string("x,y = ") + std::to_string((int)player->Position.x) + "," + std::to_string((int)player->Position.y);
    UIGroup->AddNewObject(UIMoney = new Engine::Label(std::string("$") + std::to_string(money), "pirulen.ttf", 24, 1294, 48));
    if (SpeedMult == 0)
        deathCountDown = -1;
    else if (deathCountDown != -1)
        SpeedMult = 1;
    // Calculate danger zone.
    std::vector<float> reachEndTimes;
    for (auto &it : EnemyGroup->GetObjects()) {
        reachEndTimes.push_back(dynamic_cast<Enemy *>(it)->reachEndTime);
    }
    // Can use Heap / Priority-Queue instead. But since we won't have too many enemies, sorting is fast enough.
    std::sort(reachEndTimes.begin(), reachEndTimes.end());
    float newDeathCountDown = -1;
    int danger = lives;
    for (auto &it : reachEndTimes) {
        if (it <= DangerTime) {
            danger--;
            if (danger <= 0) {
                // Death Countdown
                float pos = DangerTime - it;
                if (it > deathCountDown) {
                    // Restart Death Count Down BGM.
                    AudioHelper::StopSample(deathBGMInstance);
                    if (SpeedMult != 0)
                        deathBGMInstance = AudioHelper::PlaySample("astronomia.ogg", false, AudioHelper::BGMVolume, pos);
                }
                float alpha = pos / DangerTime;
                alpha = std::max(0, std::min(255, static_cast<int>(alpha * alpha * 255)));
                dangerIndicator->Tint = al_map_rgba(255, 255, 255, alpha);
                newDeathCountDown = it;
                break;
            }
        }
    }

    
    GameTime::gameTime += deltaTime;

    deathCountDown = newDeathCountDown;
    if (SpeedMult == 0)
        AudioHelper::StopSample(deathBGMInstance);
    if (deathCountDown == -1 && lives > 0) {
        AudioHelper::StopSample(deathBGMInstance);
        dangerIndicator->Tint.a = 0;
    }
    if (SpeedMult == 0)
        deathCountDown = -1;
    for (int i = 0; i < SpeedMult; i++) {
        IScene::Update(deltaTime);
        // Check if we should create new enemy.
        ticks += deltaTime;
        if (enemyWaveData.empty()) {
            if (EnemyGroup->GetObjects().empty()) {
                // Free resources.
                /*delete TileMapGroup;
                delete GroundEffectGroup;
                delete DebugIndicatorGroup;
                delete TowerGroup;
                delete EnemyGroup;
                delete BulletGroup;
                delete EffectGroup;
                delete UIGroup;
                delete imgTarget;*/
                // Win.
                //Engine::GameEngine::GetInstance().ChangeScene("win");
                
            }
            continue;
        }
        auto current = enemyWaveData.front();
        if (ticks < current.second)
            continue;
        ticks -= current.second;
        enemyWaveData.pop_front();
        const Engine::Point SpawnCoordinate = Engine::Point(SpawnGridPoint.x * BlockSize + BlockSize / 2, SpawnGridPoint.y * BlockSize + BlockSize / 2);
        Enemy *enemy;
        switch (current.first) {
            case 1:
                EnemyGroup->AddNewObject(enemy = new SoldierEnemy(SpawnCoordinate.x, SpawnCoordinate.y));
                break;
            // TODO HACKATHON-3 (2/3): Add your new enemy here.(okay)
            case 2:
                EnemyGroup->AddNewObject(enemy = new PlaneEnemy(SpawnCoordinate.x, SpawnCoordinate.y));
                break;
            //     ...
            case 3:
                EnemyGroup->AddNewObject(enemy = new TankEnemy(SpawnCoordinate.x, SpawnCoordinate.y));
                break;
            case 4:
                EnemyGroup->AddNewObject(enemy = new BoomEnemy(SpawnCoordinate.x, SpawnCoordinate.y));
                break;
            default:
                continue;
        }
        enemy->UpdatePath(mapDistance);
        // Compensate the time lost.
        enemy->Update(ticks);
        PlayerStat::playerX = player->Position.x;
        PlayerStat::playerY = player->Position.y;
    }

    if (preview) {
        preview->Position = Engine::GameEngine::GetInstance().GetMousePosition();
        // To keep responding when paused.
        preview->Update(deltaTime);
    }
}

Engine::Point PlayScene::getCam(){
    return Camera;
}

void PlayScene::Draw() const {
    
    IScene::Draw();
    map->draw();
    player->Draw();
    UIGroup->Draw();
    EnemyGroup->Draw();
    
    /*if (DebugMode) {
        // Draw reverse BFS distance on all reachable blocks.
        for (int i = 0; i < MapHeight; i++) {
            for (int j = 0; j < MapWidth; j++) {
                if (mapDistance[i][j] != -1) {
                    // Not elegant nor efficient, but it's quite enough for debugging.
                    Engine::Label label(std::to_string(mapDistance[i][j]), "pirulen.ttf", 32, (j + 0.5) * BlockSize, (i + 0.5) * BlockSize);
                    label.Anchor = Engine::Point(0.5, 0.5);
                    label.Draw();
                }
            }
        }
    }*/
}
void PlayScene::OnMouseDown(int button, int mx, int my) {
    if ((button & 1) && !imgTarget->Visible && preview) {
        // Cancel turret construct.
        UIGroup->RemoveObject(preview->GetObjectIterator());
        preview = nullptr;
    }
    IScene::OnMouseDown(button, mx, my);
}
void PlayScene::OnMouseMove(int mx, int my) {
    IScene::OnMouseMove(mx, my);
    const int x = mx / BlockSize;
    const int y = my / BlockSize;
    if (!preview || x < 0 || x >= MapWidth || y < 0 || y >= MapHeight) {
        imgTarget->Visible = false;
        return;
    }
    imgTarget->Visible = true;
    imgTarget->Position.x = x * BlockSize;
    imgTarget->Position.y = y * BlockSize;
}
void PlayScene::OnMouseUp(int button, int mx, int my) {
    IScene::OnMouseUp(button, mx, my);
    if (!imgTarget->Visible)
        return;
    const int x = mx / BlockSize;
    const int y = my / BlockSize;

    if(preview && dynamic_cast<Shovel*>(preview)){
        auto turretlist=TowerGroup->GetObjects();
        for(auto t:turretlist){
            int tx= t->Position.x / BlockSize;
            int ty= t->Position.y / BlockSize;
            if(tx==x && ty==y){
                TowerGroup->RemoveNewObject(t);
                EarnMoney(20);
                //mapState[ty][tx] = TILE_FLOOR;
                mapState[ty][tx] = BlockType::FLOOR;
                break;
            }
        }
        return;
    }

    /*if (button & 1) {
        if (mapState[y][x] != TILE_OCCUPIED) {
            if (!preview)
                return;
            // Check if valid.
            if (!CheckSpaceValid(x, y)) {
                Engine::Sprite *sprite;
                GroundEffectGroup->AddNewObject(sprite = new DirtyEffect("play/target-invalid.png", 1, x * BlockSize + BlockSize / 2, y * BlockSize + BlockSize / 2));
                sprite->Rotation = 0;
                return;
            }
            // Purchase.
            EarnMoney(-preview->GetPrice());
            // Remove Preview.
            preview->GetObjectIterator()->first = false;
            UIGroup->RemoveObject(preview->GetObjectIterator());
            // Construct real turret.
            preview->Position.x = x * BlockSize + BlockSize / 2;
            preview->Position.y = y * BlockSize + BlockSize / 2;
            preview->Enabled = true;
            preview->Preview = false;
            preview->Tint = al_map_rgba(255, 255, 255, 255);
            TowerGroup->AddNewObject(preview);
            // To keep responding when paused.
            preview->Update(0);
            // Remove Preview.
            preview = nullptr;

            //mapState[y][x] = TILE_OCCUPIED;
            OnMouseMove(mx, my);
        }
    }*/
}
void PlayScene::OnKeyDown(int keyCode) {
    IScene::OnKeyDown(keyCode);
    if (keyCode == ALLEGRO_KEY_TAB) {
        DebugMode = !DebugMode;
    } else {
        keyStrokes.push_back(keyCode);
        /*if (keyCode == ALLEGRO_KEY_LSHIFT || keyCode == ALLEGRO_KEY_RSHIFT) {
            keyStrokes.push_back(ALLEGRO_KEYMOD_SHIFT);  
        }*/
        if (keyStrokes.size() > code.size())
            keyStrokes.pop_front();
        
        ALLEGRO_KEYBOARD_STATE keyboardState;
        al_get_keyboard_state(&keyboardState);
        bool Shift = ( al_key_down(&keyboardState, ALLEGRO_KEY_LSHIFT) || 
                                al_key_down(&keyboardState, ALLEGRO_KEY_RSHIFT));

        bool match = true;
        auto it = keyStrokes.begin();
        for (size_t i = 0; i < code.size(); ++i, ++it) {
            if (code[i] == ALLEGRO_KEYMOD_SHIFT) {
                if (!Shift) {
                    match = false;
                    break;
                }
            } else {
                if (*it != code[i]) {
                    match = false;
                    break;
                }
            }
        }

        if (match) {
            Plane* plane = new Plane();
            EffectGroup->AddNewObject(plane);
            EarnMoney(10000);
        }
        
    }
    if (keyCode == ALLEGRO_KEY_Q) {
        // Hotkey for MachineGunTurret.
        UIBtnClicked(0);
    } else if (keyCode == ALLEGRO_KEY_Y) {
        // Hotkey for LaserTurret.
        UIBtnClicked(1);
    }else if (keyCode == ALLEGRO_KEY_E) {
        // Hotkey for FireTurret.
        UIBtnClicked(2);
    }else if (keyCode == ALLEGRO_KEY_R) {
        // Hotkey for FireTurret.
        UIBtnClicked(3);
    }else if (keyCode == ALLEGRO_KEY_T) {
        // Hotkey for FireTurret.
        UIBtnClicked(4);
    }
    if (player) {
        player->OnKeyDown(keyCode);
    }

    else if (keyCode >= ALLEGRO_KEY_0 && keyCode <= ALLEGRO_KEY_9) {
        // Hotkey for Speed up.
        SpeedMult = keyCode - ALLEGRO_KEY_0;
    }
}

void PlayScene::OnKeyUp(int keyCode) {
    IScene::OnKeyUp(keyCode);
    if (player) {
        player->OnKeyUp(keyCode);
    }
}

void PlayScene::Hit() {
    lives--;
    if (lives <= 0) {
        Engine::GameEngine::GetInstance().ChangeScene("lose");
    }
    UILives->Text = "Life: " + std::to_string(lives);
}
int PlayScene::GetMoney() const {
    return money;
}
void PlayScene::EarnMoney(int money) {
    this->money += money;
    PlayerStat::totalMoney=this->money;
    UIMoney->Text = std::string("$") + std::to_string(this->money);
}
void PlayScene::ReadMap() {
    std::string filename = std::string("Resource/map") + std::to_string(MapId) + ".txt";
    // Read map file.
    //char c;
    //std::vector<bool> mapData;
    std::vector<int> mapData;
    std::ifstream fin(filename);
    int _tmp;
    fin >> _tmp >> _tmp;
    /*while (fin >> c) {
        switch (c) {
            case '0': mapData.push_back(0); break;
            case '1': mapData.push_back(1); break;
            case '2': mapData.push_back(2); break;
            case '3': mapData.push_back(3); break;
            case '4': mapData.push_back(4); break;
            case '5': mapData.push_back(5); break;
            case '6': mapData.push_back(6); break;
            case '7': mapData.push_back(7); break;
            case '8': mapData.push_back(8); break;
            case '9': mapData.push_back(9); break;
            case '10': mapData.push_back(10); break;
            case '11': mapData.push_back(11); break;
            case '12': mapData.push_back(12); break;
            case '13': mapData.push_back(13); break;
            case '14': mapData.push_back(14); break;
            case '15': mapData.push_back(15); break;
            case '16': mapData.push_back(16); break;
            case '17': mapData.push_back(17); break;
            case '18': mapData.push_back(18); break;
            case '19': mapData.push_back(19); break;
            case '20': mapData.push_back(20); break;
            case '21': mapData.push_back(21); break;
            case '22': mapData.push_back(22); break;
            case '23': mapData.push_back(23); break;
            case '24': mapData.push_back(24); break;
            case '25': mapData.push_back(25); break;
            case '26': mapData.push_back(26); break;
            case '27': mapData.push_back(27); break;
            case '28': mapData.push_back(28); break;
            case '29': mapData.push_back(29); break;
            case '30': mapData.push_back(30); break;
            case '31': mapData.push_back(31); break;
            case '32': mapData.push_back(32); break;
            case '33': mapData.push_back(33); break;
            case '34': mapData.push_back(34); break;
            case '35': mapData.push_back(35); break;
            case '36': mapData.push_back(36); break;
            case '37': mapData.push_back(37); break;
            case '\n':
            case '\r':
                if (static_cast<int>(mapData.size()) / MapWidth != 0)
                    throw std::ios_base::failure("Map data is corrupted.");
                break;
            default: throw std::ios_base::failure("Map data is corrupted!");
        }
    }*/
   int value;
    while (fin >> value) {
        if (value < 0 || value > 600)
            throw std::ios_base::failure("Map value out of range!");
        mapData.push_back(value);
    }

    fin.close();
    // Validate map data.
    if (static_cast<int>(mapData.size()) != MapWidth * MapHeight)
        throw std::ios_base::failure("Map data is corrupted~");
    // Store map in 2d array.
    //mapState = std::vector<std::vector<TileType>>(MapHeight, std::vector<TileType>(MapWidth));
    mapState = std::vector<std::vector<BlockType>>(MapHeight, std::vector<BlockType>(MapWidth));
    for (int i = 0; i < MapHeight; i++) {
        for (int j = 0; j < MapWidth; j++) {
            const int num = mapData[i * MapWidth + j];
            //mapState[i][j] = num ? TILE_FLOOR : TILE_DIRT;
            switch (num) {
                case 0: mapState[i][j] = BlockType::FLOOR; break;
                case 1: mapState[i][j] = BlockType::WALL; break;
                case 2: mapState[i][j] = BlockType::TREE1; break;
                case 3: mapState[i][j] = BlockType::GROUND1; break;
                case 4: mapState[i][j] = BlockType::GROUND2; break;
                case 5: mapState[i][j] = BlockType::GROUND3; break;
                case 6: mapState[i][j] = BlockType::GROUND4; break;
                case 7: mapState[i][j] = BlockType::GROUND5; break;
                case 8: mapState[i][j] = BlockType::GROUND6; break;
                case 9: mapState[i][j] = BlockType::GROUND7; break;
                case 10: mapState[i][j] = BlockType::GROUND8; break;
                case 11: mapState[i][j] = BlockType::GROUND9; break;
                case 12: mapState[i][j] = BlockType::GROUND10; break;
                case 13: mapState[i][j] = BlockType::GROUND11; break;
                case 14: mapState[i][j] = BlockType::GROUND12; break;
                case 15: mapState[i][j] = BlockType::GROUND13; break;
                case 16: mapState[i][j] = BlockType::GROUND14; break;
                case 17: mapState[i][j] = BlockType::GROUND15; break;
                case 18: mapState[i][j] = BlockType::GROUND16; break;
                case 19: mapState[i][j] = BlockType::GROUND17; break;
                case 20: mapState[i][j] = BlockType::GROUND18; break;
                case 21: mapState[i][j] = BlockType::GROUND19; break;
                case 22: mapState[i][j] = BlockType::GROUND20; break;
                case 23: mapState[i][j] = BlockType::GROUND21; break;
                case 24: mapState[i][j] = BlockType::GROUND22; break;
                case 25: mapState[i][j] = BlockType::GROUND23; break;
                case 26: mapState[i][j] = BlockType::GROUND24; break;
                case 27: mapState[i][j] = BlockType::GROUND25; break;
                case 28: mapState[i][j] = BlockType::GROUND26; break;
                case 29: mapState[i][j] = BlockType::GROUND27; break;
                case 30: mapState[i][j] = BlockType::GROUND28; break;
                case 31: mapState[i][j] = BlockType::GROUND29; break;
                case 32: mapState[i][j] = BlockType::GROUND30; break;
                case 33: mapState[i][j] = BlockType::GROUND31; break;
                case 34: mapState[i][j] = BlockType::GROUND32; break;
                case 35: mapState[i][j] = BlockType::GROUND33; break;
                case 36: mapState[i][j] = BlockType::GROUND34; break;
                case 37: mapState[i][j] = BlockType::GROUND35; break;
                case 168: mapState[i][j] = BlockType::GROUND36; break;
                case 169: mapState[i][j] = BlockType::GROUND37; break;
                case 170: mapState[i][j] = BlockType::GROUND38; break;
                case 171: mapState[i][j] = BlockType::GROUND39; break;
                case 172: mapState[i][j] = BlockType::GROUND40; break;
                case 173: mapState[i][j] = BlockType::GROUND41; break;
                case 174: mapState[i][j] = BlockType::GROUND42; break;

                case 38: mapState[i][j] = BlockType::CSBUILDING1; break;
                case 39: mapState[i][j] = BlockType::CSBUILDING2; break;
                case 40: mapState[i][j] = BlockType::CSBUILDING3; break;
                case 41: mapState[i][j] = BlockType::CSBUILDING4; break;
                case 42: mapState[i][j] = BlockType::CSBUILDING5; break;
                case 43: mapState[i][j] = BlockType::CSBUILDING6; break;
                case 44: mapState[i][j] = BlockType::CSBUILDING7; break;
                case 45: mapState[i][j] = BlockType::CSBUILDING8; break;
                case 46: mapState[i][j] = BlockType::CSBUILDING9; break;
                case 47: mapState[i][j] = BlockType::CSBUILDING10; break;
                case 48: mapState[i][j] = BlockType::CSBUILDING11; break;
                case 49: mapState[i][j] = BlockType::CSBUILDING12; break;
                case 50: mapState[i][j] = BlockType::CSBUILDING13; break;
                case 51: mapState[i][j] = BlockType::CSBUILDING14; break;
                case 52: mapState[i][j] = BlockType::CSBUILDING15; break;
                case 53: mapState[i][j] = BlockType::CSBUILDING16; break;
                case 54: mapState[i][j] = BlockType::CSBUILDING17; break;
                case 55: mapState[i][j] = BlockType::CSBUILDING18; break;
                case 56: mapState[i][j] = BlockType::CSBUILDING19; break;
                case 57: mapState[i][j] = BlockType::CSBUILDING20; break;
                case 58: mapState[i][j] = BlockType::CSBUILDING21; break;
                case 59: mapState[i][j] = BlockType::CSBUILDING22; break;
                case 60: mapState[i][j] = BlockType::CSBUILDING23; break;
                case 61: mapState[i][j] = BlockType::CSBUILDING24; break;
                case 62: mapState[i][j] = BlockType::CSBUILDING25; break;
                case 63: mapState[i][j] = BlockType::CSBUILDING26; break;
                case 64: mapState[i][j] = BlockType::CSBUILDING27; break;
                case 65: mapState[i][j] = BlockType::CSBUILDING28; break;
                case 66: mapState[i][j] = BlockType::CSBUILDING29; break;
                case 67: mapState[i][j] = BlockType::CSBUILDING30; break;
                case 68: mapState[i][j] = BlockType::CSBUILDING31; break;
                case 69: mapState[i][j] = BlockType::CSBUILDING32; break;
                case 70: mapState[i][j] = BlockType::CSBUILDING33; break;
                case 71: mapState[i][j] = BlockType::CSBUILDING34; break;
                case 72: mapState[i][j] = BlockType::CSBUILDING35; break;
                case 73: mapState[i][j] = BlockType::CSBUILDING36; break;
                case 74: mapState[i][j] = BlockType::CSBUILDING37; break;
                case 75: mapState[i][j] = BlockType::CSBUILDING38; break;
                case 76: mapState[i][j] = BlockType::CSBUILDING39; break;
                case 77: mapState[i][j] = BlockType::CSBUILDING40; break;
                case 78: mapState[i][j] = BlockType::CSBUILDING41; break;
                case 79: mapState[i][j] = BlockType::CSBUILDING42; break;
                case 80: mapState[i][j] = BlockType::CSBUILDING43; break;
                case 81: mapState[i][j] = BlockType::CSBUILDING44; break;
                case 82: mapState[i][j] = BlockType::CSBUILDING45; break;
                case 83: mapState[i][j] = BlockType::CSBUILDING46; break;
                case 84: mapState[i][j] = BlockType::CSBUILDING47; break;
                case 85: mapState[i][j] = BlockType::CSBUILDING48; break;
                case 86: mapState[i][j] = BlockType::CSBUILDING49; break;
                case 87: mapState[i][j] = BlockType::CSBUILDING50; break;

                case 89: mapState[i][j] = BlockType::LAKE1; break;
                case 90: mapState[i][j] = BlockType::LAKE2; break;
                case 91: mapState[i][j] = BlockType::LAKE3; break;
                case 92: mapState[i][j] = BlockType::LAKE4; break;
                case 93: mapState[i][j] = BlockType::LAKE5; break;
                case 94: mapState[i][j] = BlockType::LAKE6; break;
                case 95: mapState[i][j] = BlockType::LAKE7; break;
                case 96: mapState[i][j] = BlockType::LAKE8; break;
                case 97: mapState[i][j] = BlockType::LAKE9; break;
                case 98: mapState[i][j] = BlockType::LAKE10; break;
                case 99: mapState[i][j] = BlockType::LAKE11; break;
                case 100: mapState[i][j] = BlockType::LAKE12; break;
                case 101: mapState[i][j] = BlockType::LAKE13; break;
                case 102: mapState[i][j] = BlockType::LAKE14; break;
                case 103: mapState[i][j] = BlockType::LAKE15; break;
                case 104: mapState[i][j] = BlockType::LAKE16; break;
                case 105: mapState[i][j] = BlockType::LAKE17; break;
                case 106: mapState[i][j] = BlockType::LAKE18; break;
                case 107: mapState[i][j] = BlockType::LAKE19; break;
                case 108: mapState[i][j] = BlockType::LAKE20; break;
                case 109: mapState[i][j] = BlockType::LAKE21; break;
                case 110: mapState[i][j] = BlockType::LAKE22; break;
                case 111: mapState[i][j] = BlockType::LAKE23; break;
                case 112: mapState[i][j] = BlockType::LAKE24; break;
                case 113: mapState[i][j] = BlockType::LAKE25; break;

                /*case 113: mapGrid[r][c] = BlockType::LAKE26; break;
                case 114: mapGrid[r][c] = BlockType::LAKE27; break;
                case 115: mapGrid[r][c] = BlockType::LAKE28; break;
                case 116: mapGrid[r][c] = BlockType::LAKE29; break;
                case 117: mapGrid[r][c] = BlockType::LAKE30; break;
                case 118: mapGrid[r][c] = BlockType::LAKE31; break;*/
                case 119: mapState[i][j] = BlockType::LIBRARY1; break;
                case 120: mapState[i][j] = BlockType::LIBRARY2; break;
                case 121: mapState[i][j] = BlockType::LIBRARY3; break;
                case 122: mapState[i][j] = BlockType::LIBRARY4; break;
                case 123: mapState[i][j] = BlockType::LIBRARY5; break;
                case 124: mapState[i][j] = BlockType::LIBRARY6; break;
                case 125: mapState[i][j] = BlockType::LIBRARY7; break;
                case 126: mapState[i][j] = BlockType::LIBRARY8; break;
                case 127: mapState[i][j] = BlockType::LIBRARY9; break;
                case 128: mapState[i][j] = BlockType::LIBRARY10; break;
                case 129: mapState[i][j] = BlockType::LIBRARY11; break;
                case 130: mapState[i][j] = BlockType::LIBRARY12; break;
                case 131: mapState[i][j] = BlockType::LIBRARY13; break;
                case 132: mapState[i][j] = BlockType::LIBRARY14; break;
                case 133: mapState[i][j] = BlockType::LIBRARY15; break;
                case 134: mapState[i][j] = BlockType::LIBRARY16; break;
                case 135: mapState[i][j] = BlockType::LIBRARY17; break;
                case 136: mapState[i][j] = BlockType::LIBRARY18; break;
                case 137: mapState[i][j] = BlockType::LIBRARY19; break;
                case 138: mapState[i][j] = BlockType::LIBRARY20; break;
                case 139: mapState[i][j] = BlockType::LIBRARY21; break;
                case 140: mapState[i][j] = BlockType::LIBRARY22; break;
                case 141: mapState[i][j] = BlockType::LIBRARY23; break;
                case 142: mapState[i][j] = BlockType::LIBRARY24; break;
                case 143: mapState[i][j] = BlockType::LIBRARY25; break;
                case 144: mapState[i][j] = BlockType::LIBRARY26; break;
                case 145: mapState[i][j] = BlockType::LIBRARY27; break;
                case 146: mapState[i][j] = BlockType::LIBRARY28; break;
                case 147: mapState[i][j] = BlockType::LIBRARY29; break;
                case 148: mapState[i][j] = BlockType::LIBRARY30; break;
                case 149: mapState[i][j] = BlockType::LIBRARY31; break;
                case 150: mapState[i][j] = BlockType::LIBRARY32; break;
                case 151: mapState[i][j] = BlockType::LIBRARY33; break;
                case 152: mapState[i][j] = BlockType::LIBRARY34; break;
                case 153: mapState[i][j] = BlockType::LIBRARY35; break;
                case 154: mapState[i][j] = BlockType::LIBRARY36; break;
                case 155: mapState[i][j] = BlockType::LIBRARY37; break;
                case 156: mapState[i][j] = BlockType::LIBRARY38; break;
                case 157: mapState[i][j] = BlockType::LIBRARY39; break;
                case 158: mapState[i][j] = BlockType::LIBRARY40; break;
                case 159: mapState[i][j]  = BlockType::LIBRARY41; break;
                case 160: mapState[i][j] = BlockType::LIBRARY42; break;
                case 161: mapState[i][j] = BlockType::LIBRARY43; break;
                case 162: mapState[i][j] = BlockType::LIBRARY44; break;
                case 163: mapState[i][j] = BlockType::LIBRARY45; break;
                case 164: mapState[i][j] = BlockType::LIBRARY46; break;
                case 165: mapState[i][j] = BlockType::LIBRARY47; break;
                case 166: mapState[i][j] = BlockType::LIBRARY48; break;

                case 167: mapState[i][j] = BlockType::TENNIS1; break;

                case 175: mapState[i][j] = BlockType::QINLAKE1; break;
                case 176: mapState[i][j] = BlockType::QINLAKE2; break;
                case 177: mapState[i][j] = BlockType::QINLAKE3; break;
                case 178: mapState[i][j] = BlockType::QINLAKE4; break;
                case 179: mapState[i][j] = BlockType::QINLAKE5; break;
                case 180: mapState[i][j] = BlockType::QINLAKE6; break;
                case 181: mapState[i][j] = BlockType::QINLAKE7; break;
                case 182: mapState[i][j] = BlockType::QINLAKE8; break;
                case 183: mapState[i][j] = BlockType::QINLAKE9; break;
                case 184: mapState[i][j] = BlockType::QINLAKE10; break;
                case 185: mapState[i][j] = BlockType::QINLAKE11; break;
                case 186: mapState[i][j] = BlockType::QINLAKE12; break;
                case 187: mapState[i][j] = BlockType::QINLAKE13; break;
                case 188: mapState[i][j] = BlockType::QINLAKE14; break;
                case 189: mapState[i][j] = BlockType::QINLAKE15; break;
                case 190: mapState[i][j] = BlockType::QINLAKE16; break;
                case 191: mapState[i][j] = BlockType::QINLAKE17; break;
                case 192: mapState[i][j] = BlockType::QINLAKE18; break;
                case 193: mapState[i][j] = BlockType::QINLAKE19; break;
                case 194: mapState[i][j] = BlockType::QINLAKE20; break;
                case 195: mapState[i][j] = BlockType::QINLAKE21; break;
                case 196: mapState[i][j] = BlockType::QINLAKE22; break;
                case 197: mapState[i][j] = BlockType::QINLAKE23; break;
                case 198: mapState[i][j] = BlockType::QINLAKE24; break;
                case 199: mapState[i][j] = BlockType::QINLAKE25; break;
                case 200: mapState[i][j] = BlockType::QINLAKE26; break;
                case 201: mapState[i][j] = BlockType::QINLAKE27; break;
                case 202: mapState[i][j] = BlockType::QINLAKE28; break;
                case 203: mapState[i][j] = BlockType::QINLAKE29; break;
                case 204: mapState[i][j] = BlockType::QINLAKE30; break;
                case 205: mapState[i][j] = BlockType::QINLAKE31; break;
                case 206: mapState[i][j] = BlockType::QINLAKE32; break;
                case 207: mapState[i][j] = BlockType::QINLAKE33; break;
                case 208: mapState[i][j] = BlockType::QINLAKE34; break;
                case 209: mapState[i][j] = BlockType::QINLAKE35; break;
                case 210: mapState[i][j] = BlockType::QINLAKE36; break;
                case 211: mapState[i][j] = BlockType::QINLAKE37; break;
                case 212: mapState[i][j] = BlockType::QINLAKE38; break;
                case 213: mapState[i][j] = BlockType::QINLAKE39; break;
                case 214: mapState[i][j] = BlockType::QINLAKE40; break;

                case 215: mapState[i][j] = BlockType::TENNIS2; break;
                case 216: mapState[i][j] = BlockType::TENNIS3; break;
                case 217: mapState[i][j] = BlockType::TENNIS4; break;
                case 218: mapState[i][j] = BlockType::TENNIS5; break;
                case 219: mapState[i][j] = BlockType::TENNIS6; break;
                case 220: mapState[i][j] = BlockType::TENNIS7; break;
                case 221: mapState[i][j] = BlockType::TENNIS8; break;
                case 222: mapState[i][j] = BlockType::TENNIS9; break;
                case 223: mapState[i][j] = BlockType::TENNIS10; break;
                case 224: mapState[i][j] = BlockType::TENNIS11; break;
                case 225: mapState[i][j] = BlockType::TENNIS12; break;
                case 226: mapState[i][j] = BlockType::TENNIS13; break;
                case 227: mapState[i][j] = BlockType::TENNIS14; break;
                case 228: mapState[i][j] = BlockType::TENNIS15; break;
                case 229: mapState[i][j] = BlockType::TENNIS16; break;
                case 230: mapState[i][j] = BlockType::TENNIS17; break;
                case 231: mapState[i][j] = BlockType::TENNIS18; break;
                case 232: mapState[i][j] = BlockType::TENNIS19; break;
                case 233: mapState[i][j] = BlockType::TENNIS20; break;
                case 234: mapState[i][j] = BlockType::TENNIS21; break;
                case 235: mapState[i][j] = BlockType::TENNIS22; break;
                case 236: mapState[i][j] = BlockType::TENNIS23; break;
                case 237: mapState[i][j] = BlockType::TENNIS24; break;
                case 238: mapState[i][j] = BlockType::TENNIS25; break;
                case 239: mapState[i][j] = BlockType::TENNIS26; break;
                case 240: mapState[i][j] = BlockType::TENNIS27; break;
                case 241: mapState[i][j] = BlockType::TENNIS28; break;
                case 242: mapState[i][j] = BlockType::TENNIS29; break;
                case 243: mapState[i][j] = BlockType::TENNIS30; break;
                case 244: mapState[i][j] = BlockType::TENNIS31; break;
                case 245: mapState[i][j] = BlockType::TENNIS32; break;
                case 246: mapState[i][j] = BlockType::TENNIS33; break;
                case 247: mapState[i][j] = BlockType::TENNIS34; break;
                case 248: mapState[i][j] = BlockType::TENNIS35; break;
                case 249: mapState[i][j] = BlockType::TENNIS36; break;
                case 250: mapState[i][j] = BlockType::TENNIS37; break;
                case 251: mapState[i][j] = BlockType::TENNIS38; break;
                case 252: mapState[i][j] = BlockType::TENNIS39; break;
                case 253: mapState[i][j] = BlockType::TENNIS40; break;
                case 254: mapState[i][j] = BlockType::TENNIS41; break;
                case 255: mapState[i][j] = BlockType::TENNIS42; break;

                case 465: mapState[i][j] = BlockType::CODE1; break;

                case 256: mapState[i][j] = BlockType::CODE2; break;
                case 257: mapState[i][j] = BlockType::CODE3; break;
                case 258: mapState[i][j] = BlockType::CODE4; break;
                case 259: mapState[i][j] = BlockType::CODE5; break;
                case 260: mapState[i][j] = BlockType::CODE6; break;
                case 261: mapState[i][j] = BlockType::CODE7; break;
                case 262: mapState[i][j] = BlockType::CODE8; break;
                case 263: mapState[i][j] = BlockType::CODE9; break;
                case 264: mapState[i][j] = BlockType::CODE10; break;
                case 265: mapState[i][j] = BlockType::CODE11; break;
                case 266: mapState[i][j] = BlockType::CODE12; break;
                case 267: mapState[i][j] = BlockType::CODE13; break;
                case 268: mapState[i][j] = BlockType::CODE14; break;
                case 269: mapState[i][j] = BlockType::CODE15; break;
                case 270: mapState[i][j] = BlockType::CODE16; break;
                case 271: mapState[i][j] = BlockType::CODE17; break;
                case 272: mapState[i][j] = BlockType::CODE18; break;
                case 273: mapState[i][j] = BlockType::CODE19; break;
                case 274: mapState[i][j] = BlockType::CODE20; break;
                case 275: mapState[i][j] = BlockType::CODE21; break;
                case 276: mapState[i][j] = BlockType::CODE22; break;
                case 277: mapState[i][j] = BlockType::CODE23; break;
                case 278: mapState[i][j] = BlockType::CODE24; break;
                case 279: mapState[i][j] = BlockType::CODE25; break;
                case 280: mapState[i][j] = BlockType::CODE26; break;
                case 281: mapState[i][j] = BlockType::CODE27; break;
                case 282: mapState[i][j] = BlockType::CODE28; break;
                case 283: mapState[i][j] = BlockType::CODE29; break;
                case 284: mapState[i][j] = BlockType::CODE30; break;

                case 285: mapState[i][j] = BlockType::HAM1; break;
                case 286: mapState[i][j] = BlockType::HAM2; break;
                case 287: mapState[i][j] = BlockType::HAM3; break;
                case 288: mapState[i][j] = BlockType::HAM4; break;
                case 289: mapState[i][j] = BlockType::HAM5; break;
                case 290: mapState[i][j] = BlockType::HAM6; break;
                case 291: mapState[i][j] = BlockType::HAM7; break;
                case 292: mapState[i][j] = BlockType::HAM8; break;
                case 293: mapState[i][j] = BlockType::HAM9; break;
                case 294: mapState[i][j] = BlockType::HAM10; break;
                case 295: mapState[i][j] = BlockType::HAM11; break;
                case 296: mapState[i][j] = BlockType::HAM12; break;
                case 297: mapState[i][j] = BlockType::HAM13; break;
                case 298: mapState[i][j] = BlockType::HAM14; break;
                case 299: mapState[i][j] = BlockType::HAM15; break;
                case 300: mapState[i][j] = BlockType::HAM16; break;
                case 301: mapState[i][j] = BlockType::HAM17; break;
                case 302: mapState[i][j] = BlockType::HAM18; break;
                case 303: mapState[i][j] = BlockType::HAM19; break;
                case 304: mapState[i][j] = BlockType::HAM20; break;
                case 305: mapState[i][j] = BlockType::HAM21; break;
                case 306: mapState[i][j] = BlockType::HAM22; break;
                case 307: mapState[i][j] = BlockType::HAM23; break;
                case 308: mapState[i][j] = BlockType::HAM24; break;
                case 309: mapState[i][j] = BlockType::HAM25; break;
                case 310: mapState[i][j] = BlockType::HAM26; break;
                case 311: mapState[i][j] = BlockType::HAM27; break;
                case 312: mapState[i][j] = BlockType::HAM28; break;
                case 313: mapState[i][j] = BlockType::HAM29; break;
                case 314: mapState[i][j] = BlockType::HAM30; break;
                case 315: mapState[i][j] = BlockType::HAM31; break;
                case 316: mapState[i][j] = BlockType::HAM32; break;
                case 317: mapState[i][j] = BlockType::HAM33; break;
                case 318: mapState[i][j] = BlockType::HAM34; break;
                case 319: mapState[i][j] = BlockType::HAM35; break;
                case 320: mapState[i][j] = BlockType::HAM36; break;

                case 321: mapState[i][j] = BlockType::POOL1; break;
                case 322: mapState[i][j] = BlockType::POOL2; break;
                case 323: mapState[i][j] = BlockType::POOL3; break;
                case 324: mapState[i][j] = BlockType::POOL4; break;
                case 325: mapState[i][j] = BlockType::POOL5; break;
                case 326: mapState[i][j] = BlockType::POOL6; break;
                case 327: mapState[i][j] = BlockType::POOL7; break;
                case 328: mapState[i][j] = BlockType::POOL8; break;
                case 329: mapState[i][j] = BlockType::POOL9; break;
                case 330: mapState[i][j] = BlockType::POOL10; break;
                case 331: mapState[i][j] = BlockType::POOL11; break;
                case 332: mapState[i][j] = BlockType::POOL12; break;
                case 333: mapState[i][j] = BlockType::POOL13; break;
                case 334: mapState[i][j] = BlockType::POOL14; break;
                case 335: mapState[i][j] = BlockType::POOL15; break;
                case 336: mapState[i][j] = BlockType::POOL16; break;
                case 337: mapState[i][j] = BlockType::POOL17; break;
                case 338: mapState[i][j] = BlockType::POOL18; break;
                case 339: mapState[i][j] = BlockType::POOL19; break;
                case 340: mapState[i][j] = BlockType::POOL20; break;
                case 341: mapState[i][j] = BlockType::POOL21; break;
                case 342: mapState[i][j] = BlockType::POOL22; break;
                case 343: mapState[i][j] = BlockType::POOL23; break;
                case 344: mapState[i][j] = BlockType::POOL24; break;
                case 345: mapState[i][j] = BlockType::POOL25; break;

                case 346: mapState[i][j] = BlockType::PARKING1; break;
                case 347: mapState[i][j] = BlockType::PARKING2; break;
                case 348: mapState[i][j] = BlockType::PARKING3; break;
                case 349: mapState[i][j] = BlockType::PARKING4; break;
                case 350: mapState[i][j] = BlockType::PARKING5; break;
                case 351: mapState[i][j] = BlockType::PARKING6; break;
                case 352: mapState[i][j] = BlockType::PARKING7; break;
                case 353: mapState[i][j] = BlockType::PARKING8; break;
                case 354: mapState[i][j] = BlockType::PARKING9; break;
                case 355: mapState[i][j] = BlockType::PARKING10; break;
                case 356: mapState[i][j] = BlockType::PARKING11; break;
                case 357: mapState[i][j] = BlockType::PARKING12; break;
                case 358: mapState[i][j] = BlockType::PARKING13; break;
                case 359: mapState[i][j] = BlockType::PARKING14; break;
                case 360: mapState[i][j] = BlockType::PARKING15; break;
                case 361: mapState[i][j] = BlockType::PARKING16; break;
                case 362: mapState[i][j] = BlockType::PARKING17; break;
                case 363: mapState[i][j] = BlockType::PARKING18; break;

                case 364: mapState[i][j] = BlockType::CLUB1; break;
                case 365: mapState[i][j] = BlockType::CLUB2; break;
                case 366: mapState[i][j] = BlockType::CLUB3; break;
                case 367: mapState[i][j] = BlockType::CLUB4; break;
                case 368: mapState[i][j] = BlockType::CLUB5; break;
                case 369: mapState[i][j] = BlockType::CLUB6; break;
                case 370: mapState[i][j] = BlockType::CLUB7; break;
                case 371: mapState[i][j] = BlockType::CLUB8; break;
                case 372: mapState[i][j] = BlockType::CLUB9; break;
                case 373: mapState[i][j] = BlockType::CLUB10; break;
                case 374: mapState[i][j] = BlockType::CLUB11; break;
                case 375: mapState[i][j] = BlockType::CLUB12; break;
                case 376: mapState[i][j] = BlockType::CLUB13; break;
                case 377: mapState[i][j] = BlockType::CLUB14; break;
                case 378: mapState[i][j] = BlockType::CLUB15; break;
                case 379: mapState[i][j] = BlockType::CLUB16; break;
                case 380: mapState[i][j] = BlockType::CLUB17; break;
                case 381: mapState[i][j] = BlockType::CLUB18; break;
                case 382: mapState[i][j] = BlockType::CLUB19; break;
                case 383: mapState[i][j] = BlockType::CLUB20; break;
                case 384: mapState[i][j] = BlockType::CLUB21; break;
                case 385: mapState[i][j] = BlockType::CLUB22; break;
                case 386: mapState[i][j] = BlockType::CLUB23; break;
                case 387: mapState[i][j] = BlockType::CLUB24; break;
                case 388: mapState[i][j] = BlockType::CLUB25; break;
                case 389: mapState[i][j] = BlockType::CLUB26; break;
                case 390: mapState[i][j] = BlockType::CLUB27; break;
                case 391: mapState[i][j] = BlockType::CLUB28; break;
                case 392: mapState[i][j] = BlockType::CLUB29; break;
                case 393: mapState[i][j] = BlockType::CLUB30; break;
                case 394: mapState[i][j] = BlockType::CLUB31; break;
                case 395: mapState[i][j] = BlockType::CLUB32; break;

                case 396: mapState[i][j] = BlockType::SHOP1; break;
                case 397: mapState[i][j] = BlockType::SHOP2; break;
                case 398: mapState[i][j] = BlockType::SHOP3; break;
                case 399: mapState[i][j] = BlockType::SHOP4; break;
                case 400: mapState[i][j] = BlockType::SHOP5; break;
                case 401: mapState[i][j] = BlockType::SHOP6; break;
                case 402: mapState[i][j] = BlockType::SHOP7; break;
                case 403: mapState[i][j] = BlockType::SHOP8; break;
                case 404: mapState[i][j] = BlockType::SHOP9; break;

                case 405: mapState[i][j] = BlockType::REST1; break;
                case 406: mapState[i][j] = BlockType::REST2; break;
                case 407: mapState[i][j] = BlockType::REST3; break;
                case 408: mapState[i][j] = BlockType::REST4; break;
                case 409: mapState[i][j] = BlockType::REST5; break;
                case 410: mapState[i][j] = BlockType::REST6; break;
                case 411: mapState[i][j] = BlockType::REST7; break;
                case 412: mapState[i][j] = BlockType::REST8; break;
                case 413: mapState[i][j] = BlockType::REST9; break;
                case 414: mapState[i][j] = BlockType::REST10; break;
                case 415: mapState[i][j] = BlockType::REST11; break;
                case 416: mapState[i][j] = BlockType::REST12; break;

                case 417: mapState[i][j] = BlockType::CASTLE1; break;
                case 418: mapState[i][j] = BlockType::CASTLE2; break;
                case 419: mapState[i][j] = BlockType::CASTLE3; break;
                case 420: mapState[i][j] = BlockType::CASTLE4; break;
                case 421: mapState[i][j] = BlockType::CASTLE5; break;
                case 422: mapState[i][j] = BlockType::CASTLE6; break;
                case 423: mapState[i][j] = BlockType::CASTLE7; break;
                case 424: mapState[i][j] = BlockType::CASTLE8; break;
                case 425: mapState[i][j] = BlockType::CASTLE9; break;
                case 426: mapState[i][j] = BlockType::CASTLE10; break;
                case 427: mapState[i][j] = BlockType::CASTLE11; break;
                case 428: mapState[i][j] = BlockType::CASTLE12; break;
                case 429: mapState[i][j] = BlockType::CASTLE13; break;
                case 430: mapState[i][j] = BlockType::CASTLE14; break;
                case 431: mapState[i][j] = BlockType::CASTLE15; break;
                case 432: mapState[i][j] = BlockType::CASTLE16; break;
                case 433: mapState[i][j] = BlockType::CASTLE17; break;
                case 434: mapState[i][j] = BlockType::CASTLE18; break;
                case 435: mapState[i][j] = BlockType::CASTLE19; break;
                case 436: mapState[i][j] = BlockType::CASTLE20; break;
                case 437: mapState[i][j] = BlockType::CASTLE21; break;
                case 438: mapState[i][j] = BlockType::CASTLE22; break;
                case 439: mapState[i][j] = BlockType::CASTLE23; break;
                case 440: mapState[i][j] = BlockType::CASTLE24; break;
                case 441: mapState[i][j] = BlockType::CASTLE25; break;
                case 442: mapState[i][j] = BlockType::CASTLE26; break;
                case 443: mapState[i][j] = BlockType::CASTLE27; break;
                case 444: mapState[i][j] = BlockType::CASTLE28; break;
                case 445: mapState[i][j] = BlockType::CASTLE29; break;
                case 446: mapState[i][j] = BlockType::CASTLE30; break;
                case 447: mapState[i][j] = BlockType::CASTLE31; break;
                case 448: mapState[i][j] = BlockType::CASTLE32; break;
                case 449: mapState[i][j] = BlockType::CASTLE33; break;
                case 450: mapState[i][j] = BlockType::CASTLE34; break;
                case 451: mapState[i][j] = BlockType::CASTLE35; break;
                case 452: mapState[i][j] = BlockType::CASTLE36; break;
                case 453: mapState[i][j] = BlockType::CASTLE37; break;
                case 454: mapState[i][j] = BlockType::CASTLE38; break;
                case 455: mapState[i][j] = BlockType::CASTLE39; break;
                case 456: mapState[i][j] = BlockType::CASTLE40; break;
                case 457: mapState[i][j] = BlockType::CASTLE41; break;
                case 458: mapState[i][j] = BlockType::CASTLE42; break;
                case 459: mapState[i][j] = BlockType::CASTLE43; break;
                case 460: mapState[i][j] = BlockType::CASTLE44; break;
                case 461: mapState[i][j] = BlockType::CASTLE45; break;
                case 462: mapState[i][j] = BlockType::CASTLE46; break;
                case 463: mapState[i][j] = BlockType::CASTLE47; break;
                case 464: mapState[i][j] = BlockType::CASTLE48; break;

                case 466: mapState[i][j] = BlockType::COFFEE1; break;
                case 467: mapState[i][j] = BlockType::COFFEE2; break;
                case 468: mapState[i][j] = BlockType::COFFEE3; break;
                case 469: mapState[i][j] = BlockType::COFFEE4; break;
                case 470: mapState[i][j] = BlockType::COFFEE5; break;
                case 471: mapState[i][j] = BlockType::COFFEE6; break;
                case 472: mapState[i][j] = BlockType::COFFEE7; break;
                case 473: mapState[i][j] = BlockType::COFFEE8; break;
                case 474: mapState[i][j] = BlockType::COFFEE9; break;
                case 475: mapState[i][j] = BlockType::COFFEE10; break;
                case 476: mapState[i][j] = BlockType::COFFEE11; break;
                case 477: mapState[i][j] = BlockType::COFFEE12; break;
                case 478: mapState[i][j] = BlockType::COFFEE13; break;
                case 479: mapState[i][j] = BlockType::COFFEE14; break;
                case 480: mapState[i][j] = BlockType::COFFEE15; break;
                case 481: mapState[i][j] = BlockType::COFFEE16; break;
                case 482: mapState[i][j] = BlockType::COFFEE17; break;
                case 483: mapState[i][j] = BlockType::COFFEE18; break;
                case 484: mapState[i][j] = BlockType::COFFEE19; break;
                case 485: mapState[i][j] = BlockType::COFFEE20; break;
                case 486: mapState[i][j] = BlockType::COFFEE21; break;
                case 487: mapState[i][j] = BlockType::COFFEE22; break;
                case 488: mapState[i][j] = BlockType::COFFEE23; break;
                case 489: mapState[i][j] = BlockType::COFFEE24; break;

                case 490: mapState[i][j] = BlockType::GRASS1; break;
                case 491: mapState[i][j] = BlockType::GRASS2; break;
                case 492: mapState[i][j] = BlockType::GRASS3; break;
                case 493: mapState[i][j] = BlockType::GRASS4; break;
                case 494: mapState[i][j] = BlockType::GRASS5; break;
                case 495: mapState[i][j] = BlockType::GRASS6; break;
                case 496: mapState[i][j] = BlockType::GRASS7; break;
                case 497: mapState[i][j] = BlockType::GRASS8; break;
                case 498: mapState[i][j] = BlockType::GRASS9; break;
                case 499: mapState[i][j] = BlockType::GRASS10; break;
                case 500: mapState[i][j] = BlockType::GRASS11; break;
                case 501: mapState[i][j] = BlockType::GRASS12; break;
                case 502: mapState[i][j] = BlockType::GRASS13; break;
                case 503: mapState[i][j] = BlockType::GRASS14; break;
                case 504: mapState[i][j] = BlockType::GRASS15; break;
                case 505: mapState[i][j] = BlockType::GRASS16; break;
                case 506: mapState[i][j] = BlockType::GRASS17; break;
                case 507: mapState[i][j] = BlockType::GRASS18; break;
                case 508: mapState[i][j] = BlockType::GRASS19; break;
                case 509: mapState[i][j] = BlockType::GRASS20; break;
                case 510: mapState[i][j] = BlockType::GRASS21; break;
                case 511: mapState[i][j] = BlockType::GRASS22; break;
                case 512: mapState[i][j] = BlockType::GRASS23; break;
                case 513: mapState[i][j] = BlockType::GRASS24; break;


                default: mapState[i][j] = BlockType::NOTHING; break; // 預設處理
            }
            //if (num)
            //    TileMapGroup->AddNewObject(new Engine::Image("play/floor.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
            //else
            //    TileMapGroup->AddNewObject(new Engine::Image("play/dirt.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
        }
    }
}
void PlayScene::ReadEnemyWave() {
    std::string filename = std::string("Resource/enemy") + std::to_string(MapId) + ".txt";
    // Read enemy file.
    float type, wait, repeat;
    enemyWaveData.clear();
    std::ifstream fin(filename);
    while (fin >> type && fin >> wait && fin >> repeat) {
        for (int i = 0; i < repeat; i++)
            enemyWaveData.emplace_back(type, wait);
    }
    fin.close();

}
void PlayScene::ConstructUI() {
    // Background
    //UIGroup->AddNewObject(new Engine::Image("play/sand.png", 1280, 0, 320, 832));
    // Text
    //UIGroup->AddNewObject(new Engine::Label(std::string("Stage ") + std::to_string(MapId), "pirulen.ttf", 32, 1294, 0));
    UIGroup->AddNewObject(UIMoney = new Engine::Label(std::string("$") + std::to_string(money), "pirulen.ttf", 24, 1294, 48));
    //UIGroup->AddNewObject(UILives = new Engine::Label(std::string("Life ") + std::to_string(lives), "pirulen.ttf", 24, 1294, 88));
    //TurretButton *btn;
    // Button 1
    //btn = new TurretButton("play/floor.png", "play/dirt.png",
    //                       Engine::Sprite("play/tower-base.png", 1294, 136, 0, 0, 0, 0),
    //                       Engine::Sprite("play/turret-1.png", 1294, 136 - 8, 0, 0, 0, 0), 1294, 136, MachineGunTurret::Price);
    // Reference: Class Member Function Pointer and std::bind.
    //btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 0));
    //UIGroup->AddNewControlObject(btn);
    // Button 2
    //btn = new TurretButton("play/floor.png", "play/dirt.png",
    //                       Engine::Sprite("play/tower-base.png", 1370, 136, 0, 0, 0, 0),
    //                       Engine::Sprite("play/turret-2.png", 1370, 136 - 8, 0, 0, 0, 0), 1370, 136, LaserTurret::Price);
    //btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 1));
    //UIGroup->AddNewControlObject(btn);

    //Button 3
    //btn = new TurretButton("play/floor.png", "play/dirt.png",
    //                       Engine::Sprite("play/tower-base.png", 1446, 136, 0, 0, 0, 0),
    //                       Engine::Sprite("play/turret-3.png", 1446, 136 , 0, 0, 0, 0), 1446, 136, FireTurret::Price);
    //btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 2));
    //UIGroup->AddNewControlObject(btn);

    //Button 4
    //btn = new TurretButton("play/floor.png", "play/dirt.png",
    //                       Engine::Sprite("play/tower-base.png", 1522, 136, 0, 0, 0, 0),
    //                       Engine::Sprite("play/turret-5.png", 1522, 136 , 0, 0, 0, 0), 1522, 136, ShieldTurret::Price);
    //btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 3));
    //UIGroup->AddNewControlObject(btn);

    //Button 5
    //btn = new TurretButton("play/floor.png", "play/dirt.png",
    //                       Engine::Sprite("play/shovel-base.png", 1294, 200, 0, 0, 0, 0),
    //                       Engine::Sprite("play/shovel.png", 1294, 200-8 , 0, 0, 0, 0), 1294, 200, 0);
    //btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 4));
    //UIGroup->AddNewControlObject(btn);

    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int shift = 135 + 25;
    dangerIndicator = new Engine::Sprite("play/benjamin.png", w - shift, h - shift);
    dangerIndicator->Tint.a = 0;
    UIGroup->AddNewObject(dangerIndicator);
}

void PlayScene::UIBtnClicked(int id) {
    if (preview)
        UIGroup->RemoveObject(preview->GetObjectIterator());
    if (id == 0 && money >= MachineGunTurret::Price)
        preview = new MachineGunTurret(0, 0);
    else if (id == 1 && money >= LaserTurret::Price)
        preview = new LaserTurret(0, 0);
    else if (id == 2 && money >= FireTurret::Price)
        preview = new FireTurret(0, 0);
    else if (id == 3 && money >= ShieldTurret::Price)
        preview = new ShieldTurret(0, 0);
    else if (id == 4)
        preview = new Shovel(0,0);
    if (!preview)
        return;
    preview->Position = Engine::GameEngine::GetInstance().GetMousePosition();
    preview->Tint = al_map_rgba(255, 255, 255, 200);
    preview->Enabled = false;
    preview->Preview = true;
    UIGroup->AddNewObject(preview);
    OnMouseMove(Engine::GameEngine::GetInstance().GetMousePosition().x, Engine::GameEngine::GetInstance().GetMousePosition().y);
}

/*bool PlayScene::CheckSpaceValid(int x, int y) {
    if (x < 0 || x >= MapWidth || y < 0 || y >= MapHeight)
        return false;
    auto map00 = mapState[y][x];
    //mapState[y][x] = TILE_OCCUPIED;
    
    std::vector<std::vector<int>> map = CalculateBFSDistance();
    mapState[y][x] = map00;
    if (map[0][0] == -1)
        return false;
    for (auto &it : EnemyGroup->GetObjects()) {
        Engine::Point pnt;
        pnt.x = floor(it->Position.x / BlockSize);
        pnt.y = floor(it->Position.y / BlockSize);
        if (pnt.x < 0) pnt.x = 0;
        if (pnt.x >= MapWidth) pnt.x = MapWidth - 1;
        if (pnt.y < 0) pnt.y = 0;
        if (pnt.y >= MapHeight) pnt.y = MapHeight - 1;
        if (map[pnt.y][pnt.x] == -1)
            return false;
    }
    // All enemy have path to exit.
    //mapState[y][x] = TILE_OCCUPIED;
    mapDistance = map;
    for (auto &it : EnemyGroup->GetObjects())
        dynamic_cast<Enemy *>(it)->UpdatePath(mapDistance);
    return true;
}*/

bool PlayScene::IsWalkable(int x, int y) const{
    if (x < 0 || x >= MapWidth || y < 0 || y >= MapHeight)
        return false;
    BlockType type = mapState[y][x];
    return (type==BlockType::FLOOR);
}

std::vector<std::vector<int>> PlayScene::CalculateBFSDistance() {
    // Reverse BFS to find path.
    std::vector<std::vector<int>> map(MapHeight, std::vector<int>(std::vector<int>(MapWidth, -1)));
    std::queue<Engine::Point> que;

    if (mapState.empty() || mapState[0].empty()) {
        std::cerr << "[ERROR] mapState not initialized before BFS!\n";
        return std::vector<std::vector<int>>(MapHeight, std::vector<int>(MapWidth, -1));
    }

    int endX = MapWidth - 1;
    int endY = MapHeight - 1;
    // Push end point.
    // BFS from end point.
    if (!IsWalkable(endX, endY)){
        std::cerr << "[ERROR] End point (" << endX << ", " << endY << ") is not walkable. BlockType = "
              << static_cast<int>(mapState[endY][endX]) << std::endl;
        return map;
    }
    que.push(Engine::Point(endX, endY));
    map[endY][endX] = 0;
    while (!que.empty()) {
        Engine::Point p = que.front();
        que.pop();
        // TODO PROJECT-1 (1/1): Implement a BFS starting from the most right-bottom block in the map.
        //               For each step you should assign the corresponding distance to the most right-bottom block.
        //               mapState[y][x] is TILE_DIRT if it is empty.
        for(auto& dir:directions){
            int nx=p.x+dir.x;
            int ny=p.y+dir.y;
            if (nx < 0 || nx >= MapWidth || ny < 0 || ny >= MapHeight)
                continue;
            if (!IsWalkable(nx, ny)){
                std::cerr << "[SKIP] (" << nx << ", " << ny << ") is not walkable. BlockType = "
                    << static_cast<int>(mapState[ny][nx]) << std::endl;
                continue;
            }
            if (map[ny][nx] != -1) {
                std::cerr << "[SKIP] (" << nx << ", " << ny << ") already visited. Distance = "
                        << map[ny][nx] << std::endl;
                continue;
            }
            map[ny][nx] = map[p.y][p.x] + 1;
            que.push(Engine::Point(nx, ny));
            std::cerr << "[DEBUG] BFS add (" << nx << ", " << ny << ") = " << map[ny][nx] << "\n";
        }
    }
    return map;
}

std::vector<Engine::Point> PlayScene::GetAllValidSpawnPoints() {
    std::vector<Engine::Point> validPoints;
    for (int y = 0; y < MapHeight; ++y) {
        for (int x = 0; x < MapWidth; ++x) {
            /*if (mapState[y][x] == TILE_DIRT) {
                validPoints.emplace_back(x, y);
            }*/
           if (mapState[y][x] == BlockType::FLOOR) {
                validPoints.emplace_back(x, y);
            }
        }
    }
    return validPoints;
}

void PlayScene::ModifyReadMapTiles(int gx,int gy){
    if (gx < 1 || gy < 1 || gx > MapWidth || gy > MapHeight) {
        std::cout << "Map size: " << MapWidth << " x " << MapHeight << "\n";
        return;
    }
    //mapState[gx][gy] = TILE_FLOOR;
    mapState[gx][gy] = BlockType::FLOOR;
    std::cout << "Tile at (" << gx << ", " << gy << ") set to FLOOR.\n";
}

Player* PlayScene::GetPlayer() const {
    return player;
}

void PlayScene::healthDraw(float health) const  {

    float x = screenW - 300;
    float y = 100;
    float width = 200;
    float height = 30;
    float maxHealth = 16.0f * 7.0f; // total range of a semester
    al_draw_filled_rectangle(x, y, x + width, y + height, al_map_rgb(100, 100, 100));

    // Compute health width
    float healthWidth = (health / maxHealth) * width;

    // Choose color based on health
    ALLEGRO_COLOR color = al_map_rgb(0, 255, 0); // green
    if (health / maxHealth < 0.3) {
        color = al_map_rgb(255, 0, 0); // red
    } else if (health / maxHealth < 0.6) {
        color = al_map_rgb(255, 255, 0); // yellow
    }

    // Draw current health
    al_draw_filled_rectangle(x, y, x + healthWidth, y + height, color);

    // Optional: border
    al_draw_rectangle(x, y, x + width, y + height, al_map_rgb(0, 0, 0), 2);
}
