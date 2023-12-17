#include "rsa/rsa.hpp"
#include "rsa/perf/msg_generator.hpp"
#include <gtest/gtest.h>

using namespace rsa;

constexpr uint16_t max_n_bit = 16; // due to overflow in math::pow_mod

TEST(rsa, keys_test) {
    for (uint8_t n_bit = 3; n_bit <= max_n_bit; n_bit++) {
        RSA rsa(n_bit);
        EXPECT_EQ(math::gcd(rsa.e(), rsa.phi()), 1) << "n_bit = " << (uint64_t) n_bit  << "\n" << rsa << std::endl;
        EXPECT_EQ((rsa.e() * rsa.d()) % rsa.phi(), 1) << "n_bit = " << (uint64_t) n_bit  << "\n" << rsa << std::endl;
        EXPECT_EQ(rsa.p() * rsa.q(), rsa.n()) << "n_bit = " << (uint64_t) n_bit  << "\n" << rsa << std::endl;
    }
}

TEST(rsa, encrypt_decrypt_test) {
    for (uint8_t n_bit = 3; n_bit <= max_n_bit; n_bit++) {
        RSA rsa(n_bit);
        uint64_t m = 25;
        uint64_t c = rsa.encrypt(m);
        uint64_t m_d = rsa.decrypt(c);
        EXPECT_EQ(m, m_d) << "n_bit = " << (uint64_t) n_bit  << "\n" << rsa << std::endl;
        EXPECT_EQ(math::gcd(rsa.e(), rsa.phi()), 1) << "n_bit = " << (uint64_t) n_bit  << "\n" << rsa << std::endl;
        EXPECT_EQ((rsa.e() * rsa.d()) % rsa.phi(), 1) << "n_bit = " << (uint64_t) n_bit  << "\n" << rsa << std::endl;
        EXPECT_EQ(rsa.p() * rsa.q(), rsa.n()) << "n_bit = " << (uint64_t) n_bit  << "\n" << rsa << std::endl;
    }
}

TEST(rsa, rsa_test) {
    constexpr uint8_t n_bit = max_n_bit;
    size_t txtlen = 128;
    int repeat_time = 10;
    assert(txtlen > 0);

    std::vector<uint64_t> in(txtlen);
    std::vector<uint64_t> out(txtlen);
    std::vector<uint64_t> din(txtlen);

    for (int t = 0; t < repeat_time; ++t) {
        RSA rsa(n_bit);
        rsa::perf::msg_generator<uint64_t> msg_gen(128, n_bit);
        for (int i = 0; i < txtlen; ++i) {
            in[i] = msg_gen[i];
        }
        rsa.encrypt(in, out, txtlen);
        rsa.decrypt(out, din, txtlen);
        for (int i = 0; i < txtlen; ++i) {
            EXPECT_EQ(in[i], din[i]) << rsa;
        }
    }
}
