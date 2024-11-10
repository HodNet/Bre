//
// Created by Jonathan on 30/10/2024.
//

#ifndef BRE_GAMEWORLD_HPP
#define BRE_GAMEWORLD_HPP

#include "World.hpp"
#include "../../res/images.hpp"
#include "../../res/dimens.hpp"
#include "../../controller/systems/MovementSystem.hpp"
#include "../../controller/systems/CollisionSystem.hpp"
#include "../../controller/systems/InGameInputSystem.hpp"
#include "../../model/entities/Game.hpp"
#include "../../model/entities/Player.hpp"
#include "../../model/entities/Arrow.hpp"
#include "../../controller/components/IconButton.hpp"

/**
 * Base class for all Worlds in which the game is played.
 */
class GameWorld : virtual public World {

protected:
    // Entities used in all GameWorlds
    static Game* game;
    static Player* player;
    static Arrow* joystick;

    // Buttons used in all GameWorlds
    static IconButton* pauseButton;

    // Systems used in all GameWorlds
    MovementSystem movementSystem;
    InGameInputSystem inGameInputSystem;

public:
    virtual void enter(unsigned int screen_w, unsigned int screen_h) override {
        World::enter(screen_w, screen_h);
        game = new Game();
        player = Player::getInstance(screen_w, screen_h);
        pauseButton = new IconButton(
                screen_w - dimens::horizontal_margin - dimens::icon_button_size,
                screen_h - dimens::vertical_margin - dimens::icon_button_size - dimens::navigation_bar_height,
                dimens::icon_button_size,
                dimens::icon_button_size,
                images::pause_button,
                dimens::pause_button_file_width,
                dimens::pause_button_file_height);
    }

    void handleInput(TouchInput* touchInput) override {
        inGameInputSystem.handleInput(touchInput);
        pauseButton->handleInput(touchInput);
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
        delete pauseButton; pauseButton = nullptr;
        inGameInputSystem.reset();
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

    static IconButton* getPauseButton() {
        return pauseButton;
    }
};

#endif //BRE_GAMEWORLD_HPP
