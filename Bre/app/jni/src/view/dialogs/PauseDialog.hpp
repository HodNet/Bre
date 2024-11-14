//
// Created by Jonathan on 10/11/2024.
//

#ifndef BRE_PAUSEDIALOG_HPP
#define BRE_PAUSEDIALOG_HPP

#include <SDL3/SDL.h>

#include "../../res/dimens.hpp"
#include "../../res/colors.hpp"

#include "../../controller/components/TransitionFromBelow.hpp"
#include "../../view/mediators/CoordinatesMediator.hpp"

class PauseDialog {

private:
    const float screen_w = 0;
    const float screen_h = 0;
    const int bars_animation_speed = 2;
    const int pause_menu_animation_speed = 20;
    const float pause_menu_width = dimens::pause_menu_background_width;
    const float pause_menu_height = dimens::pause_menu_background_height;

    SDL_Renderer* renderer;
    SDL_Texture* backBuffer;
    SDL_Texture* pauseBarsAnimation;
    SDL_FRect screenRect;

    SDL_Texture* pauseMenuBackground;
    SDL_FRect pauseMenuSrcRect;
    SDL_FRect pauseMenuDstRect;
    TransitionFromBelow* pauseMenuTransition;

public:
    PauseDialog(SDL_Renderer* renderer, const float screen_w, const float screen_h) : screen_w(screen_w), screen_h(screen_h), renderer(renderer) {
        pauseBarsAnimation = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, screen_w, screen_h);
        if (pauseBarsAnimation == nullptr) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Could not create pauseBarsAnimation texture: %s\n", SDL_GetError());
            exit();
        }
        screenRect = {0, 0, screen_w, screen_h};

        // Set the pause dialog background transparent
        SDL_SetRenderTarget(renderer, pauseBarsAnimation);
        SDL_SetRenderDrawColor(renderer, colors::transparent.r, colors::transparent.g, colors::transparent.b, colors::transparent.a);
        SDL_RenderClear(renderer);
        SDL_SetRenderTarget(renderer, NULL);

        // Load the pause menu background
        pauseMenuBackground = IMG_LoadTexture(renderer, images::menu_background);
        if (pauseMenuBackground == nullptr) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Could not load pauseMenuBackground texture: %s\n", SDL_GetError());
            exit();
        }
        pauseMenuSrcRect = {0, 0, dimens::pause_menu_background_file_width, dimens::pause_menu_background_file_height};
        Rectangle pauseMenuRect = {screen_w/2 - pause_menu_width/2, -pause_menu_height, pause_menu_width, pause_menu_height};
        pauseMenuTransition = new TransitionFromBelow(pauseMenuRect, pause_menu_animation_speed, screen_h/2 - pause_menu_height/2);
    }

    void run(SDL_Texture* backBuffer) {
        this->backBuffer = backBuffer;

        // Start animation
        for (int i=0; i < dimens::pause_dialog_gradient_animation_height; i++) {
            int max_color = dimens::pause_dialog_gradient_animation_height>255 ? 255 : dimens::pause_dialog_gradient_animation_height;
            int color = max_color - i;

            // Transition of the upper and lower bars, they have a color gradient
            if (i < dimens::pause_dialog_gradient_animation_height) {
                SDL_SetRenderTarget(renderer, pauseBarsAnimation);
                SDL_SetRenderDrawColor(renderer, color, color, color, color);
                SDL_RenderLine(renderer, 0, i * bars_animation_speed, screen_w,i * bars_animation_speed);
                SDL_RenderLine(renderer, 0, screen_h - i * bars_animation_speed, screen_w,screen_h - i * bars_animation_speed);
                SDL_SetRenderTarget(renderer, NULL);
            }

            // Transition of the pause menu background
            pauseMenuTransition->update();
            pauseMenuDstRect = {pauseMenuTransition->getX(), pauseMenuTransition->getY(), pause_menu_width, pause_menu_height};
            CoordinatesMediator::SDL_ConvertCoordinatesForRendering(pauseMenuDstRect, screen_h);

            // Render the animation
            SDL_RenderClear(renderer);
            SDL_RenderTexture(renderer, backBuffer, 0, &screenRect);
            SDL_RenderTexture(renderer, pauseBarsAnimation, 0, &screenRect);
            SDL_RenderTexture(renderer, pauseMenuBackground, &pauseMenuSrcRect, &pauseMenuDstRect);
            SDL_RenderPresent(renderer);
            SDL_Delay(1);
        }

        while (true) {
            SDL_RenderClear(renderer);
            SDL_RenderTexture(renderer, backBuffer, 0, &screenRect);
            SDL_RenderTexture(renderer, pauseBarsAnimation, 0, &screenRect);
            SDL_RenderTexture(renderer, pauseMenuBackground, &pauseMenuSrcRect, &pauseMenuDstRect);
            SDL_RenderPresent(renderer);
        }
    }

    void exit() {

    }

    void destroy() {
        delete pauseMenuTransition; pauseMenuTransition = nullptr;

        SDL_DestroyTexture(pauseBarsAnimation);
        SDL_DestroyTexture(pauseMenuBackground);
        pauseBarsAnimation = nullptr;
        pauseMenuBackground = nullptr;
    }
};

#endif //BRE_PAUSEDIALOG_HPP
