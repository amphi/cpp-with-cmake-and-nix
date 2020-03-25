#include <climits>
#include <cstdint>

#include <catch2/catch.hpp>

#include <bitmanipulation.hpp>

namespace bmi = bitmanipulation;

template <class T>
constexpr unsigned bitlen(T v) { return sizeof(v) * CHAR_BIT; }

TEST_CASE("popcnt, tzcnt and lzcnt works when all bits are cleared", "[bitmanipulation]")
{
    SECTION("functions works for 8 bit values") {
        uint8_t value { 0u };

        REQUIRE(bmi::popcnt(value) == 0);
        REQUIRE(bmi::lzcnt(value) == bitlen(value));
        REQUIRE(bmi::tzcnt(value) == bitlen(value));
    }

    SECTION("functions works for 16 bit values") {
        uint16_t value { 0u };

        REQUIRE(bmi::popcnt(value) == 0);
        REQUIRE(bmi::lzcnt(value) == bitlen(value));
        REQUIRE(bmi::tzcnt(value) == bitlen(value));
    }

    SECTION("functions works for 32 bit values") {
        uint32_t value { 0u };

        REQUIRE(bmi::popcnt(value) == 0);
        REQUIRE(bmi::lzcnt(value) == bitlen(value));
        REQUIRE(bmi::tzcnt(value) == bitlen(value));
    }

    SECTION("functions works for 64 bit values") {
        uint64_t value { 0u };

        REQUIRE(bmi::popcnt(value) == 0);
        REQUIRE(bmi::lzcnt(value) == bitlen(value));
        REQUIRE(bmi::tzcnt(value) == bitlen(value));
    }
}

TEST_CASE("popcnt, tzcnt and lzcnt works when all bits are set", "[bitmanipulation]")
{
    SECTION("functions works for 8 bit values") {
        uint8_t value { bmi::mask(8) };

        REQUIRE(bmi::popcnt(value) == bitlen(value));
        REQUIRE(bmi::lzcnt(value) == 0);
        REQUIRE(bmi::tzcnt(value) == 0);
    }

    SECTION("functions works for 16 bit values") {
        uint16_t value { bmi::mask(16) };

        REQUIRE(bmi::popcnt(value) == bitlen(value));
        REQUIRE(bmi::lzcnt(value) == 0);
        REQUIRE(bmi::tzcnt(value) == 0);
    }

    SECTION("functions works for 32 bit values") {
        uint32_t value { ~0u };

        REQUIRE(bmi::popcnt(value) == bitlen(value));
        REQUIRE(bmi::lzcnt(value) == 0);
        REQUIRE(bmi::tzcnt(value) == 0);
    }

    SECTION("functions works for 64 bit values") {
        uint64_t value { ~0ull };

        REQUIRE(bmi::popcnt(value) == bitlen(value));
        REQUIRE(bmi::lzcnt(value) == 0);
        REQUIRE(bmi::tzcnt(value) == 0);
    }
}

TEST_CASE("Values can be manipulated bitwise", "[bitmanipulation]")
{
    uint8_t mask = bmi::mask(3, 3);

    REQUIRE(mask == 0b00111000);
    REQUIRE(bmi::popcnt(mask) == 3);
    REQUIRE(bmi::lzcnt(mask) == 2);
    REQUIRE(bmi::tzcnt(mask) == 3);

    SECTION("bits in values can be set") {
	    mask = bmi::set_bits(mask, 1);

	    REQUIRE(mask == 0b00111001);
        REQUIRE(bmi::popcnt(mask) == 4);
        REQUIRE(bmi::lzcnt(mask) == 2);
        REQUIRE(bmi::tzcnt(mask) == 0);
    }

    SECTION("setting bits that are already set leaves them as they are") {
	    mask = bmi::set_bits(mask, 2, 2);

	    REQUIRE(mask == 0b00111100);
        REQUIRE(bmi::popcnt(mask) == 4);
        REQUIRE(bmi::lzcnt(mask) == 2);
        REQUIRE(bmi::tzcnt(mask) == 2);
    }

    SECTION("bits in values can be cleared") {
	    mask = bmi::clear_bits(mask, 1, 3);

	    REQUIRE(mask == 0b00110000);
        REQUIRE(bmi::popcnt(mask) == 2);
        REQUIRE(bmi::lzcnt(mask) == 2);
        REQUIRE(bmi::tzcnt(mask) == 4);
    }

    SECTION("clearing bits that are already cleared leaves them as they are") {
	    mask = bmi::clear_bits(mask, 2, 2);

	    REQUIRE(mask == 0b00110000);
        REQUIRE(bmi::popcnt(mask) == 2);
        REQUIRE(bmi::lzcnt(mask) == 2);
        REQUIRE(bmi::tzcnt(mask) == 4);
    }
}


TEST_CASE("bitmanipulation functions work as expected", "[bitmanipulation]")
{
    SECTION("isolate lowest clear bit works as expected") {
        REQUIRE(bmi::blci(uint8_t(0b00000000)) == uint8_t(0b11111110));
        REQUIRE(bmi::blci(uint8_t(0b11111111)) == uint8_t(0b11111111));
        REQUIRE(bmi::blci(uint8_t(0b11100011)) == uint8_t(0b11111011));
    }

    SECTION("isolate lowest set bit works as expected") {
        REQUIRE(bmi::blsi(uint8_t(0b00000000)) == uint8_t(0b00000000));
        REQUIRE(bmi::blsi(uint8_t(0b11111111)) == uint8_t(0b00000001));
        REQUIRE(bmi::blsi(uint8_t(0b11100110)) == uint8_t(0b00000010));
    }

    SECTION("fill from lowest clear bit works as expected") {
        REQUIRE(bmi::blcfill(uint8_t(0b00000000)) == uint8_t(0b00000000));
        REQUIRE(bmi::blcfill(uint8_t(0b11111111)) == uint8_t(0b11111111));
        REQUIRE(bmi::blcfill(uint8_t(0b11101011)) == uint8_t(0b11101000));
    }

    SECTION("fill from lowest set bit works as expected") {
        REQUIRE(bmi::blsfill(uint8_t(0b00000000)) == uint8_t(0b00000000));
        REQUIRE(bmi::blsfill(uint8_t(0b11111111)) == uint8_t(0b11111111));
        REQUIRE(bmi::blsfill(uint8_t(0b01110100)) == uint8_t(0b01110111));
    }

    SECTION("clear lowest set bit works as expected") {
        REQUIRE(bmi::blsc(uint8_t(0b00000000)) == uint8_t(0b00000000));
        REQUIRE(bmi::blsc(uint8_t(0b11111111)) == uint8_t(0b11111110));
        REQUIRE(bmi::blsc(uint8_t(0b11100010)) == uint8_t(0b11100000));
    }

    SECTION("set lowest clear bit works as expected") {
        REQUIRE(bmi::blcs(uint8_t(0b00000000)) == uint8_t(0b00000001));
        REQUIRE(bmi::blcs(uint8_t(0b11111111)) == uint8_t(0b11111111));
        REQUIRE(bmi::blcs(uint8_t(0b11100011)) == uint8_t(0b11100111));
    }
}
