//
// Created by jonat on 25/09/2024.
//

#ifndef BRE_GAME_ACTIVITY_HPP
#define BRE_GAME_ACTIVITY_HPP

#include <SDL3/SDL.h>

#include "../../controller/components/TouchInput.hpp"
#include "../../model/worlds/FreePlayWorld.hpp"
#include "../../view/dialogs/PauseDialog.hpp"
#include "../../view/mediators/InputMediator.hpp"
#include "../../view/renderers/LevelBackgroundRenderer.hpp"
#include "../../view/renderers/PlayerRenderer.hpp"
#include "../../view/renderers/JoystickRenderer.hpp"
#include "../../view/renderers/ClonesRenderer.hpp"
#include "../../view/renderers/ScoreRenderer.hpp"
#include "../../view/renderers/IconButtonRenderer.hpp"

class FreePlayActivity {

    FreePlayWorld freePlayWorld;

    const SDL_DisplayMode* screen;
    SDL_Window* freePlayWindow = nullptr;
    SDL_Renderer* freePlayRenderer = nullptr;
    SDL_Texture* frameBuffer = nullptr; // It's a screenshot of all the contents rendered in a frame
    SDL_FRect screenRect = {0, 0, 0, 0};

    // Dialogs
    PauseDialog* pauseDialog = nullptr;

    // Mediators
    InputMediator inputMediator;

    //  Renderers
    LevelBackgroundRenderer levelBackgroundRenderer;
    PlayerRenderer playerRenderer;
    JoystickRenderer joystickRenderer;
    ClonesRenderer clonesRenderer;
    ScoreRenderer scoreRenderer;
    IconButtonRenderer pauseButtonRenderer;



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
        frameBuffer = SDL_CreateTexture(freePlayRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, screen->w, screen->h);
        if (frameBuffer == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create renderer buffer: %s\n", SDL_GetError());
            //TODO: Get back to main menu
        }
        screenRect = {0, 0, static_cast<float>(screen->w), static_cast<float>(screen->h)};

        freePlayWorld.enter(screen->w, screen->h);

        levelBackgroundRenderer = LevelBackgroundRenderer(freePlayRenderer);
        playerRenderer = PlayerRenderer(freePlayRenderer);
        joystickRenderer = JoystickRenderer(freePlayRenderer);
        clonesRenderer = ClonesRenderer(freePlayRenderer);
        scoreRenderer = ScoreRenderer(freePlayRenderer);
        pauseButtonRenderer = IconButtonRenderer(freePlayWorld.getPauseButton(), freePlayRenderer);
    }

    void run() {

        while (true) {
            if(freePlayWorld.isPaused()) {
                pauseDialog = new PauseDialog(freePlayRenderer, freePlayWorld, frameBuffer);
                pauseDialog->run();
                delete pauseDialog; pauseDialog = nullptr;
            }

            SDL_Event e;

            if(SDL_PollEvent(&e)) {
                SDL_Log("Event type: %d", e.type);

                if (e.type == SDL_EVENT_QUIT) {
                    exit();
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

                freePlayWorld.handleInput(touchInput);
            }

            freePlayWorld.update();

            SDL_SetRenderTarget(freePlayRenderer, frameBuffer);
            levelBackgroundRenderer.render();
            playerRenderer.render();
            joystickRenderer.render();
            clonesRenderer.render();
            //scoreRenderer.render(); purtroppo crasha. Ritenterò con future versioni di SDL_TTF
            SDL_SetRenderTarget(freePlayRenderer, NULL);

            SDL_RenderClear(freePlayRenderer);
            SDL_RenderTexture(freePlayRenderer, frameBuffer, 0, &screenRect);
            pauseButtonRenderer.render();
            SDL_RenderPresent(freePlayRenderer);
        }
    }

    void exit() {
        levelBackgroundRenderer.destroy();
        playerRenderer.destroy();
        joystickRenderer.destroy();
        clonesRenderer.destroy();
        scoreRenderer.destroy();
        pauseButtonRenderer.destroy();

        freePlayWorld.exit();
        SDL_DestroyTexture(frameBuffer);
        SDL_DestroyRenderer(freePlayRenderer);
        SDL_DestroyWindow(freePlayWindow);
        frameBuffer = nullptr;
        freePlayRenderer = nullptr;
        freePlayWindow = nullptr;
    }

};

#endif //BRE_GAME_ACTIVITY_HPP