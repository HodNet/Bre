//
// Created by Jonathan on 01/10/2024.
//

#ifndef BRE_FREEPLAYWORLD_HPP
#define BRE_FREEPLAYWORLD_HPP

#include <map>

#include "GameWorld.hpp"
#include "../../controller/systems/ClonesSystem.hpp"
#include "../../model/entities/Clone.hpp"
#include "../../model/entities/Score.hpp"

class FreePlayWorld : public GameWorld {

private:
    bool alreadyEntered = false;

    //Entities
    static std::map<int, Clone>* clones;
    static Score* currentScore;

    //Systems
    ClonesSystem clonesSystem;

public:
    void enter(unsigned int screen_w, unsigned int screen_h) override {
        if(!alreadyEntered) {
            GameWorld::enter(screen_w, screen_h);
            clones = new std::map<int, Clone>();
            currentScore = new Score();
            alreadyEntered = true;
        }
    }

    void update() override {
        GameWorld::update();
        clonesSystem.updatePlayerPath(player, game);
        clonesSystem.addCloneEveryTwoSeconds(clones, game, screenSize, currentScore);
        clonesSystem.moveAllClones(clones);
        CollisionSystem::updatePlayerCloneCollisions(player, clones, game);

        if(game->getState() == GameState::GAME_OVER) {
            reset();
        }
    }

    void reset() override {
        GameWorld::reset();
        clones->clear();
        currentScore->resetForGameOver();
        clonesSystem.reset();
    }

    void exit() override {
        GameWorld::exit();
        clones->clear();
        delete currentScore; currentScore = nullptr;
        delete clones; clones = nullptr;
        clonesSystem.reset();
    }

    static std::map<int, Clone>* getClones() {
        return clones;
    }

    static Score* getCurrentScore() {
        return currentScore;
    }
};

#endif //BRE_FREEPLAYWORLD_HPP
