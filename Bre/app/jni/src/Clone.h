//
// Created by jonat on 25/10/2020.
//

#ifndef BRE_CLONE_H
#define BRE_CLONE_H

struct   percorso
{
    short int x;
    short int y;
};

struct CLONE
{
    SDL_rettangolo rett;
    int n=0;
};
/*
int sommatoria(std::vector<CLONE> *clone, int N)
{
    int risultato = 0;
    while(N>0)
    {
        risultato += clone->at(N-1).frame_dal_clone_prec;
        N--;
    }
    return risultato;
}*/

class Clone
{
    SDL_Renderer *renderer;
    std::stringstream ssclone;
    SDL_Surface *SRFscore;
    SDL_Texture* TXRscore;
    SDL_Rect DSTscore;
    TTF_Font* TTFscore = TTF_OpenFontRW(SDL_RWFromFile("OpenSans-Regular.ttf", "rb"), 1, 84);
    std::vector<CLONE> clone;
    int w;
    int h;
    unsigned short int ph;
    unsigned short int pw;
    unsigned short int frame_fra_ogni_clone;

public:
    std::vector<percorso> prc;

    Clone(SDL_Renderer *renderer, int screen_w, int screen_h) : renderer(renderer), w(screen_w), h(screen_h)
    {
        ph = h / 10;
        pw = w / 10;
        ssclone << 0;
        if (!TTFscore) SDL_Log("Could not load font %s\n", SDL_GetError());
        SRFscore = TTF_RenderText_Solid(TTFscore, ssclone.str().c_str(), {255, 255, 255});
        TXRscore = SDL_CreateTextureFromSurface(renderer, SRFscore);
        DSTscore = {(w / 2 - SRFscore->w / 2), ph / 4, SRFscore->w, SRFscore->h };
        if (!TXRscore) SDL_Log("problemi con texture dello score: %s", SDL_GetError());
        SDL_FreeSurface(SRFscore);
    }

    void NewRenderer(SDL_Renderer *renderer)
    {
        SDL_Surface *surface = TTF_RenderText_Solid(TTFscore, ssclone.str().c_str(), {255, 255, 255});
        TXRscore = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    void AddClone()
    {
        clone.push_back({w/2 - pw/4, h/2 - pw/4, pw/2, pw/2});
        clone.back().n = clone.size();
        if(clone.size()==1) frame_fra_ogni_clone = prc.size();
        ssclone.str("");
        ssclone << clone.size();
        SDL_Surface *surface = TTF_RenderText_Solid(TTFscore, ssclone.str().c_str(), {255, 255, 255});
        TXRscore = SDL_CreateTextureFromSurface(renderer, surface);
        DSTscore = {(w / 2 - surface->w / 2), ph / 5, surface->w, surface->h };
        SDL_FreeSurface(surface);
    };

    void GameOver(bool &playing, SDL_rettangolo player)
    {
        for (auto c : clone)
        {
            if ((player.x() >= c.rett.x() && player.x() <= c.rett.fx() && player.y() >= c.rett.y() && player.y() <= c.rett.fy()) ||
                (player.fx() >= c.rett.x() && player.fx() <= c.rett.fx() && player.y() >= c.rett.y() && player.y() <= c.rett.fy()) ||
                (player.x() >= c.rett.x() && player.x() <= c.rett.fx() && player.fy() >= c.rett.y() && player.fy() <= c.rett.fy()) ||
                (player.fx() >= c.rett.x() && player.fx() <= c.rett.fx() && player.fy() >= c.rett.y() && player.fy() <= c.rett.fy()))
            {
                playing = false;
            }
        }
    }

    void Stampa(int velocita)
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        for (auto& x : clone)
        {
            if((prc.size() - frame_fra_ogni_clone*x.n) < 1000000000)
            {
                x.rett.rect.x = prc[prc.size() - frame_fra_ogni_clone * x.n].x;
                x.rett.rect.y = prc[prc.size() - frame_fra_ogni_clone * x.n].y;
            }
            SDL_RenderFillRect(renderer, &x.rett.rect);
        }
        if (TXRscore) SDL_RenderCopy(renderer, TXRscore, nullptr, &DSTscore);
    }
};

#endif //BRE_CLONE_H
