#pragma once

#include <random>

// Get a shared RNG instance
#include "random_utils.hpp"

std::mt19937& global_rng() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
}