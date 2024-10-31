//
// Created by Jonathan on 28/10/2024.
//

#ifndef BRE_INPUTMEDIATOR_HPP
#define BRE_INPUTMEDIATOR_HPP

#include "../../model/entities/TouchInput.hpp"
#include "../../view/mediators/CoordinatesMediator.hpp"

class InputMediator {
    SDL_Event previousEvent_1; // previous input from finger with ID 1
    SDL_Event previousPreviousEvent_1; // previous input from previous input from finger with ID 1
    SDL_Event previousPreviousPreviousEvent_1; // previous input from previous input from previous input from finger with ID 1

public:
    InputMediator() = default;

    TouchInput* SDL_GetTouchInput(const SDL_Event &sdl_event, int screen_width, int screen_height) {
        TouchInput* touchInput = new TouchInput();

        // Getting input from the first finger
        if (sdl_event.tfinger.fingerID == 1) {

            // Defining a tap event
            if ((previousPreviousEvent_1.type == SDL_EVENT_FINGER_DOWN &&
                previousEvent_1.type == SDL_EVENT_FINGER_MOTION &&
                sdl_event.type == SDL_EVENT_FINGER_UP)
                ||
                (previousPreviousPreviousEvent_1.type == SDL_EVENT_FINGER_DOWN &&
                previousPreviousEvent_1.type == SDL_EVENT_FINGER_MOTION &&
                previousEvent_1.type == SDL_EVENT_FINGER_MOTION &&
                sdl_event.type == SDL_EVENT_FINGER_UP)
                ) {
                    touchInput->type = TouchInputType::SCREEN_TAP;
                    goto finish_the_input;
            }

            // Defining a scroll event
            if (previousPreviousEvent_1.type == SDL_EVENT_FINGER_MOTION &&
                previousEvent_1.type == SDL_EVENT_FINGER_MOTION &&
                sdl_event.type == SDL_EVENT_FINGER_MOTION) {
                touchInput->type = TouchInputType::SCREEN_SCROLL;
                goto finish_the_input;
            }

            switch (sdl_event.type) {
                case SDL_EVENT_FINGER_DOWN:
                    touchInput->type = TouchInputType::SCREEN_TOUCH;
                    break;
                case SDL_EVENT_FINGER_UP:
                    touchInput->type = TouchInputType::SCREEN_RELEASE;
                    break;
                default:
                    touchInput->type = TouchInputType::NONE;
                    break;
            }
        }
        finish_the_input:

        if (sdl_event.type == SDL_EVENT_FINGER_DOWN || sdl_event.type == SDL_EVENT_FINGER_UP || sdl_event.type == SDL_EVENT_FINGER_MOTION) {
            touchInput->fingerID = sdl_event.tfinger.fingerID;
            float x = sdl_event.tfinger.x * screen_width;
            float y = sdl_event.tfinger.y * screen_height;
            CoordinatesMediator::SDL_ConvertCoordinatesForVerticalOrientation(x, y, screen_height);
            touchInput->x = x;
            touchInput->y = y;

            previousPreviousPreviousEvent_1 = previousPreviousEvent_1;
            previousPreviousEvent_1 = previousEvent_1;
            previousEvent_1 = sdl_event;
        }


        return touchInput;
    }
};

#endif //BRE_INPUTMEDIATOR_HPP
