cmake_minimum_required(VERSION 3.1)

project(hdltypes
    VERSION 0.0.0
    DESCRIPTION "A library of datatypes modelled after types common in HDLs"
    HOMEPAGE_URL "https://github.com/ktbarrett/hdltypes")

include(GNUInstallDirs)

set(HDLTYPES_DONT_INSTALL_CMAKEFILES OFF CACHE BOOL "Don't install Config.cmake and Targets.cmake files")
set(HDLTYPES_DONT_INSTALL_HEADERS OFF CACHE BOOL "Don't install headers")
set(HDLTYPES_DONT_INSTALL_LIBRARIES OFF CACHE BOOL "Don't install built libraries")

add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include/hdltypes/logic.hpp>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/hdltypes/logic.hpp>)
target_include_directories(${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_14)

add_executable(test_app
    EXCLUDE_FROM_ALL
    "${CMAKE_CURRENT_LIST_DIR}/test/main.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/test/logic.cpp")
target_include_directories(test_app
    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/test")
target_link_libraries(test_app
    PRIVATE ${PROJECT_NAME})

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
                                 VERSION ${PROJECT_VERSION}
                                 COMPATIBILITY ExactVersion)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION
  ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

export(
    TARGETS hdltypes
    NAMESPACE ${PROJECT_NAME}::
    FILE ${PROJECT_NAME}Targets.cmake)

if (NOT HDLTYPES_DONT_INSTALL_LIBRARIES)

    install(
        TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

endif()

if (NOT HDLTYPES_DONT_INSTALL_CMAKEFILES)

    install(
        FILES
            "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
            "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

    install(
        EXPORT ${PROJECT_NAME}Targets
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

endif()

if (NOT HDLTYPES_DONT_INSTALL_HEADERS)

    install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/hdltypes DESTINATION include/)

endif()
