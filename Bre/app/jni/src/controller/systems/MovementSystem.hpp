//
// Created by Jonathan on 11/10/2024.
//

#ifndef BRE_MOVEMENTSYSTEM_HPP
#define BRE_MOVEMENTSYSTEM_HPP

#include "../../model/states/PlayerState.hpp"
#include "../../model/worlds/World.hpp"
#include "../components/StopWatch.hpp"

class MovementSystem {

public:
    static void movePlayer(Player* player, Arrow* joystick, StopWatch* frameTimer) {
        if(player->getState() == PlayerState::MOVING) {
            float x0 = player->getRect().x;
            float y0 = player->getRect().y;
            float v = player->getSpeed();
            double dt = frameTimer->now()/1000000.0;
            float cos = joystick->getDirection().x;
            float sin = joystick->getDirection().y;

            player->setPosition(x0 + v * cos * dt, y0 + v * sin * dt);
        }
    }

    static void stopPlayer() {
        // Stop player
    }

};

#endif //BRE_MOVEMENTSYSTEM_HPP
