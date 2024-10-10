//
// Created by Jonathan on 29/09/2024.
//

#ifndef BRE_JOYSTICKRENDERER_HPP
#define BRE_JOYSTICKRENDERER_HPP

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Renderer.hpp"
#include "../utils/SDL_Utils.hpp"
#include "../../controller/components/Rectangle.hpp"
#include "../../model/entities/Arrow.hpp"
#include "../../model/worlds/World.hpp"


class JoystickRenderer : public Renderer {

private:
    Arrow* joystick;
    bool stopRendering = false;
    double angle;

    SDL_Renderer *renderer;
    SDL_FPoint AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA;
    SDL_FRect SRCcenter{0, 0, 54, 55};
    SDL_FRect SRCbody{0, 0, 1280, 427};
    SDL_FRect SRCtip{0, 0, 54, 54};
    SDL_FRect DSTcenter{0, 0, 26, 26};
    SDL_FRect DSTbody{0, 0, 1, 26};
    SDL_FRect DSTtip{0, 0, 26, 26};
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

            DSTcenter.x = joystick->getCenter()->x;
            DSTcenter.y = joystick->getCenter()->y;

            SDL_Utils::SDL_ConvertCoordinatesForRendering(DSTcenter, World::getScreenSize()->h);
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
            SDL_Utils::SDL_ConvertAngleForRendering(angle);

            DSTbody.w = joystick->getVector()->getMagnitude();
            DSTbody.w += DSTbody.w/100; // adding a bit more length to make it connect with the tip
            DSTbody.x = joystick->getCenter()->x;
            DSTbody.y = joystick->getCenter()->y;

            DSTtip.x = joystick->getTip().x;
            DSTtip.y = joystick->getTip().y;

            SDL_Utils::SDL_ConvertCoordinatesForRendering(DSTbody, World::getScreenSize()->h);
            SDL_Utils::SDL_ConvertCoordinatesForRendering(DSTtip, World::getScreenSize()->h);
        }
    }

    void render() override {
        if(stopRendering)
            return;

        if(joystick == nullptr)
            return;

        //SDL_Log("Angle: %f", angle);

        if(joystick->getCenter() != nullptr) {
            SDL_RenderTexture(renderer, TXRcenter, &SRCcenter, &DSTcenter);
            if(joystick->getVector() != nullptr) {
                SDL_FPoint center = {DSTcenter.w/2, DSTcenter.h/2};
                SDL_RenderTextureRotated(renderer, TXRbody, &SRCbody, &DSTbody, angle, &center, SDL_FLIP_NONE);
                SDL_RenderTextureRotated(renderer, TXRtip, &SRCtip, &DSTtip, angle, &center, SDL_FLIP_NONE);
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
