#include "math/math.hpp"
#include "math/prime_generator.hpp"
#include <gtest/gtest.h>

TEST(math, inverse_mod_test) {
    for (uint8_t n_bit = 3; n_bit < 16; n_bit++) {
        uint64_t num = math::n_bit_random(n_bit - 1);
        uint64_t base = math::prime_generator(n_bit).get_prime();
        uint64_t inv_num = math::inverse_mod(num, base);
        EXPECT_EQ(inv_num * num % base, 1)
                        << "num = " << num << "; base = " << base
                        << "; inv_num = " << inv_num << "; n_bit = " << (uint64_t) n_bit << std::endl;
    }
}

TEST(math, exgcd_test) {
    for (uint8_t n_bit = 2; n_bit < 63; n_bit++) {
        uint64_t a = math::n_bit_random(n_bit);
        uint64_t b = math::n_bit_random(n_bit);
        uint64_t x, y;
        uint64_t gcd = math::exgcd(a, b , x, y);
        EXPECT_EQ(a * x + b * y, gcd)
                        << "a = " << a << "; b = " << b << "; x = " << x
                        << "; y = " << y << "; gcd = " << gcd << "; n_bit = " << (uint64_t) n_bit << std::endl;
        EXPECT_EQ(math::gcd(a, b), gcd)
                        << "a = " << a << "; b = " << b << "; x = " << x
                        << "; y = " << y << "; gcd = " << gcd << "; n_bit = " << (uint64_t) n_bit << std::endl;
    }
}
