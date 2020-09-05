#ifndef HDLTYPES_UTIL_HPP
#define HDLTYPES_UTIL_HPP

#include <type_traits>  // false_type, true_type, is_integral
#include <utility>      // declval
#include <iterator>     // begin, end
#include <cstdint>      // int32_t

namespace hdltypes {

/** Type for bounds of vector-like objects */
using bound_type = std::int32_t;

}

namespace hdltypes { namespace util {


/** User overloadable check to see if a type is a character type */
template <typename T>
struct is_char_type : std::false_type {};

template <> struct is_char_type<char> : std::true_type {};
template <> struct is_char_type<char16_t> : std::true_type {};
template <> struct is_char_type<wchar_t> : std::true_type {};
template <> struct is_char_type<char32_t> : std::true_type {};
#if cplusplus >= 201703L
template <> struct is_char_type<char8_t> : std::true_type {};
#endif


// std::is_integral is not user-specializable
// this method side-steps that issue and was originally suggested by Howard Hinnant
// in the follow SO answer (https://stackoverflow.com/a/25375158/6614127)

/** User overloadable check to see if a type is an integer type */
template <typename T>
struct is_integer_type : std::is_integral<T> {};

// void_t is not available in C++14, but C++14 has the features to support it,
// so we will just redefine it and not use the std version
template <typename ...>
using void_t = void;

template <typename Iterable, typename = void>
struct is_iterable : std::false_type {};

template <typename Iterable>
struct is_iterable<Iterable, void_t<
    decltype(std::begin(std::declval<Iterable>())),
    decltype(std::end(std::declval<Iterable>()))
>> : std::true_type {};

}}

#endif
