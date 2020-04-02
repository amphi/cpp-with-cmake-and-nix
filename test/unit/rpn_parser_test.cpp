#include <catch2/catch.hpp>

#include <rpn_parser.hpp>

namespace rpn = rpn_parser;

TEST_CASE("rpn parser supports all four calculation operations", "[rpn_parser]")
{
    SECTION("addition works") {
        SECTION("with two positive values") {
            auto calculated_value { rpn::parse("2 2 +") };
            int  expected_value   { 4 };

            REQUIRE(calculated_value);
            REQUIRE(calculated_value.value() == expected_value);
        }
        SECTION("with a positive and a negative value") {
            auto calculated_value { rpn::parse("2 -2 +") };
            int  expected_value   { 0 };

            REQUIRE(calculated_value);
            REQUIRE(calculated_value.value() == expected_value);
        }
        SECTION("with two negative values") {
            auto calculated_value { rpn::parse("-2 -2 +") };
            int  expected_value   { -4 };

            REQUIRE(calculated_value);
            REQUIRE(calculated_value.value() == expected_value);
        }
    }

    SECTION("subtraction works") {
        SECTION("with two positive values") {
            auto calculated_value { rpn::parse("2 2 -") };
            int  expected_value   { 0 };

            REQUIRE(calculated_value);
            REQUIRE(calculated_value.value() == expected_value);
        }
        SECTION("with a positive and a negative value") {
            auto calculated_value { rpn::parse("2 -2 -") };
            int  expected_value   { 4 };

            REQUIRE(calculated_value);
            REQUIRE(calculated_value.value() == expected_value);
        }
        SECTION("with a negative and a positive value") {
            auto calculated_value { rpn::parse("-2 2 -") };
            int  expected_value   { -4 };

            REQUIRE(calculated_value);
            REQUIRE(calculated_value.value() == expected_value);
        }
        SECTION("with two negative values") {
            auto calculated_value { rpn::parse("-2 -2 -") };
            int  expected_value   { 0 };

            REQUIRE(calculated_value);
            REQUIRE(calculated_value.value() == expected_value);
        }
    }

    SECTION("multiplication works") {
        SECTION("with two positive values") {
            auto calculated_value { rpn::parse("2 2 *") };
            int  expected_value   { 4 };

            REQUIRE(calculated_value);
            REQUIRE(calculated_value.value() == expected_value);
        }
        SECTION("with a positive and a negative value") {
            auto calculated_value { rpn::parse("2 -2 *") };
            int  expected_value   { -4 };

            REQUIRE(calculated_value);
            REQUIRE(calculated_value.value() == expected_value);
        }
        SECTION("with two negative values") {
            auto calculated_value { rpn::parse("-2 -2 *") };
            int  expected_value   { 4 };

            REQUIRE(calculated_value);
            REQUIRE(calculated_value.value() == expected_value);
        }
    }

    SECTION("division works") {
        SECTION("with two positive values") {
            auto calculated_value { rpn::parse("2 2 /") };
            int  expected_value   { 1 };

            REQUIRE(calculated_value);
            REQUIRE(calculated_value.value() == expected_value);
        }
        SECTION("with a positive and a negative value") {
            auto calculated_value { rpn::parse("2 -2 /") };
            int  expected_value   { -1 };

            REQUIRE(calculated_value);
            REQUIRE(calculated_value.value() == expected_value);
        }
        SECTION("with two negative values") {
            auto calculated_value { rpn::parse("-2 -2 /") };
            int  expected_value   { 1 };

            REQUIRE(calculated_value);
            REQUIRE(calculated_value.value() == expected_value);
        }
    }
}
