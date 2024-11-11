//
// Created by Jonathan on 05/11/2024.
//

#ifndef BRE_COLORS_HPP
#define BRE_COLORS_HPP

#include "../controller/components/Color.hpp"

namespace colors {

    const Color transparent = Color(0, 0, 0, 0);
    const Color white = Color("#FFFFFFFF");
    const Color red = Color("#C80815");
    const Color dark_gray = Color("#282828");
    const Color black = Color("#141414");


    const Color primary = Color("#FF6200EE");
    const Color primary_variant = Color("#FF3700B3");
    const Color secondary = Color("#FF03DAC5");
    const Color secondary_variant = Color("#FF018786");
    const Color background = Color("#141414");
    const Color surface = Color("#FFFFFFFF");
    const Color error = Color("#FFB00020");
    const Color on_primary = Color("#FFFFFFFF");
    const Color on_secondary = Color("#FF000000");
    const Color on_background = Color("#FF000000");
    const Color on_surface = Color("#FF000000");
    const Color on_error = Color("#FFFFFFFF");
    const Color on_pressed = Color(95, 95, 95, 95);

}

#endif //BRE_COLORS_HPP
