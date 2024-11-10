//
// Created by Jonathan on 08/11/2024.
//

#ifndef BRE_ICONBUTTON_HPP
#define BRE_ICONBUTTON_HPP

#include "Button.hpp"
#include "../../res/images.hpp"

class IconButton : public Button {

private:
    const char* icon = images::not_found;
    const float src_width = 0;
    const float src_height = 0;

public:
    IconButton() = default;
    IconButton(const IconButton& b) : Button(b), icon(b.icon), src_width(b.src_width), src_height(b.src_height) {}
    IconButton(const float x, const float y, const float w, const float h, const char* file_name, const float file_width, const float file_height) :
        Button(x, y, w, h), icon(file_name), src_width(file_width), src_height(file_height) {}

    const char* getIcon() const {
        return icon;
    }

    float getSrcWidth() const {
        return src_width;
    }

    float getSrcHeight() const {
        return src_height;
    }
};

#endif //BRE_ICONBUTTON_HPP
