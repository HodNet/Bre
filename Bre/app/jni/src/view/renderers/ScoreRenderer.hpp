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

class ScoreRenderer : public Renderer {

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
            scoreFont = TTF_OpenFont("font.ttf", dimens::huge_title_font_size);
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

            const char* scoreText = Utils::toString(score->getScore());
            scoreSurface = TTF_RenderText_Solid(scoreFont, scoreText, sizeof(char)*10, colors::white.toSDLColor());
            delete[] scoreText;
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
            score->getRect().setX(screen_w / 2 - scoreSurface->w / 2);
            score->getRect().setY(screen_h - dimens::vertical_margin);
            score->getRect().setW(scoreSurface->w);
            score->getRect().setH(scoreSurface->h);

            scoreRect = {
                    score->getRect().x,
                    score->getRect().y,
                    score->getRect().w,
                    score->getRect().h
            };

            CoordinatesMediator::SDL_ConvertCoordinatesForRendering(scoreRect, screen_h);
            SDL_RenderTexture(renderer, scoreTexture, NULL, &scoreRect);

            SDL_DestroySurface(scoreSurface); scoreSurface = nullptr;
            SDL_DestroyTexture(scoreTexture); scoreTexture = nullptr;
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
