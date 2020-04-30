#ifndef HDLTYPES_UTIL_HPP
#define HDLTYPES_UTIL_HPP

#include <type_traits>  // false_type, true_type

namespace hdltypes { namespace util {


/** User overloadable check to see if a type is a character type */
template <typename T>
struct is_char_type : std::false_type {};

template <> struct is_char_type<char> : std::true_type {};
template <> struct is_char_type<char16_t> : std::true_type {};
template <> struct is_char_type<wchar_t> : std::true_type {};
template <> struct is_char_type<char32_t> : std::true_type {};
#if cplusplus > 201703L
template <> struct is_char_type<char8_t> : std::true_type {};
#endif


// std::is_integral is not user-specializable
// this method side-steps that issue and was originall suggested by Howard Hinnant
// in the follow SO answer (https://stackoverflow.com/a/25375158/6614127)

/** User overloadable check to see if a type is an integer type */
template <typename T>
struct is_integer_type : std::is_integral<T> {};


}}

#endif
