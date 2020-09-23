#ifndef HDLTYPES_IMPL_LOGIC_HPP
#define HDLTYPES_IMPL_LOGIC_HPP
#include "hdltypes/logic.hpp"

#include <cstdint>          // uint8_t
#include <type_traits>      // enable_if, is_same
#include <stdexcept>        // invalid_argument
#include <cassert>

#include <hdltypes/logic.hpp>   // Logic, Bit, to_logic, to_bit, to_char, to_bool, to_int
#include <hdltypes/utils.hpp>   // is_char_type, is_integer_type, X_ASSERT


namespace hdltypes {

namespace {

    static constexpr bool logic_value_valid(const Logic::value_type value)
    {
        return (Logic::U <= value) && (value <= Logic::DC);
    }

}

constexpr Logic::Logic(const value_type value) noexcept
  : value_((X_ASSERT(logic_value_valid(value)), value))
{
}

template <typename CharType, typename std::enable_if<
    util::is_char_type<CharType>::value
, int>::type>
constexpr Logic to_logic(const CharType& c)
{
    return
        c == 'U' ? Logic(Logic::U) :
        c == 'u' ? Logic(Logic::U) :
        c == 'X' ? Logic(Logic::X) :
        c == 'x' ? Logic(Logic::X) :
        c == '0' ? Logic(Logic::_0) :
        c == '1' ? Logic(Logic::_1) :
        c == 'Z' ? Logic(Logic::Z) :
        c == 'z' ? Logic(Logic::Z) :
        c == 'W' ? Logic(Logic::W) :
        c == 'w' ? Logic(Logic::W) :
        c == 'L' ? Logic(Logic::L) :
        c == 'l' ? Logic(Logic::L) :
        c == 'H' ? Logic(Logic::H) :
        c == 'h' ? Logic(Logic::H) :
        c == '-' ? Logic(Logic::DC) :
        throw std::invalid_argument("Given value is not a Logic");
}

constexpr Logic::value_type Logic::value() const noexcept
{
    return (X_ASSERT(logic_value_valid(value_)), value_);
}

template <typename CharType>
constexpr CharType to_char(const Logic a) noexcept
{
    return
        a.value() == Logic::U ? 'U' :
        a.value() == Logic::X ? 'X' :
        a.value() == Logic::_0 ? '0' :
        a.value() == Logic::_1 ? '1' :
        a.value() == Logic::Z ? 'Z' :
        a.value() == Logic::W ? 'W' :
        a.value() == Logic::L ? 'L' :
        a.value() == Logic::H ? 'H' :
        a.value() == Logic::DC ? '-' :
        '\0';
}

constexpr Logic operator ""_l (const char c)
{
    return to_logic(c);
}

template <typename IntType, typename std::enable_if<
    util::is_integer_type<IntType>::value &&
    !util::is_char_type<IntType>::value &&
    !std::is_same<IntType, bool>::value
, int>::type>
constexpr Logic to_logic(const IntType& i)
{
    return
        i == 0 ? '0'_l :
        i == 1 ? '1'_l :
        throw std::invalid_argument("Given value is not a Logic");
}

constexpr Logic to_logic(const bool b) noexcept
{
    return b ? '1'_l : '0'_l;
}

constexpr Logic to_logic (const Logic a) noexcept
{
    return a;
}

constexpr bool operator== (const Logic a, const Logic b) noexcept
{
    return a.value() == b.value();
}

constexpr bool operator!= (const Logic a, const Logic b) noexcept
{
    return a.value() != b.value();
}

namespace {

    constexpr Logic and_table[9][9] = {
        {'U'_l, 'U'_l, '0'_l, 'U'_l, 'U'_l, 'U'_l, '0'_l, 'U'_l, 'U'_l},  // U
        {'U'_l, 'X'_l, '0'_l, 'X'_l, 'X'_l, 'X'_l, '0'_l, 'X'_l, 'X'_l},  // X
        {'0'_l, '0'_l, '0'_l, '0'_l, '0'_l, '0'_l, '0'_l, '0'_l, '0'_l},  // 0
        {'U'_l, 'X'_l, '0'_l, '1'_l, 'X'_l, 'X'_l, '0'_l, '1'_l, 'X'_l},  // 1
        {'U'_l, 'X'_l, '0'_l, 'X'_l, 'X'_l, 'X'_l, '0'_l, 'X'_l, 'X'_l},  // Z
        {'U'_l, 'X'_l, '0'_l, 'X'_l, 'X'_l, 'X'_l, '0'_l, 'X'_l, 'X'_l},  // W
        {'0'_l, '0'_l, '0'_l, '0'_l, '0'_l, '0'_l, '0'_l, '0'_l, '0'_l},  // L
        {'U'_l, 'X'_l, '0'_l, '1'_l, 'X'_l, 'X'_l, '0'_l, '1'_l, 'X'_l},  // H
        {'U'_l, 'X'_l, '0'_l, 'X'_l, 'X'_l, 'X'_l, '0'_l, 'X'_l, 'X'_l}}; // -
    //    U      X      0      1      Z      W      L      H      -

    constexpr Logic or_table[9][9] = {
        {'U'_l, 'U'_l, 'U'_l, '1'_l, 'U'_l, 'U'_l, 'U'_l, '1'_l, 'U'_l},  // U
        {'U'_l, 'X'_l, 'X'_l, '1'_l, 'X'_l, 'X'_l, 'X'_l, '1'_l, 'X'_l},  // X
        {'U'_l, 'X'_l, '0'_l, '1'_l, 'X'_l, 'X'_l, '0'_l, '1'_l, 'X'_l},  // 0
        {'1'_l, '1'_l, '1'_l, '1'_l, '1'_l, '1'_l, '1'_l, '1'_l, '1'_l},  // 1
        {'U'_l, 'X'_l, 'X'_l, '1'_l, 'X'_l, 'X'_l, 'X'_l, '1'_l, 'X'_l},  // Z
        {'U'_l, 'X'_l, 'X'_l, '1'_l, 'X'_l, 'X'_l, 'X'_l, '1'_l, 'X'_l},  // W
        {'U'_l, 'X'_l, '0'_l, '1'_l, 'X'_l, 'X'_l, '0'_l, '1'_l, 'X'_l},  // L
        {'1'_l, '1'_l, '1'_l, '1'_l, '1'_l, '1'_l, '1'_l, '1'_l, '1'_l},  // H
        {'U'_l, 'X'_l, 'X'_l, '1'_l, 'X'_l, 'X'_l, 'X'_l, '1'_l, 'X'_l}}; // -
    //    U      X      0      1      Z      W      L      H      -

    constexpr Logic xor_table[9][9] = {
        {'U'_l, 'U'_l, 'U'_l, 'U'_l, 'U'_l, 'U'_l, 'U'_l, 'U'_l, 'U'_l},  // U
        {'U'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l},  // X
        {'U'_l, 'X'_l, '0'_l, '1'_l, 'X'_l, 'X'_l, '0'_l, '1'_l, 'X'_l},  // 0
        {'U'_l, 'X'_l, '1'_l, '0'_l, 'X'_l, 'X'_l, '1'_l, '0'_l, 'X'_l},  // 1
        {'U'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l},  // Z
        {'U'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l},  // W
        {'U'_l, 'X'_l, '0'_l, '1'_l, 'X'_l, 'X'_l, '0'_l, '1'_l, 'X'_l},  // L
        {'U'_l, 'X'_l, '1'_l, '0'_l, 'X'_l, 'X'_l, '1'_l, '0'_l, 'X'_l},  // H
        {'U'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l, 'X'_l}}; // -
    //    U      X      0      1      Z      W      L      H      -

    constexpr Logic not_table[9] = {
        'U'_l, 'X'_l, '1'_l, '0'_l, 'X'_l, 'X'_l, '1'_l, '0'_l, 'X'_l};
    //   U      X      0      1      Z      W      L      H      -

}

constexpr Logic operator& (const Logic a, const Logic b) noexcept
{
    return and_table[int(a.value())][int(b.value())];
}

Logic& operator&= (Logic& a, const Logic b) noexcept
{
    return (a = a & b);
}

constexpr Logic operator| (const Logic a, const Logic b) noexcept
{
    return or_table[int(a.value())][int(b.value())];
}

Logic& operator|= (Logic& a, const Logic b) noexcept
{
    return (a = a | b);
}

constexpr Logic operator^ (const Logic a, const Logic b) noexcept
{
    return xor_table[int(a.value())][int(b.value())];
}

Logic& operator^= (Logic& a, const Logic b) noexcept
{
    return (a = a ^ b);
}

constexpr Logic operator~ (const Logic a) noexcept
{
    return not_table[int(a.value())];
}

Logic& inplace_invert (Logic& a) noexcept
{
    return (a = ~a);
}

constexpr bool is01(const Logic a) noexcept
{
    return
        (a == '0'_l) ||
        (a == '1'_l);
}

template <typename IntType>
constexpr IntType to_int(const Logic a)
{
    return
        (a == '0'_l) ? 0 :
        (a == '1'_l) ? 1 :
        throw std::invalid_argument("Logic value cannot be converted to an integer.");
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
  : value_((X_ASSERT(bit_value_valid(value)), value))
{
}

template <typename CharType, typename std::enable_if<
    util::is_char_type<CharType>::value
, int>::type>
constexpr Bit to_bit(const CharType& c)
{
    return
        c == '0' ? Bit(Bit::_0) :
        c == '1' ? Bit(Bit::_1) :
        throw std::invalid_argument("Given value is not a Bit");
}

constexpr Bit::value_type Bit::value() const noexcept
{
    return (X_ASSERT(bit_value_valid(value_)), value_);
}

template <typename CharType>
constexpr CharType to_char(const Bit a) noexcept
{
    return (a.value() == Bit::_1) ? '1' : '0';
}

constexpr Bit operator ""_b (const char c)
{
    return to_bit(c);
}

constexpr Bit to_bit(const Logic a)
{
    return
        (a == '0'_l) ? '0'_b :
        (a == '1'_l) ? '1'_b :
        throw std::invalid_argument("Logic value cannot be converted to Bit");
}

constexpr Logic to_logic(const Bit a) noexcept
{
    return (a == '0'_b) ? '0'_l :'1'_l;
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

template <typename IntType, typename std::enable_if<
    util::is_integer_type<IntType>::value &&
    !util::is_char_type<IntType>::value &&
    !std::is_same<IntType, bool>::value
, int>::type>
constexpr Bit to_bit(const IntType& i)
{
    return
        (i == 0) ? '0'_b :
        (i == 1) ? '1'_b :
        throw std::invalid_argument("Given value is not a Bit");
}

constexpr Bit to_bit(const Bit a) noexcept
{
    return a;
}

constexpr bool operator== (const Bit a, const Bit b) noexcept
{
    return a.value() == b.value();
}

constexpr bool operator!= (const Bit a, const Bit b) noexcept
{
    return a.value() != b.value();
}

constexpr Bit operator& (const Bit a, const Bit b) noexcept
{
    return to_bit((a == '1'_b) && (b == '1'_b));
}

Bit& operator&= (Bit& a, const Bit b) noexcept
{
    return (a = a & b);
}

constexpr Bit operator| (const Bit a, const Bit b) noexcept
{
    return to_bit((a == '1'_b) || (b == '1'_b));
}

Bit& operator|= (Bit& a, const Bit b) noexcept
{
    return (a = a | b);
}

constexpr Bit operator^ (const Bit a, const Bit b) noexcept
{
    return to_bit(a != b);
}

Bit& operator^= (Bit& a, const Bit b) noexcept
{
    return (a = a ^ b);
}

constexpr Bit operator~ (const Bit a) noexcept
{
    return to_bit(a == '0'_b);
}

Bit& inplace_invert (Bit& a) noexcept
{
    return (a = ~a);
}

constexpr bool is01 (const Bit) noexcept
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
