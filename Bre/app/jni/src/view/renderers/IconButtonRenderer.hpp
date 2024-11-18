//
// Created by Jonathan on 08/11/2024.
//

#ifndef BRE_ICONBUTTONRENDERER_HPP
#define BRE_ICONBUTTONRENDERER_HPP

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Renderer.hpp"
#include "../../res/images.hpp"
#include "../../res/colors.hpp"
#include "../../res/dimens.hpp"
#include "../../controller/components/IconButton.hpp"

class IconButtonRenderer : virtual public Renderer {

private:
    IconButton* button;
    bool stopRendering = false;

    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_FRect dstRect;
    SDL_FRect srcRect;
    SDL_Texture* backgroundTexture;
    SDL_FRect backgroundSrcRect;
    SDL_Texture* pressedTexture;
    SDL_FRect screen;

public:
    IconButtonRenderer() = default;
    IconButtonRenderer(IconButton* button, SDL_Renderer* renderer) : button(button), renderer(renderer) {
        if(button == nullptr) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IconButtonRenderer: Button is null");
            return;
        }

        screen = {0, 0, World::getScreenW(), World::getScreenH()};
        srcRect = {0, 0, button->getSrcWidth(), button->getSrcHeight()};
        backgroundSrcRect = {0, 0, dimens::button_background_file_width, dimens::button_background_file_height};

        texture = IMG_LoadTexture(renderer, button->getIcon());
        if (texture == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IconButtonRenderer: Failed to load texture: %s", SDL_GetError());
            texture = IMG_LoadTexture(renderer, images::not_found);
            srcRect.w = dimens::not_found_file_width;
            srcRect.h = dimens::not_found_file_height;
        }

        backgroundTexture = IMG_LoadTexture(renderer, images::button_background);
        if (backgroundTexture == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IconButtonRenderer: Failed to load button background texture: %s", SDL_GetError());
        }

        pressedTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, screen.w, screen.h);
        if (pressedTexture == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IconButtonRenderer: Failed to create pressed texture: %s", SDL_GetError());
        }
    }

    /**
     * Should be called at any frame you want to render the object.
     * ButtonRenderers will not work properly in a renderer target different from the main renderer
     */
    void render() override {
        if (stopRendering || button == nullptr || texture == nullptr) {
            return;
        }

        dstRect = {button->x, button->y, button->w, button->h};
        CoordinatesMediator::SDL_ConvertCoordinatesForRendering(dstRect, GameWorld::getScreenSize()->h);


        SDL_RenderTexture(renderer, backgroundTexture, &backgroundSrcRect, &dstRect);
        SDL_RenderTexture(renderer, texture, &srcRect, &dstRect);
        if(button->isPressed()) {
            SDL_SetRenderTarget(renderer, pressedTexture);
            SDL_SetRenderDrawColor(renderer, colors::transparent.r, colors::transparent.g, colors::transparent.b, colors::transparent.a);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, colors::on_pressed.r, colors::on_pressed.g, colors::on_pressed.b, colors::on_pressed.a);
            SDL_RenderFillRect(renderer, &dstRect);
            SDL_SetRenderTarget(renderer, NULL);
            SDL_RenderTexture(renderer, pressedTexture, NULL, &screen);
        }
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
        if(backgroundTexture != nullptr) {
            SDL_DestroyTexture(backgroundTexture);
            backgroundTexture = nullptr;
        }
        if(pressedTexture != nullptr) {
            SDL_DestroyTexture(pressedTexture);
            pressedTexture = nullptr;
        }
    }

};

#endif //BRE_ICONBUTTONRENDERER_HPP
