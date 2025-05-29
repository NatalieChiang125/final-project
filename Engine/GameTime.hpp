#ifndef GAMETIME_HPP
#define GAMETIME_HPP

class GameTime {
public:
    static float gameTime;
    static void Reset() { gameTime = 0.0f; }
};

#endif
