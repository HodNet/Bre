//
// Created by jonat on 16/10/2020.
//
#ifndef BRE_SDLFUNZIONI_H
#define BRE_SDLFUNZIONI_H
#include <sstream>

struct SDL_rettangolo
{
    SDL_Rect rect;
    char id = 0;
    short int x() { return rect.x; };
    short int y() { return rect.y; };
    unsigned short int fx() { return rect.x + rect.w; };
    unsigned short int fy() { return rect.y + rect.h; };
};

bool RectImp(SDL_rettangolo r, char& d, int *ex, int *ey)
{
    if (*ex >= r.x() && *ex <= r.fx() && *ey >= r.y() && *ey <= r.fy())
    {
        d = r.id;
        return true;
    }
    else return false;
}

bool RectImp(SDL_Rect R, int *ex, int *ey)
{
    SDL_rettangolo r{R};
    return *ex >= r.x() && *ex <= r.fx() && *ey >= r.y() && *ey <= r.fy();
}

template<typename t>
void SDL_Stampa(t obj)
{
    std::stringstream ss;
    ss << obj;
    SDL_Log("%s", ss.str().c_str());
}

#endif //BRE_SDLFUNZIONI_H
