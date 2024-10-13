//
// Created by Jonathan on 11/10/2024.
//

#ifndef BRE_TOUCHINPUT_HPP
#define BRE_TOUCHINPUT_HPP

#include <SDL3/SDL.h>

#include "../../controller/components/TouchInputType.hpp"

struct TouchInput {
    TouchInputType type = TouchInputType::NONE;
    unsigned short int fingerID;
    int x;
    int y;

    TouchInput() = default;
};

#endif //BRE_TOUCHINPUT_HPP
