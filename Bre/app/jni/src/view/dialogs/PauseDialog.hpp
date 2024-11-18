//
// Created by Jonathan on 10/11/2024.
//

#ifndef BRE_PAUSEDIALOG_HPP
#define BRE_PAUSEDIALOG_HPP

#include <SDL3/SDL.h>

#include "../../res/dimens.hpp"
#include "../../res/colors.hpp"

#include "../../model/worlds/GameWorld.hpp"
#include "../../model/worlds/PauseMenuSubWorld.hpp"
#include "../../controller/components/Transition_VerticalOscillation.hpp"
#include "../../controller/components/TouchInput.hpp"
#include "../../view/mediators/CoordinatesMediator.hpp"
#include "../../view/mediators/InputMediator.hpp"
#include "../../view/renderers/BackgroundGradientAnimationRenderer.hpp"
#include "../../view/renderers/ImageRenderer.hpp"
#include "../../view/renderers/TextRenderer.hpp"
#include "../../view/renderers/IconButtonRenderer.hpp"

class PauseDialog {

private:
    PauseMenuSubWorld pauseMenuSubWorld;

    SDL_Renderer* renderer;
    SDL_Texture* backBuffer;
    SDL_FRect screen;

    InputMediator inputMediator;

    // Renderers
    BackgroundGradientAnimationRenderer backgroundGradientAnimationRenderer;
    TextRenderer titleRenderer;
    ImageRenderer backgroundRenderer;
    IconButtonRenderer resumeButtonRenderer;
    IconButtonRenderer restartButtonRenderer;
    IconButtonRenderer exitButtonRenderer;
    IconButtonRenderer cancelButtonRenderer;

public:
    PauseDialog(SDL_Renderer* renderer, GameWorld &gameWorld, SDL_Texture* backBuffer) :
    renderer(renderer), pauseMenuSubWorld(gameWorld),
    screen{0, 0, gameWorld.getScreenW(), gameWorld.getScreenH()},
    backBuffer(backBuffer) {

        pauseMenuSubWorld.enter(screen.w, screen.h);

        // Load Renderers
        backgroundGradientAnimationRenderer = BackgroundGradientAnimationRenderer(renderer);
        titleRenderer = TextRenderer(pauseMenuSubWorld.getTitle(), renderer);
        backgroundRenderer = ImageRenderer(pauseMenuSubWorld.getBackground(), renderer);
        resumeButtonRenderer = IconButtonRenderer(pauseMenuSubWorld.getResumeButton(), renderer);
        restartButtonRenderer = IconButtonRenderer(pauseMenuSubWorld.getRestartButton(), renderer);
        exitButtonRenderer = IconButtonRenderer(pauseMenuSubWorld.getExitButton(), renderer);
        cancelButtonRenderer = IconButtonRenderer(pauseMenuSubWorld.getCancelButton(), renderer);
    }

    void run() {

        while(true) {
            if(pauseMenuSubWorld.isExited()) {
                exit();
                break;
            }

            SDL_Event e;

            if (SDL_PollEvent(&e)) {
                if (e.type == SDL_EVENT_QUIT) {
                    exit();
                    break;
                }

                TouchInput* touchInput = inputMediator.SDL_GetTouchInput(e, screen.w, screen.h);
                pauseMenuSubWorld.handleInput(touchInput);
            }

            pauseMenuSubWorld.update();
            backgroundGradientAnimationRenderer.update();

            SDL_RenderClear(renderer);
            SDL_RenderTexture(renderer, backBuffer, 0, &screen);
            backgroundGradientAnimationRenderer.render();
            backgroundRenderer.render();
            titleRenderer.render();
            resumeButtonRenderer.render();
            restartButtonRenderer.render();
            exitButtonRenderer.render();
            cancelButtonRenderer.render();
            SDL_RenderPresent(renderer);
        }
    }

    void exit() {
        backgroundGradientAnimationRenderer.destroy();
        titleRenderer.destroy();
        backgroundRenderer.destroy();
        resumeButtonRenderer.destroy();
        restartButtonRenderer.destroy();
        exitButtonRenderer.destroy();
        cancelButtonRenderer.destroy();

        pauseMenuSubWorld.exit();
        renderer = nullptr;
        backBuffer = nullptr;
    }
};

#endif //BRE_PAUSEDIALOG_HPP
