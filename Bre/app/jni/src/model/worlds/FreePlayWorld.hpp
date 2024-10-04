//
// Created by Jonathan on 01/10/2024.
//

#ifndef BRE_FREEPLAYWORLD_HPP
#define BRE_FREEPLAYWORLD_HPP

#include "../entities/Player.hpp"
#include "../entities/Arrow.hpp"
#include "World.hpp"
#include "../../controller/utils/StopWatch.hpp"

class FreePlayWorld : virtual public World {

public:
    void enter(unsigned int screen_w, unsigned int screen_h) override {
        setScreenSize(screen_w, screen_h);
        player = Player::getInstance(screen_w, screen_h);
        gameTimer = new StopWatch(TimeUnit::MILLISECONDS);
        gameTimer->start();
    }

    void exit() override {
        delete player; player = nullptr;
        delete gameTimer; gameTimer = nullptr;
        delete joystick; joystick = nullptr;
    }
};

#endif //BRE_FREEPLAYWORLD_HPP
