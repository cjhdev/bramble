/* Copyright (c) 2024 Cameron Harper
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

/// @file

#ifndef BRAMBLE_VERSION_H_INCLUDED
#define BRAMBLE_VERSION_H_INCLUDED

/** Version as string */
#define BRAMBLE_VERSION_STRING      "0.1.0"

/** Version as integer */
#define BRAMBLE_VERSION_NUMBER      1000
/** Version major number */
#define BRAMBLE_VERSION_MAJOR       0
/** Version minor number */
#define BRAMBLE_VERSION_MINOR       1
/** Version patch number */
#define BRAMBLE_VERSION_PATCH       0

#include <cstdint>

namespace Bramble {

    /** Get version string
     *
     * */
    constexpr const char *get_version_string()
    {
        return "0.1.0";
    }

    /** Get version integer
     *
     * */
    constexpr uint32_t get_version_number()
    {
        return 1000;
    }

    /** Get version major number
     *
     * */
    constexpr uint32_t get_version_major()
    {
        return 0;
    }

    /** Get version minor number
     *
     * */
    constexpr uint32_t get_version_minor()
    {
        return 1;
    }

    /** Get version patch number
     *
     * */
    constexpr uint32_t get_version_patch()
    {
        return 0;
    }
};

#endif

