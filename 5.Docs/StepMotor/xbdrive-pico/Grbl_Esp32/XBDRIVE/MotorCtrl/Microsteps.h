#pragma once

#include <cstdint>

enum class MicrostepsType : int16_t {
    full_microsteps = 1,
    half_microsteps = 2,
    _4_microsteps = 4,
    _8_microsteps = 8,
    _16_microsteps = 16,
    _32_microsteps = 32,
    _64_microsteps = 64,
    _128_microsteps = 128,
    _256_microsteps = 256,
    _512_microsteps = 512,
    _1024_microsteps = 1024,
    _2048_microsteps = 2048,
};

class MicrostepsClass {
public:
    MicrostepsType type;
    MicrostepsClass();
};

extern MicrostepsClass* microsteps;
