/**
 * @file cdedent.hpp  C++ wrappers for the C implementation of dedent.
 */
/*
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <http://unlicense.org/>
 */
#ifndef __DEDENT_HPP__
#define __DEDENT_HPP__

#include <string>

std::string dedent(const char *ctext);
std::string dedent(const char *ctext, size_t text_size);
std::string dedent(const std::string& text);
#ifdef __cpp_lib_string_view
std::string dedent(std::string_view text);
#endif // __cpp_lib_string_view

#ifdef __cpp_user_defined_literals
std::string operator""_dedent(const char *ctext, size_t text_size);
#endif // __cpp_user_defined_literals

void dedent_inplace(std::string& text);

#endif // __DEDENT_HPP__
