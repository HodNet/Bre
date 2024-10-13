#ifndef BRE_PLAYER_HPP
#define BRE_PLAYER_HPP

#include "../../controller/components/Vector2D.hpp"
#include "../../controller/components/Rectangle.hpp"
#include "../states/PlayerState.hpp"

/**
 * Singleton class representing the main player. There can only be one instance of the player at a time.
 */
class Player {
    Rectangle rect;
    const float speed = 500.0f; // pixels per second
    PlayerState state;
    static Player* instance;

    Player(unsigned int screen_w, unsigned int screen_h) :
        rect(
                screen_w/2 - screen_w/20/2,
                screen_h/2 - screen_w/20/2,
                screen_w/20,
                screen_w/20
        ) {
        state = PlayerState::IDLE;
    }

public:
    static Player* getInstance(unsigned int screen_w, unsigned int screen_h) {
        if (instance == nullptr) {
            instance = new Player(screen_w, screen_h);
        }
        return instance;
    }

    Rectangle getRect() const {
        return rect;
    }

    PlayerState getState() const {
        return state;
    }

    const float getSpeed() const {
        return speed;
    }

    void setState(PlayerState state) {
        this->state = state;
    }

    void setPosition(float x, float y) {
        rect.setX(x);
        rect.setY(y);
    }

    ~Player() {
        delete instance;
    }
};

#endif //BRE_PLAYER_HPP