FetchContent_Declare(
  catch2content
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.13.0)

FetchContent_MakeAvailable(catch2content)

add_executable(test_hdltypes EXCLUDE_FROM_ALL main.cpp logic.cpp)

target_link_libraries(test_hdltypes PRIVATE ${PROJECT_NAME} Catch2::Catch2)

target_compile_options(
  test_hdltypes
  INTERFACE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Wall
    -Wextra
    -Wpedantic
    -Wconversion
    -Wsign-conversion>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>)
