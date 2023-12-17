#include "rsa/rsa.hpp"

namespace rsa {

RSA::RSA(uint8_t n_bits) {
    assert(n_bits <= 16); // p_, q_ (16 bit) => n_, phi_ (max 32 bit) => math::pow_mod(message, e_, n_); may cause overflow
    assert(n_bits > 2);
    p_ = math::prime_generator(n_bits).get_prime();
    do {
        q_ =math::prime_generator(n_bits).get_prime();
    } while (q_ == p_);
    phi_ = (p_ - 1) * (q_ - 1);
    n_ = p_ * q_;
    do {
        e_ =  math::n_bit_random(n_bits * 2) % (phi_ - 3) + 3;
    } while (math::gcd(e_, phi_) != 1);
    d_ = math::inverse_mod(e_, phi_);
}

void RSA::encrypt(const std::vector<uint64_t> &in, std::vector<uint64_t> &out, size_t len) const {
    for (int i = 0; i < len; ++i) {
        out[i] = encrypt(in[i]);
    }
}

void RSA::decrypt(const std::vector<uint64_t> &in, std::vector<uint64_t> &out, size_t len) const {
    for (int i = 0; i < len; ++i) {
        out[i] = decrypt(in[i]);
    }
}

}

std::ostream& operator<<(std::ostream& os, const rsa::RSA& rsa) {
    std::cout << "---- p = " << rsa.p() << " ----\n";
    std::cout << "---- q = " << rsa.q() << " ----\n";
    std::cout << "---- n = " << rsa.n() << " ----\n";
    std::cout << "---- phi = " << rsa.phi() << " ----\n";
    std::cout << "---- e = " << rsa.e() << " ----\n";
    std::cout << "---- d = " << rsa.d() << " ----\n";

    return os;
}
