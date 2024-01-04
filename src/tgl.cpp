//
// Created by aboud on 1/4/2024.
//

#include <cmath>
#include "tgl.h"

namespace tgl {

    Screen::Screen()
            : _term_size(get_term_size()),
              buffer(_term_size.height, std::vector<TPixel>(_term_size.width)) {}

    Screen::Screen(size_t width, size_t height)
            : _term_size({.width = width, .height = height}),
              buffer(_term_size.height, std::vector<TPixel>(_term_size.width)) {}

    void Screen::fill(const TPixel &pixel) {
        buffer = std::vector<std::vector<TPixel>>(
                _term_size.height, std::vector<TPixel>(_term_size.width, pixel));
    }

    void Screen::drawBuffer() const {
        internal::cursor_to(0, 0);
        for (size_t i = 0; i < _term_size.height; i++) {
            for (size_t j = 0; j < _term_size.width; j++) {
                auto pix = buffer[i][j];
                std::cout << pix.bg << pix.fg << pix.pixel;
            }
            std::cout << (i == _term_size.height - 1 ? '\0' : '\n');
        }
    }

    void Screen::hideCursor() { internal::hide_cursor(); }

    void Screen::showCursor() { internal::show_cursor(); }

    void Screen::drawPixel(float x, float y, TPixel pixel) {
        int ix = std::round(x), iy = std::round(y);
        if (ix < 0 || ix >= buffer[0].size() || iy < 0 || iy >= buffer.size())
            return;

        buffer[iy][ix] = pixel;
    }

    void Screen::draw() {
#if !defined(DEBUG)
        drawBuffer();
#endif
    }

    void Screen::drawLine(float x1, float y1, float x2, float y2, const TPixel &pixel) {
        float maxx = std::max(x1, x2), minx = std::min(x2, x1);
        x1 = minx;
        x2 = maxx;

        float maxy = std::max(y1, y2), miny = std::min(y1, y2);
        y1 = miny;
        y2 = maxy;

        float dx = x2 - x1;
        float dy = y2 - y1;
        float D = 2 * dy - dx;
        float y = y1;

        for (float x = x1; x < x2; x++) {
            int ix = std::floor(x), iy = std::floor(y);

            if (!(ix < 0 || ix >= buffer[0].size() || iy < 0 || iy >= buffer.size()))
                buffer[iy][ix] = pixel;

            if (D > 0) {
                y++;
                D -= 2 * dx;
            }
            D += 2 * dy;
        }

    }

}
