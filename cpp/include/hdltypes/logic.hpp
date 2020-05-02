#ifndef HDLTYPES_LOGIC_HPP
#define HDLTYPES_LOGIC_HPP

#include <cstdint>          // uint8_t
#include <type_traits>      // enable_if_t, is_same_v, is_integral


namespace hdltypes {

    class Logic {

    public:  // types
        using repr_t = uint8_t;

    public:  // constructors
        constexpr Logic() noexcept = default;

        template <typename IntType, typename std::enable_if<std::is_integral<IntType>::value && !std::is_same<IntType, bool>::value, int>::type = 0>
        constexpr Logic(IntType i);

        template <typename BoolType, typename std::enable_if<std::is_same<BoolType, bool>::value, int>::type = 0>
        constexpr Logic(BoolType b);

    public:  // attributes
        constexpr char value() const noexcept;
        friend constexpr bool is01(const Logic& a) noexcept;

    public:  // operators
        friend constexpr bool operator== (const Logic& a, const Logic& b) noexcept;
        friend constexpr bool operator!= (const Logic& a, const Logic& b) noexcept;
        friend constexpr Logic operator& (const Logic& a, const Logic& b) noexcept;
        friend constexpr Logic operator| (const Logic& a, const Logic& b) noexcept;
        friend constexpr Logic operator^ (const Logic& a, const Logic& b) noexcept;
        friend constexpr Logic operator~ (const Logic& a) noexcept;

    private: // members
        repr_t repr_ {0};  // U
    };

    class Bit {

    public:  // types
        using repr_t = uint8_t;

    public:  // constuctors
        constexpr Bit() = default;

        template <typename IntType, typename std::enable_if<std::is_integral<IntType>::value && !std::is_same<IntType, bool>::value, int>::type = 0>
        constexpr Bit(IntType i);

        template <typename BoolType, typename std::enable_if<std::is_same<BoolType, bool>::value, int>::type = 0>
        constexpr Bit(BoolType b);

        explicit constexpr Bit(const Logic& l);

    public:  // attributes
        constexpr char value() const noexcept;
        friend constexpr bool is01(const Bit& a) noexcept;

    public:  // casts
        constexpr operator Logic() const noexcept;

    public:  // operators
        friend constexpr bool operator== (const Bit& a, const Bit& b) noexcept;
        friend constexpr bool operator!= (const Bit& a, const Bit& b) noexcept;
        friend constexpr Bit  operator&  (const Bit& a, const Bit& b) noexcept;
        friend constexpr Bit  operator|  (const Bit& a, const Bit& b) noexcept;
        friend constexpr Bit  operator^  (const Bit& a, const Bit& b) noexcept;
        friend constexpr Bit  operator~  (const Bit& a) noexcept;

    private: // members
        repr_t repr_ {0};  // 0
    };

}

#include "hdltypes/impl/logic.hpp"

#endif
