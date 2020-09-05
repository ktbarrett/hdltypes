#ifndef HDLTYPES_UTIL_HPP
#define HDLTYPES_UTIL_HPP

#include <type_traits>  // false_type, true_type, remove_cv
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
struct _is_char_type : std::false_type {};

template <> struct _is_char_type<char> : std::true_type {};
template <> struct _is_char_type<wchar_t> : std::true_type {};
template <> struct _is_char_type<char16_t> : std::true_type {};
template <> struct _is_char_type<char32_t> : std::true_type {};
#if cplusplus >= 202000L
template <> struct _is_char_type<char8_t> : std::true_type {};
#endif

template <typename T>
struct is_char_type : _is_char_type<typename std::remove_cv<T>::type> {};


// std::is_integral is not user-specializable. This method side-steps the issue by
// defining it ourselves.

/** User overloadable check to see if a type is an integer type */
template <typename T>
struct _is_integer_type : std::false_type {};

template <> struct _is_integer_type<unsigned char> : std::true_type {};
template <> struct _is_integer_type<signed char> : std::true_type {};
template <> struct _is_integer_type<unsigned short> : std::true_type {};
template <> struct _is_integer_type<signed short> : std::true_type {};
template <> struct _is_integer_type<unsigned int> : std::true_type {};
template <> struct _is_integer_type<signed int> : std::true_type {};
template <> struct _is_integer_type<unsigned long> : std::true_type {};
template <> struct _is_integer_type<signed long> : std::true_type {};
template <> struct _is_integer_type<unsigned long long> : std::true_type {};
template <> struct _is_integer_type<signed long long> : std::true_type {};

template <typename T>
struct is_integer_type : _is_integer_type<typename std::remove_cv<T>::type> {};

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
