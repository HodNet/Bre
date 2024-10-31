//
// Created by Jonathan on 31/10/2024.
// This cpp is necessary to avoid cyclic dependencies between InGameInputSystem, InGameEventSystem and GameWorld.
//

#include "../../model/worlds/GameWorld.hpp"

void InGameEventSystem::handleEvent(InGameEvent event) {
    switch (event) {
        case InGameEvent::START_GAME:
            GameWorld::getGame()->start();
            break;
        case InGameEvent::START_PLAYER_MOVEMENT:
            GameWorld::getPlayer()->setState(PlayerState::MOVING);
            break;
        case InGameEvent::STOP_PLAYER_MOVEMENT:
            GameWorld::getPlayer()->setState(PlayerState::IDLE);
            break;
    }
}
