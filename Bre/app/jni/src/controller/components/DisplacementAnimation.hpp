//
// Created by Jonathan on 14/11/2024.
//

#ifndef BRE_DISPLACEMENTANIMATION_HPP
#define BRE_DISPLACEMENTANIMATION_HPP

#include "../../controller/components/StopWatch.hpp"
#include "../../controller/components/Animation.hpp"

class DisplacementAnimation : virtual public Animation {

private:
    enum class Direction {
        FORWARD,
        BACKWARD,
    };

    float* x = nullptr;
    const float v = 20000; // pixels per second
    const float final_x = 0;
    StopWatch frameTimer{TimeUnit::MICROSECONDS};
    Direction direction;

public:
    DisplacementAnimation() = default;
    DisplacementAnimation(const DisplacementAnimation& d) = default;

    /**
     * @param x the variable to displace
     * @param final_x the final position of the displacement on the x axis
     * @param v the velocity of the displacement in pixels per second
     */
    DisplacementAnimation(float &x, const float final_x, const float v=20000) : x(&x), v(v), final_x(final_x) {
        if (final_x < x)
            direction = Direction::BACKWARD;
        else
            direction = Direction::FORWARD;
    }

    bool isFinished() const override {
        switch (direction) {
            case Direction::FORWARD:
                return *x >= final_x;
            case Direction::BACKWARD:
                return *x <= final_x;
        }
    }

    /**
     *  Update the position of the object. Should be called in every frame of the
     *  animation, until isFinished() returns true
     */
    void update() override {
        if (isFinished()) return;

        float dt = frameTimer.now()/1000000.0;
        float x0 = *x;
        *x = x0 + v*dt;

        frameTimer.start();
    }
};

#endif //BRE_DISPLACEMENTANIMATION_HPP
