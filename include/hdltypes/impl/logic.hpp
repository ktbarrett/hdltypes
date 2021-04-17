#ifndef HDLTYPES_IMPL_LOGIC_HPP
#define HDLTYPES_IMPL_LOGIC_HPP
#include "hdltypes/logic.hpp"

#include <cassert>
#include <cstdint>     // uint8_t
#include <stdexcept>   // invalid_argument
#include <type_traits> // enable_if, is_same

#include "hdltypes/utils.hpp" // is_char_type, is_integer_type

namespace hdltypes {

using namespace util;

namespace {

static constexpr bool logic_value_valid(const Logic::value_type value)
{
    return (Logic::U <= value) && (value <= Logic::DC);
}

}

constexpr Logic::Logic(const value_type value) noexcept
    : value_(value)
{
    assert(logic_value_valid(value_));
}

template <typename CharType, typename std::enable_if<is_char_type<CharType>::value, int>::type>
constexpr Logic to_logic(const CharType& c)
{
    switch (c) {
    case 'U':
        return Logic(Logic::U);
    case 'u':
        return Logic(Logic::U);
    case 'X':
        return Logic(Logic::X);
    case 'x':
        return Logic(Logic::X);
    case '0':
        return Logic(Logic::_0);
    case '1':
        return Logic(Logic::_1);
    case 'Z':
        return Logic(Logic::Z);
    case 'z':
        return Logic(Logic::Z);
    case 'W':
        return Logic(Logic::W);
    case 'w':
        return Logic(Logic::W);
    case 'L':
        return Logic(Logic::L);
    case 'l':
        return Logic(Logic::L);
    case 'H':
        return Logic(Logic::H);
    case 'h':
        return Logic(Logic::H);
    case '-':
        return Logic(Logic::DC);
    default:
        throw std::invalid_argument("Given value is not a Logic");
    }
}

constexpr Logic::value_type Logic::value() const noexcept
{
    assert(logic_value_valid(value_));
    return value_;
}

template <typename CharType>
constexpr CharType to_char(const Logic a) noexcept
{
    constexpr CharType table[9] = {
        'U', 'X', '0', '1', 'Z', 'W', 'L', 'H', '-'
    };
    return table[int(a.value())];
}

constexpr Logic operator""_l(const char c)
{
    return to_logic(c);
}

template <typename IntType, typename std::enable_if<is_integer_type<IntType>::value, int>::type>
constexpr Logic to_logic(const IntType& i)
{
    switch (i) {
    case 0:
        return '0'_l;
    case 1:
        return '1'_l;
    default:
        throw std::invalid_argument("Given value is not a Logic");
    }
}

constexpr Logic to_logic(const bool b) noexcept
{
    return b ? '1'_l : '0'_l;
}

constexpr Logic to_logic(const Logic a) noexcept
{
    return a;
}

constexpr bool operator==(const Logic a, const Logic b) noexcept
{
    return a.value() == b.value();
}

constexpr bool operator!=(const Logic a, const Logic b) noexcept
{
    return a.value() != b.value();
}

constexpr Logic operator&(const Logic a, const Logic b) noexcept
{
    constexpr Logic table[9][9] = {
        { 'U'_l, 'U'_l, '0'_l, 'U'_l, 'U'_l, 'U'_l, '0'_l, 'U'_l, 'U'_l }, // U
        { 'U'_l, 'X'_l, '0'_l, 'X'_l, 'X'_l, 'X'_l, '0'_l, 'X'_l, 'X'_l }, // X
        { '0'_l, '0'_l, '0'_l, '0'_l, '0'_l, '0'_l, '0'_l, '0'_l, '0'_l }, // 0
        { 'U'_l, 'X'_l, '0'_l, '1'_l, 'X'_l, 'X'_l, '0'_l, '1'_l, 'X'_l }, // 1
        { 'U'_l, 'X'_l, '0'_l, 'X'_l, 'X'_l, 'X'_l, '0'_l, 'X'_l, 'X'_l }, // Z
        { 'U'_l, 'X'_l, '0'_l, 'X'_l, 'X'_l, 'X'_l, '0'_l, 'X'_l, 'X'_l }, // W
        { '0'_l, '0'_l, '0'_l, '0'_l, '0'_l, '0'_l, '0'_l, '0'_l, '0'_l }, // L
        { 'U'_l, 'X'_l, '0'_l, '1'_l, 'X'_l, 'X'_l, '0'_l, '1'_l, 'X'_l }, // H
        { 'U'_l, 'X'_l, '0'_l, 'X'_l, 'X'_l, 'X'_l, '0'_l, 'X'_l, 'X'_l }  // -
    };
    //     U      X      0      1      Z      W      L      H      -
    return table[int(a.value())][int(b.value())];
}

constexpr Logic& operator&=(Logic& a, const Logic b) noexcept
{
    return (a = a & b);
}

constexpr Logic operator|(const Logic a, const Logic b) noexcept
{
    constexpr Logic table[9][9] = {
        { 'U'_l, 'U'_l, 'U'_l, '1'_l, 'U'_l, 'U'_l, 'U'_l, '1'_l, 'U'_l }, // U
        { 'U'_l, 'X'_l, 'X'_l, '1'_l, 'X'_l, 'X'_l, 'X'_l, '1'_l, 'X'_l }, // X
        { 'U'_l, 'X'_l, '0'_l, '1'_l, 'X'_l, 'X'_l, '0'_l, '1'_l, 'X'_l }, // 0
        { '1'_l, '1'_l, '1'_l, '1'_l, '1'_l, '1'_l, '1'_l, '1'_l, '1'_l }, // 1
        { 'U'_l, 'X'_l, 'X'_l, '1'_l, 'X'_l, 'X'_l, 'X'_l, '1'_l, 'X'_l }, // Z
        { 'U'_l, 'X'_l, 'X'_l, '1'_l, 'X'_l, 'X'_l, 'X'_l, '1'_l, 'X'_l }, // W
        { 'U'_l, 'X'_l, '0'_l, '1'_l, 'X'_l, 'X'_l, '0'_l, '1'_l, 'X'_l }, // L
        { '1'_l, '1'_l, '1'_l, '1'_l, '1'_l, '1'_l, '1'_l, '1'_l, '1'_l }, // H
        { 'U'_l, 'X'_l, 'X'_l, '1'_l, 'X'_l, 'X'_l, 'X'_l, '1'_l, 'X'_l }  // -
    };
    //     U      X      0      1      Z      W      L      H      -
    return table[int(a.value())][int(b.value())];
}

constexpr Logic& operator|=(Logic& a, const Logic b) noexcept
{
    return (a = a | b);
}

constexpr Logic operator^(const Logic a, const Logic b) noexcept
{
    constexpr Logic table[9][9] = {
        { 'U'_l, 'U'_l, 'U'_l, 'U'_l, 'U'_l, 'U'_l, 'U'_l, 'U'_l, 'U'_l }, // U
        { 'U'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l }, // X
        { 'U'_l, 'X'_l, '0'_l, '1'_l, 'X'_l, 'X'_l, '0'_l, '1'_l, 'X'_l }, // 0
        { 'U'_l, 'X'_l, '1'_l, '0'_l, 'X'_l, 'X'_l, '1'_l, '0'_l, 'X'_l }, // 1
        { 'U'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l }, // Z
        { 'U'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l }, // W
        { 'U'_l, 'X'_l, '0'_l, '1'_l, 'X'_l, 'X'_l, '0'_l, '1'_l, 'X'_l }, // L
        { 'U'_l, 'X'_l, '1'_l, '0'_l, 'X'_l, 'X'_l, '1'_l, '0'_l, 'X'_l }, // H
        { 'U'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l }  // -
    };
    //     U      X      0      1      Z      W      L      H      -
    return table[int(a.value())][int(b.value())];
}

constexpr Logic& operator^=(Logic& a, const Logic b) noexcept
{
    return (a = a ^ b);
}

constexpr Logic operator~(const Logic a) noexcept
{
    constexpr Logic table[9] = {
        'U'_l, 'X'_l, '1'_l, '0'_l, 'X'_l, 'X'_l, '1'_l, '0'_l, 'X'_l
    };
    //   U      X      0      1      Z      W      L      H      -
    return table[int(a.value())];
}

constexpr Logic& inplace_invert(Logic& a) noexcept
{
    return (a = ~a);
}

constexpr bool is01(const Logic a) noexcept
{
    return (a == '0'_l) || (a == '1'_l);
}

template <typename IntType>
constexpr IntType to_int(const Logic a)
{
    if (a == '0'_l) {
        return 0;
    } else if (a == '1'_l) {
        return 1;
    } else {
        throw std::invalid_argument("Logic value cannot be converted to an integer.");
    }
}

constexpr bool to_bool(const Logic a)
{
    return to_int(a);
}

namespace {

constexpr bool bit_value_valid(const Bit::value_type value)
{
    return (Bit::_0 == value) || (value <= Bit::_1);
}

}

constexpr Bit::Bit(const value_type value) noexcept
    : value_(value)
{
    assert(bit_value_valid(value_));
}

template <typename CharType, typename std::enable_if<is_char_type<CharType>::value, int>::type>
constexpr Bit to_bit(const CharType& c)
{
    switch (c) {
    case '0':
        return Bit(Bit::_0);
    case '1':
        return Bit(Bit::_1);
    default:
        throw std::invalid_argument("Given value is not a Bit");
    }
}

constexpr Bit::value_type Bit::value() const noexcept
{
    assert(bit_value_valid(value_));
    return value_;
}

template <typename CharType>
constexpr CharType to_char(const Bit a) noexcept
{
    return (a.value() == Bit::_1) ? '1' : '0';
}

constexpr Bit operator""_b(const char c)
{
    return to_bit(c);
}

constexpr Bit to_bit(const Logic a)
{
    if (a == '0'_l) {
        return '0'_b;
    } else if (a == '1'_l) {
        return '1'_b;
    } else {
        throw std::invalid_argument("Logic value cannot be converted to Bit");
    }
}

constexpr Logic to_logic(const Bit a) noexcept
{
    if (a == '0'_b) {
        return '0'_l;
    } else {
        return '1'_l;
    }
}

constexpr Bit::Bit(const Logic a)
    : Bit(to_bit(a))
{
}

constexpr Bit::operator Logic() const noexcept
{
    return (value() == _1) ? '1'_l : '0'_l;
}

constexpr Bit to_bit(const bool b) noexcept
{
    return b ? '1'_b : '0'_b;
}

template <typename IntType, typename std::enable_if<is_integer_type<IntType>::value, int>::type>
constexpr Bit to_bit(const IntType& i)
{
    switch (i) {
    case 0:
        return '0'_b;
    case 1:
        return '1'_b;
    default:
        throw std::invalid_argument("Given value is not a Bit");
    }
}

constexpr Bit to_bit(const Bit a) noexcept
{
    return a;
}

constexpr bool operator==(const Bit a, const Bit b) noexcept
{
    return a.value() == b.value();
}

constexpr bool operator!=(const Bit a, const Bit b) noexcept
{
    return a.value() != b.value();
}

constexpr Bit operator&(const Bit a, const Bit b) noexcept
{
    return to_bit((a == '1'_b) && (b == '1'_b));
}

constexpr Bit& operator&=(Bit& a, const Bit b) noexcept
{
    return (a = a & b);
}

constexpr Bit operator|(const Bit a, const Bit b) noexcept
{
    return to_bit((a == '1'_b) || (b == '1'_b));
}

constexpr Bit& operator|=(Bit& a, const Bit b) noexcept
{
    return (a = a | b);
}

constexpr Bit operator^(const Bit a, const Bit b) noexcept
{
    return to_bit(a != b);
}

constexpr Bit& operator^=(Bit& a, const Bit b) noexcept
{
    return (a = a ^ b);
}

constexpr Bit operator~(const Bit a) noexcept
{
    return to_bit(a == '0'_b);
}

constexpr Bit& inplace_invert(Bit& a) noexcept
{
    return (a = ~a);
}

constexpr bool is01(const Bit) noexcept
{
    return true;
}

template <typename IntType>
constexpr IntType to_int(const Bit a) noexcept
{
    return a == '1'_b;
}

constexpr bool to_bool(const Bit a) noexcept
{
    return to_int(a);
}

}

#endif
