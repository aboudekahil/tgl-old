/**
 * @copyright
 * MIT License
 * Copyright (c) 2024 aboude
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @author
 * ABOUDE KAHIL
 *
 * @date
 * 1/10/2024
 *
 * @headerfile
 * This is the color related header file, it is responsible for providing the
 * user a color interface using a class enum for possible terminal colors.
 *
*/

#ifndef TGL_TGL_COLORS_H
#define TGL_TGL_COLORS_H

#include <ostream>

namespace tgl::colors {


    /**
     * @enum
     * Foreground terminal colors.
     */
    enum class FG_COLORS {
        FG_DEFAULT,

        FG_RED,
        FG_BLUE,
        FG_GREEN,

        FG_BLACK,
        FG_WHITE,
    };

    /**
     * @enum
     * Background terminal colors.
     */
    enum class BG_COLORS {
        BG_DEFAULT,

        BG_RED,
        BG_BLUE,
        BG_GREEN,

        BG_BLACK,
        BG_WHITE,
    };


    namespace {
        /**
         * @function
         * A big switch statement responsible for turning the corresponding enum to the appropriate
         * ANSI Escape character.
         * @param bgColors
         * @return
         * The appropriate ANSI Escape character.
         */
        std::string get_bg_color(colors::BG_COLORS bgColors) {
            switch (bgColors) {
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

        /**
         * @function
         * A big switch statement responsible for turning the corresponding enum to the appropriate
         * ANSI Escape character.
         * @param fgColors
         * @return
         * The appropriate ANSI Escape character.
         */
        std::string get_fg_color(colors::FG_COLORS fgColors) {
            switch (fgColors) {
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

    /**
     * @operator
     * Prints the appropriate ANSI escape code depending on the provided
     * color.
     * @param out output stream
     * @param fgColors foreground color
     * @return output stream
     */
    std::ostream &operator<<(std::ostream &out, FG_COLORS fgColors);

    /**
     * @operator
     * Prints the appropriate ANSI escape code depending on the provided
     * color.
     * @param out output stream
     * @param bgColors foreground color
     * @return output stream
     */
    std::ostream &operator<<(std::ostream &out, BG_COLORS bgColors);
} // namespace tgl::colors

#endif //TGL_TGL_COLORS_H
