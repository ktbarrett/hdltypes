[![Build Status](https://travis-ci.org/ktbarrett/hdltypes.svg?branch=master)](https://travis-ci.org/ktbarrett/hdltypes)

# hdltypes

A collection of datatypes and utility functions written in modern C++ that can be used to bit-accurately model HDL code that are intuitive to use, consistent, and performant.

A [Python wrapper](https://github.com/ktbarrett/pyhdltypes) around this library in being developed in tandem.

## Contributing

Feel free to contribute! Documentation, bug reports, feature requests, anything at all.

- If you have a question or need help using the library, open an issue.
- If you have found a bug, please open an issue before creating a pull request.
- Small pull requests may be accepted without creating an issue.
- If you have a big change you want to make, please create an issue and discuss it with maintainers first.

If you have any private inquiries, feel free to [email me](mailto:dev.ktbarrett@gmail.com) directly.

## Overview

hdltypes uses VHDL's datatypes for inspiration;
VHDL's datatypes are very well designed, intuitive to use, and are battle proven.
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

***Not Yet Implemented***

#### `LogicVector` and `BitVector`

Implemented as `Vector<Logic>`and `Vector<Bit>` respectively with additional operations.
Supports element-wise logic operations like "and", "or", "xor", and "negate".
Also supports reduction logic operations that "and", "or", or "xor" all elements of the vector together.
Supports slicing the sequence and holding a mutable or immutable "views".

Similar to the relationship between `Logic` and `Bit`, `BitVector`s can be used in operation with `LogicVector`s.
In that case a `BitVector` will be implicitly upcast to a `LogicVector` with the same bounds.

Roughly equivalent to VHDL's `std_logic_vector` and `bit_vector`, respectively.

***Not Yet Implemented***

#### `Unsigned` and `Signed`

Arbitrary-precision unsigned and two's complement fixed size integers, respectively.
It supports integer math operations like addition, multiplication, etc.
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
However, results of floating-point operations will be bit-accurate compared an implementation in VHDL.

Roughly equivalent to VHDL's `float` type.

***Not Yet Implemented***

## Installation

### Prerequisites

There isn't a reason this project shouldn't work on *any* platform where a C++14 compiler and CMake are available.
However, only Ubuntu 18.04 and Debian Sid are regularly tested. YMMV.

You will need:

- C++14 compiler
  - GCC 5.0+
  - clang 3.4+
- CMake 3.1+
- Git

### Build and Install

CMake is used to build the library and the tests.
To build and install the library, first clone the repo.

```bash
git clone https://github.com/ktbarrett/hdltypes -b latest
```

Create a build directory and enter it.

```bash
mkdir build && cd build
```

Configure the project.

```bash
cmake ../hdltypes
```

Then you can build and install the library to your system.

```bash
cmake --build .
cmake --install .
```

### Additional Configuration

If you wish to change the installation prefix, append `-DCMAKE_INSTALL_PREFIX=/path/to/prefix/` to the configure command.

```bash
cmake ../hdltypes -DCMAKE_INSTALL_PREFIX=/path/to/prefix/
```

You can also enable debug mode by adding `-DCMAKE_BUILD_TYPE=Debug`.
Debug mode enables `assert`s, turns off optimization, and adds debug information useful to a debugger like gdb, or a runtime analyzer like valgrind.

```bash
cmake ../hdltypes -DCMAKE_BUILD_TYPE=Debug
```

If you have multiple C++ compilers on your system, note that CMake respects the `CC` and `CXX` environment variables.
For more info, read the [CMake documentation](https://cmake.org/cmake/help/latest/).


### Test Application

Once the project is confgured, you can build and run the test application.
From your build directory:

```bash
cmake --build . --target test_app
./test_app
```

The test application is written with Catch2. `./test_app --help` should list options you can pass to the test application.
See [Catch2's documentation](https://github.com/catchorg/Catch2/blob/master/docs/command-line.md#top) on the subject for more details.

### Using the Installed Library in Another C++ Project

When you install the library, hdltypes installs Bit configuration files to your system.
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

You can import the hdltypes library in your code with `include "hdltypes.hpp"`.
All libraries are available in the `hdltypes` namespace.

Example C++ source.
```c++
#include "hdltypes/logic.hpp"

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
