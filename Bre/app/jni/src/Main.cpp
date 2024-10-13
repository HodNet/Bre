//
// Created by Jonathan on 26/09/2024.
//
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include "view/activities/FreePlayActivity.hpp"

// Singleton declarations
Player* Player::instance = nullptr;

// Static objects declarations
const Rectangle* World::screenSize = nullptr;
Player* World::player = nullptr;
StopWatch* World::gameTimer = nullptr;
Arrow* World::joystick = nullptr;
StopWatch* World::frameTimer = nullptr;

class Main {

public:

    Main() = delete;

    static int main_in_cpp() {
        if (!SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init failed (%s)", SDL_GetError());
            SDL_Quit();
            return 1;
        }

        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_Init failed.");
            SDL_Quit();
            return 1;
        } else {
            SDL_Log("IMG_Init success.");
        }

        /*
        if (!SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Hello World",
                                      "!! Your SDL project successfully runs on Android !!", NULL)) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_ShowSimpleMessageBox failed (%s)", SDL_GetError());
            return 1;
        } */


        int* numDisplays = new int(0);
        SDL_DisplayID* displays = SDL_GetDisplays(numDisplays);
        if (displays == NULL)
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_GetDisplays failed (%s)", SDL_GetError());

        const SDL_DisplayMode* screen = SDL_GetCurrentDisplayMode(*displays);
        if (screen == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_GetCurrentDisplayMode failed (%s)", SDL_GetError());
            SDL_Quit();
            return 1;
        } else
            SDL_Log("Screen resolution: %dx%d", screen->w, screen->h);

        FreePlayActivity gameActivity(screen);
        gameActivity.run();

        SDL_Quit();
        IMG_Quit();
        return 0;
    }
};

extern "C" {
    int main_in_cpp() {
        return Main::main_in_cpp();
    }
}