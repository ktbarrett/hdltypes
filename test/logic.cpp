#include "catch2/catch.hpp"
#include <hdltypes/logic.hpp>

using namespace hdltypes;


TEST_CASE("Logic serialization", "[logic]")
{
    REQUIRE( Logic::deserialize('U').serialize() == 'U' );
    REQUIRE( Logic::deserialize('u').serialize() == 'U' );
    REQUIRE( Logic::deserialize('X').serialize() == 'X' );
    REQUIRE( Logic::deserialize('x').serialize() == 'X' );
    REQUIRE( Logic::deserialize('0').serialize() == '0' );
    REQUIRE( Logic::deserialize('1').serialize() == '1' );
    REQUIRE( Logic::deserialize('Z').serialize() == 'Z' );
    REQUIRE( Logic::deserialize('z').serialize() == 'Z' );
    REQUIRE( Logic::deserialize('W').serialize() == 'W' );
    REQUIRE( Logic::deserialize('w').serialize() == 'W' );
    REQUIRE( Logic::deserialize('L').serialize() == 'L' );
    REQUIRE( Logic::deserialize('l').serialize() == 'L' );
    REQUIRE( Logic::deserialize('H').serialize() == 'H' );
    REQUIRE( Logic::deserialize('h').serialize() == 'H' );
    REQUIRE( Logic::deserialize('-').serialize() == '-' );

    REQUIRE_THROWS( Logic::deserialize('8') );
    REQUIRE_THROWS( Logic::deserialize('\0') );
}

TEST_CASE("Logic conversions", "[logic]")
{
    REQUIRE( to_int(to_logic(0)) == 0 );
    REQUIRE( to_int(to_logic(1)) == 1 );

    REQUIRE( to_bool(to_logic(false)) == false );
    REQUIRE( to_bool(to_logic(true)) == true );

    REQUIRE_THROWS( to_int('U'_l) );
    REQUIRE_THROWS( to_bool('U'_l) );
    REQUIRE_THROWS( to_logic(2) );
}

TEST_CASE("Logic attributes", "[logic]")
{
    REQUIRE( is01('0'_l) );
    REQUIRE_FALSE( is01('z'_l) );

    REQUIRE( ('U'_l).value() == 0 );
    REQUIRE( ('X'_l).value() == 1 );
    REQUIRE( ('0'_l).value() == 2 );
    REQUIRE( ('1'_l).value() == 3 );
    REQUIRE( ('Z'_l).value() == 4 );
    REQUIRE( ('W'_l).value() == 5 );
    REQUIRE( ('L'_l).value() == 6 );
    REQUIRE( ('H'_l).value() == 7 );
    REQUIRE( ('-'_l).value() == 8 );
}

TEST_CASE("Logic operations", "[logic]")
{
    REQUIRE( '0'_l == '0'_l );
    REQUIRE( 'W'_l != 'X'_l );

    REQUIRE( ('0'_l & '1'_l) == '0'_l );
    REQUIRE( ('0'_l | '1'_l) == '1'_l );
    REQUIRE( ('X'_l ^ 'L'_l) == 'X'_l );
    REQUIRE( ('W'_l & 'U'_l) == 'U'_l );
    REQUIRE( ~'L'_l == '1'_l );
}