//
// Created by Jonathan on 11/10/2024.
//

#ifndef BRE_INGAMEINPUTSYSTEM_HPP
#define BRE_INGAMEINPUTSYSTEM_HPP

#include "../../controller/components/TouchInput.hpp"
#include "../../controller/systems/InGameEventSystem.hpp"

class InGameInputSystem {
    bool gameStarted = false;

public:
    InGameInputSystem() = default;

    void handleInput(TouchInput* touchInput) {
        if (touchInput == nullptr)
            return;

        // Handle behavior of the first finger
        if (touchInput->fingerID == 1) {
            SDL_Log("input type: %d", touchInput->type);
            switch (touchInput->type) {
                case TouchInputType::SCREEN_SCROLL:
                    InGameEventSystem::handleEvent(InGameEvent::START_PLAYER_MOVEMENT);
                    if (!gameStarted) {
                        InGameEventSystem::handleEvent(InGameEvent::START_GAME);
                        gameStarted = true;
                    }
                    break;
                case TouchInputType::SCREEN_TAP:
                    InGameEventSystem::handleEvent(InGameEvent::STOP_PLAYER_MOVEMENT);
                    break;
            }
        }
    }

    void reset() {
        gameStarted = false;
    }
};

#endif //BRE_INGAMEINPUTSYSTEM_HPP
