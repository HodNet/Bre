//
// Created by Jonathan on 23/10/2024.
//

#ifndef BRE_GAME_HPP
#define BRE_GAME_HPP

#include "../../controller/components/StopWatch.hpp"
#include "../../model/states/GameState.hpp"

class Game {

private:
    StopWatch timer;
    GameState state;

public:
    Game() : timer(TimeUnit::MILLISECONDS), state(GameState::NOT_STARTED) {}

    void start() {
        timer.start();
        state = GameState::PLAYING;
    }

    void pause() {
        timer.stop();
        state = GameState::PAUSED;
    }

    void resume() {
        timer.resume();
        state = GameState::PLAYING;
    }

    void over() {
        timer.stop();
        state = GameState::GAME_OVER;
    }

    void reset() {
        timer.reset();
        state = GameState::NOT_STARTED;
    }

    StopWatch getTimer() const {
        return timer;
    }

    GameState getState() const {
        return state;
    }
};

#endif //BRE_GAME_HPP
