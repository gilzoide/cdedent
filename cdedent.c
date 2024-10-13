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
#include <stdint.h>
#include <string.h>

#include "cdedent.h"

static const char *__dedent_get_next_line(const char *text) {
	// skip content
	text += strcspn(text, "\r\n");
	// skip new lines
	text += strspn(text, "\r\n");
	return text;
}

static const char *__dedent_get_next_line_with_info(const char *text, size_t *content_size, size_t *newlines_size) {
	// skip whitespace
	text += strspn(text, " \t");
	// skip content
	text += (*content_size = strcspn(text, "\r\n"));
	// skip new lines
	text += (*newlines_size = strspn(text, "\r\n"));
	return text;
}

void __dedent_copy_bytes(char *dest, const char *src, size_t size) {
	if (dest != src) {
		memmove(dest, src, size);
	}
}

size_t get_indent_size(const char *line) {
	return strspn(line, " \t");
}

const char *get_common_indent(const char *text, size_t *out_common_indent_size) {
	return get_common_indentn(text, SIZE_MAX, out_common_indent_size);
}

const char *get_common_indentn(const char *text, size_t text_size, size_t *out_common_indent_size) {
	if (text == NULL || text_size == 0 || text[0] == '\0') {
		if (out_common_indent_size) {
			*out_common_indent_size = '\0';
		}
		return NULL;
	}

	const char *common_indent = NULL;
	size_t common_indent_size = 0;

	const char *line = text;
	while (line - text < text_size) {
		size_t indent_size = get_indent_size(line);
		if (line[indent_size] == '\0') {
			break;
		}

		// skip blank lines when deciding common indent, even if they are indented
		size_t immediate_newline_count = strspn(line + indent_size, "\r\n");
		if (immediate_newline_count > 0) {
			line += indent_size + immediate_newline_count;
			continue;
		}

		if (indent_size > 0) {
			if (common_indent) {
				if (indent_size < common_indent_size) {
					common_indent_size = indent_size;
				}
				// check what common indent and current line indent really have in common
				for (int i = 0; i < common_indent_size; i++) {
					if (common_indent[i] != line[i]) {
						common_indent_size = i;
						break;
					}
				}
			}
			else {
				common_indent_size = indent_size;
			}
			common_indent = line;
		}
		else {
			common_indent_size = 0;
		}
		if (common_indent_size == 0) {
			common_indent = NULL;
			break;
		}

		line = __dedent_get_next_line(line + indent_size);
	}

	if (out_common_indent_size) {
		*out_common_indent_size = common_indent_size;
	}
	return common_indent;
}

size_t dedent(const char *text, char *output_buffer, size_t output_size) {
	return dedentn(text, SIZE_MAX, output_buffer, output_size);
}

size_t dedentn(const char *text, size_t text_size, char *output_buffer, size_t output_size) {
	if (output_buffer == NULL || output_size == 0) {
		return 0;
	}

	if (text == NULL || text_size == 0 || text[0] == '\0') {
		*output_buffer = '\0';
		return 0;
	}

	// find common indent
	size_t common_indent_size;
	const char *common_indent = get_common_indentn(text, text_size, &common_indent_size);

	// copy data, skipping common indent and removing indentation from empty lines
	const char *line = text;
	size_t total_copied_bytes = 0;
	for (size_t remaining_text = text_size; output_size > 0 && remaining_text > 0 && *line != '\0'; ) {
		// here it is: skip the common indent!
		if (common_indent_size > 0 && strncmp(line, common_indent, common_indent_size) == 0) {
			line += common_indent_size;
		}

		size_t content_size, newlines_size;
		const char *next_line = __dedent_get_next_line_with_info(line, &content_size, &newlines_size);
		size_t copy_size = next_line - line;
		if (copy_size > output_size) {
			copy_size = output_size;
		}
		if (copy_size > remaining_text) {
			copy_size = remaining_text;
		}
		// line has some content, copy it over
		if (content_size > 0) {
			__dedent_copy_bytes(output_buffer, line, copy_size);
			output_buffer += copy_size;
			output_size -= copy_size;
			total_copied_bytes += copy_size;
		}
		// empty line, skip any indentation but copy newline characters ('\r' and '\n')
		else if (newlines_size > 0) {
			__dedent_copy_bytes(output_buffer, line + copy_size - newlines_size, newlines_size);
			output_buffer += newlines_size;
			output_size -= newlines_size;
			total_copied_bytes += newlines_size;
		}
		// EOL, bail out
		else {
			break;
		}
		remaining_text -= copy_size;
		line = next_line;
	}

	if (output_size > 0) {
		*output_buffer = '\0';
	}

	return total_copied_bytes;
}

size_t dedent_inplace(char *text) {
	return dedent(text, text, SIZE_MAX);
}

size_t dedentn_inplace(char *text, size_t text_size) {
	return dedentn(text, text_size, text, text_size);
}
