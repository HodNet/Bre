//
// Created by jonat on 25/09/2024.
//

#ifndef BRE_GAME_ACTIVITY_HPP
#define BRE_GAME_ACTIVITY_HPP

#include <stdexcept>
#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "../controllers/GameController.hpp"

class GameActivity {

    bool playing = true;
    GameController* gameController = NULL;

    const SDL_DisplayMode* screen;
    SDL_Window* gameWindow = NULL;
    SDL_Renderer* gameRenderer = NULL;

public:
    GameActivity(const SDL_DisplayMode* screen) {
        this->screen = screen;
        this->gameController = new GameController();
        this->gameWindow = SDL_CreateWindow("Game", screen->w, screen->h, SDL_WINDOW_FULLSCREEN);
        if (gameWindow == NULL) {
            SDL_Log("Could not create window: %s\n", SDL_GetError());
        }
        this->gameRenderer = SDL_CreateRenderer(gameWindow, NULL);
        if (gameRenderer == NULL) {
            SDL_Log("Could not create renderer: %s\n", SDL_GetError());
        }
    }

    void run() {
        while (playing) {

        }
    }

};

#endif //BRE_GAME_ACTIVITY_HPP