//
// Created by aboud on 1/4/2024.
//

#ifndef TGL_INTERNAL_H
#define TGL_INTERNAL_H


#if defined(linux) || defined(__unix__)

#include <cstdio>
#include <sys/ioctl.h>
#include <unistd.h>

#elif defined(__WIN32__)

#include <windows.h>

#endif


namespace tgl::internal {
    typedef struct {
        size_t width;
        size_t height;
    } wsize_t;

    void clear_window();

    wsize_t get_term_size();

    void hide_cursor();

    void show_cursor();

    void cursor_to(size_t x, size_t y);
}


#endif //TGL_INTERNAL_H
