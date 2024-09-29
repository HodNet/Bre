//
// Created by Jonathan on 29/09/2024.
//

#ifndef BRE_LEVELBACKGROUNDRENDERER_HPP
#define BRE_LEVELBACKGROUNDRENDERER_HPP

#include <SDL3/SDL.h>


class LevelBackgroundRenderer {

    SDL_Renderer* renderer;

public:
    LevelBackgroundRenderer() = default;
    LevelBackgroundRenderer(SDL_Renderer* renderer) {
        this->renderer = renderer;
    }

    void render() {
        SDL_SetRenderDrawColor(renderer, 39, 39, 39, 255);
        SDL_RenderClear(renderer);
    }

};

#endif //BRE_LEVELBACKGROUNDRENDERER_HPP
