[![Build Status](https://travis-ci.org/ktbarrett/hdltypes.svg?branch=master)](https://travis-ci.org/ktbarrett/hdltypes)
[![Documentation Status](https://readthedocs.org/projects/hdltypes/badge/?version=latest)](https://hdltypes.readthedocs.io/en/latest/?badge=latest)


# hdltypes

A collection of datatypes and utility functions written in modern C++ that bit-accurately model HDL datatypes.
These types are design to be intuitive to use, consistent, and performant.

## Contributing

Feel free to contribute! Documentation, bug reports, feature requests, anything at all.

- If you have a question or need help using the library, open an issue.
- If you have found a bug, please open an issue before creating a pull request.
- Small pull requests may be accepted without creating an issue.
- If you have a big change you want to make, please create an issue and discuss it with maintainers first.

If you have any private inquiries, feel free to [email me](mailto:dev.ktbarrett@gmail.com) directly.

## Overview

hdltypes uses VHDL's datatypes for inspiration;
VHDL's datatypes are very well designed, intuitive to use, and are battle proven (literally in some cases).
We list each of the core datatypes and their main features below.

#### `Logic`

Can represent `0`, `1`, high impedance (`Z`), weak values (`L` and `H`), or indeterminate values (`X`, `U`, and `-`) that can occur in hardware.
Supports logic operations like "and", "or", "xor", and "negate".

Equivalent to VHDL's `std_logic`.

```c++
Logic mux2(Logic a, Logic b, Logic sel)
{
    return (a & ~sel) | (b & sel);
}
```

#### `Bit`

A type similar to `Logic`, but can represent only `0` or `1`.
Supports similar operations to `Logic`.
Can be used in operations with `Logic`, where it is implicitly upcasted to a `Logic`.

Similar to VHDL's `bit`.
VHDL's `bit` is not a subtype of `std_logic` like one would expect, so hdltypes has better behavior in this regard.

```c++
void full_adder(Bit a, Bit b, Bit c_in, Bit& r, Bit& c_out)
{
    const auto t = a ^ b;
    r = t ^ c_in;
    c_out = (a & b) | (t & c_in);
}
```

#### `Vector<>`

A templated sequential container type that support VHDL's arrays semantics.
Like VHDL, `Vector<>`s have "bounds" to support an arbitrary indexing scheme that can either be descending or ascending.
For example, a `Vector<>` instance could have the bounds (-4, 4).
If you index into that array with the index -4, you will get the leftmost element in the array.
Supports slicing the sequence and holding a mutable or immutable "views".

***Not Yet Implemented***

#### `LogicVector` and `BitVector`

Implemented as `Vector<Logic>`and `Vector<Bit>` respectively with additional operations.
Supports element-wise logic operations like "and", "or", "xor", and "negate".
Also supports reduction logic operations that "and", "or", or "xor" all elements of the vector together.

Similar to the relationship between `Logic` and `Bit`, `BitVector`s can be used in operation with `LogicVector`s.
In that case a `BitVector` will be implicitly upcast to a `LogicVector` with the same bounds.
This upcasting creates a new value, so views do not become invalid.

Roughly equivalent to VHDL's `std_logic_vector` and `bit_vector`, respectively.

***Not Yet Implemented***

#### `Unsigned` and `Signed`

Arbitrary-precision unsigned and two's complement fixed size integers, respectively.
Supports integer math operations like addition, multiplication, etc.
All operations which would exceed the available precision of the type wrap.
Values of these types cannot be indexed or sliced due to their implementation with integers; but this should radically improve performance.

Roughly equivalent to VHDL's `unsigned` and `signed` types.

***Not Yet Implemented***

#### `Ufixed` and `Sfixed`

Arbitrary-precision unsigned and two's complement fixed point numbers.
The bounds of these types are used to describe the number of integer and fractional bits in the fixed point format.
Unlike `Unsigned` and `Signed`, every integer operation on values of these type yields a value with bounds adjusted to prevent data loss.
To reduce the precision after an operation, the user must elect to lose data at that point by calling `resize`.
Values of these types cannot be indexed or sliced due to their implementation with integers; but this should radically improve performance.

Roughly equivalent to VHDL's `ufixed` and `sfixed` types.

***Not Yet Implemented***

#### `Float`

Arbitrary-precision software floating point values.
The bounds of these types are used to describe the number of mantissa and exponent bits.
The behavior of the type is a generalization of IEEE754.
Values of these types cannot be indexed or sliced due to their implementation with integers; but this should radically improve performance.

The performance will be much lower than builtin floating point types available to C++ like `float` and `double`.
However, results of floating-point operations will be bit-accurate for non-IEEE754 formats.

Roughly equivalent to VHDL's `float` type.

***Not Yet Implemented***

## Installation

### Using pip

The C++ library and Python wrapper can be built and installed as a Python package using pip.
See [pyhdltypes](https://github.com/ktbarrett/pyhdltypes) for details.
This method uses scikit-build to run the CMake build system if you are installing from source and not a prebuilt wheel.

#### Prerequisites

This package should build and be usable on any supported version of Python that is supported by pybind11.
It also requires a pip that supports PEP517 and scikit-build.

- Python 3.5+
- pip 10.0+

#### Installation

```command
pip install hdltypes
```

### Using CMake

#### Prerequisites

There isn't a reason this project shouldn't work on *any* platform where a C++14 compiler and CMake are available.
However, only Ubuntu 18.04 and Debian Sid are regularly tested. YMMV.

You will need:

- C++14 compiler
  - GCC 5.0+
  - Clang 3.4+
- CMake 3.14+

#### Build and Install

CMake is used to build the library and the tests.
To build and install the library, first clone the repo.

```command
git clone https://github.com/ktbarrett/hdltypes
```

Configure the project

```command
cmake -S hdltypes -B build
```

Build the project

```command
cmake --build build
```

Then you can install the library to your system.

```command
cmake --install build
```

#### Additional Configuration

If you wish to change the installation prefix, append `-DCMAKE_INSTALL_PREFIX=/path/to/prefix/` to the configure command.

```command
cmake -S hdltypes -B build -DCMAKE_INSTALL_PREFIX=/path/to/prefix/
```

You can also enable debug mode by adding `-DCMAKE_BUILD_TYPE=Debug`.
Debug mode enables `assert`s, turns off optimization, and adds debug information useful to a debugger like gdb, or a runtime analyzer like valgrind.

```command
cmake -S hdltypes -B build -DCMAKE_BUILD_TYPE=Debug
```

If you have multiple C++ compilers on your system, note that CMake respects the `CC` and `CXX` environment variables.
For more info, read the [CMake documentation](https://cmake.org/cmake/help/latest/).

## Tests

Tests are implementing using the Catch2 framework and built with cmake.
The test application is not built by default.

To build the test, first folow the commands above for configuring the library. Then,

```command
cmake --build build --target test_hdltypes
```

Then you can run the tests

```command
./build/tests/test_hdltypes
```

Catch supports running individual tests, tests that match patterns, and more.
Interogate the built test executable for more information.

```command
./build/tests/test_hdltypes --help
```

## Using the Installed Library in Another C++ Project

When you install the library, hdltypes installs CMake configuration files to your system.
Once installed, you can include this library into your own CMake project with `find_package(hdltypes)`.
Then, you can link your targets against the `hdltypes::hdltypes` target to link your project with hdltypes.

Example CMakeLists.txt file:
```cmake
cmake_minimum_required(VERSION 3.1)
project(hdltypes_example)

# import hdltypes package
find_package(hdltypes)

add_executable(${PROJECT_NAME}
    "src/main.cpp")

# hdltypes package defines the hdltypes::hdltypes library target
target_link_libraries(${PROJECT_NAME}
    PRIVATE hdltypes::hdltypes)
```

The use of `add_subdirectory` and `FetchContent` is also supported, and uses the same `hdltypes::hdltypes` target.
You should probably use `EXCLUDE_FROM_ALL` in the call to `add_subdirectory`.

You can import the hdltypes library in your C++ code with `include "hdltypes.hpp"`.
All libraries are available in the `hdltypes` namespace.

Example C++ source.
```c++
#include "hdltypes.hpp"

using namespace hdltypes;


int main()
{
    auto a = '0'_l;
    auto b = '1'_b;
    return (a & b) == '0'_l;
}
```

## Scope

Initially the project will implement all the builtin types of VHDL, albiet with different names:

- `bit`
- `logic`
- `bit_vector`
- `logic_vector`
- `unsigned`
- `signed`
- `ufixed`
- `sfixed`
- `float`

There will be two version of each aggregate type, one with bounds being runtime values, and another with bounds being compile-time values.
The compile-time bounds will be implemented using non-type template parameters.
This will allow the compiler additional optimization opportunities while retaining the dynamicity and ease-of-use of runtime-bound types.

Scope may increase after initial support has been completed.
