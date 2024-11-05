//
// Created by jonat on 25/09/2024.
//

#ifndef BRE_GAME_ACTIVITY_HPP
#define BRE_GAME_ACTIVITY_HPP

#include <SDL3/SDL.h>

#include "../../model/entities/TouchInput.hpp"
#include "../../model/worlds/FreePlayWorld.hpp"
#include "../../view/renderers/LevelBackgroundRenderer.hpp"
#include "../../view/renderers/PlayerRenderer.hpp"
#include "../../view/renderers/JoystickRenderer.hpp"
#include "../../view/renderers/ClonesRenderer.hpp"
#include "../../view/renderers/ScoreRenderer.hpp"
#include "../../view/mediators/InputMediator.hpp"

class FreePlayActivity {

    bool playing = false;
    bool developer_mode = false;
    FreePlayWorld freePlayWorld;

    const SDL_DisplayMode* screen;
    SDL_Window* freePlayWindow = nullptr;
    SDL_Renderer* freePlayRenderer = nullptr;

    //  Renderers
    LevelBackgroundRenderer levelBackgroundRenderer;
    PlayerRenderer playerRenderer;
    JoystickRenderer joystickRenderer;
    ClonesRenderer clonesRenderer;
    ScoreRenderer scoreRenderer;

    // Mediators
    InputMediator inputMediator;


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
        scoreRenderer = ScoreRenderer(freePlayRenderer);
    }

    void run() {
        playing = true;
        freePlayWorld.enter(screen->w, screen->h);

        while (playing) {
            SDL_Event e;
            if(SDL_PollEvent(&e)) {
                SDL_Log("Event type: %d", e.type);

                if(e.type == SDL_EVENT_QUIT) {
                    playing = false;
                    break;
                }

                TouchInput* touchInput = inputMediator.SDL_GetTouchInput(e, screen->w, screen->h);

                //Handle rendering for first finger
                if(touchInput->fingerID==1) {
                    switch (touchInput->type) {
                        case TouchInputType::SCREEN_TOUCH:
                            joystickRenderer.buildCenter(touchInput->x, touchInput->y);
                            break;
                        case TouchInputType::SCREEN_SCROLL:
                            joystickRenderer.buildEntireArrow(touchInput->x, touchInput->y);
                            break;
                        case TouchInputType::SCREEN_RELEASE:
                            joystickRenderer.stop();
                            break;
                        case TouchInputType::SCREEN_TAP:
                            joystickRenderer.stop();
                            break;
                    }
                }

                //Handle logic
                freePlayWorld.handleInput(touchInput);
            }

            freePlayWorld.update();

            SDL_RenderClear(freePlayRenderer);
            levelBackgroundRenderer.render();
            playerRenderer.render();
            joystickRenderer.render();
            clonesRenderer.render();
            //scoreRenderer.render(); purtroppo crasha. Ritenterò con future versioni di SDL_TTF
            SDL_RenderPresent(freePlayRenderer);

        }
    }

    void exit() {
        playing = false;
        levelBackgroundRenderer.destroy();
        playerRenderer.destroy();
        joystickRenderer.destroy();
        clonesRenderer.destroy();
        scoreRenderer.destroy();
        freePlayWorld.exit();
        SDL_DestroyRenderer(freePlayRenderer);
        SDL_DestroyWindow(freePlayWindow);
    }

};

#endif //BRE_GAME_ACTIVITY_HPP