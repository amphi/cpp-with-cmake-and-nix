#include <cstdint>
#include <cstdio>
#include <string>

#include <rpn_parser.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* Data, size_t Size)
{
    auto convert = [](const uint8_t* d, size_t sz) {
        std::string s {};
        s.reserve(sz);

        for (unsigned i { 0 }; i < sz; i++) {
            s += std::string(reinterpret_cast<const char*>(d + i));
        }

        return s;
    };

    auto input { convert(Data, Size) };
    std::printf("Input: \"%s\" is ", input.c_str());

    auto output { rpn_parser::parse(input) };
    if (output) {
        std::printf("a valid rpn expression. Result: %i.\n", output.value());
    } else {
        std::printf("no valid rpn expression.\n");
    }
    return 0;
}
