#ifndef HDLTYPES_VECTOR_HPP
#define HDLTYPES_VECTOR_HPP

#include <vector>               // vector
#include <cstdint>              // fixed ints
#include <type_traits>          // enable_if, is_convertible
#include <algorithm>            // copy
#include <iterator>             // distance, begin, end
#include <utility>              // declval
#include <hdltypes/utils.hpp>   // is_iterable


namespace hdltypes {

/** DESIGN NOTES

    */

template <typename value_type>
class Vector;

template <typename value_type>
class VectorView;

template <typename value_type>
class VectorConstView;


template <typename value_type_>
class Vector {
public: // types
    using value_type = value_type_;
    using bound_type = hdltypes::bound_type;
public: // constructors
    Vector() = delete;
    Vector(bound_type left, bound_type right);
public: // attributes
    bound_type left() const noexcept { return left_; }
    bound_type right() const noexcept { return right_; }
    bool ascending() const noexcept { return left() <= right(); }
    bound_type high() const noexcept { return ascending() ? right() : left(); }
    bound_type low() const noexcept { return ascending() ? left() : right(); }
    bound_type length() const noexcept { return high() - low() + 1; }
public: // indexing and slicing
    value_type & operator() (bound_type i);
    value_type const & operator() (bound_type i) const;
    VectorView<value_type> operator() (bound_type left, bound_type right);
    VectorConstView<value_type> operator() (bound_type left, bound_type right) const;
public: // iteration
    auto begin() noexcept { return array_.begin(); }
    auto begin() const noexcept { return array_.begin(); }
    auto cbegin() const noexcept { return array_.cbegin(); }
    auto end() noexcept { return array_.end(); }
    auto end() const noexcept { return array_.end(); }
    auto cend() const noexcept { return array_.cend(); }
protected:
    bound_type index_helper(bound_type idx) const;
private:
    bound_type left_;
    bound_type right_;
    std::vector<value_type> array_;
};

template <typename value_type_>
class VectorView {
public:
    using value_type = value_type_;
    using bound_type = hdltypes::bound_type;
    friend class Vector<value_type>;
public: // constructors
    VectorView() = delete;
    VectorView(VectorView<value_type> const &) = default;
    VectorView(VectorView<value_type> &&) = default;
private: // constructors
    VectorView(bound_type left, bound_type right, Vector<value_type> & vector);
public: // attributes
    bound_type left() const noexcept { return left_; }
    bound_type right() const noexcept { return right_; }
    bool ascending() const noexcept { return left() <= right(); }
    bound_type high() const noexcept { return ascending() ? right() : left(); }
    bound_type low() const noexcept { return ascending() ? left() : right(); }
    bound_type length() const noexcept { return high() - low() + 1; }
public: // indexing and slicing
    value_type & operator() (bound_type i);
    value_type const & operator() (bound_type i) const;
    VectorView<value_type> operator() (bound_type left, bound_type right);
    VectorConstView<value_type> operator() (bound_type left, bound_type right) const;
public: // assignment
    VectorView<value_type> & operator= (VectorView<value_type> const &) = delete;
    VectorView<value_type> & operator= (VectorView<value_type> &&) = delete;
    template <typename Iterator, typename std::enable_if<
        std::is_convertible<decltype(*std::declval<Iterator>()), value_type>::value &&
        true
    , int>::type = 0>
    VectorView<value_type> & assign (Iterator const & start, Iterator const & end);
    template <typename Iterable, typename std::enable_if<
        //util::is_iterable<Iterable>::value &&
        std::is_convertible<decltype(*std::begin(std::declval<Iterable&>())), value_type>::value &&
        true
    , int>::type = 0>
    VectorView<value_type> & assign (Iterable const & it);
    template <typename Iterable, typename std::enable_if<
        //util::is_iterable<Iterable>::value &&
        std::is_convertible<decltype(*std::begin(std::declval<Iterable&>())), value_type>::value &&
        true
    , int>::type = 0>
    VectorView<value_type> & operator= (Iterable const & it) { return assign(it); }
public: // iteration
    auto begin() noexcept;
    auto begin() const noexcept;
    auto cbegin() const noexcept;
    auto end() noexcept;
    auto end() const noexcept;
    auto cend() const noexcept;
private:
    bound_type left_;
    bound_type right_;
    Vector<value_type> & vector_;
};

template <typename value_type_>
class VectorConstView {
public:
    using value_type = value_type_;
    using bound_type = hdltypes::bound_type;
    friend class Vector<value_type>;
    friend class VectorView<value_type>;
public: // constructors
    VectorConstView() = delete;
    VectorConstView(VectorConstView<value_type> const &) = default;
    VectorConstView(VectorConstView<value_type> &&) = default;
private: // constructors
    VectorConstView(bound_type left, bound_type right, Vector<value_type> const & vector);
public: // attributes
    bound_type left() const noexcept { return left_; }
    bound_type right() const noexcept { return right_; }
    bool ascending() const noexcept { return left() <= right(); }
    bound_type high() const noexcept { return ascending() ? right() : left(); }
    bound_type low() const noexcept { return ascending() ? left() : right(); }
    bound_type length() const noexcept { return high() - low() + 1; }
public: // indexing and slicing
    value_type const & operator() (bound_type i) const;
    VectorConstView<value_type> operator() (bound_type left, bound_type right) const;
public: // assignment
    VectorView<value_type> & operator= (VectorView<value_type> const &) = delete;
    VectorView<value_type> & operator= (VectorView<value_type> &&) = delete;
public: // iteration
    auto begin() const noexcept;
    auto cbegin() const noexcept;
    auto end() const noexcept;
    auto cend() const noexcept;
private:
    bound_type left_;
    bound_type right_;
    Vector<value_type> const & vector_;
};

}

#include "hdltypes/impl/vector.hpp"

#endif
