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
// this method side-steps that issue and was originally suggested by Howard Hinnant
// in the follow SO answer (https://stackoverflow.com/a/25375158/6614127)

/** User overloadable check to see if a type is an integer type */
template <typename T>
struct is_integer_type : std::is_integral<T> {};

// The implementation of X_ASSERT is provided by Andrzej Krzemieński
// in the article about the subject. This attempts to work around issues with
// assert() in constexpr functions in GCC 4.8.
// https://akrzemi1.wordpress.com/2017/05/18/asserts-in-constexpr-functions/

#if defined NDEBUG
# define X_ASSERT(CHECK) void(0)
#else
# define X_ASSERT(CHECK) \
    ( CHECK ?  void(0) : []{assert(!#CHECK);}() )
#endif

}}

#endif
