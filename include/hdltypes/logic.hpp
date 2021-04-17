#ifndef HDLTYPES_LOGIC_HPP
#define HDLTYPES_LOGIC_HPP

#include <cstdint>              // uint8_t
#include <type_traits>          // enable_if, is_same
#include "hdltypes/utils.hpp"   // is_char_type, is_integer_type


namespace hdltypes {

using namespace util;

/** Logic value type

    This effectively models VHDL's std_ulogic type. See value_type for details on the
    values of this type.

    This type supports logical operations "and", "or", "xor", and inversion.
    Can be converted "from" and "to" int or bool representations of Logic values.
    Supports serialization and deserialization as well.

    Like VHDL:
      * weak value when operated on become strong (due to implicit buffering)
      * operations on non-0/1 values yield "unknowns"
      * operations involving unassigned result in unassigned results
    */
class Logic {

public:  // types

    /** Representation of acceptable values of a Logic.

        Naming and ordering are public information and must be controlled.
        */
    enum value_type : uint8_t {
        U,  ///< Unassigned. Represents the container holding a value of this type did not take on an actual value.
        X,  ///< Unknown. Typically a result of doing operations on non-0/1 values.
        _0, ///< 0
        _1, ///< 1
        Z,  ///< High Impedance. Useful for modeling pull-ups and pull-downs.
        W,  ///< Weak Unknown. Like X, but the value is weak.
        L,  ///< Weak 0. Like 0, but the value is weak.
        H,  ///< Weak 1. Like 1, but the value is weak.
        DC  ///< Don't Care. Like X, but explicit rather than accidental.
    };

public:  // constructors

    /** Default Logic to U. */
    constexpr Logic() noexcept = default;

    /** Create a Logic given a value_type value.

        Note that this function is noexcept, there is *no* checking on passed values.
        This is justified because it is difficult to break, except on purpose;
        while allowing us additional performance.
        */
    explicit constexpr Logic(value_type value) noexcept;

public:  // attributes

    /** Obtain the value_type value. */
    constexpr value_type value() const noexcept;

private: // members

    value_type value_ {U};
};

/** \relates Logic UDL convenience syntax for Logic::deserialize. */
constexpr Logic operator ""_l (char c);

/** \relates Logic Converts bool values `false` and `true` to Logic `0` and `1`, respectively. */
constexpr Logic to_logic(bool b) noexcept;

/** \relates Logic Converts integer values `0` and `1` into Logic `0` and `1`, respectively. */
template <typename IntType, typename std::enable_if<
    is_integer_type<IntType>::value
, int>::type = 0>
constexpr Logic to_logic(const IntType& i);

/** \relates Logic Converts character values into Logic. See table below for more details.

\verbatim
'U'  'u'    => U
'X'  'x'    => X
'0'         => _0
'1'         => _1
'Z'  'z'    => Z
'W'  'w'    => W
'L'  'l'    => L
'H'  'h'    => H
'-'         => DC
\endverbatim
    */
template <typename CharType, typename std::enable_if<
    is_char_type<CharType>::value
, int>::type = 0>
constexpr Logic to_logic(const CharType& c);

/** \relates Logic Returns the given Logic. */
constexpr Logic to_logic (Logic a) noexcept;

/** \relates Logic Value equality. */
constexpr bool operator== (Logic a, Logic b) noexcept;

/** \relates Logic Value inequality. */
constexpr bool operator!= (Logic a, Logic b) noexcept;

/** \relates Logic Logical "and" operation. See implementation for details. */
constexpr Logic operator& (Logic a, Logic b) noexcept;

/** \relates Logic Inplace version of the logical "and" operation. */
constexpr Logic& operator&= (Logic& a, Logic b) noexcept;

/** \relates Logic Logical "or" operation. See implementation for details. */
constexpr Logic operator| (Logic a, Logic b) noexcept;

/** \relates Logic Inplace version of the logical "or" operation. */
constexpr Logic& operator|= (Logic& a, Logic b) noexcept;

/** \relates Logic Logical "xor" operation. See implementation for details. */
constexpr Logic operator^ (Logic a, Logic b) noexcept;

/** \relates Logic Inplace version of the logical "xor" operation. */
constexpr Logic& operator^= (Logic& a, Logic b) noexcept;

/** \relates Logic Logical inversion operation. See implementation for details. */
constexpr Logic operator~ (Logic a) noexcept;

/** \relates Logic Inplace version of the logical "invert" operation. */
constexpr Logic& inplace_invert (Logic& a) noexcept;

/** \relates Logic Returns `true` if the value is `0` or `1`. */
constexpr bool is01 (Logic a) noexcept;

/** \relates Logic Converts a Logic `0`/`L` or `1`/`H` to the integer `0` or `1`, respectively. */
template <typename IntType = int>
constexpr IntType to_int(Logic a);

/** \relates Logic Converts a Logic `0`/`L` or `1`/`H` to the integer `false` or `true`, respectively. */
constexpr bool to_bool(Logic a);

/** \relates Logic Converts a Logic into a character. See the below details for the mapping.

\verbatim
U       => 'U'
X       => 'X'
_0      => '0'
_1      => '1'
Z       => 'Z'
W       => 'W'
L       => 'L'
H       => 'H'
DC      => '-'
\endverbatim
    */
template <typename CharType = char>
constexpr CharType to_char(Logic a) noexcept;

/** Bit value type

    Implementation of a bit value. Supports the values `0` and `1`. Values of this
    type are immutable. Supports (de)serialization, comparison, and logic operations:
    "and", "or", "xor", and inversion.
    */
class Bit {

public:  // types

    /** Representation of acceptable values of a Bit.

        Naming and ordering are public information and must be controlled.
        */
    enum value_type : uint8_t {
        _0, ///< 0
        _1  ///< 1
    };

public:  // constructors

    /** Default Bit to 0. */
    constexpr Bit() noexcept = default;

    /** Create a Bit given a value_type value.

        Note that this function is noexcept, there is *no* checking on passed values.
        This is justified because it is difficult to break, except on purpose;
        while allowing us additional performance.
        */
    explicit constexpr Bit(value_type value) noexcept;

public:  // attributes

    /** Obtain the value_type value. */
    constexpr value_type value() const noexcept;

public:  // Logic conversion

    /** Allows a Logic to be converted to a Bit. Fails if the Logic is not `0` or `1`. */
    explicit constexpr Bit(Logic a);

    /** Allows a Bit to be converted *implicitly* to a Logic. */
    constexpr operator Logic() const noexcept;

private: // members

    value_type value_ {_0};
};

/** \relates Bit UDL convience syntax for Bit::deserialize. */
constexpr Bit operator ""_b (char c);

/** \relates Bit Converts bool values `false` and `true` to Bit `0` and `1`, respectively. */
constexpr Bit to_bit(bool b) noexcept;

/** \relates Bit Converts integer values `0` and `1` into Bit `0` and `1`, respectively. */
template <typename IntType, typename std::enable_if<
    is_integer_type<IntType>::value
, int>::type = 0>
constexpr Bit to_bit(const IntType& i);

/** \relates Bit Converts character values into Logic. See table below for more details.

\verbatim
'0'      => _0
'1'      => _1
\endverbatim
    */
template <typename CharType, typename std::enable_if<
    is_char_type<CharType>::value
, int>::type = 0>
constexpr Bit to_bit(const CharType& c);

/** \relates Bit Converts the Logic values `0` and `1` to Bit `0` and `1`, respectively. */
constexpr Bit to_bit(Logic a);

/** \relates Bit Returns the given Bit. */
constexpr Bit to_bit(Bit a) noexcept;

/** \relates Logic converts the Bit values `0` and `1` to Logic `0` and `1`, respectively. */
constexpr Logic to_logic(Bit a) noexcept;

/** \relates Bit Value equality. */
constexpr bool operator== (Bit a, Bit b) noexcept;

/** \relates Bit Value inequality. */
constexpr bool operator!= (Bit a, Bit b) noexcept;

/** \relates Bit Logical "and" operation. Returns `1` if both arguments are `1`. */
constexpr Bit operator& (Bit a, Bit b) noexcept;

/** \relates Bit In-place version of the logical "and" operation. */
constexpr Bit& operator&= (Bit& a, Bit b) noexcept;

/** \relates Bit Logical "or" operation. Returns `1` if either arguments are `1`. */
constexpr Bit operator| (Bit a, Bit b) noexcept;

/** \relates Bit In-place version of the logical "or" operation. */
constexpr Bit& operator|= (Bit& a, Bit b) noexcept;

/** \relates Bit Logical "xor" operation. Returns `1` if arguments aren't equivalent. */
constexpr Bit operator^ (Bit a, Bit b) noexcept;

/** \relates Bit In-place version of the logical "xor" operation. */
constexpr Bit& operator^= (Bit& a, Bit b) noexcept;

/** \relates Bit Logical inversion operation. Returns `1` if given `0`, and vice versa. */
constexpr Bit operator~ (Bit a) noexcept;

/** \relates Bit In-place version of the logical "invert" operation. */
constexpr Bit& inplace_invert (Bit& a) noexcept;

/** \relates Bit Returns `true`. */
constexpr bool is01 (Bit a) noexcept;

/** \relates Bit Converts a Bit `0` or `1` to the integer `0` or `1`, respectively. */
template <typename IntType = int>
constexpr IntType to_int(Bit a) noexcept;

/** \relates Bit Converts a Bit `0` or `1` to the boolean `false` or `true`, respectively. */
constexpr bool to_bool(Bit a) noexcept;

/** \relates Bit Converts a Bit `0` or `1` to the characters `'0'` and `'1'`, respectively. */
template <typename CharType = char>
constexpr CharType to_char(const Bit a) noexcept;

}

#include "hdltypes/impl/logic.hpp"

#endif
