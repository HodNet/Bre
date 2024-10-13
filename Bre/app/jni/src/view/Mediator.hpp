//
// Created by Jonathan on 09/10/2024.
//

#ifndef BRE_MEDIATOR_HPP
#define BRE_MEDIATOR_HPP

#include <SDL3/SDL.h>
#include "../model/entities/TouchInput.hpp"

class Mediator {
public:
    static void SDL_ConvertCoordinatesForVerticalOrientation(int &x, int &y, int screen_height) {
        if(y<0 || y>screen_height)
            return;

        y = screen_height - y;
    }

    static void SDL_ConvertCoordinatesForRendering(SDL_FRect &rect, int screen_height) {
        if(rect.y<0 || rect.y>screen_height)
            return;

        rect.y = screen_height - rect.y;
    }

    static void SDL_ConvertAngleForRendering(double &angle) {
        angle = 360 - angle;
    }

    static TouchInput* SDL_GetTouchInput(const SDL_Event &sdl_event, int screen_width, int screen_height) {
        TouchInput* touchInput = new TouchInput();

        switch (sdl_event.type) {
            case SDL_EVENT_FINGER_DOWN:
                touchInput->type = TouchInputType::SCREEN_TOUCH;
                break;
            case SDL_EVENT_FINGER_UP:
                touchInput->type = TouchInputType::SCREEN_RELEASE;
                break;
            case SDL_EVENT_FINGER_MOTION:
                touchInput->type = TouchInputType::SCREEN_SCROLL;
                break;
        }

        touchInput->fingerID = sdl_event.tfinger.fingerID;

        int x = sdl_event.tfinger.x * screen_width;
        int y = sdl_event.tfinger.y * screen_height;
        SDL_ConvertCoordinatesForVerticalOrientation(x, y, screen_height);
        touchInput->x = x;
        touchInput->y = y;

        return touchInput;
    }
};

#endif //BRE_MEDIATOR_HPP
