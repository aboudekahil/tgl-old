//
// Created by aboud on 1/4/2024.
//

#ifndef TGL_TGL_H
#define TGL_TGL_H

#include <iostream>
#include <vector>
#include "internal/internal.h"
#include "colors/tgl_colors.h"

using namespace tgl::internal;

namespace tgl {

    typedef struct {
        colors::FG_COLORS fg;
        colors::BG_COLORS bg;
        char pixel;
    } TPixel;

    class Screen {
    public:
        Screen(size_t width, size_t height);

        Screen();

        void fill(const TPixel &pixel);

        static void hideCursor() ;

        static void showCursor() ;

        void drawPixel(float x, float y, TPixel pixel);

        void draw();

        void drawLine(float x1, float y1, float x2, float y2, const TPixel &pixel);
        void drawRect(float x, float y, float w, float h, const TPixel &pixel);

        size_t get_width() const;

        size_t get_height() const;

        void swap_buffers();

    private:
        void drawBuffer() const;

        wsize_t _term_size;
        std::vector <std::vector<TPixel>> buffer;
        std::vector <std::vector<TPixel>> buffer2;

    };

}

#endif //TGL_TGL_H
