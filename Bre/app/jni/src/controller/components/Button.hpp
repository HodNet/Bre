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
    StopWatch timer = StopWatch(TimeUnit::MILLISECONDS);
    std::function<void()> onClick = [](){};
    std::function<void()> onLongClick = [](){};

    static constexpr int LONG_CLICK_DURATION = 1000;

public:
    Button() = default;
    Button(const Button& b) = default;
    Button(const float x, const float y, const float w, const float h) : Rectangle(x, y, w, h) {}

    bool isPressed() const {
        return pressed;
    }

    bool isClicked(const float x, const float y) const {
        return contains(x, y);
    }

    bool isClickedForLong(const float x, const float y) const {
        return pressed && contains(x, y) && timer.now() > LONG_CLICK_DURATION;
    }

    void handleInput(const TouchInput* touchInput) {
        if (touchInput == nullptr)
            return;

        const float x = touchInput->x;
        const float y = touchInput->y;

        if (isClicked(x, y)) {
            if (!pressed) {
                timer.start();
                pressed = true;
            }
        } else {
            if (pressed) {
                pressed = false;
                timer.stop();
            }
        }

        if (isClickedForLong(x, y)) {
            onLongClick();
        }

        if (touchInput->type == TouchInputType::SCREEN_RELEASE || touchInput->type == TouchInputType::SCREEN_TAP) {
            if(pressed) {
                pressed = false;
                timer.stop();
                if (timer.now() <= LONG_CLICK_DURATION) {
                    onClick();
                }
            }
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
