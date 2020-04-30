#ifndef HDLTYPES_LOGIC_HPP
#define HDLTYPES_LOGIC_HPP

#include <cstdint>          // uint8_t
#include <type_traits>      // enable_if_t, is_same_v, is_integral
#include <stdexcept>        // invalid_argument


namespace hdltypes {

    class Logic {

    public:  // types
        using repr_t = uint8_t;

    private: // helper
        template <typename IntType>
        constexpr repr_t int_to_logic_repr(IntType i) {
            // U X 0 1 Z W L H -
            switch (i) {
                case 'U': return 0;
                case 'u': return 0;
                case 'X': return 1;
                case 'x': return 1;
                case  0 : return 2;
                case '0': return 2;
                case  1 : return 3;
                case '1': return 3;
                case 'Z': return 4;
                case 'z': return 4;
                case 'W': return 5;
                case 'w': return 5;
                case 'L': return 6;
                case 'l': return 6;
                case 'H': return 7;
                case 'h': return 7;
                case '-': return 8;
            }
            throw std::invalid_argument("Given value is not a Logic");
        }

    public:  // constructors
        constexpr Logic() noexcept = default;

        template <typename IntType, typename std::enable_if<std::is_integral<IntType>::value && !std::is_same<IntType, bool>::value, int>::type = 0>
        constexpr Logic(IntType i) : repr_(int_to_logic_repr(i)) {}

        template <typename BoolType, typename std::enable_if<std::is_same<BoolType, bool>::value, int>::type = 0>
        constexpr Logic(BoolType b) noexcept : repr_(repr_t(b) + 2) {}

    public:  // attributes
        constexpr char value() const noexcept
        {
            constexpr char table[9] = {'U', 'X', '0', '1', 'Z', 'W', 'L', 'H', '-'};
            return table[repr_];
        }

        friend constexpr bool is01(const Logic& a) noexcept
        {
            return a.repr_ == 2 || a.repr_ == 3;
        }

    public:  // operators
        friend constexpr bool operator== (const Logic& a, const Logic& b) noexcept
        {
            return a.repr_ == b.repr_;
        }

        friend constexpr bool operator!= (const Logic& a, const Logic& b) noexcept
        {
            return a.repr_ != b.repr_;
        }

        friend constexpr Logic operator& (const Logic& a, const Logic& b) noexcept
        {
            constexpr Logic table[9][9] = {
                {'U', 'U', '0', 'U', 'U', 'U', '0', 'U', 'U'},  // U
                {'U', 'X', '0', 'X', 'X', 'X', '0', 'X', 'X'},  // X
                {'0', '0', '0', '0', '0', '0', '0', '0', '0'},  // 0
                {'U', 'X', '0', '1', 'X', 'X', '0', '1', 'X'},  // 1
                {'U', 'X', '0', 'X', 'X', 'X', '0', 'X', 'X'},  // Z
                {'U', 'X', '0', 'X', 'X', 'X', '0', 'X', 'X'},  // W
                {'0', '0', '0', '0', '0', '0', '0', '0', '0'},  // L
                {'U', 'X', '0', '1', 'X', 'X', '0', '1', 'X'},  // H
                {'U', 'X', '0', 'X', 'X', 'X', '0', 'X', 'X'}}; // -
            //    U    X    0    1    Z    W    L    H    -
            return table[a.repr_][b.repr_];
        }

        friend constexpr Logic operator| (const Logic& a, const Logic& b) noexcept
        {
            constexpr Logic table[9][9] = {
                {'U', 'U', 'U', '1', 'U', 'U', 'U', '1', 'U'},  // U
                {'U', 'X', 'X', '1', 'X', 'X', 'X', '1', 'X'},  // X
                {'U', 'X', '0', '1', 'X', 'X', '0', '1', 'X'},  // 0
                {'1', '1', '1', '1', '1', '1', '1', '1', '1'},  // 1
                {'U', 'X', 'X', '1', 'X', 'X', 'X', '1', 'X'},  // Z
                {'U', 'X', 'X', '1', 'X', 'X', 'X', '1', 'X'},  // W
                {'U', 'X', '0', '1', 'X', 'X', '0', '1', 'X'},  // L
                {'1', '1', '1', '1', '1', '1', '1', '1', '1'},  // H
                {'U', 'X', 'X', '1', 'X', 'X', 'X', '1', 'X'}}; // -
            //    U    X    0    1    Z    W    L    H    -
            return table[a.repr_][b.repr_];
        }

        friend constexpr Logic operator^ (const Logic& a, const Logic& b) noexcept
        {
            constexpr Logic table[9][9] = {
                {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'},  // U
                {'U', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},  // X
                {'U', 'X', '0', '1', 'X', 'X', '0', '1', 'X'},  // 0
                {'U', 'X', '1', '0', 'X', 'X', '1', '0', 'X'},  // 1
                {'U', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},  // Z
                {'U', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},  // W
                {'U', 'X', '0', '1', 'X', 'X', '0', '1', 'X'},  // L
                {'U', 'X', '1', '0', 'X', 'X', '1', '0', 'X'},  // H
                {'U', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'}}; // -
            //    U    X    0    1    Z    W    L    H    -
            return table[a.repr_][b.repr_];
        }

        friend constexpr Logic operator~ (const Logic& a) noexcept
        {
            constexpr Logic table[9] = {
                'U', 'X', '1', '0', 'X', 'X', '1', '0', 'X'};
            //   U    X    0    1    Z    W    L    H    -
            return table[a.repr_];
        }

    private: // members
        repr_t repr_ {0};  // U
    };

    class Bit {

    public:  // types
        using repr_t = uint8_t;

    private: // helpers
        template <typename IntType>
        constexpr repr_t int_to_bit_repr(IntType i)
        {
            if (i == 0 || i == 1) {
                return i;
            }
            throw std::invalid_argument("Given value is not a Bit");
        }

    public:  // constuctors
        constexpr Bit() = default;

        template <typename IntType, typename std::enable_if<std::is_integral<IntType>::value && !std::is_same<IntType, bool>::value, int>::type = 0>
        constexpr Bit(IntType i) : repr_(int_to_bit_repr(i)) {}

        template <typename BoolType, typename std::enable_if<std::is_same<BoolType, bool>::value, int>::type = 0>
        constexpr Bit(BoolType b) noexcept : repr_(b) {}

        explicit constexpr Bit(const Logic& l) : Bit(l.value()) {}

    public:  // attributes
        constexpr char value() const noexcept
        {
            return repr_ ? '1' :'0';
        }

        friend constexpr bool is01(const Bit& a) noexcept
        {
            return true;
        }

    public:  // casts
        constexpr operator Logic() const noexcept
        {
            return bool(repr_);
        }

    public:  // operators
        friend constexpr bool operator== (const Bit& a, const Bit& b) noexcept
        {
            return a.repr_ == b.repr_;
        }

        friend constexpr bool operator!= (const Bit& a, const Bit& b) noexcept
        {
            return a.repr_ != b.repr_;
        }

        friend constexpr Bit operator& (const Bit& a, const Bit& b) noexcept
        {
            return a.repr_ && b.repr_;
        }

        friend constexpr Bit operator| (const Bit& a, const Bit& b) noexcept
        {
            return a.repr_ || b.repr_;
        }

        friend constexpr Bit operator^ (const Bit& a, const Bit& b) noexcept
        {
            return a.repr_ != b.repr_;
        }

        friend constexpr Bit operator~ (const Bit& a) noexcept
        {
            return !a.repr_;
        }

    private: // members
        repr_t repr_ {0};  // 0
    };

}

#endif
