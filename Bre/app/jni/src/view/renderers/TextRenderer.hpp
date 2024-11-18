//
// Created by Jonathan on 15/11/2024.
//

#ifndef BRE_TEXTRENDERER_HPP
#define BRE_TEXTRENDERER_HPP

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "Renderer.hpp"
#include "../../res/colors.hpp"
#include "../../res/dimens.hpp"
#include "../../controller/components/Text.hpp"
#include "../../view/mediators/CoordinatesMediator.hpp"

class TextRenderer : virtual public Renderer {

private:
    Text* text;
    bool stopRendering = false;

    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Surface* surface;
    SDL_FRect rect;
    TTF_Font* font;

public:
    TextRenderer() = default;
    TextRenderer(Text* text, SDL_Renderer* renderer) : text(text), renderer(renderer) {
        if (text == nullptr) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TextRenderer: Text is null");
            return;
        }

        if (text->isBold())
            font = TTF_OpenFont("font_bold.ttf", text->getFontSize());
        else
            font = TTF_OpenFont("font.ttf", text->getFontSize());

        if (font == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TextRenderer: Failed to load font: %s",
                         SDL_GetError());
        }
    }

    void render() override {
        if (stopRendering || text == nullptr || font == nullptr)
            return;

        surface = TTF_RenderText_Solid(font, text->getText(), text->getLength(), colors::font.toSDLColor());
        if (surface == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TextRenderer: Failed to render text: %s", SDL_GetError());
            return;
        }

        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TextRenderer: Failed to create texture: %s", SDL_GetError());
            return;
        }

        text->setX(text->getCenterX() - surface->w/2);
        text->setY(text->getCenterY() - surface->h/2);

        rect = {
                static_cast<float>(text->x),
                static_cast<float>(text->y),
                static_cast<float>(surface->w),
                static_cast<float>(surface->h)
        };

        CoordinatesMediator::SDL_ConvertCoordinatesForRendering(rect, GameWorld::getScreenSize()->h);
        SDL_RenderTexture(renderer, texture, NULL, &rect);

        SDL_DestroySurface(surface); surface = nullptr;
        SDL_DestroyTexture(texture); texture = nullptr;
    }

    void stop() override {
        stopRendering = true;
    }

    void resume() override {
        stopRendering = false;
    }

    void destroy() override {
        text = nullptr; // The text is not owned by this class
        if (font != nullptr) {
            TTF_CloseFont(font);
            font = nullptr;
        }
    }
};

#endif //BRE_TEXTRENDERER_HPP
