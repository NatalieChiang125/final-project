#ifndef TILE_HPP
#define TILE_HPP

#include <list>
#include <string>
#include <set>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include "Engine/Sprite.hpp"


class Tile : public Engine::Sprite {
public:
    Tile(std::string imgTile, float x, float y);
private:
    int spriteWidth = 64;        // 單格寬度
    int spriteHeight = 64;       // 單格高度

};
#endif   // Tiles_HPP
