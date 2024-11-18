//
// Created by Jonathan on 12/11/2024.
//

#ifndef BRE_TRANSITION_HORIZONTALOSCILLATION_HPP
#define BRE_TRANSITION_HORIZONTALOSCILLATION_HPP

#include <cmath>
#include <memory>

#include "../../controller/components/Animation.hpp"
#include "../../controller/components/Rectangle.hpp"
#include "../../controller/components/OscillationAnimation.hpp"

/**
 * The rectangle will come from the left or from the right and stop at the final point, oscillating
 * around it, through a damped harmonic motion
 */
class Transition_HorizontalOscillation : virtual public Animation {

private:
    OscillationAnimation horizontalOscillation;

public:
    Transition_HorizontalOscillation() = default;
    Transition_HorizontalOscillation(const Transition_HorizontalOscillation& t) = default;

    Transition_HorizontalOscillation(Rectangle& rect, const float x0) {
        float final_x = rect.x;
        rect.setX(x0);
        horizontalOscillation = OscillationAnimation(rect.x, 0, final_x);
    }

    bool isFinished() const override {
        return horizontalOscillation.isFinished();
    }

    void update() override {
        horizontalOscillation.update();
    }
};

#endif //BRE_TRANSITION_HORIZONTALOSCILLATION_HPP
