#pragma once

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>
#include <cassert>
#include <limits>

namespace math {

uint64_t n_bit_random(uint8_t n);

uint64_t gcd(uint64_t a, uint64_t b);

/**
 * Finds x, y, gcd(a, b) such, that: a * x + b * y = gcd(a, b)
 */
uint64_t exgcd(uint64_t a, uint64_t b, uint64_t &x, uint64_t &y);

/**
 * Finds x such that: a * x = 1 mod m. It is required that: gcd(a, m) = 1
 *
 */
uint64_t inverse_mod(uint64_t a, uint64_t m);

uint64_t pow_mod(uint64_t base, uint64_t exp, uint64_t m);

} // namespace math
