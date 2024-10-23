//
// Created by Jonathan on 11/10/2024.
//

#ifndef BRE_INGAMEINPUTSYSTEM_HPP
#define BRE_INGAMEINPUTSYSTEM_HPP

#include "../../model/entities/TouchInput.hpp"
#include "InGameEventsSystem.hpp"

class InGameInputSystem {
    TouchInput previousInput_1; // previous input from finger with ID 1
    bool gameStarted = false;

public:
    InGameInputSystem() = default;

    void handleInput(TouchInput* touchInput) {
        if(touchInput->fingerID == 1) {
            if(previousInput_1.type == TouchInputType::SCREEN_RELEASE)
                touchInput->type = TouchInputType::SCREEN_TAP;
        }

        switch (touchInput->type) {
            case TouchInputType::SCREEN_SCROLL:
                if(touchInput->fingerID == 1) {
                    InGameEventsSystem::handleEvent(InGameEvent::START_PLAYER_MOVEMENT);
                    if (!gameStarted) {
                        InGameEventsSystem::handleEvent(InGameEvent::START_GAME);
                        gameStarted = true;
                    }
                }
                break;
            case TouchInputType::SCREEN_TAP:
                if(touchInput->fingerID == 1)
                    InGameEventsSystem::handleEvent(InGameEvent::STOP_PLAYER_MOVEMENT);
                break;
        }
        if(touchInput->fingerID == 1)
            previousInput_1 = *touchInput;
        delete touchInput;
    }
};

#endif //BRE_INGAMEINPUTSYSTEM_HPP
