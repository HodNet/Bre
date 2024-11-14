//
// Created by Jonathan on 12/11/2024.
//

#ifndef BRE_TRANSITIONFROMBELOW_HPP
#define BRE_TRANSITIONFROMBELOW_HPP

#include <cmath>

#include "../../controller/components/Transition.hpp"

/**
 * The rectangle will come from below and stop at the final point oscillating around it through a damped harmonic motion
 */
class TransitionFromBelow : public Transition {

private:
    constexpr static float γ = 4.2f; // damping factor
    constexpr static float ω = 8.f; // frequency

public:
    TransitionFromBelow() = default;
    TransitionFromBelow(const TransitionFromBelow& t) = default;

    TransitionFromBelow(Rectangle rect, const float velocity, const float final_y) :
        Transition(rect, velocity, Point2D(rect.x, final_y)) {}

    bool isFinished() const override {
        return v<0.0000000001f && Transition::isFinished();
    }

    void update() override {
        if (isFinished()) return;
        SDL_Log("TransitionFromBelow::update()");

        float dt = frameTimer.now()/1000000.0;
        float y0 = rect.y - final_position.y;
        float v0 = v;

        float ϕ = atan( (-v0 - γ*y0)/(ω * y0) );
        float A = y0/cos(ϕ);

        rect.y = final_position.y + A * exp(-γ*dt) * cos(ω * dt + ϕ);
        v = - γ*A*exp(-γ*dt)*cos(ω*dt + ϕ) - ω*A*exp(-γ*dt)*sin(ω*dt + ϕ);

        frameTimer.start();
    }
};

#endif //BRE_TRANSITIONFROMBELOW_HPP
