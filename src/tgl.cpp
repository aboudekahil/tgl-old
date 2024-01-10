//
// Created by aboud on 1/4/2024.
//

#include <cmath>
#include "tgl.h"

namespace tgl {

    Screen::Screen()
            : _term_size(get_term_size()),
              buffer(_term_size.height, std::vector<TPixel>(_term_size.width)),
              buffer2(_term_size.height, std::vector<TPixel>(_term_size.width))
              {}

    Screen::Screen(size_t width, size_t height)
            : _term_size({.width = width, .height = height}),
              buffer(_term_size.height, std::vector<TPixel>(_term_size.width)),
              buffer2(_term_size.height, std::vector<TPixel>(_term_size.width))
              {}

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
        bool steep = std::abs(y2 - y1) > std::abs(x2 - x1);
        if (steep) {
            std::swap(x1, y1);
            std::swap(x2, y2);
        }

        if (x1 > x2) {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }

        float dx = x2 - x1;
        float dy = std::abs(y2 - y1);
        float error = dx / 2.0f;
        int ystep = (y1 < y2) ? 1 : -1;
        int y = (int) y1;

        const int maxX = (int) x2;

        for (int x = (int) x1; x <= maxX; x++) {
            if (steep) {
                if (y >= 0 && y < buffer[0].size() && x >= 0 && x < buffer.size()) {
                    buffer[x][y] = pixel;
                }
            } else {
                if (x >= 0 && x < buffer[0].size() && y >= 0 && y < buffer.size()) {
                    buffer[y][x] = pixel;
                }
            }

            error -= dy;
            if (error < 0) {
                y += ystep;
                error += dx;
            }
        }
    }

    void Screen::drawRect(float x, float y, float w, float h, const TPixel &pixel) {
        drawLine(x, y, x + w, y, pixel);
        drawLine(x, y, x, y + h, pixel);
        drawLine(x, y + h, x + w, y + h, pixel);
        drawLine(x + w, y, x + w, y + h, pixel);
    }

    size_t Screen::get_width() const {
        return _term_size.width;
    }
    size_t Screen::get_height() const {
        return _term_size.height;
    }

    void Screen::swap_buffers() {
        std::swap(buffer, buffer2);
    }

}