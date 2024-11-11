//
// Created by Jonathan on 10/11/2024.
//

#ifndef BRE_PAUSEDIALOG_HPP
#define BRE_PAUSEDIALOG_HPP

#include <SDL3/SDL.h>

#include "../../res/dimens.hpp"
#include "../../res/colors.hpp"

class PauseDialog {

private:
    const int screen_w = 0;
    const int screen_h = 0;

    SDL_Renderer* renderer;
    SDL_Texture* backBuffer;
    SDL_Texture* pauseBarsAnimation;
    SDL_FRect screenRect;

public:
    PauseDialog(SDL_Renderer* renderer, const int screen_w, const int screen_h) : screen_w(screen_w), screen_h(screen_h), renderer(renderer) {
        pauseBarsAnimation = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, screen_w, screen_h);
        if (pauseBarsAnimation == nullptr) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Could not create pauseBarsAnimation texture: %s\n", SDL_GetError());
            exit();
        }
        screenRect = {0, 0, static_cast<float>(screen_w), static_cast<float>(screen_h)};

        // Set the pause dialog background transparent
        SDL_SetRenderTarget(renderer, pauseBarsAnimation);
        SDL_SetRenderDrawColor(renderer, colors::transparent.r, colors::transparent.g, colors::transparent.b, colors::transparent.a);
        SDL_RenderClear(renderer);
        SDL_SetRenderTarget(renderer, NULL);
    }

    void run(SDL_Texture* backBuffer) {
        this->backBuffer = backBuffer;

        // Start animation
        for (int i= 0; i < dimens::pause_dialog_gradient_animation_height; i+=2) {
            int max_color = dimens::pause_dialog_gradient_animation_height>255 ? 255 : dimens::pause_dialog_gradient_animation_height;
            int color = max_color - i;

            // Animation of the upper and lower bars, they have a color gradient
            SDL_SetRenderTarget(renderer, pauseBarsAnimation);
            SDL_SetRenderDrawColor(renderer, color, color, color, color);
            SDL_RenderLine(renderer, 0, i, screen_w, i);
            SDL_RenderLine(renderer, 0, screen_h - i, screen_w, screen_h - i);
            SDL_SetRenderTarget(renderer, NULL);

            // Render the animation
            SDL_RenderClear(renderer);
            SDL_RenderTexture(renderer, backBuffer, 0, &screenRect);
            SDL_RenderTexture(renderer, pauseBarsAnimation, 0, &screenRect);
            SDL_RenderPresent(renderer);
            SDL_Delay(1);
        }

        while (true) {}
    }

    void exit() {

    }

    void destroy() {
        SDL_DestroyTexture(pauseBarsAnimation);
        pauseBarsAnimation = nullptr;
    }
};

#endif //BRE_PAUSEDIALOG_HPP
