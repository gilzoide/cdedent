/**
 * @file cdedent.h  Dedent functionality for removing common leading whitespace from every line in text.
 *
 * Dedent functions follow the same principles as Python's `textwrap.dedent`:
 *   - Removes any common leading whitespace from every line in text
 *   - Tabs and spaces are both treated as indentation, but they are not equal
 *   - Lines containing only whitespace are ignored in the input and normalized to a single newline character in the output
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

/**
 * Removes any common leading whitespace from every line in text.
 *
 * Tabs and spaces are both treated as whitespace, but they are not equal:
 * the lines "  hello" and "\thello" are considered to have no common leading whitespace.
 *
 * Lines containing only whitespace are ignored in the input and normalized to a single newline character in the output.
 *
 * If there is space in the output buffer, it will be null-terminated after storing all dedented text.
 *
 * @warning If the output size is not enough for storing all dedented text, it will NOT be null-terminated.
 * Use the return value and check if it's smaller than `output_size` if you're not sure it's big enough.
 *
 * @param text  The input text.
 * @param output_buffer  The output buffer, where dedented text will be stored.
 * @param output_size  The size of the output buffer.
 * @return Size of the dedented text copied into `output_buffer`. This size does not include added null characters.
 */
size_t dedent(const char *text, char *output_buffer, size_t output_size);

/**
 * Removes any common leading whitespace from every line in text, limited by the passed `text_size`.
 *
 * Tabs and spaces are both treated as whitespace, but they are not equal:
 * the lines "  hello" and "\thello" are considered to have no common leading whitespace.
 *
 * Lines containing only whitespace are ignored in the input and normalized to a single newline character in the output.
 *
 * If there is space in the output buffer, it will be null-terminated after storing all dedented text.
 *
 * @warning If the output size is not enough for storing all dedented text, it will NOT be null-terminated.
 * Use the return value and check if it's smaller than `output_size` if you're not sure it's big enough.
 *
 * @param text  The input text.
 * @param text_size  The size limit of the input text.
 *                   If you are sure `text` is null-terminated, it's safe to pass `SIZE_MAX` here.
 * @param output_buffer  The output buffer, where dedented text will be stored.
 * @param output_size  The size of the output buffer.
 * @return Size of the dedented text copied into `output_buffer`. This size does not include added null characters.
 */
size_t dedentn(const char *text, size_t text_size, char *output_buffer, size_t output_size);

/**
 * Removes any common leading whitespace from every line in text.
 *
 * Tabs and spaces are both treated as whitespace, but they are not equal:
 * the lines "  hello" and "\thello" are considered to have no common leading whitespace.
 *
 * Lines containing only whitespace are ignored in the input and normalized to a single newline character in the output.
 *
 * @warning The output is stored in the input `text` buffer itself, this is a destructive operation.
 *
 * @param text  The input/output text.
 * @return Size of the dedented text. This size does not include added null characters.
 */
size_t dedent_inplace(char *text);

/**
 * Removes any common leading whitespace from every line in text, limited by the passed `text_size`.
 *
 * Tabs and spaces are both treated as whitespace, but they are not equal:
 * the lines "  hello" and "\thello" are considered to have no common leading whitespace.
 *
 * Lines containing only whitespace are ignored in the input and normalized to a single newline character in the output.
 *
 * @warning The output is stored in the input `text` buffer itself, this is a destructive operation.
 *
 * @param text  The input/output text.
 * @param text_size  The size limit of the input text.
 *                   If you are sure `text` is null-terminated, it's safe to pass `SIZE_MAX` here.
 * @return Size of the dedented text. This size does not include added null characters.
 */
size_t dedentn_inplace(char *text, size_t text_size);

/**
 * Get the number of indent characters (spaces and tabs) in `line`.
 *
 * @param line  The line.
 * @return Number of indent characters in `line`.
 */
size_t get_indent_size(const char *line);

/**
 * Find the common indentation between all lines in the whole text.
 *
 * @warning The returned pointer alias memory inside `text`, so it will most likely NOT be null-terminated.
 * Pass a valid pointer to `out_common_indent_size` to get the common indent size.
 *
 * @param text  The text
 * @param out_common_indent_size  If not NULL, the size of the found common indent is stored in it.
 * @return Pointer to the common indent, if found. Returns NULL if there's no common indent.
 */
const char *get_common_indent(const char *text, size_t *out_common_indent_size);

/**
 * Find the common indentation between all lines in the text, limited by the passed `text_size`.
 *
 * @warning The returned pointer alias memory inside `text`, so it will most likely NOT be null-terminated.
 * Pass a valid pointer to `out_common_indent_size` to get the common indent size.
 *
 * @param text  The text
 * @param text_size  The size limit of the input text.
 *                   If you are sure `text` is null-terminated, it's safe to pass `SIZE_MAX` here.
 * @param out_common_indent_size  If not NULL, the size of the found common indent is stored in it.
 * @return Pointer to the common indent, if found. Returns NULL if there's no common indent.
 */
const char *get_common_indentn(const char *text, size_t text_size, size_t *out_common_indent_size);

#ifdef __cplusplus
}
#endif //  __cplusplus

#endif // __DEDENT_H__
