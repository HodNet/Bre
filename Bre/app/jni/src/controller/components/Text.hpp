//
// Created by Jonathan on 14/11/2024.
//

#ifndef BRE_TEXT_HPP
#define BRE_TEXT_HPP

#include "../../controller/components/Rectangle.hpp"

class Text : public Point2D {

protected:
    const Point2D center;
    char* text = nullptr;
    int fontSize = 0;
    bool bold = false;

public:
    Text() = default;
    Text(const Text& t) = default;
    Text(const float x, const float y, const char* text, const int fontSize, const bool bold = false) :
            Point2D(x, y), center(x, y), text(const_cast<char *>(text)), fontSize(fontSize), bold(bold) {}

    void setText(char* text) {
        this->text = text;
    }

    const char* getText() const {
        return text;
    }

    std::size_t getLength() const {
        return std::strlen(text);
    }

    int getFontSize() const {
        return fontSize;
    }

    bool isBold() const {
        return bold;
    }

    int getCenterX() const {
        return center.x;
    }

    int getCenterY() const {
        return center.y;
    }
};

#endif //BRE_TEXT_HPP
