//
// Created by Jonathan on 05/11/2024.
//

#ifndef BRE_COLOR_HPP
#define BRE_COLOR_HPP

#include <SDL3/SDL.h>

struct Color {
    int r;
    int g;
    int b;
    int a;

    Color() : r(0), g(0), b(0), a(0) {}
    Color(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}
    Color(const Color& c) : r(c.r), g(c.g), b(c.b), a(c.a) {}

    Color(const char* hex) : r(0), g(0), b(0), a(255) { // Default alpha to 255
        if (hex && hex[0] == '#') {
            size_t len = std::strlen(hex);
            if (len == 7) { // #RRGGBB
                sscanf(hex, "#%02x%02x%02x", &r, &g, &b);
            } else if (len == 9) { // #RRGGBBAA
                sscanf(hex, "#%02x%02x%02x%02x", &r, &g, &b, &a);
            }
        }
    }

    Color& operator=(const Color& c) {
        r = c.r;
        g = c.g;
        b = c.b;
        a = c.a;
        return *this;
    }

    SDL_Color toSDLColor() const {
        return { (Uint8) r, (Uint8) g, (Uint8) b, (Uint8) a };
    }
};

#endif //BRE_COLOR_HPP

