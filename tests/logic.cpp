#include "catch2/catch.hpp"
#include <hdltypes.hpp>

using namespace hdltypes;


TEST_CASE("Logic char conversions", "[logic]")
{
    REQUIRE( to_char(to_logic('U')) == 'U' );
    REQUIRE( to_char(to_logic('u')) == 'U' );
    REQUIRE( to_char(to_logic('X')) == 'X' );
    REQUIRE( to_char(to_logic('x')) == 'X' );
    REQUIRE( to_char(to_logic('0')) == '0' );
    REQUIRE( to_char(to_logic('1')) == '1' );
    REQUIRE( to_char(to_logic('Z')) == 'Z' );
    REQUIRE( to_char(to_logic('z')) == 'Z' );
    REQUIRE( to_char(to_logic('W')) == 'W' );
    REQUIRE( to_char(to_logic('w')) == 'W' );
    REQUIRE( to_char(to_logic('L')) == 'L' );
    REQUIRE( to_char(to_logic('l')) == 'L' );
    REQUIRE( to_char(to_logic('H')) == 'H' );
    REQUIRE( to_char(to_logic('h')) == 'H' );
    REQUIRE( to_char(to_logic('-')) == '-' );

    REQUIRE_THROWS( to_logic('8') );
    REQUIRE_THROWS( to_logic('\0') );
}

TEST_CASE("Logic int conversions", "[logic]")
{
    REQUIRE( to_int(to_logic(0)) == 0 );
    REQUIRE( to_int(to_logic(1)) == 1 );

    REQUIRE_THROWS( to_int('U'_l) );
    REQUIRE_THROWS( to_logic(2) );
}

TEST_CASE("Logic bool conversions", "[logic]")
{
    REQUIRE( to_bool(to_logic(false)) == false );
    REQUIRE( to_bool(to_logic(true)) == true );

    REQUIRE_THROWS( to_bool('U'_l) );
}

TEST_CASE("Logic/Bit conversions", "[logic]")
{
    REQUIRE( to_logic('X'_l) == 'X'_l);
    REQUIRE( to_logic('0'_b) == '0'_l);
    REQUIRE( to_bit('0'_l) == '0'_b );
    REQUIRE( to_bit('1'_b) == '1'_b );

    REQUIRE_THROWS( to_bit('U'_l) );
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

    {   auto a = 'H'_l;
        a &= '1'_l;
        REQUIRE(a == '1'_l);
    }

    {   auto a = '0'_l;
        a |= '1'_l;
        REQUIRE(a == '1'_l);
    }

    {   auto a = 'W'_l;
        a ^= '1'_l;
        REQUIRE(a == 'X'_l);
    }

    {   auto a = '0'_l;
        inplace_invert(a);
        REQUIRE(a == '1'_l);
    }
}

TEST_CASE("Bit char conversions", "[logic]")
{
    REQUIRE( to_char(to_bit('0')) == '0' );
    REQUIRE( to_char(to_bit('1')) == '1' );

    REQUIRE_THROWS( to_bit('\0') );
    REQUIRE_THROWS( to_bit('X') );
}

TEST_CASE("Bit int conversions", "[logic]")
{
    REQUIRE( to_bit(0) == '0'_b );
    REQUIRE( to_bit(1) == '1'_b );

    REQUIRE_THROWS( to_bit(123) );
}

TEST_CASE("Bit bool conversions", "[logic]")
{
    REQUIRE( to_bit(false) == '0'_b );
    REQUIRE( to_bit(true) == '1'_b );
}

TEST_CASE("Bit attributes", "[logic]")
{
    REQUIRE( is01('0'_b) );
    REQUIRE( is01('1'_b) );

    REQUIRE( ('0'_b).value() == 0 );
    REQUIRE( ('1'_b).value() == 1 );
}

TEST_CASE("Bit operations", "[logic]")
{
    REQUIRE( '0'_b == '0'_b );
    REQUIRE( '0'_b != '1'_b );

    // we can afford to be exhaustive
    REQUIRE( ('0'_b & '0'_b) == '0'_b );
    REQUIRE( ('0'_b & '1'_b) == '0'_b );
    REQUIRE( ('1'_b & '0'_b) == '0'_b );
    REQUIRE( ('1'_b & '1'_b) == '1'_b );

    REQUIRE( ('0'_b | '0'_b) == '0'_b );
    REQUIRE( ('0'_b | '1'_b) == '1'_b );
    REQUIRE( ('1'_b | '0'_b) == '1'_b );
    REQUIRE( ('1'_b | '1'_b) == '1'_b );

    REQUIRE( ('0'_b ^ '0'_b) == '0'_b );
    REQUIRE( ('0'_b ^ '1'_b) == '1'_b );
    REQUIRE( ('1'_b ^ '0'_b) == '1'_b );
    REQUIRE( ('1'_b ^ '1'_b) == '0'_b );

    REQUIRE( ~'0'_b == '1'_b );
    REQUIRE( ~'1'_b == '0'_b );

    {   auto a = '0'_b;
        a &= '1'_b;
        REQUIRE(a == '0'_b);
    }

    {   auto a = '0'_b;
        a |= '1'_b;
        REQUIRE(a == '1'_b);
    }

    {   auto a = '1'_b;
        a ^= '1'_b;
        REQUIRE(a == '0'_b);
    }

    {   auto a = '0'_b;
        inplace_invert(a);
        REQUIRE(a == '1'_b);
    }
}
