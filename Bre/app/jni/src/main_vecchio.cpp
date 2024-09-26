#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL2_gfxPrimitives.h"
#include "SDL_ttf.h"
#include "Cronometro.h"
#include "SDLFunzioni.h"
#include "SDLFreccia.h"
#include "Clone.h"
#include "SDLPausa.h"
#include "FPS.h"
#include <vector>

using namespace std;

int velocita = 3;

int main(int argc, char** argsv)
{
    bool menu = true;
    bool running = true;
    bool avanzate = false;

    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG); IMG_Init(IMG_INIT_PNG);
    if (TTF_Init() == -1) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_Init: %s\n", TTF_GetError());
        return 7;
    }

    SDL_DisplayMode screen;
    SDL_GetDisplayMode(0, 0, &screen);
    unsigned short int pw = screen.w / 10;
    unsigned short int ph = screen.h / 10;

    SDL_Window* window = SDL_CreateWindow("Bre", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen.w, screen.h, SDL_WINDOW_FULLSCREEN);
    if (window == NULL) {
        SDL_Log("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* textureFPS;

    SDL_Color textColor = { 255, 255, 255 };
    SDL_Surface* surface;
    SDL_Rect rect_FPS;

    while (running)
    {
        stringstream ssFPS;
        ssFPS << "FPS: 60";
        TTF_Font* fontFPS = TTF_OpenFontRW(SDL_RWFromFile("OpenSans-Regular.ttf", "rb"), 1, 24);
        if (!fontFPS) SDL_Log("Could not load font %s\n", SDL_GetError());
        surface = TTF_RenderText_Solid(fontFPS, ssFPS.str().c_str(), textColor);
        textureFPS = SDL_CreateTextureFromSurface(renderer, surface);
        rect_FPS = { 0, ph / 6, surface ? surface->w : 0, surface ? surface->h : 0 };
        SDL_FreeSurface(surface);

        bool playing = true;
        float MovOriz = 0;
        float MovVert = 0;
        SDL_rettangolo player{{screen.w / 2 - pw/4, screen.h / 2 - pw/4, pw/2, pw/2} };

        Cronometro Tgame;
        bool BTgame = true;
        Clone clone{renderer, screen.w, screen.h};
        bool Bclone = false;

        Fps FPS;
        int FPSprec = 0;

        Freccia freccia{renderer};
        Pausa pausa{renderer, screen.w, screen.h};

        while (menu)
        {
            break;
        }

        while (playing)
        {
            pausa.run(); //è importante che questo si trovi prima di pausa.premuta

            SDL_Event e;
            if (SDL_PollEvent(&e))
            {
                int ex = e.tfinger.x * screen.w;
                int ey = e.tfinger.y * screen.h;

                if(e.type == 1792 && e.tfinger.fingerId == 0) freccia.BuildCoda(ex, ey);
                if(e.type == 1794 && e.tfinger.fingerId == 0) freccia.BuildPunta(ex, ey);
                if(e.type == 1793 && e.tfinger.fingerId == 0) freccia.destroy();
                if(e.tfinger.fingerId==3) avanzate= true; //fingerId dice quante dita stanno cliccando contemporaneamente lo schermo
                //SDL_Log("%lld", e.tfinger.fingerId); //credo che "%lld" sia più corretto quando si stampa un int, me lo ha consigliato il compilatore

                Cronometro *Tpoint[] = {&freccia.Tx, &freccia.Ty, &FPS.t, &Tgame}; //il pointer di tutti i tempi
                pausa.premuta(&ex, &ey, &FPS.fps, *Tpoint, 4);
                if (e.type == 260)
                {
                    if (renderer)
                        SDL_DestroyRenderer(renderer);

                    freccia.Tx.stop();
                    freccia.Ty.stop();
                    FPS.t.stop();
                    Tgame.stop();
                }
                if (e.type == 262)
                {
                    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
                    freccia.NewRenderer(renderer);
                    clone.NewRenderer(renderer);
                    surface = TTF_RenderText_Solid(fontFPS, ssFPS.str().c_str(), textColor);
                    textureFPS = SDL_CreateTextureFromSurface(renderer, surface);
                    SDL_FreeSurface(surface);

                    freccia.Tx.riprendi();
                    freccia.Ty.riprendi();
                    FPS.t.riprendi();
                    Tgame.riprendi();
                }

                if (freccia.Bpunta)
                    if (BTgame)
                    {
                        Tgame.start();
                        BTgame = false;
                    }

                if (e.type == SDL_QUIT)
                {
                    running = false;
                    playing = false;
                }
            }

            FPS.update();
            if (FPS.fps != FPSprec)
            {
                ssFPS.str("");
                ssFPS << "FPS: ";
                ssFPS << FPS.fps;
                //if (tempo.now('m') % 100 == 0)
                //{
                    surface = TTF_RenderText_Solid(fontFPS, ssFPS.str().c_str(), textColor);
                    textureFPS = SDL_CreateTextureFromSurface(renderer, surface);
                    rect_FPS = { 0, ph / 6, surface ? surface->w : 0, surface ? surface->h : 0 };
                    SDL_FreeSurface(surface);
                //}
            }
            FPSprec = FPS.fps;

            if(Tgame.now('m')!=0) clone.prc.push_back({player.x(), player.y()});
            if((int)MovOriz >= (screen.w - player.rect.w) / 2 && freccia.angle >= 0 && freccia.angle < 180) freccia.Tx.stop();
            if((int)MovOriz <= -(screen.w - player.rect.w) / 2 && !(freccia.angle >= 0 && freccia.angle < 180)) freccia.Tx.stop();
            if((int)MovVert >= (screen.h - player.rect.w) / 2 && freccia.angle >= 90 && freccia.angle < 270) freccia.Ty.stop();
            if((int)MovVert <= -(screen.h - player.rect.w) / 2 && !(freccia.angle >= 90 && freccia.angle < 270)) freccia.Ty.stop();
            freccia.movimento(MovOriz, MovVert, velocita);
            player.rect.x = screen.w / 2 + MovOriz - 25;
            player.rect.y = screen.h / 2 + MovVert - 25;

            if ( Tgame.now('s') % 3 == 0 &&  Tgame.now('s') != 0 && Bclone) {Bclone = false; clone.AddClone();}
            if (Tgame.now('s') % 3 == 1) Bclone = true;

            clone.GameOver(playing, player);

            if(pausa.pausing) SDL_SetRenderTarget(renderer, pausa.TXRsfondo);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &player.rect);
            clone.Stampa(velocita);
            if (textureFPS && avanzate) SDL_RenderCopy(renderer, textureFPS, nullptr, &rect_FPS);
            if(pausa.pausing) SDL_SetRenderTarget(renderer, NULL);
            freccia.stampa();
            pausa.stampa();
            SDL_RenderPresent(renderer);
        }
    }
    if (textureFPS)
        SDL_DestroyTexture(textureFPS);

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    TTF_Quit();
    SDL_Quit();

    return 0;
}