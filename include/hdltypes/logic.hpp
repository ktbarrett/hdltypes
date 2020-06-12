#ifndef HDLTYPES_LOGIC_HPP
#define HDLTYPES_LOGIC_HPP

#include <cstdint>          // uint8_t
#include <type_traits>      // enable_if, is_same, is_integral


namespace hdltypes {

    /* DESIGN NOTES
     * It would simply be too convenient to support methods on enums to implement enumerated datatypes. Thank you, C++.
        Instead, we make classes that encapsulate internally defined "value_type" enums and offer a method, `.value()`
        to obtain the stored enum.
     * In VHDL Bit could be a Logic subtype, but we have no way to describe that relationship in C++. We could use
        dependent types, which VHDL also has, but C++ still does not... Inheritance here has issues; slicing is not safe
        since it may put a child Bit into an invalid state because technically Bit has additional invariants (the
        dependent condition). So, we have just-another-type that relates to Logic through constructors and casts with
        carefully placed `explicit` so we get implicit casting to wider types (Bit -> Logic). Other Logic-like types
        should follow the same recipe as Bit.
     */

    /** Logic value type

        This effectively models VHDL's std_ulogic type. Values of this type are immutable.
        See value_type for details on the values of this type.

        This type supports logical operations "and", "or", "xor", and inversion. Can be
        converted "from" and "to" int or bool representations of Logic values. Also
        supports (de)serialization from printable characters values.

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
            Z,  ///< High Impedance. Useful for modelling pull-ups and pull-downs.
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

        /** Converts character values into Logic. See table below for more details.

            `U`, `u` => U
            `X`, `x` => X
            `0`      => _0
            `1`      => _1
            `Z`, `z` => Z
            `W`, `w` => W
            `L`, `l` => L
            `H`, `h` => H
            `-`      => DC
            */
        template <typename CharType>
        static constexpr Logic deserialize(const CharType& c);

    public:  // attributes

        /** Obtain the value_type value */
        constexpr value_type value() const noexcept;

        /** Convert a Logic into a printable representation */
        template <typename CharType = char>
        constexpr CharType serialize() const noexcept;

    private: // members

        value_type value_ {U};
    };

    /** \relates Logic UDL convience syntax for Logic::deserialize */
    constexpr Logic operator ""_l (char c);

    /** \relates Logic Converts bool values `false` and `true` to Logic `0` and `1`, respectively. */
    constexpr Logic to_logic(bool b) noexcept;

    /** \relates Logic Converts integer values `0` and `1` into Logic `0` and `1`, respectively. */
    template <typename IntType, typename std::enable_if<
        std::is_integral<IntType>::value &&
        !std::is_same<IntType, bool>::value
    , int>::type = 0>
    constexpr Logic to_logic(const IntType& i);

    /** \relates Logic Value equality */
    constexpr bool operator== (Logic a, Logic b) noexcept;

    /** \relates Logic Value inqueality */
    constexpr bool operator!= (Logic a, Logic b) noexcept;

    /** \relates Logic Logical "and" operation. See implementation for details. */
    constexpr Logic operator& (Logic a, Logic b) noexcept;

    /** \relates Logic Logical "or" operation. See implementation for details. */
    constexpr Logic operator| (Logic a, Logic b) noexcept;

    /** \relates Logic Logical "xor" operation. See implementation for details. */
    constexpr Logic operator^ (Logic a, Logic b) noexcept;

    /** \relates Logic Logical inversion operation. See implementation for details. */
    constexpr Logic operator~ (Logic a) noexcept;

    /** \relates Logic Returns `true` if the value is `0` or `1` */
    constexpr bool is01 (Logic a) noexcept;

    /** \relates Logic Converts a Logic `0`/`L` or `1`/`H` to the integer `0` or `1`, respectively. */
    template <typename IntType = int>
    constexpr IntType to_int(Logic a);

    /** \relates Logic Converts a Logic `0`/`L` or `1`/`H` to the integer `0` or `1`, respectively. */
    constexpr bool to_bool(Logic a);

}

#include "hdltypes/impl/logic.hpp"

#endif