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
 * This is the internal header file, it is responsible for building the functions
 * that handle multi-platform compatibility and is meant for developers only.
 * This file will contain functions that will be handled as interfaces for the
 * actual user library, each function should be short and have one goal.
 * All the multi-platform handling should be done within the internal namespace
 * and NEVER in any other namespace.
 *
*/

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
    /**
     * @struct
     * Window size metrics.
     *
     * @example
     * @code
     * using namespace tgl::internal;
     * wsize_t window_size = get_term_size();
     * std::cout << "Terminal width: " << window_size.width << std::endl;
     * std::cout << "Terminal height: " << window_size.height << std::endl;
     * @endcode
     */
    typedef struct {
        size_t width;
        size_t height;
    } wsize_t;

    /**
     * @function
     * Runs a new "clear" child process based on the operating system.
     *
     * @example
     * @code
     * using namespace tgl::internal
     * clear_window(); // runs "clear" on linux and "cls" on windows.
     * @endcode
     */
    void clear_window();

    /**
     * @function
     * Returns the width and height of the current terminal.
     *
     * @return wsize_t
     *
     * @example
     * @code
     * using namespace tgl::internal;
     * wsize_t window_size = get_term_size();
     * std::cout << "Terminal width: " << window_size.width << std::endl;
     * std::cout << "Terminal height: " << window_size.height << std::endl;
     * @endcode
     */
    wsize_t get_term_size();

    /**
     * @function
     * Hides the terminal cursor.
     *
     * @example
     * @code
     * hide_cursor(); // the cursor is no longer visible.
     * show_cursor(); // the cursor is visible again.
     * @endcode
     */
    void hide_cursor();

    /**
     * @function
     * Shows the terminal cursor.
     *
     * @example
     * @code
     * hide_cursor(); // the cursor is no longer visible.
     * show_cursor(); // the cursor is visible again.
     * @endcode
     */
    void show_cursor();

    /**
     * @function
     * Moves the terminal cursor to the position `x` and `y`.
     * @param x
     * The x position on the screen.
     *
     * @param y
     * The y position on the screen.
     */
    void cursor_to(size_t x, size_t y);
} // namespace tgl::internal


#endif //TGL_INTERNAL_H
