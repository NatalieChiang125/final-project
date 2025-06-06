// Map.cpp
#include "map.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/IScene.hpp"
#include "Scene/PlayScene.hpp"
#include <fstream>
#include <iostream>

Map::Map() {
    /*loadMapFromFile(filepath);
    // 這裡可以載入圖片資源，音效等
    tileset = al_load_bitmap("tileset.png");
    coinSprites = al_load_bitmap("coin_sprites.png");
    // 其他初始化*/
    tiles = std::vector<std::vector<BlockType>>(
        PlayScene::MapHeight,
        std::vector<BlockType>(PlayScene::MapWidth, BlockType::FLOOR)
    );
}

/*Map::~Map() {
    cleanup();
}

void Map::cleanup() {
    if (tileset) al_destroy_bitmap(tileset);
    if (coinSprites) al_destroy_bitmap(coinSprites);
    if (coinAudio) al_destroy_sample(coinAudio);
}*/

void Map::Initialize() {
    //tiles = std::vector<std::vector<int>>(PlayScene::MapHeight, std::vector<int>(PlayScene::MapWidth, static_cast<int>(BlockType::FLOOR)));
    tiles = std::vector<std::vector<BlockType>>(PlayScene::MapHeight, std::vector<BlockType>(PlayScene::MapWidth, BlockType::FLOOR));
}

void Map::Terminate() {
    IScene::Terminate();
}

void Map::loadMapFromFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file) {
        std::cerr << "Failed to open map file: " << filepath << std::endl;
        return;
    }

    // 簡單示範從檔案讀地圖
    file >> rows >> cols;

    mapGrid.resize(rows, std::vector<BlockType>(cols, BlockType::NOTHING));
    coinStatus.resize(rows, std::vector<CoinStatus>(cols, CoinStatus::DISAPPEAR));
    coinAnimationFrame.resize(rows, std::vector<int>(cols, 0));

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int tile;
            file >> tile;
            mapGrid[r][c] = static_cast<BlockType>(tile);
            if (mapGrid[r][c] == BlockType::COIN) {
                coinStatus[r][c] = CoinStatus::APPEAR;
            }
        }
    }

    // 假設檔案接著還有產生點、敵人資料等
    // ...
}

void Map::draw(const Point& cameraPos) {
    // 用 Allegro 畫出可視範圍的地圖 tiles
    // cameraPos 代表相機(玩家視角)左上角的座標

     // 假設每格32x32像素

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int drawX = c * tileSize - cameraPos.x;
            int drawY = r * tileSize - cameraPos.y;

            // 這裡依據 mapGrid[r][c] 繪製相應圖片
            // 假設 tileset 分割好，每種 BlockType 對應一塊圖
            BlockType type = mapGrid[r][c];
            if (type != BlockType::NOTHING) {
                // 例如：
                // al_draw_bitmap_region(tileset, srcX, srcY, tileSize, tileSize, drawX, drawY, 0);
            }

            // 繪製硬幣動畫（如果有）
            if (coinStatus[r][c] == CoinStatus::APPEAR) {
                // al_draw_bitmap_region(coinSprites, frameX, frameY, ..., drawX, drawY, 0);
            }
        }
    }
}

void Map::update(const Point& playerPos, int& totalCoins) {
    // 更新硬幣動畫、硬幣狀態等
    // 例如判斷玩家是否在硬幣上，更新 totalCoins 等
}

bool Map::isWalkable(BlockType block) const {
    switch (block) {
        case BlockType::FLOOR: return true;
        case BlockType::COIN: return true; // 可走
        // 其他判斷
        default: return false;
    }
}

Engine::Point Map::WorldToTile(const Engine::Point& pos){
    return Engine::Point(static_cast<int>(pos.x) / tileSize, static_cast<int>(pos.y) / tileSize);
}

BlockType Map::GetBlock(const Engine::Point& tilePos) {
    // 確保 tilePos 在合法範圍內
    int x = static_cast<int>(tilePos.x);
    int y = static_cast<int>(tilePos.y);

    if (x >= 0 && x < PlayScene::MapWidth && y >= 0 && y < PlayScene::MapHeight) {
        return tiles[y][x]; // y 是 row x 是 column
    }
    // 超出邊界
    return BlockType::NOTHING;
}