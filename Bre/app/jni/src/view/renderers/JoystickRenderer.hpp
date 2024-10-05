//
// Created by Jonathan on 29/09/2024.
//

#ifndef BRE_JOYSTICKRENDERER_HPP
#define BRE_JOYSTICKRENDERER_HPP

#include <SDL3/SDL.h>
#include <SDL3_Image/SDL_image.h>

#include "../../controller/components/Rectangle.hpp"
#include "../../model/entities/Arrow.hpp"
#include "Renderer.hpp"
#include "../../model/worlds/FreePlayWorld.hpp"
#include "../../../SDL_image/include/SDL3_image/SDL_image.h"


class JoystickRenderer : public Renderer {
    Arrow* joystick;
    bool stopRendering = false;
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
    JoystickRenderer() = default;
    JoystickRenderer(SDL_Renderer *renderer) : renderer(renderer) {
        TXRcenter = IMG_LoadTexture(renderer, "center_arrow.png");
        TXRbody = IMG_LoadTexture(renderer, "body_arrow.png");
        TXRtip = IMG_LoadTexture(renderer, "tip_arrow.png");
        if (TXRcenter == NULL || TXRbody == NULL || TXRtip == NULL)
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "JoystickRenderer: Failed to load textures: %s", SDL_GetError());
    }

    /**
     * Should be called when the user press the touch screen
     * @param input_x position x of the touch
     * @param input_y position y of the touch
     */
    void buildCenter(int input_x, int input_y) {
        if(stopRendering) {
            World::destroyJoystick();
            joystick = nullptr;
            resume();
        }

        if(joystick == nullptr) {
            joystick = new Arrow();
            World::setJoystick(joystick);
            joystick->setCenter(input_x, input_y);

            SDLcenter.x = joystick->getCenter()->x;
            SDLcenter.y = joystick->getCenter()->y;
            DSTcenter.x = joystick->getCenter()->x;
            DSTcenter.y = joystick->getCenter()->y;
        }
    }

    /**
     * Should be called when the user, after he touched the screen with his finger, he is moving it
     * @param input_x position x of the touch
     * @param input_y position y of the touch
     */
    void buildEntireArrow(int input_x, int input_y) {
        if(joystick == nullptr)
            return;

        if(joystick->getCenter() != nullptr) {
            joystick->setVector(input_x, input_y);
            angle = joystick->getVector()->getAngleInDegrees();

            DSTbody.h = 2 * joystick->getVector()->getMagnitude();
            DSTbody.x = joystick->getCenter()->x;
            DSTbody.y = joystick->getCenter()->y + DSTcenter.h / 2 - DSTbody.h / 2;

            DSTtip.x = joystick->getTip().x;
            DSTtip.y = joystick->getTip().y;
        }
    }

    void render() override {
        if(stopRendering)
            return;

        if(joystick == nullptr)
            return;

        if(joystick->getCenter() != nullptr) {
            SDL_RenderTexture(renderer, TXRcenter, &SRCcenter, &DSTcenter);
            if(joystick->getVector() != nullptr) {
                SDL_RenderTextureRotated(renderer, TXRbody, &SRCbody, &DSTbody, angle, &SDLcenter, SDL_FLIP_NONE);
                SDL_RenderTextureRotated(renderer, TXRtip, &SRCtip, &DSTtip, angle, &SDLcenter, SDL_FLIP_NONE);
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
        joystick = nullptr; // The world will take care of deleting the joystick

        if(SRFcenter != nullptr && SRFbody != nullptr && SRFtip != nullptr) {
            SDL_DestroySurface(SRFcenter);
            SDL_DestroySurface(SRFbody);
            SDL_DestroySurface(SRFtip);
            SRFcenter = nullptr;
            SRFbody = nullptr;
            SRFtip = nullptr;
        }

        if(TXRcenter != nullptr && TXRbody != nullptr && TXRtip != nullptr) {
            SDL_DestroyTexture(TXRcenter);
            SDL_DestroyTexture(TXRbody);
            SDL_DestroyTexture(TXRtip);
            TXRcenter = nullptr;
            TXRbody = nullptr;
            TXRtip = nullptr;
        }
    }
};

#endif //BRE_JOYSTICKRENDERER_HPP
