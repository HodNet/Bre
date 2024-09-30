//
// Created by Jonathan on 29/09/2024.
//

#ifndef BRE_ARROWJOYSTICKRENDERER_HPP
#define BRE_ARROWJOYSTICKRENDERER_HPP

#include <SDL3/SDL.h>

#include "../../controller/components/Rectangle.hpp"
#include "../../model/entities/Arrow.hpp"


class ArrowJoystickRenderer {
    Arrow* arrow;
    double angle;

    SDL_Renderer *renderer;
    SDL_FPoint SDLcenter;
    SDL_FRect SRCcenter{0, 0, 54, 55};
    SDL_FRect SRCbody{0, 0, 54, 362};
    SDL_FRect SRCtip{0, 0, 54, 54};
    SDL_FRect DSTcenter{0, 0, 26, 26};
    SDL_FRect DSTbody{0, 0, 26, 1};
    SDL_FRect DSTtip{0, 0, 26, 26};
    SDL_Surface *SRFcenter;
    SDL_Surface *SRFbody;
    SDL_Surface *SRFtip;
    SDL_Texture *TXRcenter;
    SDL_Texture *TXRbody;
    SDL_Texture *TXRtip;

public:
    ArrowJoystickRenderer(SDL_Renderer *renderer) : renderer(renderer) {
        SRFcenter = SDL_LoadBMP("center_arrow.bmp");
        SRFbody = SDL_LoadBMP("body_arrow.bmp");
        SRFtip = SDL_LoadBMP("tip_arrow.bmp");
        if (SRFcenter == NULL || SRFbody == NULL || SRFtip == NULL)
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not load arrow surfaces: %s\n", SDL_GetError());
        else {
            TXRcenter = SDL_CreateTextureFromSurface(renderer, SRFcenter);
            TXRbody = SDL_CreateTextureFromSurface(renderer, SRFbody);
            TXRtip = SDL_CreateTextureFromSurface(renderer, SRFtip);
            if (TXRcenter == NULL || TXRbody == NULL || TXRtip == NULL)
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not load arrow textures: %s\n", SDL_GetError());
        }
    }

    void buildCenter(int input_x, int input_y) {
        if(arrow == nullptr) {
            arrow = new Arrow();
            arrow->setCenter(input_x, input_y);

            SDLcenter.x = arrow->getCenter()->x;
            SDLcenter.y = arrow->getCenter()->y;
            DSTcenter.x = arrow->getCenter()->x;
            DSTcenter.y = arrow->getCenter()->y;
        }
    }

    void buildEntireArrow(int input_x, int input_y) {
        if(arrow == nullptr)
            return;

        if(arrow->getCenter() != nullptr) {
            arrow->setVector(input_x, input_y);
            angle = arrow->getVector()->getAngleInDegrees();

            DSTbody.h = 2*arrow->getVector()->getMagnitude();
            DSTbody.x = arrow->getCenter()->x;
            DSTbody.y = arrow->getCenter()->y + DSTcenter.h/2 - DSTbody.h/2;

            DSTtip.x = arrow->getTip().x;
            DSTtip.y = arrow->getTip().y;
        }
    }

    void render() {
        if(arrow == nullptr)
            return;

        if(arrow->getCenter() != nullptr) {
            SDL_RenderTexture(renderer, TXRcenter, &SRCcenter, &DSTcenter);
            if(arrow->getVector() != nullptr) {
                SDL_RenderTextureRotated(renderer, TXRbody, &SRCbody, &DSTbody, angle, &SDLcenter, SDL_FLIP_NONE);
                SDL_RenderTextureRotated(renderer, TXRtip, &SRCtip, &DSTtip, angle, &SDLcenter, SDL_FLIP_NONE);
            }
        }
    }

    void destroy() {
        delete arrow;
        SDL_DestroySurface(SRFcenter);
        SDL_DestroySurface(SRFbody);
        SDL_DestroySurface(SRFtip);
        SDL_DestroyTexture(TXRcenter);
        SDL_DestroyTexture(TXRbody);
        SDL_DestroyTexture(TXRtip);
    }

    ~ArrowJoystickRenderer() {
        destroy();
    }
};

#endif //BRE_ARROWJOYSTICKRENDERER_HPP
