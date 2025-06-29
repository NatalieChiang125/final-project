#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <list>
#include <memory>
#include <utility>
#include <vector>

#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/map.hpp"
#include "Player/Player.hpp"

class Turret;
namespace Engine {
    class Group;
    class Image;
    class Label;
    class Sprite;
}   // namespace Engine

class PlayScene final : public Engine::IScene {
private:
    enum TileType {
        TILE_DIRT,
        TILE_FLOOR,
        //TILE_GRASS,
        TILE_TREE,
        TILE_GROUND,
        TILE_CSBUIDING,
        TILE_LAKE,
        TILE_ROCKROAD,
        TILE_HOUSE,
        TILE_FLOWER1,
        TILE_FLOWER2,
        TILE_OCCUPIED,
        TILE_UNKNOWN,
    };
    ALLEGRO_SAMPLE_ID bgmId;
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> deathBGMInstance;
    float totalGameTime = 0.0f;
    

protected:
    int lives;
    int money;
    int SpeedMult;

public:
    Player* player;
    Engine::Point Camera;
    Player* GetPlayer() const;
    Map* map;
    int screenW;
    int screenH;
    static bool DebugMode;
    static const std::vector<Engine::Point> directions;
    static const int MapWidth, MapHeight;
    static const int BlockSize;
    static const float DangerTime;
    static const Engine::Point SpawnGridPoint;
    static const Engine::Point EndGridPoint;
    static const std::vector<int> code;
    int MapId;
    float ticks;
    float deathCountDown;
    // Map tiles.
    Group *TileMapGroup;
    Group *GroundEffectGroup;
    Group *DebugIndicatorGroup;
    Group *BulletGroup;
    Group *TowerGroup;
    Group *EnemyGroup;
    Group *EffectGroup;
    Group *UIGroup;
    Engine::Label *UIMoney;
    Engine::Label *UILives;
    Engine::Image *imgTarget;
    Engine::Sprite *dangerIndicator;
    Turret *preview;
    //std::vector<std::vector<TileType>> mapState;
    std::vector<std::vector<BlockType>> mapState;
    std::vector<std::vector<int>> mapDistance;
    std::list<std::pair<int, float>> enemyWaveData;
    std::list<int> keyStrokes;
    static Engine::Point GetClientSize();
    explicit PlayScene() = default;
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void Draw() const override;
    void OnMouseDown(int button, int mx, int my) override;
    void OnMouseMove(int mx, int my) override;
    void OnMouseUp(int button, int mx, int my) override;
    void OnKeyDown(int keyCode) override;
    void OnKeyUp(int keyCode) override;
    void Hit();
    int GetMoney() const;
    void EarnMoney(int money);
    void ReadMap();
    void ReadEnemyWave();
    void ConstructUI();
    void UIBtnClicked(int id);
    bool CheckSpaceValid(int x, int y);
    std::vector<std::vector<int>> CalculateBFSDistance();
    std::vector<Engine::Point> GetAllValidSpawnPoints();
    void ModifyReadMapTiles(int gx,int gy);
    Engine::Point getCam();
    bool IsWalkable(int x, int y) const;
    void healthDraw(float health) const;
};
#endif   // PLAYSCENE_HPP
