//
// Created by Jonathan on 01/10/2024.
//

#ifndef BRE_WORLD_HPP
#define BRE_WORLD_HPP

#include "../../controller/components/Rectangle.hpp"
#include "controller/components/StopWatch.hpp"

/**
 * This classes are static containers of all the entities in the world of a game.
 *
 * For example, a world could be the level 1 of a game, or the free play mode.
 * The world should be the ONLY responsible for the creation and destruction of all the entities in it.
 * All the entities should be static, so they can be accessed from anywhere in the code.
 * All the entities should be private and accessible with getters and setters.
 *
 */
class World{
protected:
    //Entities contained in all Worlds
    static const Rectangle* screenSize;
    static Player* player;
    static StopWatch* gameTimer;
    static Arrow* joystick;
    static StopWatch* frameTimer;

public:
    /**
     * Should be called when the player just entered the world.
     * This function should set the screen size and initialize all the entities in the world.
     */
    virtual void enter(unsigned int screen_w, unsigned int screen_h) = 0;

    /**
     * Should be called every frame.
     * This function should update all the entities in the world.
     */
    virtual void update() = 0;

    /**
     * Should be called when the player is leaving the world.
     * This function should destroy all the entities in the world.
     */
    virtual void exit() = 0;

    static void setScreenSize(unsigned int w, unsigned int h) {
        screenSize = new Rectangle(0, 0, w, h);
    }

    static const Rectangle* getScreenSize() {
        return screenSize;
    }

    static Player* getPlayer() {
        return player;
    }

    static StopWatch* getGameTimer() {
        return gameTimer;
    }

    static Arrow* getJoystick() {
        return joystick;
    }

    static StopWatch* getFrameTimer() {
        return frameTimer;
    }

    static void setJoystick(Arrow* new_joystick) {
        joystick = new_joystick;
    }

    static void destroyJoystick() {
        delete joystick;
        joystick = nullptr;
    }
};

#endif //BRE_WORLD_HPP
