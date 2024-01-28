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
*/

#include <cmath>
#include "tgl.h"

namespace tgl {

    bool Screen::m_isCursorVisible = true;

    Screen::Screen()
            : m_term_size(get_term_size()),
              m_buffer(m_term_size.width, m_term_size.height),
              m_buffer2(m_term_size.width, m_term_size.height) {}

    Screen::Screen(size_t width, size_t height)
            : m_term_size({.width = width, .height = height}),
              m_buffer(m_term_size.width, m_term_size.height),
              m_buffer2(m_term_size.width, m_term_size.height) {}

    void Screen::fill(const TPixel &pixel) {
        m_buffer.setAll(pixel);
    }

    void Screen::drawBuffer() const {
        internal::cursor_to(0, 0);
        for (size_t i = 0; i < m_buffer.height(); i++) {
            for (size_t j = 0; j < m_buffer.width(); j++) {
                auto pix = m_buffer.get(i, j);
                std::cout << pix.bg << pix.fg << pix.pixel;
            }
            std::cout << (i == m_term_size.height - 1 ? '\0' : '\n');
        }
    }

    void Screen::hideCursor() {
        internal::hide_cursor();
        m_isCursorVisible = false;
    }

    void Screen::showCursor() {
        internal::show_cursor();
        m_isCursorVisible = true;
    }

    void Screen::drawPixel(float x, float y, const TPixel &pixel) {
        int ix = static_cast<int>(x), iy = static_cast<int>(y);
        putPixel(ix, iy, pixel);
    }

    void Screen::draw() {
        drawBuffer();
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
        int y = static_cast<int>(y1);

        const int maxX = static_cast<int>(x2);

        for (int x = static_cast<int>(x1); x <= maxX; x++) {
            if (steep) {
                putPixel(y, x, pixel);
            } else {
                putPixel(x, y, pixel);
            }

            error -= dy;
            if (error < 0) {
                y += ystep;
                error += dx;
            }
        }
    }

    void Screen::drawRect(float x, float y, float w, float h, const TPixel &pixel) {
        drawStraightLine(x, y, x + w, y, pixel);
        drawStraightLine(x, y, x, y + h, pixel);
        drawStraightLine(x, y + h, x + w, y + h, pixel);
        drawStraightLine(x + w, y, x + w, y + h, pixel);
    }

    size_t Screen::width() const {
        return m_term_size.width;
    }

    size_t Screen::height() const {
        return m_term_size.height;
    }

    void Screen::swapBuffers() {
        std::swap(m_buffer, m_buffer2);
    }

    void Screen::drawStraightLine(float x1, float y1, float x2, float y2, const TPixel &pixel) {
        if (x1 == x2) {
            int ix = static_cast<int>(x1);
            int iy2 = static_cast<int>(y2);
            for (int y = static_cast<int>(y1); y <= iy2; ++y) {
                putPixel(ix, y, pixel);
            }
        } else if (y1 == y2) {
            int iy = static_cast<int>(y1);
            int ix2 = static_cast<int>(x2);
            for (int x = static_cast<int>(x1); x <= ix2; ++x) {
                putPixel(x, iy, pixel);
            }
        }
    }

    void Screen::putPixel(size_t x, size_t y, const TPixel &pixel) {
        if (x >= m_buffer.width() || y >= m_buffer.height())
            return;

        m_buffer.get(y, x) = pixel;
    }

    bool Screen::isCursorVisible() {
        return m_isCursorVisible;
    }

    void Screen::drawEllipse(float x, float y, float r1, float r2, const TPixel &pixel) {
        int wx, wy;
        int thresh;
        int asq = r1 * r1;
        int bsq = r2 * r2;
        int xa, ya;

        putPixel(x, y + r2, pixel);
        putPixel(x, y - r2, pixel);

        wx = 0;
        wy = r2;
        xa = 0;
        ya = asq * 2 * r2;
        thresh = asq / 4 - asq * r2;

        for (;;) {
            thresh += xa + bsq;

            if (thresh >= 0) {
                ya -= asq * 2;
                thresh -= ya;
                wy--;
            }

            xa += bsq * 2;
            wx++;

            if (xa >= ya)
                break;


            putPixel(x + wx, y - wy, pixel);
            putPixel(x - wx, y - wy, pixel);
            putPixel(x + wx, y + wy, pixel);
            putPixel(x - wx, y + wy, pixel);
        }

        putPixel(x + r1, y, pixel);
        putPixel(x - r1, y, pixel);

        wx = r1;
        wy = 0;
        xa = bsq * 2 * r1;

        ya = 0;
        thresh = bsq / 4 - bsq * r1;

        for (;;) {
            thresh += ya + asq;

            if (thresh >= 0) {
                xa -= bsq * 2;
                thresh = thresh - xa;
                wx--;
            }

            ya += asq * 2;
            wy++;

            if (ya > xa)
                break;

            putPixel(x + wx, y - wy, pixel);
            putPixel(x - wx, y - wy, pixel);
            putPixel(x + wx, y + wy, pixel);
            putPixel(x - wx, y + wy, pixel);
        }
    }
}
