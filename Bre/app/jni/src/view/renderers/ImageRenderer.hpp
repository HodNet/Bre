//
// Created by Jonathan on 15/11/2024.
//

#ifndef BRE_IMAGERENDERER_HPP
#define BRE_IMAGERENDERER_HPP

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Renderer.hpp"
#include "../../res/images.hpp"
#include "../../res/colors.hpp"
#include "../../res/dimens.hpp"
#include "../../controller/components/Image.hpp"

class ImageRenderer : virtual public Renderer {

private:
    Image* image;
    bool stopRendering = false;

    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_FRect dstRect;
    SDL_FRect srcRect;

public:
    ImageRenderer() = default;
    ImageRenderer(Image* image, SDL_Renderer* renderer) : image(image), renderer(renderer) {
        if(image == nullptr) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "ImageRenderer: Image is null");
            return;
        }

        srcRect = {0, 0, image->getSrcWidth(), image->getSrcHeight()};
        texture = IMG_LoadTexture(renderer, image->getFilename());
        if (texture == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "ImageRenderer: Failed to load texture: %s", SDL_GetError());
            texture = IMG_LoadTexture(renderer, images::not_found);
            srcRect.w = dimens::not_found_file_width;
            srcRect.h = dimens::not_found_file_height;
        }
    }

    void render() override {
        if (stopRendering || image == nullptr || texture == nullptr)
            return;

        dstRect = {image->x, image->y, image->w, image->h};
        CoordinatesMediator::SDL_ConvertCoordinatesForRendering(dstRect, GameWorld::getScreenSize()->h);
        SDL_RenderTexture(renderer, texture, &srcRect, &dstRect);
    }

    void stop() override {
        stopRendering = true;
    }

    void resume() override {
        stopRendering = false;
    }

    void destroy() override {
        image = nullptr; // The image is not owned by this class
        if (texture != nullptr) {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }
};

#endif //BRE_IMAGERENDERER_HPP
