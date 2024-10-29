//
// Created by Jonathan on 11/10/2024.
//

#ifndef BRE_MOVEMENTSYSTEM_HPP
#define BRE_MOVEMENTSYSTEM_HPP

#include "../../controller/components/StopWatch.hpp"
#include "../../model/states/PlayerState.hpp"
#include "../../model/entities/Player.hpp"
#include "../../model/entities/Arrow.hpp"

class MovementSystem {
    StopWatch frameTimer{TimeUnit::MICROSECONDS};
    float cos = 0;
    float sin = 0;

public:
    MovementSystem() = default;

    void movePlayer(Player* player, Arrow* joystick) {
        if(player->getState() == PlayerState::MOVING) {
            float x0 = player->getRect().x;
            float y0 = player->getRect().y;
            float v = player->getSpeed();
            double dt = frameTimer.now()/1000000.0;

            if(joystick->getVector() != nullptr) {
                cos = joystick->getDirection().x;
                sin = joystick->getDirection().y;
            }

            player->setPosition(x0 + v * cos * dt, y0 + v * sin * dt);
        }

        frameTimer.start();
    }

};

#endif //BRE_MOVEMENTSYSTEM_HPP
