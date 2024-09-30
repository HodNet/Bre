#ifndef BRE_PLAYER_HPP
#define BRE_PLAYER_HPP

#include "../../controller/components/Vector2D.hpp"
#include "../../controller/components/Rectangle.hpp"

/**
 * Singleton class representing the main player. There can only be one istance of the player at a time.
 */
class Player {
    Rectangle rect;
    const static int speed = 3;
    static Player* instance;

    Player(unsigned int screen_w, unsigned int screen_h) :
        rect(
                screen_w/2 - screen_w/20/2,
                screen_h/2 - screen_w/20/2,
                screen_w/20,
                screen_w/20
        ) {}

public:
    static Player* getInstance(unsigned int screen_w, unsigned int screen_h) {
        if (instance == nullptr) {
            instance = new Player(screen_w, screen_h);
        }
        return instance;
    }

    static Player* getInstance() {
        if (instance == nullptr) {
            throw std::runtime_error("NullPointerException: Player instance not initialized. Call getInstance(unsigned int, unsigned int) first.");
        }
        return instance;
    }

    Rectangle getRect() const {
        return rect;
    }

    ~Player() {
        delete instance;
    }
};

#endif //BRE_PLAYER_HPP