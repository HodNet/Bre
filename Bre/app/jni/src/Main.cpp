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

/*
static char * icon_xpm[] = {
        "32 23 3 1",
        "     c #FFFFFF",
        ".    c #000000",
        "+    c #FFFF00",
        "                                ",
        "            ........            ",
        "          ..++++++++..          ",
        "         .++++++++++++.         ",
        "        .++++++++++++++.        ",
        "       .++++++++++++++++.       ",
        "      .++++++++++++++++++.      ",
        "      .+++....++++....+++.      ",
        "     .++++.. .++++.. .++++.     ",
        "     .++++....++++....++++.     ",
        "     .++++++++++++++++++++.     ",
        "     .++++++++++++++++++++.     ",
        "     .+++++++++..+++++++++.     ",
        "     .+++++++++..+++++++++.     ",
        "     .++++++++++++++++++++.     ",
        "      .++++++++++++++++++.      ",
        "      .++...++++++++...++.      ",
        "       .++............++.       ",
        "        .++..........++.        ",
        "         .+++......+++.         ",
        "          ..++++++++..          ",
        "            ........            ",
        "                                "};
*/

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
        else
            SDL_Log("Number of displays: %i", *numDisplays);

        const SDL_DisplayMode* screen = SDL_GetCurrentDisplayMode(*displays);
        if (screen == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_GetCurrentDisplayMode failed (%s)", SDL_GetError());
            SDL_Quit();
            return 1;
        } else {
            SDL_Log("Screen resolution: %dx%d", screen->w, screen->h);
            SDL_Log("Display ID is %i", *displays);
        }

        SDL_Log("Display pixel format: %s", SDL_GetPixelFormatName(screen->format));

        SDL_Window* window = SDL_CreateWindow("Game", screen->w, screen->h, SDL_WINDOW_VULKAN | SDL_WINDOW_FULLSCREEN);
        if (window == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create window: %s\n", SDL_GetError());
        }

        SDL_PixelFormat windowPixelFormat = SDL_GetWindowPixelFormat(window);
        if(windowPixelFormat == SDL_PIXELFORMAT_UNKNOWN)
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not get window pixel format: %s\n", SDL_GetError());
        else
            SDL_Log("Window pixel format: %s", SDL_GetPixelFormatName(windowPixelFormat));

        SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
        if (renderer == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create renderer: %s\n", SDL_GetError());
        }

        SDL_Log("Number of renderer: %i", SDL_GetNumRenderDrivers());
        SDL_Log("Renderer name: %s", SDL_GetRendererName(renderer));

        SDL_PropertiesID info;
        info = SDL_GetRendererProperties(renderer);

        //  Get the texture formats supported by the renderer
        const SDL_PixelFormat *formats = (const SDL_PixelFormat*)SDL_GetPointerProperty(info, SDL_PROP_RENDERER_TEXTURE_FORMATS_POINTER, NULL);
        if(formats == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not get texture formats: %s\n", SDL_GetError());
        } else {
            int i;
            for (i = 0; *(formats+i) != SDL_PIXELFORMAT_UNKNOWN; i++) {
                SDL_Log("Renderer supports %s texture formats", SDL_GetPixelFormatName(*(formats+i)));
            }
        }

        // Get the texture max supported width and height
        SDL_Log("%u", SDL_GetPropertyType(info, SDL_PROP_RENDERER_MAX_TEXTURE_SIZE_NUMBER));
        int maxTextureSize = SDL_GetNumberProperty(info, SDL_PROP_RENDERER_MAX_TEXTURE_SIZE_NUMBER, 0);
        SDL_Log("Max texture size: %i", maxTextureSize);

        /*
        //  ATTEMPT 1
        SDL_Surface* surface = SDL_LoadBMP("center_arrow.bmp");
        if (surface == NULL)
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not load surface: %s\n", SDL_GetError());
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == NULL)
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not load texture: %s\n", SDL_GetError());
        */

        /*
        //  ATTEMPT 2
        SDL_Texture* texture = IMG_LoadTexture(renderer, "center_arrow.png");
        if (texture == NULL)
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not load texture: %s\n", SDL_GetError());
        */

        /*
        //  ATTEMPT 3
        SDL_Surface* surface = IMG_Load("center_arrow.png");
        if (surface == NULL)
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not load surface: %s\n", SDL_GetError());
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == NULL)
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not load texture: %s\n", SDL_GetError());
        */

        /*
        //  ATTEMPT 4
        SDL_IOStream* stream = SDL_IOFromFile("center_arrow.png", "rb");
        if(stream == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not load stream: %s\n", SDL_GetError());
        }
        SDL_Surface* surface = IMG_LoadPNG_IO(stream);
        if (surface == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not load surface: %s\n", SDL_GetError());
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not load texture: %s\n", SDL_GetError());
        } */

        /*
        //  ATTEMPT 5
        SDL_Surface* surface = SDL_LoadBMP("lettuce.bmp");
        if (surface == NULL)
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not load surface: %s\n", SDL_GetError());
        else
            SDL_Log("Surface pixel format: %s", SDL_GetPixelFormatName(surface->format));

        SDL_Surface* converted_surface = SDL_ConvertSurface(surface, windowPixelFormat);
        if (converted_surface == NULL)
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not convert surface: %s\n", SDL_GetError());
        else
            SDL_Log("Converted surface pixel format: %s", SDL_GetPixelFormatName(converted_surface->format));

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, converted_surface);
        if (texture == NULL)
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not load texture: %s\n", SDL_GetError());
        */

        /*
        //  ATTEMPT 6
        SDL_Surface* surface = IMG_ReadXPMFromArray(icon_xpm);
        if (surface == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not load surface: %s\n", SDL_GetError());
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                         "Couldn't load texture: %s", SDL_GetError());
        }
        */


        //  ATTEMPT 7
        SDL_Texture* texture = IMG_LoadTexture(renderer, "Phone_Sized_Image.jpg");
        if (texture == NULL)
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not load texture: %s\n", SDL_GetError());


        while(false) {
            SDL_Event e;
            if(SDL_PollEvent(&e)) {
                if(e.type == SDL_EVENT_QUIT) {
                    break;
                }
            }

            SDL_SetRenderDrawColor(renderer, 39, 39, 39, 255);
            SDL_RenderClear(renderer);
            SDL_RenderTexture(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
        }

        //FreePlayActivity gameActivity(screen);
        //gameActivity.run();

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