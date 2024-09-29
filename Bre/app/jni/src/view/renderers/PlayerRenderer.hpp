//
// Created by Jonathan on 28/09/2024.
//

#ifndef BRE_PLAYERRENDERER_HPP
#define BRE_PLAYERRENDERER_HPP

#include <SDL3/SDL.h>
#include "../../model/entities/Player.hpp"


class PlayerRenderer {

    Player* player;

    SDL_Renderer* renderer;
    SDL_FRect playerRect;

public:
    PlayerRenderer() = default;
    PlayerRenderer(SDL_Renderer* renderer) {
        this->renderer = renderer;
        this->player = Player::getInstance();
        this->playerRect = {
                (float) player->getRect().x,
                (float) player->getRect().y,
                (float) player->getRect().w,
                (float) player->getRect().h
        };
    }

    void render() {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &playerRect);
    }

};


#endif //BRE_PLAYERRENDERER_HPP
