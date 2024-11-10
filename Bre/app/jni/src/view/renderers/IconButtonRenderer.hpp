//
// Created by Jonathan on 08/11/2024.
//

#ifndef BRE_ICONBUTTONRENDERER_HPP
#define BRE_ICONBUTTONRENDERER_HPP

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Renderer.hpp"
#include "../../controller/components/IconButton.hpp"

class IconButtonRenderer : public Renderer {

private:
    IconButton* button;
    bool stopRendering = false;

    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_FRect dstRect;
    SDL_FRect srcRect;

public:
    IconButtonRenderer() = default;
    IconButtonRenderer(IconButton* button, SDL_Renderer* renderer) : button(button), renderer(renderer) {
        if(button == nullptr) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IconButtonRenderer: Button is null");
            return;
        }

        dstRect = {button->x, button->y, button->w, button->h};
        srcRect = {0, 0, button->getSrcWidth(), button->getSrcHeight()};
        texture = IMG_LoadTexture(renderer, button->getIcon());
        if (texture == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IconButtonRenderer: Failed to load texture: %s", SDL_GetError());
            texture = IMG_LoadTexture(renderer, images::not_found);
        }

        CoordinatesMediator::SDL_ConvertCoordinatesForRendering(dstRect, GameWorld::getScreenSize()->h);
    }

    void render() override {
        if (stopRendering) {
            return;
        }

        SDL_RenderTexture(renderer, texture, &srcRect, &dstRect);
    }

    void stop() override {
        stopRendering = true;
    }

    void resume() override {
        stopRendering = false;
    }

    void destroy() override {
        button = nullptr; // The button is not owned by this class
        if(texture != nullptr) {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }

};

#endif //BRE_ICONBUTTONRENDERER_HPP
