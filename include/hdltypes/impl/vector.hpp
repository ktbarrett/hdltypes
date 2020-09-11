#ifndef HDLTYPES_IMPL_VECTOR_HPP
#define HDLTYPES_IMPL_VECTOR_HPP

#include <hdltypes/vector.hpp>  // Vector, VectorView, VectorConstView, to_vector
#include <memory>               // default_delete
#include <type_traits>          // enable_if, is_convertible
#include <algorithm>            // copy
#include <iterator>             // distance, begin, end
#include <utility>              // declval
#include <stdexcept>            // out_of_range, invalid_argument
#include <hdltypes/utils.hpp>   // is_iterable


namespace hdltypes {

template <typename value_type>
Vector<value_type>::Vector(bound_type left, bound_type right)
  : left_(left),
    right_(right),
    array_(length())
{
}

template <typename value_type>
auto Vector<value_type>::index_helper(bound_type i) const -> bound_type
{
    if (ascending()) {
        return i - left();
    } else {
        return left() - i;
    }
}

template <typename value_type>
value_type & Vector<value_type>::operator() (bound_type i)
{
    bound_type idx = index_helper(i);
    #ifndef HDLTYPES_NO_BOUNDS_CHECK
    if (idx < 0 || length() <= idx) {
        throw std::out_of_range("Index out of range.");
    }
    #endif
    return array_[idx];
}

template <typename value_type>
value_type const& Vector<value_type>::operator() (bound_type i) const
{
    bound_type idx = index_helper(i);
    #ifndef HDLTYPES_NO_BOUNDS_CHECK
    if (idx < 0 || length() <= idx) {
        throw std::out_of_range("Index out of range.");
    }
    #endif
    return array_[idx];
}

template <typename value_type>
VectorView<value_type> Vector<value_type>::operator() (bound_type left, bound_type right)
{
    return VectorView<value_type>(left, right, *this);
}

template <typename value_type>
VectorConstView<value_type> Vector<value_type>::operator() (bound_type left, bound_type right) const
{
    return VectorConstView<value_type>(left, right, *this);
}

template <typename value_type>
VectorView<value_type>::VectorView(bound_type left, bound_type right, Vector<value_type> & vector)
  : left_(left),
    right_(right),
    vector_(vector)
{
    #ifndef HDLTYPES_NO_BOUNDS_CHECK
    if (vector_.ascending() != ascending()) {
        throw std::invalid_argument("Slice direction doesn't match vector's.");
    }
    else if (low() < vector_.low()) {
        throw std::out_of_range("Index out of range.");
    }
    else if (high() > vector_.high()) {
        throw std::out_of_range("Index out of range.");
    }
    #endif
}

template <typename value_type>
value_type & VectorView<value_type>::operator() (bound_type i)
{
    #ifndef HDLTYPES_NO_BOUNDS_CHECK
    if (i < low()) {
        throw std::out_of_range("Index out of range.");
    }
    else if (i > high()) {
        throw std::out_of_range("Index out of range.");
    }
    #endif
    return vector_(i);
}

template <typename value_type>
value_type const& VectorView<value_type>::operator() (bound_type i) const
{
    #ifndef HDLTYPES_NO_BOUNDS_CHECK
    if (i < low()) {
        throw std::out_of_range("Index out of range.");
    }
    else if (i > high()) {
        throw std::out_of_range("Index out of range.");
    }
    #endif
    return vector_(i);
}

template <typename value_type>
VectorView<value_type> VectorView<value_type>::operator() (bound_type left, bound_type right)
{
    auto res = VectorView<value_type>(left, right, vector_);
    #ifndef HDLTYPES_NO_BOUNDS_CHECK
    if (res.low() < low()) {
        throw std::out_of_range("Index out of range");
    }
    else if (res.high() > high()) {
        throw std::out_of_range("Index out of range");
    }
    #endif
    return res;
}

template <typename value_type>
VectorConstView<value_type> VectorView<value_type>::operator() (bound_type left, bound_type right) const
{
    auto res = VectorConstView<value_type>(left, right, vector_);
    #ifndef HDLTYPES_NO_BOUNDS_CHECK
    if (res.low() < low()) {
        throw std::out_of_range("Index out of range");
    }
    else if (res.high() > high()) {
        throw std::out_of_range("Index out of range");
    }
    #endif
    return res;
}

template <typename value_type>
template <typename Iterator, typename std::enable_if<
    std::is_convertible<decltype(*std::declval<Iterator>()), value_type>::value
, int>::type>
VectorView<value_type> & VectorView<value_type>::assign (Iterator const & start, Iterator const & end)
{
    #ifndef HDLTYPES_NO_BOUNDS_CHECK
    if (length() != std::distance(start, end)) {
        throw std::invalid_argument("Slice and argument length are not the same");
    }
    #endif
    std::copy(start, end, begin());
    return *this;
}

template <typename value_type>
template <typename Iterable, typename std::enable_if<
    util::is_iterable<Iterable>::value &&
    std::is_convertible<decltype(*std::begin(std::declval<Iterable&>())), value_type>::value
, int>::type>
VectorView<value_type> & VectorView<value_type>::assign (Iterable const & it)
{
    #ifndef HDLTYPES_NO_BOUNDS_CHECK
    if (length() != std::distance(std::begin(it), std::end(it))) {
        throw std::invalid_argument("Slice and argument length are not the same");
    }
    #endif
    std::copy(std::begin(it), std::end(it), begin());
    return *this;
}

template <typename value_type>
auto VectorView<value_type>::begin() noexcept
{
    if (ascending()) {
        return vector_.begin() + (left() - vector_.left());
    } else {
        return vector_.begin() + (vector_.left() - left());
    }
}

template <typename value_type>
auto VectorView<value_type>::begin() const noexcept
{
    if (ascending()) {
        return vector_.begin() + (left() - vector_.left());
    } else {
        return vector_.begin() + (vector_.left() - left());
    }
}

template <typename value_type>
auto VectorView<value_type>::cbegin() const noexcept
{
    return begin();
}

template <typename value_type>
auto VectorView<value_type>::end() noexcept
{
    if (ascending()) {
        return vector_.end() - (vector_.right() - right());
    } else {
        return vector_.end() - (right() - vector_.right());
    }
}

template <typename value_type>
auto VectorView<value_type>::end() const noexcept
{
    if (ascending()) {
        return vector_.end() - (vector_.right() - right());
    } else {
        return vector_.end() - (right() - vector_.right());
    }
}

template <typename value_type>
auto VectorView<value_type>::cend() const noexcept
{
    return end();
}

template <typename value_type>
VectorConstView<value_type>::VectorConstView(bound_type left, bound_type right, Vector<value_type> const & vector)
  : left_(left),
    right_(right),
    vector_(vector)
{
    #ifndef HDLTYPES_NO_BOUNDS_CHECK
    if (vector_.ascending() != ascending()) {
        throw std::invalid_argument("Slice direction doesn't match vector's.");
    }
    else if (low() < vector_.low()) {
        throw std::out_of_range("Index out of range.");
    }
    else if (high() > vector_.high()) {
        throw std::out_of_range("Index out of range.");
    }
    #endif
}

template <typename value_type>
value_type const& VectorConstView<value_type>::operator() (bound_type i) const
{
    #ifndef HDLTYPES_NO_BOUNDS_CHECK
    if (i < low()) {
        throw std::out_of_range("Index out of range.");
    }
    else if (i > high()) {
        throw std::out_of_range("Index out of range.");
    }
    #endif
    return vector_(i);
}

template <typename value_type>
VectorConstView<value_type> VectorConstView<value_type>::operator() (bound_type left, bound_type right) const
{
    auto res = VectorConstView<value_type>(left, right, vector_);
    #ifndef HDLTYPES_NO_BOUNDS_CHECK
    if (res.low() < low()) {
        throw std::out_of_range("index out of range");
    }
    if (res.high() > high()) {
        throw std::out_of_range("index out of range");
    }
    #endif
    return res;
}

template <typename value_type>
auto VectorConstView<value_type>::begin() const noexcept
{
    if (ascending()) {
        return vector_.begin() + (left() - vector_.left());
    } else {
        return vector_.begin() + (vector_.left() - left());
    }
}

template <typename value_type>
auto VectorConstView<value_type>::cbegin() const noexcept
{
    return begin();
}

template <typename value_type>
auto VectorConstView<value_type>::end() const noexcept
{
    if (ascending()) {
        return vector_.end() - (vector_.right() - right());
    } else {
        return vector_.end() - (right() - vector_.right());
    }
}

template <typename value_type>
auto VectorConstView<value_type>::cend() const noexcept
{
    return end();
}

}

#endif
