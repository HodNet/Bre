//
// Created by jonat on 25/09/2024.
//

#ifndef BRE_GAME_CONTROLLER_HPP
#define BRE_GAME_CONTROLLER_HPP

#include <vector>
#include "../model/entities/Player.hpp"
#include "utils/StopWatch.hpp"

class GameController {

    bool developer_mode = false;

    Rectangle screenSize;
    Player* player;
    StopWatch gameTimer = StopWatch(TimeUnit::MILLISECONDS);

    //TTF_Font *fontFPS;
    //stringstream ssFPS;

    //vector<percorso> prc;
    //vector<CLONE> clone;

public:
    GameController() = default;
    GameController(unsigned int screen_w, unsigned int screen_h) : screenSize(0, 0, screen_w, screen_h) {
        player = Player::getInstance(screen_w, screen_h);
    }

    void start() {
        gameTimer.start();
    }

    void exit() {
        delete player;
    }

};

#endif //BRE_GAME_CONTROLLER_HPP