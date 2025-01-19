#pragma once

#include <bits/stdc++.h>
#include <stdint.h>

using COORDINATE_TYPE = uint16_t;

namespace utils {
struct Coordinate {
    COORDINATE_TYPE x;
    COORDINATE_TYPE y;
};

enum Direction : uint8_t {
    up = 0b00000001,
    down = 0b00000010,
    left = 0b00000100,
    right = 0b00001000,
    none = 0b00010000,
};

enum InteractionType : uint8_t {
    text_object = 0b00000001,
    text_human = 0b00000010,
    simple_choice = 0b00000100,
    multiple_choice = 0b00001000,
    collect_object = 0b00010000,
    status_change = 0b00100000,
    trigger = 0b01000000,
    trainer = 0b10000000
};

enum InteractionStatus : uint8_t {
    ENABLED = 0b00000001,
    INTERACTION_NEVER_HAPPENED = 0b00000010,
    IS_PLAYING = 0b00000100,
    INTERACTION_ENDED = 0b00001000,
    PLAYED_BIT1 = 0b00010000,
    PLAYED_BIT2 = 0b00100000,
    PLAYED_BIT3 = 0b01000000,
    PLAYED_BIT4 = 0b10000000

};

enum MapTypes : uint8_t { generic_building = 0b00000001, outside_world = 0b00000010, gym = 0b00000100, rocket_hideout = 0b00001000, cave = 0b00010000, dark_cave = 0b00100000 };

// read n-th bit
template <class T>
bool readBit(const T& field, const T& n) {
    return field & ((T)1 << n);
}
// set n-th bit
template <class T>
void setBit(T& number, const T& n) {
    number&((T)1 << n);
}
// clear n-th bit
template <class T>
void clearBit(T& number, const T& n) {
    number & ~((T)1 << n);
}
// set n-th bit to
template <class T>
void setBitTo(T& number, const T& n, const bool& value) {
    if (value) {
        setBit<uint8_t>(number, n);
    } else {
        clearBit<uint8_t>(number, n);
    }
}

// function to find the position of rightmost set bit
template <class T>
T getPosOfRightmostSetBit(T n) {
    return std::log2(n & -n);
}

// function to toggle the last m bits
template <class T>
T toggleLastKBits(T n, T k) {
    // calculating a number 'num' having 'm' bits and all are set
    T num = (1 << k) - 1;

    // toggle the last m bits and return the number
    return (n ^ num);
}

// function to increment a number by one by manipulating the bits
template <class T>
T incrementByOne(T n) {
    // get position of rightmost unset bit
    // if all bits of 'n' are set, then the
    // bit left to the MSB is the rightmost
    // unset bit
    T k = getPosOfRightmostSetBit(~n);

    // kth bit of n is being set by this operation
    n = ((1 << k) | n);

    // from the right toggle all the bits before the k-th bit
    if (k != 0) {
        n = toggleLastKBits(n, k);
    }

    return n;
}

}  // namespace utils
