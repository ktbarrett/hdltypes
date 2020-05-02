cmake_minimum_required(VERSION 3.12)

project(pyhdltypes
    VERSION 0.0.0
    DESCRIPTION "A library of datatypes modelled after types common in HDLs"
    HOMEPAGE_URL "https://github.com/ktbarrett/hdltypes")

include(GNUInstallDirs)

add_subdirectory(pybind11/)

find_package(hdltypes ${PROJECT_VERSION} REQUIRED)

pybind11_add_module(pyhdltypes src/hdltypes.cpp)
target_link_libraries(pyhdltypes
    PRIVATE hdltypes::hdltypes)
