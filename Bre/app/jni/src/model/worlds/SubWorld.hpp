//
// Created by Jonathan on 15/11/2024.
//

#ifndef BRE_SUBWORLD_HPP
#define BRE_SUBWORLD_HPP

#include "World.hpp"

/**
 * Represents a sub-world, which is a part of a world.
 * A sub-world is a world that is not the main world, but a part of it.
 * For example, the pause menu is a sub-world of the game world.
 * The sub-world should be the ONLY responsible for the creation and destruction of all the entities in it.
 * It must NOT allocate or deallocate the entities of the main world.
 * For that, even if it inherits from World, it should not create the screenSize entity, because
 * it already exists (virtual inheritance), it would recreate it and cause a memory leak,
 * and it should not destroy it, because it would destroy the screenSize of the main world.
 * As for the World:
 * - All the entities should be static, so they can be accessed from anywhere in the code.
 * - All the entities should be private and accessible with getters and setters.
 */
class SubWorld : virtual public World {
public:
    /**
     * Should be called when the player just entered the sub-world.
     * This function should initialize all the entities in the sub-world.
     */
    virtual void enter(unsigned int screen_w, unsigned int screen_h) override = 0;

    /**
     * Should be called when the player is in the sub-world and has touched the screen.
     * This function should handle the input of the player.
     * WARNING: delete touchInput; should be called at the end of the function.
     * @param touchInput the input. delete it at the end of the function.
     */
    virtual void handleInput(TouchInput* touchInput) override = 0;

    /**
     * Should be called every frame.
     * This function should update all the entities in the sub-world.
     */
    virtual void update() override = 0;

    /**
     * Should be called when the player is leaving the sub-world.
     * This function should destroy all the entities in the sub-world.
     */
    virtual void exit() override = 0;
};

#endif //BRE_SUBWORLD_HPP
