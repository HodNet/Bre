//
// Created by jonat on 30/10/2020.
//

#ifndef BRE_SDLPAUSA_H
#define BRE_SDLPAUSA_H

class Pausa
{
    SDL_Renderer *renderer;
    SDL_Rect SRCpausa{0, 0, 256, 256};
    SDL_Rect SRCLowSfondo{0, 0, 360, 100};
    SDL_Rect SRCUpSfondo{0, 0, 360, 100};
    SDL_Rect DSTpausa;
    SDL_Rect DSTLowSfondo;
    SDL_Rect DSTUpSfondo;
    SDL_Rect RECTsfondo;
    SDL_Texture *TXRpausa;
    SDL_Texture *TXRLowSfondo;
    SDL_Texture *TXRUpSfondo;
    int v;
    int w;
    int h;

public:
    SDL_Texture *TXRsfondo;
    bool pausing = false;

    Pausa(SDL_Renderer *renderer, int screen_w, int screen_h) : renderer(renderer), w(screen_w), h(screen_h)
    {
        v = h/640*2;
        DSTpausa = {w-(w/13), h/60, w/13, w/13};
        DSTLowSfondo = {0, h, w, h*100/640};
        DSTUpSfondo = {0, 0 - h*100/640, w, h*100/640};
        RECTsfondo = {0, 0, w, h};
        TXRpausa = IMG_LoadTexture(renderer, "pausa.png");
        TXRLowSfondo = IMG_LoadTexture(renderer, "Pausa sfondo basso.png");
        TXRUpSfondo = IMG_LoadTexture(renderer, "Pausa sfondo alto.png");
        TXRsfondo = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
        if (TXRpausa == NULL || TXRLowSfondo == NULL || TXRUpSfondo == NULL) SDL_Log("problemi con texture della pausa: %s", SDL_GetError());
    }

    void premuta(int *ex, int *ey, unsigned short int *FPS, Cronometro *tempi, int quantita_di_tempi)
    {
        if(RectImp(DSTpausa, ex, ey))
        {
            for(int i=0; i<quantita_di_tempi; i++) tempi[i].stop();
            pausing = true;
            SDL_Log("%s", "ciao");
        }
        SDL_Log("%s", "ciao2");
    }

    void run()
    {
        while(pausing)
        {
            if(DSTLowSfondo.y >= (h - h*100/640)) DSTLowSfondo.y-=v;
            if(DSTUpSfondo.y <= 0) DSTUpSfondo.y+=v;

            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, TXRsfondo, NULL, &RECTsfondo);
            SDL_RenderCopy(renderer, TXRLowSfondo, &SRCLowSfondo, &DSTLowSfondo);
            SDL_RenderCopy(renderer, TXRUpSfondo, &SRCUpSfondo, &DSTUpSfondo);
            SDL_RenderPresent(renderer);
        }
    }

    void stampa()
    {
        SDL_RenderCopy(renderer, TXRpausa, &SRCpausa, &DSTpausa);
    }
};

#endif //BRE_SDLPAUSA_H
