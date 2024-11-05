//
// Created by Jonathan on 29/09/2024.
//

#ifndef BRE_LEVELBACKGROUNDRENDERER_HPP
#define BRE_LEVELBACKGROUNDRENDERER_HPP

#include <SDL3/SDL.h>
#include "Renderer.hpp"
#include "../../res/colors.hpp"

class LevelBackgroundRenderer : public Renderer {

    SDL_Renderer* renderer;

public:
    LevelBackgroundRenderer() = default;
    LevelBackgroundRenderer(SDL_Renderer* renderer) {
        this->renderer = renderer;
    }

    void render() override {
        SDL_SetRenderDrawColor(renderer, colors::background.r, colors::background.g, colors::background.b, colors::background.a);
        SDL_RenderClear(renderer);
    }

    void stop() override {
        // Do nothing
    }

    void resume() override {
        // Do nothing
    }

    void destroy() override {
        // Do nothing
    }
};

#endif //BRE_LEVELBACKGROUNDRENDERER_HPP
