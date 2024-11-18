//
// Created by Jonathan on 14/11/2024.
//

#ifndef BRE_OSCILLATIONANIMATION_HPP
#define BRE_OSCILLATIONANIMATION_HPP

#include <cmath>

#include "../../controller/components/StopWatch.hpp"
#include "../../controller/components/Animation.hpp"

class OscillationAnimation : virtual public Animation {

private:
    constexpr static float γ = 4.2f; // damping factor
    constexpr static float ω = 8.0f; // frequency
    float* x = nullptr;
    float v = 0;
    float center = 0;
    StopWatch frameTimer{TimeUnit::MICROSECONDS};

public:
    OscillationAnimation() = default;
    OscillationAnimation(const OscillationAnimation& o) = default;
    OscillationAnimation& operator=(const OscillationAnimation& o) = default;

    /**
     * @param x the variable to oscillate
     * @param initial_velocity the initial velocity of the oscillation
     * @param center_of_oscillation_on_x_axis the center of the oscillation on the x axis
     */
    OscillationAnimation(float &x, const float initial_velocity, const float center_of_oscillation_on_x_axis) :
        x(&x), v(initial_velocity), center(center_of_oscillation_on_x_axis) {}


    bool isFinished() const override {
        return abs(v) < 0.001f  &&  abs((*x)-center) < 0.001f;
    }

    /**
     *  Update the position and velocity of the object. Should be called in every frame of the
     *  animation, until isFinished() returns true
     */
    void update() override {
        if (isFinished()) return;

        float dt = frameTimer.now()/1000000.0;
        float x0 = (*x) - center;
        float v0 = v;

        float ϕ = atan( (-v0 - γ*x0)/(ω * x0) );
        float A = x0/cos(ϕ);

        *x = center + A * exp(-γ*dt) * cos(ω * dt + ϕ);
        v = - γ*A*exp(-γ*dt)*cos(ω*dt + ϕ) - ω*A*exp(-γ*dt)*sin(ω*dt + ϕ);

        frameTimer.start();
    }
};

#endif //BRE_OSCILLATIONANIMATION_HPP
