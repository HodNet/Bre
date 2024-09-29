//
// Created by jonat on 25/09/2024.
//

#ifndef BRE_GAME_ACTIVITY_HPP
#define BRE_GAME_ACTIVITY_HPP

#include <SDL3/SDL.h>

#include "../../controller/GameController.hpp"
#include "../renderers/LevelBackgroundRenderer.hpp"
#include "../renderers/PlayerRenderer.hpp"

class GameActivity {

    bool playing = false;
    GameController gameController;

    const SDL_DisplayMode* screen;
    SDL_Window* gameWindow = nullptr;
    SDL_Renderer* gameRenderer = nullptr;

    //  Renderers
    LevelBackgroundRenderer levelBackgroundRenderer;
    PlayerRenderer playerRenderer;


public:
    GameActivity(const SDL_DisplayMode* screen) : screen(screen) {
        gameController = GameController(screen->w, screen->h);

        gameWindow = SDL_CreateWindow("Game", screen->w, screen->h, SDL_WINDOW_VULKAN | SDL_WINDOW_FULLSCREEN);
        if (gameWindow == nullptr) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create window: %s\n", SDL_GetError());
        }
        gameRenderer = SDL_CreateRenderer(gameWindow, nullptr);
        if (gameRenderer == nullptr) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create renderer: %s\n", SDL_GetError());
        }

        levelBackgroundRenderer = LevelBackgroundRenderer(gameRenderer);
        playerRenderer = PlayerRenderer(gameRenderer);
    }

    void run() {
        playing = true;
        gameController.start();

        while (playing) {
            levelBackgroundRenderer.render();
            playerRenderer.render();
            SDL_RenderPresent(gameRenderer);
        }
    }

    void exit() {
        playing = false;
        gameController.exit();
        SDL_DestroyRenderer(gameRenderer);
        SDL_DestroyWindow(gameWindow);
    }

};

#endif //BRE_GAME_ACTIVITY_HPP