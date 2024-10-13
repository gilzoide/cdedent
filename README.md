# cdedent
Pure C implementation of Python's [textwrap.dedent](https://docs.python.org/3/library/textwrap.html#textwrap.dedent), with C++ wrappers.

Mostly useful to dedent C++ raw literal strings using the `_dedent` user defined literal suffix:
```cpp
#include <cdedent.hpp>

std::string dedented = R"(
    Here's an indented text.
    Dedenting it will remove the common indentation between all lines.

    Empty lines like the one above are ignored when searching for indentation.
    Also, if they do have any indentation, it is removed, so that empty lines
    don't have any whitespace in the output.
)"_dedent;
```


## Features
- Follows the same principles as Python's `textwrap.dedent`:
  + Removes any common leading whitespace from every line in text
  + Tabs and spaces are both treated as indentation, but they are not equal
  + Lines containing only whitespace are ignored in the input and normalized to a single newline character in the output
- Easy to build, there are only 2 source files to compile: `cdedent.c` and `cdedent.cpp`.
- The implementation does no heap allocations: data is copied directly to the provided output buffer.
- Supports dedenting a string inplace, overwriting the provided text buffer.
- Supports maximum text size, for processing string views.
- C++ wrappers that return `std::string`.
- C++ user defined literal suffix `_dedent`, so you can dedent string literals more easily (requires compiling with C++11)


## Integrating with CMake
```cmake
# Import project and link the `cdedent` library to your target
add_subdirectory(cdedent)
target_link_libraries(my_target cdedent)

# Optional: setup C++ standard used to compile cdedent
# C++11 is necessary for `_dedent` user defined literal
# C++17 is necessary for overload accepting `std::string_view`
target_compile_features(cdedent PRIVATE cxx_std_17)
```


## Building a library
```sh
# Build using CMake
# In this example, we build a static library in Release mode
cmake . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF
cmake --build build

# voilà, there should be a `build/libcdedent.a` file there
# (the extension may be different and there may be no "lib" prefix on some platforms)
ls build/libcdedent.a
```
