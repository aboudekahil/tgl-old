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
 * This file is for the user interface. Everything here is meant to be used
 * by the whoever is interacting with the code.
*/

#ifndef TGL_TGL_H
#define TGL_TGL_H

#include <iostream>
#include <vector>
#include "internal/internal.h"
#include "colors/tgl_colors.h"

using namespace tgl::internal;

namespace tgl {

    /**
     * @struct
     * TPixel is the "pixel" of the terminal, each pixel has a character
     * representation, a foreground color and a background color.
     *
     * @example
     * @code
     * using namespace tgl;
     * auto red_black_a = TPixel{
     *  .fg=colors::FG_COLORS::FG_BLACK,
     *  .bg=colors::BG_COLORS:BG_RED,
     *  .pixel='a'
     *  }; // red background black text with 'a' character pixel.
     * @endcode
     */
    using TPixel = struct {
        colors::FG_COLORS fg;
        colors::BG_COLORS bg;
        char pixel;
    };

    /**
     * @class
     * Screen class is supposed to be your interface towards everything
     * rendering.
     */
    class Screen {
    public:
        /**
         * @contructor
         * With-arg constructor for the Screen class with specified wdth
         * and height.
         * @param width
         * @param height
         */
        Screen(size_t width, size_t height);

        /**
         * @constructor
         * No-arg constructor for the scrreen class. By defaults it takes
         * the entire terminal size as the size for the terminal.
         */
        Screen();

        /**
         * @method
         * Fill the entire screen with a certain pixel.
         * @param pixel The pixel the screen will be filled with.
         */
        void fill(const TPixel &pixel);

        /**
         * @method
         * Hides the terminal cursor.
         */
        static void hideCursor();

        /**
         * @method
         * Shows the terminal cursor.
         */
        static void showCursor();

        /**
         * @method
         * Draws a pixel on a certain position in the screen.
         *
         * @param x the pixel's x position.
         * @param y the pixel's y position.
         * @param pixel the pixel that will be drawn.
         */
        void drawPixel(float x, float y, TPixel pixel);

        /**
         * @method
         * Render your pixels on the terminal.
         */
        void draw();

        /**
         * @method
         * Draws a line in the terminal from point (x1, y1) to (x2, y2).
         *
         * @param x1 The starting x position for the line.
         * @param y1 The starting y position for the line.
         * @param x2 The ending x position for the line.
         * @param y2 The ending y position for the line.
         * @param pixel The pixel the line will be filled with.
         */
        void drawLine(float x1, float y1, float x2, float y2, const TPixel &pixel);

        /**
         * @method
         * Draws a rectangle of position (x, y) with width w and height h.
         *
         * @param x The starting x position for the rectangle.
         * @param y The starting y position for the rectangle.
         * @param w The width of the rectangle.
         * @param h The height of the rectangle.
         * @param pixel The pixels the rect will be outlined with.
         */
        void drawRect(float x, float y, float w, float h, const TPixel &pixel);

        /**
         * @method
         * @return
         * Width of screen.
         */
        [[nodiscard]]
        size_t get_width() const;

        /**
         * @method
         * @return
         * Height of screen.
         */
        [[nodiscard]]
        size_t get_height() const;

        /**
         * @method
         * swaps the internal buffers.
         */
        void swap_buffers();

    private:
        /**
         * @method
         * Draws the current buffer on the screen.
         */
        void drawBuffer() const;

        wsize_t _term_size;
        std::vector<std::vector<TPixel>> buffer;
        std::vector<std::vector<TPixel>> buffer2;

    };

} // namespace tgl

#endif //TGL_TGL_H
