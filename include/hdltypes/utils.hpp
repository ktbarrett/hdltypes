#ifndef HDLTYPES_UTIL_HPP
#define HDLTYPES_UTIL_HPP

#include <type_traits>  // false_type, true_type

namespace hdltypes { namespace util {


/** User overloadable check to see if a type is a character type */
template <typename T>
struct is_char_type : std::false_type {};

template <> struct is_char_type<char> : std::true_type {};
template <> struct is_char_type<wchar_t> : std::true_type {};
template <> struct is_char_type<char16_t> : std::true_type {};
template <> struct is_char_type<char32_t> : std::true_type {};
#if cplusplus >= 202000L
template <> struct is_char_type<char8_t> : std::true_type {};
#endif


/*
  std::is_integral is not user-specializable. This method side-steps the
  issue by defining it ourselves.
*/

/** User overloadable check to see if a type is an integer type */
template <typename T>
struct is_integer_type : std::false_type {};

template <> struct is_integer_type<unsigned char> : std::true_type {};
template <> struct is_integer_type<signed char> : std::true_type {};
template <> struct is_integer_type<unsigned short> : std::true_type {};
template <> struct is_integer_type<signed short> : std::true_type {};
template <> struct is_integer_type<unsigned int> : std::true_type {};
template <> struct is_integer_type<signed int> : std::true_type {};
template <> struct is_integer_type<unsigned long> : std::true_type {};
template <> struct is_integer_type<signed long> : std::true_type {};
template <> struct is_integer_type<unsigned long long> : std::true_type {};
template <> struct is_integer_type<signed long long> : std::true_type {};


}}

#endif
