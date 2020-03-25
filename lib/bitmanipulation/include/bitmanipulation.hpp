#pragma once

#include <climits>
#include <cstdint>

namespace bitmanipulation {

constexpr uintmax_t mask(unsigned bits, unsigned shift = 0) {
    return ~(static_cast<uintmax_t>(~0) << bits) << shift;
}

template <class T>
constexpr T set_bits(T value, unsigned bits, unsigned shift = 0) {
    T mask = static_cast<T>(bitmanipulation::mask(bits, shift));
    return value | mask;
}

template <class T>
constexpr T clear_bits(T value, unsigned bits, unsigned shift = 0) {
    T mask = static_cast<T>(bitmanipulation::mask(bits, shift));
    return value & static_cast<T>(~mask);
}

/**
 * returns the number of set bits. (population count)
 */
template <class T>
unsigned count_bits_set(T value) {
    unsigned count { 0u };
    for (; value; count++) {
        value = value & static_cast<T>(value - 1);
    }
    return count;
}

template <class T>
unsigned popcnt(T value) { return count_bits_set(value); }

template <class T>
unsigned leading_zeroes_count(T value)
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
unsigned lzcnt(T value) { return leading_zeroes_count(value); }

template <class T>
unsigned trailing_zeroes_count(T value)
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
unsigned tzcnt(T value) { return trailing_zeroes_count(value); }

/**
 * isolates the lowest clear bit.
 * e.g. isolate_lowest_clear_bit(0b11100011) = 0b11111011
 */
template <class T>
constexpr T isolate_lowest_clear_bit(T v)
{
    return v | static_cast<T>(~(v + 1));
}

template <class T>
constexpr T blci(T v) { return isolate_lowest_clear_bit(v); }

/**
 * isolates the lowest set bit.
 * e.g. isolate_lowest_set_bit(0b11100011) = 0b00000001
 */
template <class T>
constexpr T isolate_lowest_set_bit(T v)
{
    return v & static_cast<T>(-v);
}

template <class T>
constexpr T blsi(T v) { return isolate_lowest_set_bit(v); }

/**
 * clears all set bits to the right of the first clear bit
 * e.g. fill_from_lowest_clear_bit(0b11101011) = 0b11101000
 */
template <class T>
constexpr T fill_from_lowest_clear_bit(T v)
{
    if (bitmanipulation::popcnt(v) == sizeof(v) * CHAR_BIT) {
        return v;
    }
    return v & static_cast<T>(v + 1);
}

template <class T>
constexpr T blcfill(T v) { return fill_from_lowest_clear_bit(v); }

/**
 * sets all clear bits to the right of the first set bit
 * e.g. fill_from_lowest_set_bit(0b01110100) = 0b01110111
 */
template <class T>
constexpr T fill_from_lowest_set_bit(T v)
{
    if (bitmanipulation::popcnt(v) == 0) {
        return 0;
    }
    return v | static_cast<T>(v - 1);
}

template <class T>
constexpr T blsfill(T v) { return fill_from_lowest_set_bit(v); }

/**
 * clears the lowest set bit
 * e.g. clear_lowest_set_bit(0b11100010) = 0b11100000
 */
template <class T>
constexpr T clear_lowest_set_bit(T v)
{
    return v & static_cast<T>(v - 1);
}

template <class T>
constexpr T blsc(T v) { return clear_lowest_set_bit(v); }

/**
 * sets the lowest clear bit
 * e.g. set_lowest_clear_bit(0b11100011) = 0b11100111
 */
template <class T>
constexpr T set_lowest_clear_bit(T v)
{
    return v | static_cast<T>(v + 1);
}

template <class T>
constexpr T blcs(T v) { return set_lowest_clear_bit(v); }

} // namespace bitmanipulation
