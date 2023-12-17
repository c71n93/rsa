#pragma once

#include <iostream>
#include <cstdint>
#include <vector>
#include "math/math.hpp"

namespace math {

class prime_generator final {
public:
    prime_generator(uint8_t n_bits) : n_bits_(n_bits) {
        assert(n_bits <= 64);
    }

    uint64_t get_prime() {
        while (true) {
            uint64_t candidate = get_pseudo_prime();
            if (miller_rabin_test(candidate))
                return candidate;
        }
    }

private:
    uint8_t n_bits_;
    const std::vector<uint64_t> first_primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                                                31, 37, 41, 43, 47, 53, 59, 61, 67,
                                                71, 73, 79, 83, 89, 97, 101, 103,
                                                107, 109, 113, 127, 131, 137, 139,
                                                149, 151, 157, 163, 167, 173, 179,
                                                181, 191, 193, 197, 199, 211, 223,
                                                227, 229, 233, 239, 241, 251, 257,
                                                263, 269, 271, 277, 281, 283, 293,
                                                307, 311, 313, 317, 331, 337, 347, 349};

    uint64_t get_pseudo_prime() {
        while (true) {
            uint64_t candidate = math::n_bit_random(n_bits_);
            bool is_prime = true;
            for (auto first_prime: first_primes) {
                if (candidate == first_prime)
                    return candidate;

                if (candidate % first_prime == 0) {
                    is_prime = false;
                    break;
                }
            }
            if (is_prime)
                return candidate;
        }
    }

    static bool miller_rabin_test(uint64_t to_test) {
        constexpr int accuracy = 20;

        int max_div_2 = 0;
        uint64_t evenC = to_test - 1;
        while (evenC % 2 == 0) {
            evenC >>= 1;
            max_div_2++;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<uint64_t> distr(2, to_test);

        for (int i = 0; i < accuracy; i++) {
            uint64_t a = distr(gen);

            if (trial_composite(a, evenC, to_test, max_div_2)) {
                return false;
            }
        }

        return true;
    }

    static bool trial_composite(uint64_t a, uint64_t evenC, uint64_t to_test, int max_div_2) {
        if (math::pow_mod(a, evenC, to_test) == 1)
            return false;

        for (int i = 0; i < max_div_2; i++) {
            uint64_t temp = static_cast<uint64_t>(1) << i;
            if (math::pow_mod(a, temp * evenC, to_test) == to_test - 1)
                return false;
        }

        return true;
    }
};

}
