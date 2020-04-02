#pragma once

#include <optional>
#include <string_view>

/**
 * This is just a very small and very simple parser for reverse polish notation
 * to try fuzz-testing.
 */
namespace rpn_parser {
    auto parse(std::string_view input) -> std::optional<int>;
}
