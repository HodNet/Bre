//
// Created by jonat on 16/10/2020.
//

#ifndef BRE_FRECCIA_H
#define BRE_FRECCIA_H

#include <cmath>
//#include "Cronometro.h"

class Freccia
{
private:
    SDL_Renderer *renderer;
    SDL_Rect SRCcoda{0, 0, 54, 55};
    SDL_Rect SRCcorpo{0, 0, 54, 362};
    SDL_Rect SRCpunta{0, 0, 54, 54};
    SDL_Rect DSTcoda{0, 0, 26, 26};
    SDL_Rect DSTcorpo{0, 0, 26, 1};
    SDL_Rect DSTpunta{0, 0, 26, 26};
    SDL_Texture *TXRcoda;
    SDL_Texture *TXRcorpo;
    SDL_Texture *TXRpunta;
    float x0 = 0;
    float y0 = 0;
    float *x = nullptr;
    float *y = nullptr;

public:
    float angle;
    float *RadAngle = nullptr;
    Cronometro Tx;
    Cronometro Ty;
    bool Bcoda = false;
    bool Bpunta = false;

    Freccia(SDL_Renderer *renderer) : renderer(renderer)
    {
        TXRcoda = IMG_LoadTexture(renderer, "center_arrow.png");
        TXRcorpo = IMG_LoadTexture(renderer, "corpo freccia.png");
        TXRpunta = IMG_LoadTexture(renderer, "punta freccia.png");
        if (TXRcoda == NULL || TXRcorpo == NULL || TXRpunta == NULL) SDL_Log("problemi con texture della freccia: %s", SDL_GetError());
    }

    void NewRenderer(SDL_Renderer *renderer)
    {
        this->renderer = renderer;
        TXRcoda = IMG_LoadTexture(renderer, "center_arrow.png");
        TXRcorpo = IMG_LoadTexture(renderer, "corpo freccia.png");
        TXRpunta = IMG_LoadTexture(renderer, "punta freccia.png");
        if (TXRcoda == NULL || TXRcorpo == NULL || TXRpunta == NULL) SDL_Log("problemi con texture della freccia: %s", SDL_GetError());
    }

    void BuildCoda(int ex, int ey)
    {
        DSTcoda.x = ex;
        DSTcoda.y = ey;
        Bcoda = true;
    }

    void BuildPunta(int ex, int ey)
    {
        if(Bcoda)
        {
            Bpunta = true;
            DSTpunta.x = DSTcoda.x + (ex - DSTcoda.x)/2;
            DSTpunta.y = DSTcoda.y + (ey - DSTcoda.y)/2;
            DSTcorpo.h = 2*sqrt(pow(DSTpunta.x - DSTcoda.x, 2) + pow(DSTpunta.y - DSTcoda.y, 2));
            DSTcorpo.x = DSTcoda.x;
            DSTcorpo.y = DSTcoda.y + DSTcoda.h/2 - DSTcorpo.h/2;
            RadAngle = new float{atan((float)(DSTpunta.x - DSTcoda.x) / (float)(DSTcoda.y - DSTpunta.y))};
            if(DSTpunta.y > DSTcoda.y) *RadAngle+=M_PI;
            angle = *RadAngle * 180 / M_PI;
            Tx.start();
            Ty.start();
            y0 = *y;
            x0 = *x;
        }
    }

    void movimento(float &x, float &y, int velocita)
    {
        if(Bcoda)
        {
            this->x = &x;
            this->y = &y;
        }
        if(RadAngle && (*RadAngle >= 0 || *RadAngle < 0))
        {
            x = x0 + velocita * Tx.now('m') * (float)sin(*RadAngle) / 10.0f;
            y = y0 - velocita * Ty.now('m') * (float)cos(*RadAngle) / 10.0f;
        }
    }

    void stampa()
    {
        if(Bcoda)
        {
            SDL_RenderCopy(renderer, TXRcoda, &SRCcoda, &DSTcoda);
            if(Bpunta)
            {
                SDL_RenderCopyEx(renderer, TXRpunta, &SRCpunta, &DSTpunta, angle, NULL, SDL_FLIP_NONE);
                SDL_RenderCopyEx(renderer, TXRcorpo, &SRCcorpo, &DSTcorpo, angle, NULL, SDL_FLIP_NONE);
            }
        }
    }

    void destroy()
    {
        Bcoda = false;
        Bpunta = false;
    }
};

#endif //BRE_FRECCIA_H
