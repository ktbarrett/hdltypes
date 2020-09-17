#include <hdltypes/range.hpp>
#include <catch2/catch.hpp>

using namespace hdltypes;


TEST_CASE("Compile-time range ascending", "[range]")
{
    auto a = range<1, TO, 8>();
    REQUIRE(a.left() == 1);
    REQUIRE(a.right() == 8);
    REQUIRE(a.ascending());
    REQUIRE(a.low() == 1);
    REQUIRE(a.high() == 8);
    REQUIRE(a.length() == 8);
    REQUIRE(sizeof(a) == 0);
}
