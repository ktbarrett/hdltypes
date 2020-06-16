cmake_minimum_required(VERSION 3.1)

## PROJECT #############################
########################################

project(hdltypes
    VERSION 0.0.0
    LANGUAGES CXX
    DESCRIPTION "A library of datatypes modelled after types common in HDLs"
    HOMEPAGE_URL "https://github.com/ktbarrett/hdltypes")

## INCLUDES ############################
########################################

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

## CONFIGURATIONS ######################
########################################

set(HDLTYPES_DONT_INSTALL_CMAKEFILES OFF CACHE BOOL "Don't install Config.cmake and Targets.cmake files")
set(HDLTYPES_DONT_INSTALL_HEADERS OFF CACHE BOOL "Don't install headers")
set(HDLTYPES_DONT_INSTALL_LIBRARIES OFF CACHE BOOL "Don't install built libraries")

set(HDLTYPES_CMAKEFILES_INSTALL_DIR "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake" CACHE PATH "Where to install Config.cmake and Target.cmake files")
set(HDLTYPES_HEADER_INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}" CACHE PATH "Where to install public headers")
set(HDLTYPES_LIBRARIES_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}" CACHE PATH "Where to install shared libraries")

## LIBRARIES ###########################
########################################

add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include/hdltypes/logic.hpp>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/hdltypes/logic.hpp>
        $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include/hdltypes.hpp>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/hdltypes.hpp>)
target_include_directories(${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_14)

## TESTS ###############################
########################################

add_executable(test_app
    EXCLUDE_FROM_ALL
    "${CMAKE_CURRENT_LIST_DIR}/test/main.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/test/logic.cpp")
target_include_directories(test_app
    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/test")
target_link_libraries(test_app
    PRIVATE ${PROJECT_NAME})

target_compile_options(test_app
    INTERFACE $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
          -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion>
     $<$<CXX_COMPILER_ID:MSVC>:
          /W4>)  # TODO care about Windows

## CONFIG AND TARGET CMAKE FILES #######
########################################

write_basic_package_version_file(${PROJECT_NAME}ConfigVersion.cmake
                                 VERSION ${PROJECT_VERSION}
                                 COMPATIBILITY ExactVersion)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION
  "${HDLTYPES_CMAKEFILES_INSTALL_DIR}")

export(
    TARGETS hdltypes
    NAMESPACE ${PROJECT_NAME}::
    FILE ${PROJECT_NAME}Targets.cmake)

## INSTALLATION ########################
########################################

if (NOT HDLTYPES_DONT_INSTALL_LIBRARIES)

    install(
        TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION "${HDLTYPES_LIBRARIES_INSTALL_DIR}")

endif()

if (NOT HDLTYPES_DONT_INSTALL_CMAKEFILES)

    install(
        FILES
            "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
            "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION "${HDLTYPES_CMAKEFILES_INSTALL_DIR}")

    install(
        EXPORT ${PROJECT_NAME}Targets
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION "${HDLTYPES_CMAKEFILES_INSTALL_DIR}")

endif()

if (NOT HDLTYPES_DONT_INSTALL_HEADERS)

    install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/hdltypes" DESTINATION "${HDLTYPES_HEADER_INSTALL_DIR}")
    install(FILES "${PROJECT_SOURCE_DIR}/include/hdltypes.hpp" DESTINATION "${HDLTYPES_HEADER_INSTALL_DIR}")

endif()
