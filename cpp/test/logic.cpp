#include "catch2/catch.hpp"
#include "hdltypes/logic.hpp"

using namespace hdltypes;


TEST_CASE("Logic constructors", "[logic]")
{
    REQUIRE_NOTHROW( Logic() );
}
