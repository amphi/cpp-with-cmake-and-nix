#include "rpn_parser.hpp"

#include <cctype>
#include <cstdint>
#include <queue>
#include <stack>
#include <stdexcept>
#include <string>

namespace {
    enum class token_type_t { OPERATOR, OPERAND };
    class token_t {
    public:
        token_t(std::size_t from, std::size_t count, token_type_t type)
            : from_(from)
            , count_(count)
            , type_(type)
        { }

        [[nodiscard]] auto  from() const -> std::size_t { return from_;  }
        [[nodiscard]] auto count() const -> std::size_t { return count_; }

        [[nodiscard]] auto type() const -> token_type_t { return type_;  }

    private:
        std::size_t from_;
        std::size_t count_;
        token_type_t type_;
    };

    auto tokenize(std::string_view input)
        -> std::optional<std::queue<token_t>>
    {
        std::queue<token_t> tokens {};
        std::size_t pos { 0 };

        auto isoperator = [](const char c) {
            return c == '+' || c == '-' || c == '*' || c == '/';
        };

        while (pos < input.length()) {
            if (std::isblank(input[pos]) != 0) {
                pos++;
                continue;
            }

            if (std::isdigit(input[pos]) != 0
                    || (std::isdigit(input[pos+1]) != 0 && input[pos] == '-')) {

                std::size_t count { 1 };
                while (std::isdigit(input[pos+count]) != 0) {
                    count++;
                }
                tokens.emplace(pos, count-1, token_type_t::OPERAND);
                pos += count;
                continue;
            }

            if (isoperator(input[pos])) {
                tokens.emplace(pos, 1, token_type_t::OPERATOR);
                pos++;
                continue;
            }

            return std::nullopt;
            //throw std::invalid_argument(
            //            "Unexpected character " + std::string(input.substr(pos, 1)) +
            //            " at position " + std::to_string(pos) + ".");
        }

        return tokens;
    }
}

auto rpn_parser::parse(std::string_view input)
    -> std::optional<int>
{
    auto tokens { tokenize(input) };
    if (!tokens) {
        return std::nullopt;
    }

    std::stack<int> stack {};

    while (!tokens->empty()) {
        auto token { tokens->front() };

        if (token.type() == token_type_t::OPERAND) {
            int number { 0 };
            try {
                number = std::stoi(input.substr(token.from(), token.count()).data());
            } catch (const std::out_of_range& /* e */) {
                return std::nullopt;
            }

            stack.emplace(number);

        } else {
            if (stack.size() < 2) {
                //throw std::invalid_argument(
                //    "Not enough operands for operator " + std::string(input.substr(token.from(), 1)) +
                //    " at position " + std::to_string(token.from()) + ".");
                return std::nullopt;
            }

            auto op2 { stack.top() };
            stack.pop();

            auto op1 { stack.top() };
            stack.pop();

            switch (input[token.from()]) {
                case '+':
                    stack.emplace(op1 + op2);
                    break;
                case '-':
                    stack.emplace(op1 - op2);
                    break;
                case '*':
                    stack.emplace(op1 * op2);
                    break;
                case '/':
                    stack.emplace(op1 / op2);
                    break;
            }
        }

        tokens->pop();
    }

    if (stack.size() > 1) {
        //throw std::invalid_argument(
        //    "There are too many operands. Calculation finished but there are " +
        //    std::to_string(stack.size()) + " operands left. (Should be one!)");
        return std::nullopt;
    }

    if (stack.empty()) {
        //throw std::invalid_argument(
        //    "There were no numbers in the input.);
        return std::nullopt;
    }

    return stack.top();
}
