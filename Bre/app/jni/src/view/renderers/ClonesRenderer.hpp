//
// Created by Jonathan on 24/10/2024.
//

#ifndef BRE_CLONESRENDERER_HPP
#define BRE_CLONESRENDERER_HPP

#include <SDL3/SDL.h>

#include "Renderer.hpp"
#include "../Mediator.hpp"
#include "../../model/entities/Clone.hpp"
#include "../../model/worlds/FreePlayWorld.hpp"

class ClonesRenderer : public Renderer {

private:
    std::map<int, Clone>* clones;
    bool stopRendering = false;

    SDL_Renderer* renderer;
    SDL_FRect cloneRect;

public:
    ClonesRenderer() = default;
    ClonesRenderer(SDL_Renderer* renderer) {
        this->renderer = renderer;
    }

    void render() override {
        if(stopRendering)
            return;

        this->clones = FreePlayWorld::getClones();
        for(auto& clone_pair : *clones) {
            Clone& clone = clone_pair.second;

            cloneRect = {
                    (float) clone.getRect().x,
                    (float) clone.getRect().y,
                    (float) clone.getRect().w,
                    (float) clone.getRect().h
            };
            Mediator::SDL_ConvertCoordinatesForRendering(cloneRect, World::getScreenSize()->h);

            SDL_SetRenderDrawColor(renderer, 204, 2, 2, 255);
            SDL_RenderFillRect(renderer, &cloneRect);
        }
    }

    void stop() override {
        stopRendering = true;
    }

    void resume() override {
        stopRendering = false;
    }

    void destroy() override {
        // Do nothing
    }
};

#endif //BRE_CLONESRENDERER_HPP
