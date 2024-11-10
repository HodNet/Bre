//
// Created by Jonathan on 09/10/2024.
//

#ifndef BRE_COORDINATESMEDIATOR_HPP
#define BRE_COORDINATESMEDIATOR_HPP

#include <SDL3/SDL.h>

class CoordinatesMediator {
public:
    static void SDL_ConvertCoordinatesForVerticalOrientation(float &x, float &y, int screen_height) {
        if(y<0 || y>screen_height)
            return;

        y = screen_height - y;
    }

    static void SDL_ConvertCoordinatesForRendering(SDL_FRect &rect, float screen_height) {
        if(rect.y<0 || rect.y>screen_height)
            return;

        rect.y = screen_height - rect.y - rect.h;
    }

    static void SDL_ConvertAngleForRendering(double &angle) {
        angle = 360 - angle;
    }
};

#endif //BRE_COORDINATESMEDIATOR_HPP
