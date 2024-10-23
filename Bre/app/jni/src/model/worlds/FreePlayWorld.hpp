//
// Created by Jonathan on 01/10/2024.
//

#ifndef BRE_FREEPLAYWORLD_HPP
#define BRE_FREEPLAYWORLD_HPP

#include <map>

#include "World.hpp"
#include "../../model/entities/Player.hpp"
#include "../../model/entities/Arrow.hpp"
#include "../../controller/components/StopWatch.hpp"
#include "../../controller/systems/MovementSystem.hpp"
#include "../../controller/systems/ClonesSystem.hpp"

class FreePlayWorld : virtual public World {

private:
    //Entities
    static std::map<int, Clone>* clones;

    //Systems
    ClonesSystem clonesSystem;

public:
    void enter(unsigned int screen_w, unsigned int screen_h) override {
        setScreenSize(screen_w, screen_h);
        game = new Game();
        player = Player::getInstance(screen_w, screen_h);
        clones = new std::map<int, Clone>();
    }

    void update() override {
        movementSystem.movePlayer(player, joystick);
        clonesSystem.updatePlayerPath(player, game);
        clonesSystem.addCloneEveryThreeSeconds(clones, game, screenSize);
        clonesSystem.moveAllClones(clones);
    }

    void exit() override {
        delete screenSize; screenSize = nullptr;
        delete player; player = nullptr;
        delete game; game = nullptr;
        delete joystick; joystick = nullptr;
        delete clones; clones = nullptr;
    }

    static std::map<int, Clone>* getClones() {
        return clones;
    }
};

#endif //BRE_FREEPLAYWORLD_HPP
