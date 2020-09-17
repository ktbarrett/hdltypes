#ifndef HDLTYPES_RANGE_HPP
#define HDLTYPES_RANGE_HPP

#include <hdltypes/utils.hpp>


namespace hdltypes {

enum Direction {
    DOWNTO = 0,
    TO = 1,
};

template <bound_type left_, Direction ascending_, bound_type right_>
class Range1 {
public:
    constexpr Range1() noexcept = default;
    constexpr bound_type left() const noexcept { return left_; }
    constexpr bound_type right() const noexcept { return right_; }
    constexpr bool ascending() const noexcept { return ascending_ == TO; }
    constexpr bound_type low() const noexcept { return ascending() ? left() : right(); }
    constexpr bound_type high() const noexcept { return ascending() ? right() : left(); }
    constexpr bound_type length() const noexcept { return high() - low() + 1; }
};

class Range2 {
public:
    constexpr Range2(bound_type left, Direction ascending, bound_type right) noexcept
      : left_(left), ascending_(ascending), right_(right) {}
    constexpr bound_type left() const noexcept { return left_; }
    constexpr bound_type right() const noexcept { return right_; }
    constexpr bool ascending() const noexcept { return ascending_ == TO; }
    constexpr bound_type low() const noexcept { return ascending() ? left() : right(); }
    constexpr bound_type high() const noexcept { return ascending() ? right() : left(); }
    constexpr bound_type length() const noexcept { return high() - low() + 1; }
private:
    bound_type left_;
    Direction ascending_;
    bound_type right_;
};

template <Direction ascending_>
class Range3 {
public:
    constexpr Range3(bound_type left, bound_type right) noexcept
      : left_(left), right_(right) {}
    constexpr bound_type left() const noexcept { return left_; }
    constexpr bound_type right() const noexcept { return right_; }
    constexpr bool ascending() const noexcept { return ascending_ == TO; }
    constexpr bound_type low() const noexcept { return ascending() ? left() : right(); }
    constexpr bound_type high() const noexcept { return ascending() ? right() : left(); }
    constexpr bound_type length() const noexcept { return high() - low() + 1; }
private:
    bound_type left_;
    bound_type right_;
};

template <bound_type left, Direction ascending, bound_type right>
auto range()
{
    return Range1<left, ascending, right>();
}

template <typename = void, typename = void, typename = void>
auto range(bound_type left, Direction ascending, bound_type right)
{
    return Range2(left, ascending, right);
}

template <Direction ascending, typename = void, typename = void>
auto range(bound_type left, bound_type right)
{
    return Range3<ascending>(left, right);
}

using AscendingRange = Range3<TO>;
using DescendingRange = Range3<DOWNTO>;

}

#endif
