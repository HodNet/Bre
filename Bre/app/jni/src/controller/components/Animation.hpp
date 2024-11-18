//
// Created by Jonathan on 12/11/2024.
//

#ifndef BRE_ANIMATION_HPP
#define BRE_ANIMATION_HPP

class Animation {

public:
    Animation() = default;

    /**
     *  Update the animation. Should be called in every frame of the animation
     */
    virtual void update() = 0;

    /**
     *  Check if the animation is finished
     */
     virtual bool isFinished() const = 0;

     virtual ~Animation() = default;
};

#endif //BRE_ANIMATION_HPP
