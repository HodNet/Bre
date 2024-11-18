//
// Created by Jonathan on 12/11/2024.
//

#ifndef BRE_TRANSITION_VERTICALOSCILLATION_HPP
#define BRE_TRANSITION_VERTICALOSCILLATION_HPP

#include <cmath>

#include "../../controller/components/Animation.hpp"
#include "../../controller/components/Rectangle.hpp"
#include "../../controller/components/OscillationAnimation.hpp"

/**
 * The rectangle will come from below or from above and stop at the final point, oscillating
 * around it, through a damped harmonic motion
 */
class Transition_VerticalOscillation : virtual public Animation {

private:
    OscillationAnimation verticalOscillation;

public:
    Transition_VerticalOscillation() = default;
    Transition_VerticalOscillation(const Transition_VerticalOscillation& t) = default;

    Transition_VerticalOscillation(Rectangle& rect, const float y0) {
        float final_y = rect.y;
        rect.setY(y0);
        verticalOscillation = OscillationAnimation(rect.y, 0, final_y);
    }

    bool isFinished() const override {
        return verticalOscillation.isFinished();
    }

    void update() override {
        verticalOscillation.update();
    }
};

#endif //BRE_TRANSITION_VERTICALOSCILLATION_HPP
