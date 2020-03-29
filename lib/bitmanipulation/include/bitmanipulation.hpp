#pragma once

#include <climits>
#include <cstdint>

namespace bitmanipulation {

/**
 * Creates a bitmask. E.g. mask(2,2) = 0b1100
 * @param bits  the number of set bits in the mask
 * @param shift the set bits in the mask will be shifted to the left by this amount
 */
[[nodiscard]] constexpr auto mask(unsigned bits, unsigned shift = 0) -> uintmax_t
{
    return ~(static_cast<uintmax_t>(~0) << bits) << shift;
}

/**
 * Sets bits in a given value and returns the value with the additional set bits.
 * E.g. set_bits(0b1100, 2, 0) = 0b1111
 * @param value the given value
 * @param bits  the number of bits to set
 * @param shift the additionally set bits will be shifted to the left by this amount
 */
template <class T>
[[nodiscard]] constexpr auto set_bits(T value, unsigned bits, unsigned shift = 0) -> T
{
    T mask = static_cast<T>(bitmanipulation::mask(bits, shift));
    return value | mask;
}

/**
 * Clears bits in a given value and returns the value with the cleared bits.
 * E.g. clear_bits(0b1111, 2, 1) = 0b1001
 * @param value the given value
 * @param bits  the number of bits to clear
 * @param shift the cleared bits will be shifted to the left by this amount
 */
template <class T>
[[nodiscard]] constexpr auto clear_bits(T value, unsigned bits, unsigned shift = 0) -> T
{
    T mask = static_cast<T>(bitmanipulation::mask(bits, shift));
    return value & static_cast<T>(~mask);
}

/**
 * Returns the number of set bits in the given value.
 * E.g. count_bits_set(0b11) = 2
 */
template <class T>
[[nodiscard]] constexpr auto count_bits_set(T value) -> unsigned
{
    unsigned count { 0u };
    for (; value; count++) {
        value = value & static_cast<T>(value - 1);
    }
    return count;
}

template <class T>
[[nodiscard]] constexpr auto popcnt(T value) -> unsigned { return count_bits_set(value); }

/**
 * Returns the number of leading zeroes in the given value.
 * E.g. leading_zeroes_count(0b00001111) = 4
 */
template <class T>
[[nodiscard]] constexpr auto leading_zeroes_count(T value) -> unsigned
{
    if (value == 0) {
        return sizeof(value) * CHAR_BIT;
    }

    unsigned       count {                       0u };
    const unsigned len   { sizeof(value) * CHAR_BIT };

    for (unsigned i = 1; i <= len; i++) {
        if (bitmanipulation::mask(1, len - i) & value) {
            break;
        }
        count++;
    }

    return count;
}

template <class T>
[[nodiscard]] constexpr auto lzcnt(T value) -> unsigned { return leading_zeroes_count(value); }

/**
 * Returns the number of trailing zeroes in the given value.
 * E.g. trailing_zeroes_count(0b1100) = 2
 */
template <class T>
constexpr auto trailing_zeroes_count(T value) -> unsigned
{
    if (value == 0) {
        return sizeof(value) * CHAR_BIT;
    }

    unsigned       count {                       0u };
    const unsigned len   { sizeof(value) * CHAR_BIT };

    for (unsigned i = 0; i < len; i++) {
        if (bitmanipulation::mask(1, i) & value) {
            break;
        }
        count++;
    }

    return count;
}

template <class T>
[[nodiscard]] constexpr auto tzcnt(T value) -> unsigned { return trailing_zeroes_count(value); }

/**
 * Isolates the lowest clear bit in the given value.
 * E.g. isolate_lowest_clear_bit(0b11100011) = 0b11111011
 */
template <class T>
[[nodiscard]] constexpr auto isolate_lowest_clear_bit(T v) -> T
{
    return v | static_cast<T>(~(v + 1));
}

template <class T>
[[nodiscard]] constexpr auto blci(T v) -> T { return isolate_lowest_clear_bit(v); }

/**
 * Isolates the lowest set bit in the given value.
 * E.g. isolate_lowest_set_bit(0b11100011) = 0b00000001
 */
template <class T>
[[nodiscard]] constexpr auto isolate_lowest_set_bit(T v) -> T
{
    return v & static_cast<T>(-v);
}

template <class T>
[[nodiscard]] constexpr auto blsi(T v) -> T { return isolate_lowest_set_bit(v); }

/**
 * Clears all set bits to the right of the first clear bit in the given value.
 * E.g. fill_from_lowest_clear_bit(0b11101011) = 0b11101000
 */
template <class T>
[[nodiscard]] constexpr auto fill_from_lowest_clear_bit(T v) -> T
{
    if (bitmanipulation::popcnt(v) == sizeof(v) * CHAR_BIT) {
        return v;
    }
    return v & static_cast<T>(v + 1);
}

template <class T>
[[nodiscard]] constexpr auto blcfill(T v) -> T { return fill_from_lowest_clear_bit(v); }

/**
 * Sets all clear bits to the right of the first set bit in the given value.
 * E.g. fill_from_lowest_set_bit(0b01110100) = 0b01110111
 */
template <class T>
[[nodiscard]] constexpr auto fill_from_lowest_set_bit(T v) -> T
{
    if (bitmanipulation::popcnt(v) == 0) {
        return 0;
    }
    return v | static_cast<T>(v - 1);
}

template <class T>
[[nodiscard]] constexpr auto blsfill(T v) -> T { return fill_from_lowest_set_bit(v); }

/**
 * Clears the lowest set bit in the given value.
 * E.g. clear_lowest_set_bit(0b11100010) = 0b11100000
 */
template <class T>
[[nodiscard]] constexpr auto clear_lowest_set_bit(T v) -> T
{
    return v & static_cast<T>(v - 1);
}

template <class T>
[[nodiscard]] constexpr auto blsc(T v) -> T { return clear_lowest_set_bit(v); }

/**
 * Sets the lowest clear bit in the given value.
 * E.g. set_lowest_clear_bit(0b11100011) = 0b11100111
 */
template <class T>
[[nodiscard]] constexpr auto set_lowest_clear_bit(T v) -> T
{
    return v | static_cast<T>(v + 1);
}

template <class T>
[[nodiscard]] constexpr auto blcs(T v) -> T { return set_lowest_clear_bit(v); }

} // namespace bitmanipulation
