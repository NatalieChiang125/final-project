// Map.cpp
#include "map.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/IScene.hpp"
#include "Scene/PlayScene.hpp"
#include <fstream>
#include <iostream>

PlayScene *Map::getPlayScene() {
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
    
}

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

    tileSet[0] = new Tile("play/sand.png", 0, 0);
    tileSet[1] = new Tile("play/grass.png", 0, 0);
    tileSet[2] = new Tile("play/bigtree.png", 0, 0);
    tileSet[3] = new Tile("play/rockroad.png", 0, 0);
    tileSet[4] = new Tile("play/house.png", 0, 0);
    tileSet[5] = new Tile("play/flower1.png", 0, 0);
    tileSet[6] = new Tile("play/flower2.png", 0, 0);
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
    if (!file || rows <= 0 || cols <= 0) {
        std::cerr << "Invalid map dimensions in file." << std::endl;
        return;
    }

    mapGrid.resize(rows, std::vector<BlockType>(cols, BlockType::NOTHING));
    //coinStatus.resize(rows, std::vector<CoinStatus>(cols, CoinStatus::DISAPPEAR));
    //coinAnimationFrame.resize(rows, std::vector<int>(cols, 0));

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            char tile;
            file >> tile;
            //mapGrid[r][c] = static_cast<BlockType>(tile-'0');
            //if (mapGrid[r][c] == BlockType::COIN) {
            //    coinStatus[r][c] = CoinStatus::APPEAR;
            //}
            if (!file) {
                std::cerr << "Error reading tile at (" << r << "," << c << ")." << std::endl;
                throw std::ios_base::failure("Map data is corrupted.");
            }

           switch (tile) {
                case '0': mapGrid[r][c] = BlockType::FLOOR; break;
                case '1': mapGrid[r][c] = BlockType::WALL; break;
                case '2': mapGrid[r][c] = BlockType::TREE1; break;
                case '3': mapGrid[r][c] = BlockType::ROCKROAD; break;
                case '4': mapGrid[r][c] = BlockType::HOUSE; break;
                case '5': mapGrid[r][c] = BlockType::FLOWER1; break;
                case '6': mapGrid[r][c] = BlockType::FLOWER2; break;
                
                default:  
                    if (!file) {
                        std::cerr << "Error reading tile at (" << r << "," << c << ")." << std::endl;
                        throw std::ios_base::failure("Map data is corrupted.");
                    }
                    mapGrid[r][c] = BlockType::NOTHING;
                    break;
            }
        }
    }
    tiles = mapGrid;
    
    std::cerr << "[DEBUG] Map loaded: " << rows << " rows, " << cols << " cols.\n";

    std::cerr << "[DEBUG] mapGrid size: " << mapGrid.size() << " * " 
          << (mapGrid.empty() ? 0 : mapGrid[0].size()) << std::endl;

    
    // 假設檔案接著還有產生點、敵人資料等
    // ...
}




void Map::draw() {
    // 用 Allegro 畫出可視範圍的地圖 tiles
    // cameraPos 代表相機(玩家視角)左上角的座標

     // 假設每格32x32像素

    Engine::Point cameraPos = scene->getCam();

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int drawX = c * tileSize - cameraPos.x;
            int drawY = r * tileSize - cameraPos.y;

            // 這裡依據 mapGrid[r][c] 繪製相應圖片
            // 假設 tileset 分割好，每種 BlockType 對應一塊圖
            BlockType type = mapGrid[r][c];
            //BlockType type = tiles[r][c];
            //if (type != BlockType::NOTHING) {
                // 例如：
                // al_draw_bitmap_region(tileset, srcX, srcY, tileSize, tileSize, drawX, drawY, 0);
            //}

            // 繪製硬幣動畫（如果有）
            //if (coinStatus[r][c] == CoinStatus::APPEAR) {
                // al_draw_bitmap_region(coinSprites, frameX, frameY, ..., drawX, drawY, 0);
            //}

            if (type == BlockType::FLOOR) {
                // 例如：
                // al_draw_bitmap_region(tileset, srcX, srcY, tileSize, tileSize, drawX, drawY, 0);
                al_draw_scaled_bitmap(tileSet[0]->bmp.get(), // image 
                                             0, 0, 16, 16, // source x, source y, width, height
                                             drawX, drawY, tileSize, tileSize, // destiny x, destiny y, destiny width, destiny height
                                             0 // flag : set 0
                                             );
            }
            else if (type == BlockType::WALL) {

                al_draw_scaled_bitmap(tileSet[1]->bmp.get(), // image
                                             0, 0, 16, 16, // source x, source y, width, height
                                             drawX, drawY, tileSize, tileSize, // destiny x, destiny y, destiny width, destiny height
                                             0 // flag : set 0
                                             );
            }
            else if (type == BlockType::TREE1) {

                /*al_draw_scaled_bitmap(tileSet[2]->bmp.get(), // image
                                             0, 0, 16, 16, // source x, source y, width, height
                                             drawX, drawY, tileSize, tileSize, // destiny x, destiny y, destiny width, destiny height
                                             0 // flag : set 0
                                             );*/
                ALLEGRO_BITMAP* bmp = tileSet[2]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::ROCKROAD) {

                ALLEGRO_BITMAP* bmp = tileSet[3]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::HOUSE) {

                ALLEGRO_BITMAP* bmp = tileSet[4]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::FLOWER1) {

                ALLEGRO_BITMAP* bmp = tileSet[5]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }
            else if (type == BlockType::FLOWER2) {

                ALLEGRO_BITMAP* bmp = tileSet[6]->bmp.get();
                int imgW = al_get_bitmap_width(bmp);
                int imgH = al_get_bitmap_height(bmp);

                al_draw_scaled_bitmap(bmp,
                                    0, 0, imgW, imgH, // ← 使用整張圖
                                    drawX, drawY, tileSize, tileSize, // ← 縮放到 tile 大小
                                    0);
                

            }

        }
    }
}

void Map::update(float deltaTime) {
    // 更新硬幣動畫、硬幣狀態等
    // 例如判斷玩家是否在硬幣上，更新 totalCoins 等
    scene = getPlayScene();
    if (!scene) return;

    int playerX = static_cast<int>(scene->GetPlayer()->Position.x) / tileSize;
    int playerY = static_cast<int>(scene->GetPlayer()->Position.y) / tileSize;

    if (playerX < 0 || playerY < 0 || playerX >= cols || playerY >= rows) return;

    BlockType tile = mapGrid[playerY][playerX];

    /*if (tile == BlockType::HOUSE) {
        // 玩家走進房子，切換到任務場景
        Engine::GameEngine::GetInstance().ChangeScene("quiz");
    }*/

    std::pair<int, int> currentTile = {playerY, playerX};
    if (tile == BlockType::ROCKROAD && triggeredQuizzes.find(currentTile) == triggeredQuizzes.end() && !WaitToChangeScene) {
        //triggeredQuizzes.insert(currentTile);
        //Engine::GameEngine::GetInstance().ChangeScene("quiz");
        WaitToChangeScene = true;
        quizTriggerTimer = 1.0f;
    }
    if (WaitToChangeScene) {
        quizTriggerTimer -= deltaTime;
        if (quizTriggerTimer <= 0.0f) {
            WaitToChangeScene = false;
            triggeredQuizzes.insert(currentTile);
            Engine::GameEngine::GetInstance().ChangeScene("quiz");
        }
    }
}

bool Map::isWalkable(BlockType block) const {
    switch (block) {
        case BlockType::FLOOR: return true;
        case BlockType::ROCKROAD: return true;
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

int Map::GetWidth() const{
    return cols;
}
int Map::GetHeight() const{
    return rows;
}

