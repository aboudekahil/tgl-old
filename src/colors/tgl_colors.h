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
    enum class FG {
        DEFAULT,

        RED,
        BLUE,
        GREEN,

        BLACK,
        WHITE,
    };

    /**
     * @enum
     * Background terminal colors.
     */
    enum class BG {
        DEFAULT,

        RED,
        BLUE,
        GREEN,

        BLACK,
        WHITE,
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
        std::string get_bg_color(colors::BG bgColors) {
            switch (bgColors) {
                case colors::BG::BLACK:
                    return "\033[40m";

                case colors::BG::WHITE:
                    return "\033[107m";

                case colors::BG::RED:
                    return "\033[41m";

                case colors::BG::BLUE:
                    return "\033[44m";

                case colors::BG::GREEN:
                    return "\033[42m";

                default:
                case colors::BG::DEFAULT:
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
        std::string get_fg_color(colors::FG fgColors) {
            switch (fgColors) {
                case colors::FG::BLACK:
                    return "\033[30m";

                case colors::FG::WHITE:
                    return "\033[97m";

                case colors::FG::RED:
                    return "\033[31m";

                case colors::FG::BLUE:
                    return "\033[34m";

                case colors::FG::GREEN:
                    return "\033[32m";

                default:
                case colors::FG::DEFAULT:
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
    std::ostream &operator<<(std::ostream &out, FG fgColors);

    /**
     * @operator
     * Prints the appropriate ANSI escape code depending on the provided
     * color.
     * @param out output stream
     * @param bgColors foreground color
     * @return output stream
     */
    std::ostream &operator<<(std::ostream &out, BG bgColors);
} // namespace tgl::colors

#endif //TGL_TGL_COLORS_H
