//
// Created by jonat on 25/09/2024.
//

#ifndef BRE_GAME_ACTIVITY_HPP
#define BRE_GAME_ACTIVITY_HPP

#include <SDL3/SDL.h>

#include "../../model/worlds/FreePlayWorld.hpp"
#include "../renderers/LevelBackgroundRenderer.hpp"
#include "../renderers/PlayerRenderer.hpp"
#include "../renderers/JoystickRenderer.hpp"

class FreePlayActivity {

    bool playing = false;
    bool developer_mode = false;
    FreePlayWorld world;

    const SDL_DisplayMode* screen;
    SDL_Window* gameWindow = nullptr;
    SDL_Renderer* gameRenderer = nullptr;

    //  Renderers
    LevelBackgroundRenderer levelBackgroundRenderer;
    PlayerRenderer playerRenderer;
    JoystickRenderer joystickRenderer;


public:
    FreePlayActivity(const SDL_DisplayMode* screen) : screen(screen) {
        gameWindow = SDL_CreateWindow("Game", screen->w, screen->h, SDL_WINDOW_VULKAN | SDL_WINDOW_FULLSCREEN);
        if (gameWindow == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create window: %s\n", SDL_GetError());
            //TODO: Get back to main menu
        }
        gameRenderer = SDL_CreateRenderer(gameWindow, NULL);
        if (gameRenderer == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create renderer: %s\n", SDL_GetError());
            //TODO: Get back to main menu
        }

        levelBackgroundRenderer = LevelBackgroundRenderer(gameRenderer);
        playerRenderer = PlayerRenderer(gameRenderer);
        joystickRenderer = JoystickRenderer(gameRenderer);
    }

    void run() {
        playing = true;
        world.enter(screen->w, screen->h);

        while (playing) {
            SDL_Event e;
            if(SDL_PollEvent(&e)) {
                SDL_Log("Event type: %d", e.type);
                switch(e.type) {
                    case SDL_EVENT_FINGER_DOWN:
                        if(e.tfinger.fingerID==1)
                            joystickRenderer.buildCenter(e.tfinger.x, e.tfinger.y);
                        break;
                    case SDL_EVENT_FINGER_MOTION:
                        if(e.tfinger.fingerID==1)
                            joystickRenderer.buildEntireArrow(e.tfinger.x, e.tfinger.y);
                        break;
                    case SDL_EVENT_FINGER_UP:
                        if(e.tfinger.fingerID==1)
                            joystickRenderer.stop();
                        break;
                }
            }

            SDL_RenderClear(gameRenderer);
            levelBackgroundRenderer.render();
            playerRenderer.render();
            joystickRenderer.render();
            SDL_RenderPresent(gameRenderer);

        }
    }

    void exit() {
        playing = false;
        levelBackgroundRenderer.destroy();
        playerRenderer.destroy();
        joystickRenderer.destroy();
        world.exit();
        SDL_DestroyRenderer(gameRenderer);
        SDL_DestroyWindow(gameWindow);
    }

};

#endif //BRE_GAME_ACTIVITY_HPP