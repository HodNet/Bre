//
// Created by Jonathan on 05/11/2024.
//

#ifndef BRE_DIMENS_HPP
#define BRE_DIMENS_HPP

namespace dimens {

    // Margins according to the Android guidelines
    constexpr float horizontal_margin = 16;
    constexpr float vertical_margin = 16;

    // sizes according to the Android documentation
    constexpr float navigation_bar_height = 48;

    // font sizes
    constexpr int small_text_font_size = 14;
    constexpr int medium_text_font_size = 18;
    constexpr int large_text_font_size = 24;
    constexpr int small_title_font_size = 30;
    constexpr int medium_title_font_size = 36;
    constexpr int large_title_font_size = 48;
    constexpr int extra_large_title_font_size = 60;
    constexpr int huge_title_font_size = 84;

    // file images sizes
    constexpr int not_found_file_width = 300;
    constexpr int not_found_file_height = 300;
    constexpr int button_background_file_width = 716;
    constexpr int button_background_file_height = 716;
    constexpr int pause_button_file_width = 256;
    constexpr int pause_button_file_height = 256;
    constexpr int pause_menu_background_file_width = 716;
    constexpr int pause_menu_background_file_height = 716;
    constexpr int resume_button_file_width = 96;
    constexpr int resume_button_file_height = 96;
    constexpr int restart_button_file_width = 144;
    constexpr int restart_button_file_height = 144;
    constexpr int exit_button_file_width = 96;
    constexpr int exit_button_file_height = 96;
    constexpr int cancel_button_file_width = 480;
    constexpr int cancel_button_file_height = 480;

    // button sizes
    constexpr int small_icon_button_size = 112;
    constexpr int large_icon_button_size = 224;

    // pause dialog sizes
    constexpr int pause_menu_background_width = 784;
    constexpr int pause_menu_background_height = 1344;

}

#endif //BRE_DIMENS_HPP
