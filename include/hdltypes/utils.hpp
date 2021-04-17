#ifndef HDLTYPES_UTIL_HPP
#define HDLTYPES_UTIL_HPP

#include <type_traits> // false_type, true_type, remove_cv

namespace hdltypes {
namespace util {

/** User overloadable check to see if a type is a character type */
template <typename T>
struct _is_char_type : std::false_type {
};

#define IS_CHAR_TYPE(type)                        \
    template <>                                   \
    struct _is_char_type<type> : std::true_type { \
    }

IS_CHAR_TYPE(char);
IS_CHAR_TYPE(wchar_t);
IS_CHAR_TYPE(char16_t);
IS_CHAR_TYPE(char32_t);
#if __cplusplus >= 202000L
IS_CHAR_TYPE(char8_t);
#endif

#undef IS_CHAR_TYPE

template <typename T>
struct is_char_type : _is_char_type<typename std::remove_cv<T>::type> {
};

/*
  std::is_integral is not user-specializable. This method side-steps the
  issue by defining it ourselves.
*/

/** User overloadable check to see if a type is an integer type */
template <typename T>
struct _is_integer_type : std::false_type {
};

#define IS_INTEGER_TYPE(type)                        \
    template <>                                      \
    struct _is_integer_type<type> : std::true_type { \
    }

IS_INTEGER_TYPE(unsigned char);
IS_INTEGER_TYPE(signed char);
IS_INTEGER_TYPE(unsigned short);
IS_INTEGER_TYPE(signed short);
IS_INTEGER_TYPE(unsigned int);
IS_INTEGER_TYPE(signed int);
IS_INTEGER_TYPE(unsigned long);
IS_INTEGER_TYPE(signed long);
IS_INTEGER_TYPE(unsigned long long);
IS_INTEGER_TYPE(signed long long);

#undef IS_INTEGER_TYPE

template <typename T>
struct is_integer_type : _is_integer_type<typename std::remove_cv<T>::type> {
};

}
}

#endif
