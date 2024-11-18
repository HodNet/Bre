//
// Created by Jonathan on 15/11/2024.
//

#ifndef BRE_BACKGROUNDGRADIENTANIMATIONRENDERER_HPP
#define BRE_BACKGROUNDGRADIENTANIMATIONRENDERER_HPP

#include <SDL3/SDL.h>

#include "../../res/dimens.hpp"
#include "../../res/colors.hpp"
#include "../../controller/components/Animation.hpp"
#include "../../view/renderers/Renderer.hpp"
#include "../../model/worlds/World.hpp"

class BackgroundGradientAnimationRenderer : virtual public Animation, virtual public Renderer {

private:
    constexpr static int gradient = 3;
    int color = 200;
    int y = 0;

    bool stopRendering = false;
    SDL_Renderer *renderer;
    SDL_Texture *gradientAnimation;
    SDL_FRect screen;

public:
    BackgroundGradientAnimationRenderer() = default;
    BackgroundGradientAnimationRenderer(SDL_Renderer *renderer) : renderer(renderer) {
        screen = {0, 0, World::getScreenW(), World::getScreenH()};

        // Load the pause background
        gradientAnimation = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, screen.w, screen.h);
        if (gradientAnimation == nullptr) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create gradient texture: %s\n", SDL_GetError());
        }

        // Set the pause background transparent
        SDL_SetRenderTarget(renderer, gradientAnimation);
        SDL_SetRenderDrawColor(renderer, colors::transparent.r, colors::transparent.g, colors::transparent.b, colors::transparent.a);
        SDL_RenderClear(renderer);
        SDL_SetRenderTarget(renderer, NULL);
    }

    bool isFinished() const override {
        return color<0;
    }

    void update() override {
        if (isFinished())
            return;

        SDL_SetRenderTarget(renderer, gradientAnimation);

        SDL_SetRenderDrawColor(renderer, color, color, color, color);
        SDL_RenderLine(renderer, 0, screen.h - y, screen.w, screen.h - y);
        SDL_RenderLine(renderer, 0, y, screen.w, y);
        color-=1;
        y += gradient;

        if (!isFinished()) {
            SDL_SetRenderDrawColor(renderer, color, color, color, color);
            SDL_RenderLine(renderer, 0, screen.h - y, screen.w, screen.h - y);
            SDL_RenderLine(renderer, 0, y, screen.w, y);
            color -= 1;
            y += gradient;
        }

        SDL_SetRenderTarget(renderer, NULL);
    }

    void render() override {
        if(gradientAnimation == nullptr || stopRendering)
            return;

        SDL_RenderTexture(renderer, gradientAnimation, NULL, &screen);
    }

    void stop() override {
        stopRendering = true;
    }

    void resume() override {
        stopRendering = false;
    }

    void destroy() override {
        if (gradientAnimation != nullptr) {
            SDL_DestroyTexture(gradientAnimation);
            gradientAnimation = nullptr;
        }
    }
};

#endif //BRE_BACKGROUNDGRADIENTANIMATIONRENDERER_HPP
