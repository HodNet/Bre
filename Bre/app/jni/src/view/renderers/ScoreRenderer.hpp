//
// Created by Jonathan on 02/11/2024.
//

#ifndef BRE_SCORERENDERER_HPP
#define BRE_SCORERENDERER_HPP

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "Renderer.hpp"
#include "../../res/colors.hpp"
#include "../../res/dimens.hpp"
#include "../../controller/utils/Utils.hpp"
#include "../../model/entities/Score.hpp"

class ScoreRenderer : virtual public Renderer {

private:
    Score* score;
    bool stopRendering = false;

    SDL_FRect scoreRect;
    SDL_Surface* scoreSurface;
    SDL_Texture* scoreTexture;
    TTF_Font* scoreFont;

    SDL_Renderer* renderer;

public:
    ScoreRenderer() = default;
    ScoreRenderer(SDL_Renderer* renderer) : renderer(renderer) {
        if (FreePlayWorld::getCurrentScore() != nullptr) {
            scoreFont = TTF_OpenFont("RasterInfo.ttf", dimens::huge_title_font_size);
            if (scoreFont == NULL) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "ScoreRenderer: Failed to load font: %s", SDL_GetError());
            }
        }
    }

    void render() override {
        if (stopRendering)
            return;

        if(FreePlayWorld::getCurrentScore() != nullptr) {
            this->score = FreePlayWorld::getCurrentScore();

            scoreSurface = TTF_RenderText_Solid(scoreFont, score->getText(), score->getLength(), colors::font.toSDLColor());
            if(scoreSurface == NULL)
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "ScoreRenderer: Failed to render text: %s", SDL_GetError());
            else
                SDL_Log("ScoreRenderer: Score surface created successfully!");

            scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
            if(scoreTexture == NULL)
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "ScoreRenderer: Failed to create texture: %s", SDL_GetError());
            else
                SDL_Log("ScoreRenderer: Score texture created successfully!");

            float screen_w = FreePlayWorld::getScreenSize()->w;
            float screen_h = FreePlayWorld::getScreenSize()->h;
            score->setX(screen_w/2 - scoreSurface->w/2);
            score->setY(screen_h - scoreSurface->h - dimens::vertical_margin);

            scoreRect = {
                    static_cast<float>(score->x),
                    static_cast<float>(score->y),
                    static_cast<float>(scoreSurface->w),
                    static_cast<float>(scoreSurface->h)
            };

            CoordinatesMediator::SDL_ConvertCoordinatesForRendering(scoreRect, screen_h);
            SDL_RenderTexture(renderer, scoreTexture, NULL, &scoreRect);

            if(scoreSurface != nullptr && scoreTexture != nullptr) {
                SDL_DestroySurface(scoreSurface);
                SDL_DestroyTexture(scoreTexture);
                scoreSurface = nullptr;
                scoreTexture = nullptr;
            }
        }

    }

    void stop() override {
        stopRendering = true;
    }

    void resume() override {
        stopRendering = false;
    }

    void destroy() override {
        score = nullptr; // The world will take care of deleting the score
        if (scoreFont != NULL) {
            TTF_CloseFont(scoreFont);
        }
    }
};

#endif //BRE_SCORERENDERER_HPP
