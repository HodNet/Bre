//
// Created by Jonathan on 05/11/2024.
//

#ifndef BRE_COLORS_HPP
#define BRE_COLORS_HPP

#include "../controller/components/Color.hpp"

namespace colors {

    const Color transparent = Color(0, 0, 0, 0);
    const Color semi_transparent_white = Color(95, 95, 95, 95);
    const Color white = Color("#FFFFFFFF");
    const Color red = Color("#C81028");
    const Color dark_red = Color("#7C0A02");
    const Color bordeaux = Color("#342424");
    const Color dark_gray = Color("#282828");
    const Color black = Color("#141414");


    //const Color primary = Color("#FF6200EE");
    //const Color primary_variant = Color("#FF3700B3");
    //const Color secondary = Color("#FF03DAC5");
    //const Color secondary_variant = Color("#FF018786");
    const Color background = dark_gray;
    const Color danger = dark_red;
    const Color on_error = dark_red;
    const Color on_pressed = semi_transparent_white;

}

#endif //BRE_COLORS_HPP
