//
// Created by Jonathan on 30/10/2024.
//

#ifndef BRE_GAMEWORLD_HPP
#define BRE_GAMEWORLD_HPP

#include "World.hpp"
#include "../../controller/systems/MovementSystem.hpp"
#include "../../controller/systems/CollisionSystem.hpp"
#include "../../controller/systems/InGameInputSystem.hpp"
#include "../../model/entities/Game.hpp"
#include "../../model/entities/Player.hpp"
#include "../../model/entities/Arrow.hpp"

/**
 * Base class for all Worlds in which the game is played.
 */
class GameWorld : virtual public World {

protected:
    // Entities used in all GameWorlds
    static Game* game;
    static Player* player;
    static Arrow* joystick;

    // Systems used in all GameWorlds
    MovementSystem movementSystem;
    InGameInputSystem inGameInputSystem;

public:
    virtual void enter(unsigned int screen_w, unsigned int screen_h) override {
        World::enter(screen_w, screen_h);
        game = new Game();
        player = Player::getInstance(screen_w, screen_h);
    }

    void handleInput(TouchInput* touchInput) override {
        inGameInputSystem.handleInput(touchInput);
    }

    virtual void update() override {
        movementSystem.movePlayer(player, joystick);
        CollisionSystem::updatePlayerMapMarginsCollisions(player, screenSize, game);
    }

    virtual void reset() {
        player->reset();
        inGameInputSystem.reset();
        game->reset();
    }

    virtual void exit() override {
        delete screenSize; screenSize = nullptr;
        delete game; game = nullptr;
        delete player; player = nullptr;
        delete joystick; joystick = nullptr;
    }

    static Player* getPlayer() {
        return player;
    }

    static Game* getGame() {
        return game;
    }

    static Arrow* getJoystick() {
        return joystick;
    }

    static void setJoystick(Arrow* new_joystick) {
        joystick = new_joystick;
    }

    static void destroyJoystick() {
        delete joystick;
        joystick = nullptr;
    }
};

#endif //BRE_GAMEWORLD_HPP
