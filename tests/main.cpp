#include <cassert>
#include <iostream>
#include <ostream>

#include "../cdedent.hpp"

#define test(text1, text2) \
	{ \
		std::string result = dedent(text1); \
		if (result != text2) { std::cerr << '"' << result << "\"(" << result.size() << ")" << std::endl; } \
		assert(result == text2); \
	}

int main() {
	test("text", "text");
	test("  text", "text");
	test("\ttext", "text");

#ifdef __cpp_user_defined_literals
	assert(dedent("text") == "text"_dedent);
	assert(dedent("  text") == "  text"_dedent);
	assert(dedent("\ttext") == "\ttext"_dedent);
#endif // __cpp_user_defined_literals
#ifdef __cpp_lib_string_view
	assert(dedent(std::string_view("text")) == "text");
#endif // __cpp_lib_string_view
	
	test((
		"line1"
		"\n"
		"line2"
	), (
		"line1"
		"\n"
		"line2"
	));
	test((
		"  line1"
		"\n"
		"  line2"
	), (
		"line1"
		"\n"
		"line2"
	));
	test((
		"\tline1"
		"\n"
		"\tline2"
	), (
		"line1"
		"\n"
		"line2"
	));
	
	test((
		"  line1"
		"\n"
		"\tline2"
	), (
		"  line1"
		"\n"
		"\tline2"
	));
	test((
		"\tline1"
		"\n"
		"  line2"
	), (
		"\tline1"
		"\n"
		"  line2"
	));
	
	
	test((
		"line1"
		"\n"
		"  line2"
	), (
		"line1"
		"\n"
		"  line2"
	));
	test((
		"  line1"
		"\n"
		"line2"
	), (
		"  line1"
		"\n"
		"line2"
	));

	std::cout << "All tests passed!" << std::endl;
	return 0;
}
