#pragma once

#include <cstdio>
#include <cassert>
#include "math/math.hpp"
#include "math/prime_generator.hpp"

namespace rsa {

class RSA final {
public:
    RSA(uint8_t n_bits);

    uint64_t encrypt(uint64_t m) const { return math::pow_mod(m, e_, n_); }
    uint64_t decrypt(uint64_t c) const { return math::pow_mod(c, d_, n_); }

    void encrypt(const std::vector<uint64_t> &in, std::vector<uint64_t> &out, size_t len) const;
    void decrypt(const std::vector<uint64_t> &in, std::vector<uint64_t> &out, size_t len) const;

    const uint64_t& p() const { return p_;}
    const uint64_t& q() const { return q_;}
    const uint64_t& n() const { return n_;}
    const uint64_t& phi() const { return phi_;}
    const uint64_t& e() const { return e_;}
    const uint64_t& d() const { return d_;}

private:
    uint64_t p_, q_, n_, phi_, e_, d_;
};

}

std::ostream& operator<<(std::ostream& os, const rsa::RSA& rsa);
