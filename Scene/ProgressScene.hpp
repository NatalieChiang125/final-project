#ifndef PROGRESSSCENE_HPP
#define PROGRESSSCENE_HPP
#include "Engine/IScene.hpp"
#include <allegro5/allegro_audio.h>
#include <memory>

namespace Engine{
    class Label;
    class Image;
    class Sprite;
}

class ProgressScene final : public Engine::IScene {
private:
    

public:
    explicit ProgressScene() = default;
    void Initialize() override;
    void Terminate() override;
    void Draw() const override;
    void BackOnClick();
   // void BackOnClick(int stage);
};

#endif