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

    void hide_cursor() {
#if defined(__WIN32__) || defined(_WIN32) || _WIN32

        HANDLE hStdOut = nullptr;
        CONSOLE_CURSOR_INFO curInfo;

        hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleCursorInfo(hStdOut, &curInfo);
        curInfo.bVisible = FALSE;
        SetConsoleCursorInfo(hStdOut, &curInfo);
        std::cout << "\033[?25l";

#elif defined(linux) || defined(__unix__)

        std::cout << "\033[?25l";
#endif
    }

    void show_cursor() { std::cout << "\033[?25h"; }

    void cursor_to(size_t x, size_t y) { printf("\033[%zu;%zuH", x, y); }
}