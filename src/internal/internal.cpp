//
// Created by aboud on 1/4/2024.
//

#include <cstdlib>
#include <iostream>
#include "internal.h"

namespace tgl::internal {
    wsize_t get_term_size() {
        wsize_t window_size{};
#if defined(__WIN32__)
        CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  window_size.width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  window_size.height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#elif defined(linux) || defined(__unix__)
        struct winsize w{};
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        window_size.width = w.ws_col;
        window_size.height = w.ws_row;
#endif
        return window_size;
    }

    void clear_window() {

#if defined(__WIN32__)
        std::system("cls");
#elif defined(linux) || defined(__unix__)
        std::system("clear");
#endif
    }

    void hide_cursor() { std::cout << "\033[?25l"; }

    void show_cursor() { std::cout << "\033[?25h"; }

    void cursor_to(size_t x, size_t y) { printf("\033[%zu;%zuH", x, y); }
}