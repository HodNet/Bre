//
// Created by Jonathan on 11/10/2024.
//

#ifndef BRE_INGAMEINPUTSYSTEM_HPP
#define BRE_INGAMEINPUTSYSTEM_HPP

#include "../../model/entities/TouchInput.hpp"
#include "InGameEventsSystem.hpp"

class InGameInputSystem {
    bool gameStarted = false;

public:
    InGameInputSystem() = default;

    void handleInput(TouchInput* touchInput) {
        if (touchInput == nullptr)
            return;

        // Handle behavior of the first finger
        if (touchInput->fingerID == 1) {
            switch (touchInput->type) {
                case TouchInputType::SCREEN_SCROLL:
                    InGameEventsSystem::handleEvent(InGameEvent::START_PLAYER_MOVEMENT);
                    if (!gameStarted) {
                        InGameEventsSystem::handleEvent(InGameEvent::START_GAME);
                        gameStarted = true;
                    }
                    break;
                case TouchInputType::SCREEN_TAP:
                    InGameEventsSystem::handleEvent(InGameEvent::STOP_PLAYER_MOVEMENT);
                    break;
            }
        }

        delete touchInput;
    }
};

#endif //BRE_INGAMEINPUTSYSTEM_HPP
