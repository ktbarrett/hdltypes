[![Build Status](https://travis-ci.org/ktbarrett/hdltypes.svg?branch=master)](https://travis-ci.org/ktbarrett/hdltypes)

# hdltypes

A collection of datatypes and utility functions written in modern C++ that can be used to model HDL code.
This project aims to create a set of datatypes that are intuitive to use, consistent, and performant.

A [Python wrapper](https://github.com/ktbarrett/pyhdltypes) around this library in being developed in tandem.

## Contributing

Feel free to contribute!
If you have a question or need help using the library, open an issue.
If you have found a bug, please open an issue before creating a pull request.
Small pull requests may be accepted without an issue, but if you have a big change planned please create an issue first and discuss it with maintainers.

If you have any private inquiries, feel free to [email me](mailto:dev.ktbarrett@gmail.com) directly.

## Overview

?????????
- uses VHDL datatypes as inspiration
- value semantics rather than container semantics
- code snippet?

## Installation

### Prerequisites

There isn't a reason this project shouldn't work on *any* platform where a C++14 compiler and CMake are available.
However, only Ubuntu 18.04 and Debian Sid are regularly tested. YMMV.

- C++14 compiler
  - GCC 5.0
  - clang 3.4
- cmake 3.1
- git

### Build and Install

CMake is used to build the library and the tests.
To build and install the library, first clone the repo.

```bash
git clone https://github.com/ktbarrett/hdltypes -b latest
```

Create build directory and enter it.

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

If you wish to change the installation prefix, append `-DCMAKE_INSTALL_PREFIX=/path/to/install/root/` to the configure command.

```bash
cmake ../hdltypes -DCMAKE_INSTALL_PREFIX=/home/you/prefix/
```

You can also enable debug mode by adding `-DCMAKE_BUILD_TYPE=Debug`.
Debug mode enables `assert`s, turns off optimization, and adds debug information useful to a debugger like gdb, or a runtime analyzer like valgrind.

```bash
cmake ../hdltypes -DCMAKE_BUILD_TYPE=Debug
```

If you have multiple C++ compilers on your system, note that CMake respects the `CC` and `CXX` environment variables.
For more info, read the [cmake documentation](https://cmake.org/cmake/help/latest/).


### Test Application

Once the project is confgured, you can build and run the test application.
From your build directory:

```bash
cmake --build --target test_app .
./test_app
```

The test application is written with Catch2. `./test_app --help` should illustrate options you can pass to the test application.
See [Catch2's documentation](https://github.com/catchorg/Catch2/blob/master/docs/command-line.md#top) on the subject for more details.

### Using the Installed Library in Another C++ Project

When you install the library, it also installs cmake configuration files to your system.
Once installed, you can include this library into your own cmake project with `find_package(hdltypes)`.
Then, you can link your targets against the `hdltypes::hdltypes` target to compile your project with hdltypes.

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
