//
// Created by Jonathan on 26/09/2024.
//
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "view/activities/GameActivity.hpp"

// Singleton declarations
Player* Player::instance = nullptr;

class Main {

public:

    Main() = delete;

    static int main_in_cpp() {
        if (!SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init failed (%s)", SDL_GetError());
            return 1;
        }

        /*
        if (!SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Hello World",
                                      "!! Your SDL project successfully runs on Android !!", NULL)) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_ShowSimpleMessageBox failed (%s)", SDL_GetError());
            return 1;
        } */

        const SDL_DisplayMode* screen = SDL_GetCurrentDisplayMode(1);
        if (screen == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_GetCurrentDisplayMode failed (%s)", SDL_GetError());
            return 1;
        } else {
            SDL_Log("Screen resolution: %dx%d", screen->w, screen->h);
        }

        GameActivity gameActivity(screen);
        gameActivity.run();

        SDL_Quit();
        return 0;
    }
};

extern "C" {
    int main_in_cpp() {
        return Main::main_in_cpp();
    }
}