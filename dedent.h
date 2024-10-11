/**
 * @file dedent.h  Dedent functionality for removing common leading whitespace from every line in text.
 */
#ifndef __DEDENT_H__
#define __DEDENT_H__

#include <limits.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif //  __cplusplus

size_t get_indent_size(const char *line);
const char *get_common_indent(const char *text, size_t *out_common_indent_size);
const char *get_common_indentn(const char *text, size_t text_size, size_t *out_common_indent_size);

size_t dedent(const char *text, char *output_buffer, size_t output_size);
size_t dedentn(const char *text, size_t text_size, char *output_buffer, size_t output_size);

size_t dedent_inplace(char *text);
size_t dedentn_inplace(char *text, size_t text_size);

#ifdef __cplusplus
}

#include <string>

std::string dedent(const char *ctext);
std::string dedent(const char *ctext, size_t text_size);
std::string dedent(const std::string& text);
#ifdef __cpp_user_defined_literals
std::string operator""_dedent(const char *ctext, size_t text_size);
#endif // __cpp_user_defined_literals
#ifdef __cpp_lib_string_view
std::string dedent(std::string_view text);
#endif // __cpp_lib_string_view
#endif //  __cplusplus

#endif // __DEDENT_H__


#ifdef DEDENT_IMPLEMENTATION

#ifdef __cplusplus
extern "C" {
#endif //  __cplusplus

static const char *__dedent_get_next_line(const char *text) {
	// skip content
	text += strcspn(text, "\r\n");
	// skip new lines
	text += strspn(text, "\r\n");
	return text;
}

static size_t __dedent_strcpy(char *output_buffer, size_t output_size, const char *text, size_t text_size) {
	// avoid copying data when running inplace, just return text length
	if (output_buffer == text) {
		return strlen(text);
	}

	// copy all bytes from text to output_buffer, respecting size limits
	if (text_size < output_size) {
		text_size = output_size;
	}
	int i;
	for (i = 0; text[i] && i < text_size; i++) {
		output_buffer[i] = text[i];
	}
	return i;
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
		return 0;
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

	// if there's no common indent, just copy `text` into `output_buffer`
	if (common_indent_size == 0) {
		return __dedent_strcpy(output_buffer, output_size, text, text_size);
	}

	// copy data, skipping indents
	const char *line = text;
	size_t total_copied_bytes = 0;
	for (size_t remaining_text = text_size; *line != '\0' && remaining_text; ) {
		// here it is: skip the common indent!
		if (common_indent_size && strncmp(line, common_indent, common_indent_size) == 0) {
			line += common_indent_size;
		}

		const char *next_line = __dedent_get_next_line(line);
		size_t copy_size = next_line - line;
		if (copy_size > output_size) {
			copy_size = output_size;
		}
		if (copy_size > remaining_text) {
			copy_size = remaining_text;
		}
		strncpy(output_buffer, line, copy_size);
		output_buffer += copy_size;
		output_size -= copy_size;
		remaining_text -= copy_size;
		total_copied_bytes += copy_size;
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

#ifdef __cplusplus
}

std::string dedent(const char *ctext) {
	return dedent(std::string(ctext));
}

std::string dedent(const char *ctext, size_t text_size) {
	return dedent(std::string(ctext, text_size));
}

std::string dedent(const std::string& text) {
	std::string text_copy(text);
	size_t result_size = dedentn_inplace((char *) text_copy.data(), text_copy.size());
	text_copy.resize(result_size);
	return text_copy;
}

#ifdef __cpp_user_defined_literals
std::string operator""_dedent(const char *ctext, size_t text_size) {
	return dedent(ctext, text_size);
}
#endif // __cpp_user_defined_literals
#ifdef __cpp_lib_string_view
std::string dedent(std::string_view text) {
	std::string text_copy(text);
	size_t result_size = dedentn_inplace((char *) text_copy.data(), text_copy.size());
	text_copy.resize(result_size);
	return text_copy;
}
#endif // __cpp_lib_string_view
#endif //  __cplusplus

#endif // DEDENT_IMPLEMENTATION
