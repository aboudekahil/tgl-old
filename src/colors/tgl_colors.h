//
// Created by aboud on 1/4/2024.
//

#ifndef TGL_TGL_COLORS_H
#define TGL_TGL_COLORS_H

#include <ostream>

namespace tgl::colors {


    enum class FG_COLORS {
        FG_DEFAULT,

        FG_RED,
        FG_BLUE,
        FG_GREEN,

        FG_BLACK,
        FG_WHITE,
    };

    enum class BG_COLORS {
        BG_DEFAULT,

        BG_RED,
        BG_BLUE,
        BG_GREEN,

        BG_BLACK,
        BG_WHITE,
    };


    namespace {
        std::string get_bg_color(colors::BG_COLORS color) {
            switch (color) {
                case colors::BG_COLORS::BG_BLACK:
                    return "\033[40m";

                case colors::BG_COLORS::BG_WHITE:
                    return "\033[107m";

                case colors::BG_COLORS::BG_RED:
                    return "\033[41m";

                case colors::BG_COLORS::BG_BLUE:
                    return "\033[44m";

                case colors::BG_COLORS::BG_GREEN:
                    return "\033[42m";

                default:
                case colors::BG_COLORS::BG_DEFAULT:
                    return "\033[49m";
            }
        }

        std::string get_fg_color(colors::FG_COLORS color) {
            switch (color) {
                case colors::FG_COLORS::FG_BLACK:
                    return "\033[30m";

                case colors::FG_COLORS::FG_WHITE:
                    return "\033[97m";

                case colors::FG_COLORS::FG_RED:
                    return "\033[31m";

                case colors::FG_COLORS::FG_BLUE:
                    return "\033[34m";

                case colors::FG_COLORS::FG_GREEN:
                    return "\033[32m";

                default:
                case colors::FG_COLORS::FG_DEFAULT:
                    return "\033[39m";
            }
        }
    }

    std::ostream &operator<<(std::ostream &out, FG_COLORS c);

    std::ostream &operator<<(std::ostream &out, BG_COLORS c);
}

#endif //TGL_TGL_COLORS_H
