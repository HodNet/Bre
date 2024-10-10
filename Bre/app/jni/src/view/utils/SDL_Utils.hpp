//
// Created by Jonathan on 09/10/2024.
//

#ifndef BRE_SDL_UTILS_HPP
#define BRE_SDL_UTILS_HPP

class SDL_Utils {
public:
    static void SDL_ConvertCoordinatesForVerticalOrientation(int &x, int &y, int screen_height) {
        if(y<0 || y>screen_height)
            return;

        y = screen_height - y;
    }

    static void SDL_ConvertCoordinatesForRendering(SDL_FRect &rect, int screen_height) {
        if(rect.y<0 || rect.y>screen_height)
            return;

        rect.y = screen_height - rect.y;
    }

    static void SDL_ConvertAngleForRendering(double &angle) {
        angle = 360 - angle;
    }
};

#endif //BRE_SDL_UTILS_HPP
