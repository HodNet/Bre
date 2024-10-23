//
// Created by Jonathan on 23/10/2024.
//

#ifndef BRE_CLONE_HPP
#define BRE_CLONE_HPP

#include "../../controller/components/Rectangle.hpp"

class Clone {

private:
    Rectangle rect;

public:
    Clone(unsigned int screen_w, unsigned int screen_h) :
            rect(
                    screen_w/2 - screen_w/20/2,
                    screen_h/2 - screen_w/20/2,
                    screen_w/20,
                    screen_w/20
            ) {
    }

    Rectangle getRect() const {
        return rect;
    }

    void setPosition(float x, float y) {
        rect.setX(x);
        rect.setY(y);
    }
};

#endif //BRE_CLONE_HPP
