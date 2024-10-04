//
// Created by Jonathan on 29/09/2024.
//

#ifndef BRE_LEVELBACKGROUNDRENDERER_HPP
#define BRE_LEVELBACKGROUNDRENDERER_HPP

#include <SDL3/SDL.h>
#include "Renderer.hpp"

class LevelBackgroundRenderer : public Renderer {

    SDL_Renderer* renderer;

public:
    LevelBackgroundRenderer() = default;
    LevelBackgroundRenderer(SDL_Renderer* renderer) {
        this->renderer = renderer;
    }

    void render() override {
        SDL_SetRenderDrawColor(renderer, 39, 39, 39, 255);
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
