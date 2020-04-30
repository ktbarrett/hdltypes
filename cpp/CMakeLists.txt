cmake_minimum_required(VERSION 3.1)

project(hdltypes VERSION 0.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(hdltypes INTERFACE)
target_include_directories(hdltypes
    INTERFACE "${CMAKE_CURRENT_LIST_DIR}")
set_target_properties(hdltypes PROPERTIES PUBLIC_HEADER "hdltypes/logic.hpp")

add_executable(test_app
    "${CMAKE_CURRENT_LIST_DIR}/test/main.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/test/logic.cpp")
target_link_libraries(test_app
    PRIVATE hdltypes)

install(TARGETS hdltypes
    LIBRARY DESTINATION lib/
    PUBLIC_HEADER DESTINATION include/)
