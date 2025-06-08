// Map.hpp
#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "Engine/AudioHelper.hpp"
#include "Engine/IScene.hpp"
#include "Engine/Tile.hpp"
#include "Engine/Sprite.hpp"
#include "Player/Player.hpp"

// 基本點座標結構
struct Point {
    int x;
    int y;
};

namespace Engine {
    class Group;
    class Image;
    class Label;
    class Sprite;
    class Tile;
}   // namespace Engine

enum class BlockType : uint8_t {
    FLOOR,
    WALL,
    DOOR_CLOSE,
    HOLE,
    COIN,
    NOTHING
};

enum class CoinStatus : uint8_t {
    APPEAR,
    DISAPPEARING,
    DISAPPEAR
};

class Map  : public Engine::IScene {
protected:
    PlayScene *getPlayScene();
    PlayScene *scene;
public:
    int tileSize = 256;
    //Map(const std::string& filepath);
    Map();

    // 不允許拷貝，避免資源錯亂
    Map(const Map&) = delete;
    Map& operator=(const Map&) = delete;

    //void draw(const Point& cameraPos);
    //void update(const Point& playerPos, int& totalCoins);
    void draw();
    void update();

    bool isWalkable(BlockType block) const;
    void Initialize() override;
    void Terminate()override;
    Engine::Point WorldToTile(const Engine::Point& pos);
    BlockType GetBlock(const Engine::Point& tilePos);

    void loadMapFromFile(const std::string& filepath);

    int GetWidth() const;
    int GetHeight() const;

private:
    int rows;
    int cols;

    Tile* tileSet[6];

    // 使用vector管理地圖格子與硬幣狀態
    std::vector<std::vector<BlockType>> mapGrid;
    std::vector<std::vector<CoinStatus>> coinStatus;
    std::vector<std::vector<BlockType>> tiles;
    ALLEGRO_BITMAP* tileset = nullptr;
    ALLEGRO_BITMAP* coinSprites = nullptr;
    ALLEGRO_SAMPLE_ID coinAudio;

    Point spawnPoint;
    std::vector<Point> enemySpawns;
    std::vector<char> enemyCodes;

    // 硬幣動畫相關
    std::vector<std::vector<int>> coinAnimationFrame;
    int coinAnimationTimer = 0;

    
    

};
