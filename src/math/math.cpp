#include "math/math.hpp"

namespace math {

uint64_t n_bit_random(uint8_t n) {
    assert(n <= 64);
    assert(n > 1);
    auto max = static_cast<uint64_t>(std::pow(2, n) - 1);
    auto min = static_cast<uint64_t>(std::pow(2, n - 1) + 1);
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis;

    return min + (dis(gen) % ( max - min + 1 ) );
}
uint64_t gcd(uint64_t a, uint64_t b) {
    while (a > 0) {
        uint64_t tmp;
        tmp = a;
        a = b % a;
        b = tmp;
    }
    return b;
}
uint64_t exgcd(uint64_t a, uint64_t b, uint64_t &x, uint64_t &y) {
    if (a == 0) {
        x = 0, y = 1;
        return b;
    }
    uint64_t x1, y1;
    uint64_t gcd = exgcd(b % a, a, x1, y1);

    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}
uint64_t inverse_mod(uint64_t a, uint64_t m) {
    assert(a < m);
    uint64_t x, y;
    // a * x + m * y = 1 mod m => a * x = 1 mod m
    uint64_t gcd = exgcd(a, m, x, y);
    assert(gcd == 1);
    return (x + m) % m;
}
uint64_t pow_mod(uint64_t base, uint64_t exp, uint64_t m) {
    assert(base < std::numeric_limits<uint32_t>::max());
    base %= m;
    uint64_t result = 1;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % m;
        }
        base = (base * base) % m;
        exp >>= 1;
    }
    return result;
}


} // namespace math
