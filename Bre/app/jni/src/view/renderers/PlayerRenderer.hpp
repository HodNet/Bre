//
// Created by Jonathan on 28/09/2024.
//

#ifndef BRE_PLAYERRENDERER_HPP
#define BRE_PLAYERRENDERER_HPP

#include <SDL3/SDL.h>
#include "Renderer.hpp"
#include "../../res/colors.hpp"
#include "../../view/mediators/CoordinatesMediator.hpp"
#include "../../model/entities/Player.hpp"
#include "../../model/worlds/GameWorld.hpp"


class PlayerRenderer : public Renderer {

    Player* player;
    bool stopRendering = false;

    SDL_Renderer* renderer;
    SDL_FRect playerRect;

public:
    PlayerRenderer() = default;
    PlayerRenderer(SDL_Renderer* renderer) {
        this->renderer = renderer;
    }

    void render() override {
        if(stopRendering)
            return;

        this->player = GameWorld::getPlayer();
        this->playerRect = {
                (float) player->getRect().x,
                (float) player->getRect().y,
                (float) player->getRect().w,
                (float) player->getRect().h
        };
        CoordinatesMediator::SDL_ConvertCoordinatesForRendering(playerRect, GameWorld::getScreenSize()->h);

        SDL_SetRenderDrawColor(renderer, colors::white.r, colors::white.g, colors::white.b, colors::white.a);
        SDL_RenderFillRect(renderer, &playerRect);
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


#endif //BRE_PLAYERRENDERER_HPP
