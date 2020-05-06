#include "catch2/catch.hpp"
#include <hdltypes/logic.hpp>

using namespace hdltypes;


TEST_CASE("Logic constructors", "[logic]")
{
    REQUIRE_NOTHROW( Logic() );
    REQUIRE_NOTHROW( Logic(0) );
    REQUIRE_NOTHROW( Logic(1) );
    REQUIRE_NOTHROW( Logic(false) );
    REQUIRE_NOTHROW( Logic(true) );
    REQUIRE_NOTHROW( Logic('U') );
    REQUIRE_NOTHROW( Logic('u') );
    REQUIRE_NOTHROW( Logic('X') );
    REQUIRE_NOTHROW( Logic('x') );
    REQUIRE_NOTHROW( Logic('0') );
    REQUIRE_NOTHROW( Logic('1') );
    REQUIRE_NOTHROW( Logic('Z') );
    REQUIRE_NOTHROW( Logic('z') );
    REQUIRE_NOTHROW( Logic('W') );
    REQUIRE_NOTHROW( Logic('w') );
    REQUIRE_NOTHROW( Logic('L') );
    REQUIRE_NOTHROW( Logic('l') );
    REQUIRE_NOTHROW( Logic('H') );
    REQUIRE_NOTHROW( Logic('h') );
    REQUIRE_NOTHROW( Logic('-') );
    REQUIRE_NOTHROW( Logic(Bit(0)) );

    REQUIRE_THROWS( Logic(6578) );
    REQUIRE_THROWS( Logic('3') );
}

TEST_CASE("Bit constructors", "[logic]")
{
    REQUIRE_NOTHROW( Bit() );
    REQUIRE_NOTHROW( Bit(0) );
    REQUIRE_NOTHROW( Bit(1) );
    REQUIRE_NOTHROW( Bit(false) );
    REQUIRE_NOTHROW( Bit(true) );
    REQUIRE_NOTHROW( Bit('0') );
    REQUIRE_NOTHROW( Bit('1') );
    REQUIRE_NOTHROW( Bit(Logic(0)) );
}

TEST_CASE("Logic bitops", "[logic]")
{
    Logic a {'L'};
    Logic b {1};

    REQUIRE( (a & b) == Logic(0) );
    REQUIRE( (a | b) == Logic(1) );
    REQUIRE( (a ^ b) == Logic(1) );
    REQUIRE( ~a == Logic(1) );
}

TEST_CASE("Bit bitops", "[logic]")
{
    Bit a {0};
    Bit b {1};

    REQUIRE( (a & b) == Bit(0) );
    REQUIRE( (a | b) == Bit(1) );
    REQUIRE( (a ^ b) == Bit(1) );
    REQUIRE( ~a == Bit(1) );
}

TEST_CASE("Logic and Bit bitops automatic conversion", "[logic]")
{
    REQUIRE_NOTHROW( Bit(0) | '1' != 0 );
    REQUIRE_NOTHROW( false ^ Logic(0) );
    REQUIRE_NOTHROW( Bit('0') & Logic('Z') );
}
