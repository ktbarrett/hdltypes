#ifndef HDLTYPES_UTIL_HPP
#define HDLTYPES_UTIL_HPP

namespace hdltypes { namespace util {


/** User overloadable check to see if a type is a character type */
template <typename T>
struct is_char_type
{
    static constexpr bool value = false;
};

#define def_is_char_type(type) \
template <> struct is_char_type<type> { static constexpr bool value = true; };

def_is_char_type(char);
def_is_char_type(wchar_t);
def_is_char_type(char16_t);
def_is_char_type(char32_t);
#if cplusplus > 201703L
def_is_char_type(char8_t);
#endif

#undef def_is_char_type


}}

#endif
