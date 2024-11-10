//
// Created by Jonathan on 08/11/2024.
//

#ifndef BRE_TEXTBUTTON_HPP
#define BRE_TEXTBUTTON_HPP

#include "Button.hpp"

class TextButton : public Button {

private:
    const char* text = "";

public:
    TextButton() = default;
    TextButton(const TextButton& b) : Button(b), text(b.text) {}
    TextButton(const float x, const float y, const float w, const float h, const char* text) : Button(x, y, w, h), text(text) {}

    const char* getText() const {
        return text;
    }

    void setText(const char* text) {
        this->text = text;
    }
};

#endif //BRE_TEXTBUTTON_HPP
