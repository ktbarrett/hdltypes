cmake_minimum_required(VERSION 3.14)

file(READ "${CMAKE_CURRENT_LIST_DIR}/version" hdltypes_VERSION)

project(
  hdltypes
  VERSION "${hdltypes_VERSION}"
  LANGUAGES CXX
  DESCRIPTION "C++ and Python datatype library based on VHDL's types"
  HOMEPAGE_URL "https://github.com/ktbarrett/hdltypes")

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(FetchContent)

add_library(${PROJECT_NAME} INTERFACE)

configure_file(
  "${${PROJECT_NAME}_SOURCE_DIR}/templates/include/hdltypes/version.hpp.in"
  "${${PROJECT_NAME}_BINARY_DIR}/include/hdltypes/version.hpp")

target_sources(
  ${PROJECT_NAME}
  INTERFACE
    $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include/hdltypes.hpp>
    $<BUILD_INTERFACE:${${PROJECT_NAME}_BINARY_DIR}/include/hdltypes/version.hpp>
    $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include/hdltypes/logic.hpp>
    $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include/hdltypes/impl/logic.hpp>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/hdltypes.hpp>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/hdltypes/version.hpp>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/hdltypes/logic.hpp>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/hdltypes/impl/logic.hpp>)

target_include_directories(
  ${PROJECT_NAME}
  INTERFACE $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>
            $<BUILD_INTERFACE:${${PROJECT_NAME}_BINARY_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_14)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")

install(DIRECTORY "${${PROJECT_NAME}_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

install(DIRECTORY "${${PROJECT_NAME}_BINARY_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

install(
  EXPORT ${PROJECT_NAME}Targets
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake")

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

write_basic_package_version_file(
  ${PROJECT_NAME}ConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY ExactVersion)

configure_package_config_file(
  "${${PROJECT_NAME}_SOURCE_DIR}/templates/${PROJECT_NAME}Config.cmake.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake")

install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
              "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake")

add_subdirectory(tests)
