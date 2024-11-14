//
// Created by Jonathan on 12/11/2024.
//

#ifndef BRE_TRANSITION_HPP
#define BRE_TRANSITION_HPP

#include "../../controller/components/Rectangle.hpp"
#include "../../controller/components/StopWatch.hpp"

class Transition {

protected:
    Rectangle rect;
    float v = 0; // velocity
    const Point2D final_position;

    StopWatch frameTimer{TimeUnit::MICROSECONDS};

public:
    Transition() = default;
    Transition(const Transition& t) = default;
    Transition(Rectangle rect, const float velocity, const Point2D& final_position) :
        rect(rect), v(velocity), final_position(final_position) {}

    Transition(Rectangle rect, const float velocity, const int final_x, const int final_y) :
        rect(rect), v(velocity), final_position(final_x, final_y) {}

    /**
     *  Update the animation. Should be called in every frame of the animation
     */
    virtual void update() = 0;

    /**
     *  Check if the animation is finished
     */
     virtual bool isFinished() const {
         Point2D current_position(rect.x, rect.y);
         return  current_position.distance(final_position) < 1.0f;
     }

     float getX() const {
         return rect.x;
     }

     float getY() const {
         return rect.y;
     }

     float getW() const {
         return rect.w;
     }

     float getH() const {
         return rect.h;
     }
};

#endif //BRE_TRANSITION_HPP
