/**
 * @file cdedent.h  Dedent functionality for removing common leading whitespace from every line in text.
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
#ifndef __DEDENT_H__
#define __DEDENT_H__

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif //  __cplusplus

size_t dedent(const char *text, char *output_buffer, size_t output_size);
size_t dedentn(const char *text, size_t text_size, char *output_buffer, size_t output_size);

size_t dedent_inplace(char *text);
size_t dedentn_inplace(char *text, size_t text_size);

size_t get_indent_size(const char *line);
const char *get_common_indent(const char *text, size_t *out_common_indent_size);
const char *get_common_indentn(const char *text, size_t text_size, size_t *out_common_indent_size);

#ifdef __cplusplus
}
#endif //  __cplusplus

#endif // __DEDENT_H__
