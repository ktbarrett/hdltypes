#include "hdltypes.hpp"
#include <cstdint>

using hdltypes::util::is_integer_type;
using hdltypes::util::is_char_type;


static_assert(is_integer_type<unsigned char>::value);
static_assert(is_integer_type<signed char>::value);
static_assert(is_integer_type<unsigned short>::value);
static_assert(is_integer_type<signed short>::value);
static_assert(is_integer_type<unsigned int>::value);
static_assert(is_integer_type<signed int>::value);
static_assert(is_integer_type<unsigned long>::value);
static_assert(is_integer_type<signed long>::value);
static_assert(is_integer_type<unsigned long long>::value);
static_assert(is_integer_type<signed long long>::value);
static_assert(is_integer_type<std::size_t>::value);
static_assert(is_integer_type<uint8_t>::value);
static_assert(is_integer_type<int8_t>::value);
static_assert(is_integer_type<uint16_t>::value);
static_assert(is_integer_type<int16_t>::value);
static_assert(is_integer_type<uint32_t>::value);
static_assert(is_integer_type<int32_t>::value);
static_assert(is_integer_type<uint64_t>::value);
static_assert(is_integer_type<int64_t>::value);
static_assert(is_integer_type<uintptr_t>::value);
static_assert(is_integer_type<intptr_t>::value);
static_assert(is_integer_type<intmax_t>::value);
static_assert(is_integer_type<uintmax_t>::value);
static_assert(is_integer_type<const volatile int>::value);

static_assert(!is_integer_type<bool>::value);
static_assert(!is_integer_type<char>::value);

static_assert(is_char_type<char>::value);
static_assert(is_char_type<wchar_t>::value);
static_assert(is_char_type<char16_t>::value);
static_assert(is_char_type<char32_t>::value);
static_assert(is_char_type<const volatile char>::value);
