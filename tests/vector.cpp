#include "catch2/catch.hpp"
#include <hdltypes/vector.hpp>

using namespace hdltypes;


TEST_CASE("Vector bound attributes", "[vector]")
{
    SECTION("ascending vector") {
        Vector<int> v {1, 2};
        REQUIRE(v.left() == 1);
        REQUIRE(v.right() == 2);
        REQUIRE(v.ascending());
        REQUIRE(v.low() == 1);
        REQUIRE(v.high() == 2);
        REQUIRE(v.length() == 2);
    }
    SECTION("descending vector") {
        Vector<int> w {5, -5};
        REQUIRE(w.left() == 5);
        REQUIRE(w.right() == -5);
        REQUIRE_FALSE(w.ascending());
        REQUIRE(w.low() == -5);
        REQUIRE(w.high() == 5);
        REQUIRE(w.length() == 11);
    }
}

TEST_CASE("Vector indexing and slicing", "[vector]")
{
    SECTION("ascending Vector") {
        Vector<int> v {-2, 2};
        v(1) = 123;
        const Vector<int> cv = v;
        SECTION("indexing non-const Vector") {
            REQUIRE(v(1) == 123);
            REQUIRE_THROWS(v(3));
            REQUIRE_THROWS(v(-80));
        }
        SECTION("indexing const Vector") {
            REQUIRE(cv(1) == 123);
            REQUIRE_THROWS(cv(3));
            REQUIRE_THROWS(cv(-80));
        }
        SECTION("slicing non-const Vector") {
            REQUIRE_THROWS(v(-4, 0));
            REQUIRE_THROWS(v(0, 4));
            REQUIRE_THROWS(v(1, -1));
            VectorView<int> vv = v(-1, 1);
            REQUIRE(vv.left() == -1);
            REQUIRE(vv.right() == 1);
            REQUIRE(vv.ascending());
            REQUIRE(vv.low() == -1);
            REQUIRE(vv.high() == 1);
            REQUIRE(vv.length() == 3);
        }
        SECTION("slicing const Vector") {
            REQUIRE_THROWS(cv(-4, 0));
            REQUIRE_THROWS(cv(0, 4));
            REQUIRE_THROWS(cv(1, -1));
            VectorConstView<int> vv = cv(-1, 1);
            REQUIRE(vv.left() == -1);
            REQUIRE(vv.right() == 1);
            REQUIRE(vv.ascending());
            REQUIRE(vv.low() == -1);
            REQUIRE(vv.high() == 1);
            REQUIRE(vv.length() == 3);
        }
        SECTION("indexing non-const VectorView") {
            VectorView<int> w = v(-1, 1);
            REQUIRE(w(1) == v(1));
            REQUIRE_THROWS(w(-5));
            REQUIRE_THROWS(w(5));
            REQUIRE_THROWS(w(-2));
            REQUIRE_THROWS(w(2));
        }
        SECTION("indexing const VectorView") {
            const VectorView<int> cw = v(-1, 1);
            REQUIRE(cw(1) == v(1));
            REQUIRE_THROWS(cw(-5));
            REQUIRE_THROWS(cw(5));
            REQUIRE_THROWS(cw(-2));
            REQUIRE_THROWS(cw(2));
        }
        SECTION("indexing VectorConstView") {
            VectorConstView<int> cw = cv(-1, 1);
            REQUIRE(cv(1) == cw(1));
            REQUIRE_THROWS(cw(-5));
            REQUIRE_THROWS(cw(5));
            REQUIRE_THROWS(cw(-2));
            REQUIRE_THROWS(cw(2));
        }
        SECTION("slicing non-const VectorView") {
            VectorView<int> w = v(-1, 1);
            REQUIRE_THROWS(w(-3, 0));
            REQUIRE_THROWS(w(0, 3));
            REQUIRE_THROWS(w(1, -1));
            REQUIRE_THROWS(w(-2, 0));
            REQUIRE_THROWS(w(0, 2));
            VectorView<int> z = w(0, 1);
            REQUIRE(z(1) == w(1));
            REQUIRE(z(1) == v(1));
        }
        SECTION("slicing const VectorView") {
            const VectorView<int> w = v(-1, 1);
            REQUIRE_THROWS(w(-3, 0));
            REQUIRE_THROWS(w(0, 3));
            REQUIRE_THROWS(w(1, -1));
            REQUIRE_THROWS(w(-2, 0));
            REQUIRE_THROWS(w(0, 2));
            VectorConstView<int> z = w(0, 1);
            REQUIRE(z(1) == w(1));
            REQUIRE(z(1) == v(1));
        }
        SECTION("slicing VectorConstView") {
            VectorConstView<int> cw = cv(-1, 1);
            REQUIRE_THROWS(cw(-3, 0));
            REQUIRE_THROWS(cw(0, 3));
            REQUIRE_THROWS(cw(1, -1));
            REQUIRE_THROWS(cw(-2, 0));
            REQUIRE_THROWS(cw(0, 2));
            VectorConstView<int> z = cw(0, 1);
            REQUIRE(z(1) == cw(1));
            REQUIRE(z(1) == cv(1));
        }
        SECTION("assigning to VectorView") {
            Vector<int> v {-2, 2};
            SECTION("A Vector (using =)") {
                const Vector<int> w {1, 5};
                v(-2, 2) = w;
                REQUIRE(v(v.left()) == w(w.left()));
                REQUIRE_THROWS(v(0, 1) = w);
            }
            SECTION("A C array using assign(Iterable)") {
                int const a[3] = {0, 1, 2};
                v(-2, 0).assign(a);
                REQUIRE(v(0) == 2);
                REQUIRE_THROWS(v(0, 1) = a);
            }
            SECTION("A std::vector using assign(begin, end), with conversion") {
                std::vector<char> b {'b', 'a', 'd'};
                v(-1, 1).assign(b.begin(), b.end());
                REQUIRE(v(0) == 'a');
                REQUIRE_THROWS(v(0, 1).assign(b.begin(), b.end()));
            }
        }
    }
    SECTION("descending vector") {
        Vector<int> v {2, -2};
        v(1) = 123;
        const Vector<int> cv = v;
        SECTION("indexing non-const Vector") {
            REQUIRE(v(1) == 123);
            REQUIRE_THROWS(v(3));
            REQUIRE_THROWS(v(-80));
        }
        SECTION("indexing const Vector") {
            REQUIRE(cv(1) == 123);
            REQUIRE_THROWS(cv(3));
            REQUIRE_THROWS(cv(-80));
        }
        SECTION("slicing non-const Vector") {
            REQUIRE_THROWS(v(4, 0));
            REQUIRE_THROWS(v(0, -4));
            REQUIRE_THROWS(v(-1, 1));
            REQUIRE_NOTHROW(v(1, -1));
        }
        SECTION("slicing const Vector") {
            REQUIRE_THROWS(cv(4, 0));
            REQUIRE_THROWS(cv(0, -4));
            REQUIRE_THROWS(cv(-1, 1));
            REQUIRE_NOTHROW(cv(1, -1));
        }
        SECTION("indexing non-const VectorView") {
            VectorView<int> w = v(1, -1);
            REQUIRE(w(1) == v(1));
            REQUIRE_THROWS(w(-5));
            REQUIRE_THROWS(w(5));
            REQUIRE_THROWS(w(-2));
            REQUIRE_THROWS(w(2));
        }
        SECTION("indexing const VectorView") {
            const VectorView<int> cw = v(1, -1);
            REQUIRE(cw(1) == v(1));
            REQUIRE_THROWS(cw(-5));
            REQUIRE_THROWS(cw(5));
            REQUIRE_THROWS(cw(-2));
            REQUIRE_THROWS(cw(2));
        }
        SECTION("indexing VectorConstView") {
            VectorConstView<int> cw = cv(1, -1);
            REQUIRE(cv(1) == cw(1));
            REQUIRE_THROWS(cw(-5));
            REQUIRE_THROWS(cw(5));
            REQUIRE_THROWS(cw(-2));
            REQUIRE_THROWS(cw(2));
        }
        SECTION("slicing non-const VectorView") {
            VectorView<int> w = v(1, -1);
            REQUIRE_THROWS(w(3, 0));
            REQUIRE_THROWS(w(0, -3));
            REQUIRE_THROWS(w(-1, 1));
            REQUIRE_THROWS(w(2, 0));
            REQUIRE_THROWS(w(0, -2));
            VectorView<int> z = w(1, 0);
            REQUIRE(z(1) == w(1));
            REQUIRE(z(1) == v(1));
        }
        SECTION("slicing const VectorView") {
            const VectorView<int> w = v(1, -1);
            REQUIRE_THROWS(w(3, 0));
            REQUIRE_THROWS(w(0, -3));
            REQUIRE_THROWS(w(-1, 1));
            REQUIRE_THROWS(w(2, 0));
            REQUIRE_THROWS(w(0, -2));
            VectorConstView<int> z = w(1, 0);
            REQUIRE(z(1) == w(1));
            REQUIRE(z(1) == v(1));
        }
        SECTION("slicing VectorConstView") {
            VectorConstView<int> cw = cv(1, -1);
            REQUIRE_THROWS(cw(3, 0));
            REQUIRE_THROWS(cw(0, -3));
            REQUIRE_THROWS(cw(-1, 1));
            REQUIRE_THROWS(cw(2, 0));
            REQUIRE_THROWS(cw(0, -2));
            VectorConstView<int> z = cw(1, 0);
            REQUIRE(z(1) == cw(1));
            REQUIRE(z(1) == cv(1));
        }
    }
}

TEST_CASE("Vector iteration", "[vector]")
{
    SECTION("ascending vector") {
        Vector<int> v {1, 8};
        SECTION("Vector") {
            for (auto& elem : v) {
                elem = 0;
            }
            const Vector<int> cv = v;
            REQUIRE(std::equal(cv.begin(), cv.end(), v.cbegin()));
            REQUIRE((v.cbegin() + v.length()) == v.cend());
        }
        SECTION("VectorView") {
            VectorView<int> vv = v(v.left(), v.right());
            for (auto& elem : vv) {
                elem = 0;
            }
            const VectorView<int> cvv = vv;
            REQUIRE(std::equal(cvv.begin(), cvv.end(), vv.cbegin()));
            REQUIRE((vv.cend() - vv.cbegin()) == vv.length());
        }
        SECTION("VectorConstView") {
            const Vector<int> cv = v;
            VectorConstView<int> vcv = cv(v.left(), v.right());
            REQUIRE(std::equal(vcv.begin(), vcv.end(), cv.cbegin()));
            REQUIRE((vcv.cend() - vcv.cbegin()) == vcv.length());
        }
    }
    SECTION("descending vector") {
        Vector<int> v {7, 0};
        SECTION("Vector") {
            for (auto& elem : v) {
                elem = 0;
            }
            const Vector<int> cv = v;
            REQUIRE(std::equal(cv.begin(), cv.end(), v.cbegin()));
            REQUIRE((v.cbegin() + v.length()) == v.cend());
        }
        SECTION("VectorView") {
            VectorView<int> vv = v(v.left(), v.right());
            for (auto& elem : vv) {
                elem = 0;
            }
            const VectorView<int> cvv = vv;
            REQUIRE(std::equal(cvv.begin(), cvv.end(), vv.cbegin()));
            REQUIRE((vv.cend() - vv.cbegin()) == vv.length());
        }
        SECTION("VectorConstView") {
            const Vector<int> cv = v;
            VectorConstView<int> vcv = cv(v.left(), v.right());
            REQUIRE(std::equal(vcv.begin(), vcv.end(), cv.cbegin()));
            REQUIRE((vcv.cend() - vcv.cbegin()) == vcv.length());
        }
    }
}

TEST_CASE("Convert iterable to vector", "[vector]")
{
    std::string const s {"example"};
    SECTION("Infered bounds") {
        auto v = to_vector<int>(s);
        REQUIRE((std::size_t)v.length() == s.size());
        REQUIRE(v.left() == 1);
        REQUIRE(v(4) == 'm');
    }
    SECTION("Supplied bounds") {
        REQUIRE_THROWS(to_vector<char>(1, 8, s));
        auto v = to_vector<char>(s.size()-1, 0, s);
        REQUIRE(v.right() == 0);
        REQUIRE((std::size_t)v.length() == s.size());
        REQUIRE(v(0) == 'e');
    }
}

TEST_CASE("Convert iterator pair to vector", "[vector]")
{
    std::string const s {"example"};
    auto const begin = s.begin();
    auto const end = s.end();
    SECTION("Infered bounds") {
        auto v = to_vector<int>(begin, end);
        REQUIRE((std::size_t)v.length() == s.size());
        REQUIRE(v.left() == 1);
        REQUIRE(v(4) == 'm');
    }
    SECTION("Supplied bounds") {
        REQUIRE_THROWS(to_vector<char>(1, 8, begin, end));
        auto v = to_vector<char>(s.size()-1, 0, begin, end);
        REQUIRE(v.right() == 0);
        REQUIRE((std::size_t)v.length() == s.size());
        REQUIRE(v(0) == 'e');
    }
}

TEST_CASE("Convert array to vector", "[vector]")
{
    constexpr int N = 4;
    std::int8_t const wow[N] = {5, 6, 4, 3};
    SECTION("Infered bounds") {
        auto v = to_vector<long>(wow);
        REQUIRE(v.length() == N);
        REQUIRE(v.left() == 1);
        REQUIRE(v(1) == 5);
    }
    SECTION("Supplied bounds") {
        REQUIRE_THROWS(to_vector<long>(1, 8, wow));
        auto v = to_vector<long>(N-1, 0, wow);
        REQUIRE(v.right() == 0);
        REQUIRE(v.length() == N);
        REQUIRE(v(0) == 3);
    }
}
