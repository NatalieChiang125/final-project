// Engine/TextInput.cpp
/*#include "TextInput.hpp"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>

namespace Engine {
    TextInput::TextInput(float x, float y, float w, float h,
                         const std::string& font, int fontSize,
                         ALLEGRO_COLOR textColor,
                         ALLEGRO_COLOR bgColor,
                         ALLEGRO_COLOR borderColor)
        : IControl(x, y), width(w), height(h), bgColor(bgColor), borderColor(borderColor), focused(false) {
        label = std::make_shared<Label>("", font, fontSize, x + 5, y + h / 2, 
                                        textColor.r * 255, textColor.g * 255, textColor.b * 255, 255, 0, 0.5f);
    }

    void Engine::TextInput::SetTextAlignment(Alignment align) {
        alignment = align;
    }

    void TextInput::Draw() const {
        // Background
        al_draw_filled_rectangle(Position.x, Position.y, Position.x + width, Position.y + height, bgColor);
        // Border (highlight if focused)
        ALLEGRO_COLOR finalBorder = focused ? al_map_rgb(0, 120, 255) : borderColor;
        al_draw_rectangle(Position.x, Position.y, Position.x + width, Position.y + height, finalBorder, 2);
        // Text
        label->Draw();
    }

    void TextInput::OnKeyDown(int keyCode) {
        if (!focused) return;

        if (keyCode >= ALLEGRO_KEY_A && keyCode <= ALLEGRO_KEY_Z) {
            text += static_cast<char>('a' + (keyCode - ALLEGRO_KEY_A));
        } else if (keyCode >= ALLEGRO_KEY_0 && keyCode <= ALLEGRO_KEY_9) {
            text += static_cast<char>('0' + (keyCode - ALLEGRO_KEY_0));
        } else if (keyCode == ALLEGRO_KEY_SPACE) {
            text += ' ';
        } else if (keyCode == ALLEGRO_KEY_BACKSPACE && !text.empty()) {
            text.pop_back();
        }

        label->SetText(text);
    }

    void TextInput::OnMouseDown(int button, int mx, int my) {
        // Focus if inside the box
        focused = (mx >= Position.x && mx <= Position.x + width &&
                   my >= Position.y && my <= Position.y + height);
    }

    void TextInput::SetText(const std::string& newText) {
        text = newText;
        label->SetText(text);
    }

    std::string TextInput::GetText() const {
        return text;
    }

    void TextInput::SetFocus(bool f) {
        focused = f;
    }
}*/
