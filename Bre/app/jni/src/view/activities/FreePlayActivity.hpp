//
// Created by jonat on 25/09/2024.
//

#ifndef BRE_GAME_ACTIVITY_HPP
#define BRE_GAME_ACTIVITY_HPP

#include <SDL3/SDL.h>

#include "../../model/entities/TouchInput.hpp"
#include "../../model/worlds/FreePlayWorld.hpp"
#include "../../controller/systems/InGameInputSystem.hpp"
#include "../../view/renderers/LevelBackgroundRenderer.hpp"
#include "../../view/renderers/PlayerRenderer.hpp"
#include "../../view/renderers/JoystickRenderer.hpp"
#include "../../view/renderers/ClonesRenderer.hpp"
#include "../Mediator.hpp"

class FreePlayActivity {

    bool playing = false;
    bool developer_mode = false;
    FreePlayWorld freePlayWorld;

    InGameInputSystem inGameInputSystem;

    const SDL_DisplayMode* screen;
    SDL_Window* freePlayWindow = nullptr;
    SDL_Renderer* freePlayRenderer = nullptr;

    //  Renderers
    LevelBackgroundRenderer levelBackgroundRenderer;
    PlayerRenderer playerRenderer;
    JoystickRenderer joystickRenderer;
    ClonesRenderer clonesRenderer;


public:
    FreePlayActivity(const SDL_DisplayMode* screen) : screen(screen) {
        freePlayWindow = SDL_CreateWindow("Game", screen->w, screen->h, SDL_WINDOW_VULKAN | SDL_WINDOW_FULLSCREEN);
        if (freePlayWindow == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create window: %s\n", SDL_GetError());
            //TODO: Get back to main menu
        }
        freePlayRenderer = SDL_CreateRenderer(freePlayWindow, NULL);
        if (freePlayRenderer == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create renderer: %s\n", SDL_GetError());
            //TODO: Get back to main menu
        }

        levelBackgroundRenderer = LevelBackgroundRenderer(freePlayRenderer);
        playerRenderer = PlayerRenderer(freePlayRenderer);
        joystickRenderer = JoystickRenderer(freePlayRenderer);
        clonesRenderer = ClonesRenderer(freePlayRenderer);
    }

    void run() {
        playing = true;
        freePlayWorld.enter(screen->w, screen->h);

        while (playing) {
            SDL_Event e;
            if(SDL_PollEvent(&e)) {
                SDL_Log("Event type: %d", e.type);

                TouchInput* touchInput = Mediator::SDL_GetTouchInput(e, screen->w, screen->h);

                //Handle render
                switch(touchInput->type) {
                    case TouchInputType::SCREEN_TOUCH:
                        if(touchInput->fingerID==1)
                            joystickRenderer.buildCenter(touchInput->x, touchInput->y);
                        break;
                    case TouchInputType::SCREEN_SCROLL:
                        if(touchInput->fingerID==1)
                            joystickRenderer.buildEntireArrow(touchInput->x, touchInput->y);
                        break;
                    case TouchInputType::SCREEN_RELEASE:
                        if(touchInput->fingerID==1)
                            joystickRenderer.stop();
                        break;
                }

                //Handle logic
                inGameInputSystem.handleInput(touchInput);

                if(e.type == SDL_EVENT_QUIT)
                    playing = false;
            }

            freePlayWorld.update();

            SDL_RenderClear(freePlayRenderer);
            levelBackgroundRenderer.render();
            playerRenderer.render();
            joystickRenderer.render();
            clonesRenderer.render();
            SDL_RenderPresent(freePlayRenderer);

        }
    }

    void exit() {
        playing = false;
        levelBackgroundRenderer.destroy();
        playerRenderer.destroy();
        joystickRenderer.destroy();
        clonesRenderer.destroy();
        freePlayWorld.exit();
        SDL_DestroyRenderer(freePlayRenderer);
        SDL_DestroyWindow(freePlayWindow);
    }

};

#endif //BRE_GAME_ACTIVITY_HPP