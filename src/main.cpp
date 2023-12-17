#include <iostream>
#include "rsa/perf/rsa-perf.hpp"

int main() {
#ifdef PERF
    rsa::perf::RSA_perf rsa_perf("./watermelon32.txt", 1 << 20, 1, 8);
    rsa_perf.run_encrypt();
    rsa_perf.run_decrypt();
    rsa_perf.run_keygen(1 << 12);
    return 0;
#else
    uint8_t key_n_bit = 16;
    rsa::RSA rsa(16);
    std::cout << "key length: " << static_cast<uint64_t>(key_n_bit) << " bit" << std::endl;
    std::cout << rsa << std::endl;
    rsa::perf::msg_generator<uint64_t> gen{1, 8};
    uint64_t m = gen[0];
    std::cout << "message: " << m << std::endl;
    uint64_t c = rsa.encrypt(m);
    std::cout << "encrypted message " << c << std::endl;
    uint64_t m_d = rsa.decrypt(c);
    std::cout << "decrypted message " << m_d << std::endl;
#endif
}
