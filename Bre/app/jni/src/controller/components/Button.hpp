//
// Created by Jonathan on 05/11/2024.
//

#ifndef BRE_BUTTON_HPP
#define BRE_BUTTON_HPP

#include <string>
#include <functional>
#include "Rectangle.hpp"
#include "StopWatch.hpp"

class Button : public Rectangle {

private:
    bool pressed = false;
    std::string text = "";
    StopWatch timer = StopWatch(TimeUnit::MILLISECONDS);
    std::function<void()> onClick = [](){};
    std::function<void()> onLongClick = [](){};

    static constexpr int LONG_CLICK_DURATION = 1000;

public:
    Button() = default;
    Button(const Button& b) : Rectangle(b), pressed(b.pressed), text(b.text), timer(b.timer), onClick(b.onClick), onLongClick(b.onLongClick) {}
    Button(const float x, const float y, const float w, const float h) : Rectangle(x, y, w, h) {}

    bool isClicked(const float x, const float y) const {
        return contains(x, y);
    }

    bool isClickedForLong(const float x, const float y) const {
        return pressed && contains(x, y) && timer.now() > LONG_CLICK_DURATION;
    }

    void handleInput(const float x, const float y) {
        if (isClicked(x, y)) {
            if(!pressed) {
                timer.start();
                pressed = true;
            }
        } else {
            if (pressed) {
                pressed = false;
                timer.stop();
                if (timer.now() <= LONG_CLICK_DURATION) {
                    onClick();
                }
            }
        }

        if (isClickedForLong(x, y)) {
            onLongClick();
        }
    }

    long unsigned int getForHowLongTheButtonHasBeenPressed() const {
        return timer.now();
    }

    void setOnClickListener(const std::function<void()>& onClick) {
        this->onClick = onClick;
    }

    void setOnLongClickListener(const std::function<void()>& onLongClick) {
        this->onLongClick = onLongClick;
    }
};

#endif //BRE_BUTTON_HPP
