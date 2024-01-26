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
 * 1/21/2024
 *
 * @headerfile
 * This is the internal header file, it is responsible for creating an matspan implementation.
 * An matspan is a continuous span in memory that will represent a multidimensional array.
 *
*/
#ifndef TGL_MATSPAN_H
#define TGL_MATSPAN_H

#include <cstddef>
#include <span>
#include <concepts>

namespace tgl::ds {

    /**
     * @class
     * Matspan is a 2d list abstraction used to create a continuous span of elements in
     * memory to be represented as a 2d array interface.
     *
     * @tparam T Type of element
     */
    template<typename T>
    class matspan {
    public:
        /**
         * @constructor
         *
         * no-arg constructor initializes array size to 0.
         */
        explicit matspan() : _width(0), _height(0), arr(nullptr), _size(0) {
        }

        /**
         * @constructor
         *
         * with-arg constructor initializes 2d array to width and column parameters.
         *
         * @param width columns count
         * @param height rows count
         */
        matspan(size_t width, size_t height)
                : _width(width), _height(height), arr(new T[width * height]), _size(width * height) {
        }

        /**
         * @constructor
         *
         * with-arg constructor initializes 2d array to width and column parameters.
         * Also initializes every element to defaultVal.
         *
         * @param width
         * @param height
         * @param defaultVal
         */
        matspan(size_t width, size_t height, const T &defaultVal)
                : _width(width), _height(height), arr(new T[width * height]), _size(width * height) {

            for (size_t i = 0; i < _size; ++i) {
                arr[i] = defaultVal;
            }
        }

        /**
         * @constructor
         *
         * move-constructor
         *
         * @param other
         */
        matspan(matspan<T> &&other) noexcept:
                _width(other._width), _height(other._height), arr(other.arr), _size(other.size()) {
            other.arr = nullptr;
        }

        /**
         * @destructor
         */
        ~matspan() {
            delete[] arr;
        }

        /**
         * @operator
         *
         * copy assignment operator
         *
         * @param other
         * @return
         */
        matspan<T> &operator=(const matspan<T> &other) {
            if (this == &other) return *this;

            _width = other._width;
            _height = other._height;
            _size = other._size;

            arr = new T[_size];

            std::copy(other.arr, other.arr + other._size, arr);

            return *this;
        }

        /**
         * @operator
         *
         * move assignment operator
         *
         * @param other
         * @return
         */
        matspan<T> &operator=(matspan<T> &&other) noexcept {
            if (this == &other) return *this;
            _width = other._width;
            _height = other._height;
            _size = other._size;

            arr = other.arr;

            other.arr = nullptr;

            return *this;
        }

        /**
         * @operator
         *
         * returns a reference to the element in the i-th row and j-th column.
         *
         * @param i
         * @param j
         * @return reference to the element
         */
        T &operator[](size_t i, size_t j) {
            return arr[j * _height + i];
        }

        /**
         * @operator
         *
         * returns a copy of the element in the i-th row and j-th column.
         *
         * @param i
         * @param j
         * @return copy of the value of the element
         */
        T operator[](size_t i, size_t j) const {
            return arr[j * _height + i];
        }

        /**
         * @method
         *
         * returns a reference to the element in the i-th row and j-th column.
         *
         * @param i
         * @param j
         * @return reference to the element
         */
        T &get(size_t i, size_t j) {
            return arr[j * _height + i];
        }

        /**
         * @method
         *
         * returns a copy of the element in the i-th row and j-th column.
         *
         * @param i
         * @param j
         * @return copy of the value of the element
         */
        T get(size_t i, size_t j) const {
            return arr[j * _height + i];
        }

        /**
         * @method
         *
         * set all the elements in the array to the value passed in.
         * @param content
         */
        void setAll(T content) {
            for (size_t i = 0; i < _size; ++i) {
                arr[i] = content;
            }
        }

        /**
         * @method
         *
         * getter for the size of the 1d array representing the 2d array.
         *
         * @return size of the 1d array
         */
        [[nodiscard]] size_t size() const {
            return _size;
        }

        /**
         * @method
         *
         * getter for the columns count of the 2d array.
         *
         * @return columns count of the 2d array
         */
        [[nodiscard]] size_t width() const {
            return _width;
        }

        /**
         * @method
         *
         * getter for the rows count of the 2d array.
         *
         * @return rows count of the 2d array
         */
        [[nodiscard]] size_t height() const {
            return _height;
        }

    private:
        size_t _width{};
        size_t _height{};
        T *arr;
        size_t _size{};
    };
} // namespace tgl::ds


#endif //TGL_MATSPAN_H
