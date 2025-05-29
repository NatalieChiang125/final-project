// Engine/TextInput.hpp
/*#pragma once
#include <memory>
#include <string>
#include "UI/Component/Label.hpp"
#include "IControl.hpp"
#include "Point.hpp"

namespace Engine {
    class TextInput : public IControl {
    protected:
        std::shared_ptr<Label> label;
        std::string text;
        float width, height;
        ALLEGRO_COLOR bgColor;
        ALLEGRO_COLOR borderColor;
        bool focused;

    public:

        enum class Alignment {
            Left,
            Center,
            Right
        };

        void SetTextAlignment(Alignment align);

        TextInput(float x, float y, float width, float height,
                  const std::string& font, int fontSize,
                  ALLEGRO_COLOR textColor = al_map_rgb(0, 0, 0),
                  ALLEGRO_COLOR bgColor = al_map_rgb(255, 255, 255),
                  ALLEGRO_COLOR borderColor = al_map_rgb(0, 0, 0));

        void Draw() const;
        void OnKeyDown(int keyCode) override;
        void OnMouseDown(int button, int mx, int my) override;

        void SetText(const std::string& newText);
        std::string GetText() const;
        void SetFocus(bool f);

    private:
        Alignment alignment = Alignment::Left;

    };
}*/
