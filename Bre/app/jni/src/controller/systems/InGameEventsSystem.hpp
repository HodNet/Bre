//
// Created by Jonathan on 11/10/2024.
//

#ifndef BRE_INPUTSYSTEM_HPP
#define BRE_INPUTSYSTEM_HPP

#include "../../model/worlds/World.hpp"
#include "../../model/states/PlayerState.hpp"
#include "MovementSystem.hpp"

enum class InGameEvent {
    START_PLAYER_MOVEMENT,
    STOP_PLAYER_MOVEMENT
};

class InGameEventsSystem {

public:
    static void handleEvent(InGameEvent event) {
        switch (event) {
            case InGameEvent::START_PLAYER_MOVEMENT:
                World::getPlayer()->setState(PlayerState::MOVING);
                break;
            case InGameEvent::STOP_PLAYER_MOVEMENT:
                World::getPlayer()->setState(PlayerState::IDLE);
                break;
        }
    }

};

#endif //BRE_INPUTSYSTEM_HPP
