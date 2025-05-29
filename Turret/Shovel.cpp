#include <allegro5/base.h>
#include <cmath>
#include <string>
#include "Shovel.hpp"

Shovel::Shovel(float x,float y)
    : Turret("play/shovel-base.png", "play/shovel.png", x, y, 0, 0, 0){}