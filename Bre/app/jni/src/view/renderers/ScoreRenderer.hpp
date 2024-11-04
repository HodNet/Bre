//
// Created by Jonathan on 02/11/2024.
//

#ifndef BRE_SCORERENDERER_HPP
#define BRE_SCORERENDERER_HPP

#include "../../model/entities/Score.hpp"
#include "SDL3/SDL.h"

class ScoreRenderer {

private:
    Score* score;
    bool stopRendering = false;
    int fontSize = 24;

    SDL_FRect scoreRect;
    SDL_Surface* scoreSurface;
    SDL_Texture* scoreTexture;

    SDL_Renderer* renderer;

public:
    ScoreRenderer(SDL_Renderer* renderer, int fontSize, float x, float y, float w, float z) : fontSize(fontSize), renderer(renderer) {

    }
};

#endif //BRE_SCORERENDERER_HPP
