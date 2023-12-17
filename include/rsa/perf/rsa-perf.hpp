#pragma once

#include <filesystem>
#include <utility>
#include <fstream>
#include <chrono>
#include "msg_generator.hpp"
#include "rsa/rsa.hpp"

namespace rsa::perf {

class RSA_perf {
public:
    RSA_perf(std::filesystem::path res_path, size_t n_iters, size_t text_len, uint8_t msg_n_bit) :
        n_iters_(n_iters), out_file_(res_path, std::ios::out), text_len_(text_len), msg_n_bit_(msg_n_bit) {
        out_file_ << "number of bits in single message chunk: " << static_cast<uint64_t>(msg_n_bit_) << std::endl
                  << "number of message chunks: " << text_len_ << std::endl;
    }

    void run_encrypt(uint64_t n_iters) {
        out_file_ << "---ENCRYPT---" << std::endl;
        uint8_t max_n_bit = 32;
        for (uint8_t n_bit = 3; n_bit <= max_n_bit; n_bit++) {
            msg_generator<uint64_t> msg_gen{text_len_, msg_n_bit_};
            rsa::RSA rsa(n_bit);
            auto start = std::chrono::high_resolution_clock::now();
            for (size_t i = 0; i < n_iters; i++) {
                for (const auto &m : msg_gen) {
                    rsa.encrypt(m);
                }
            }
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
            out_file_ << duration / n_iters << " " << static_cast<uint64_t>(n_bit) << std::endl;
        }
    }
    void run_encrypt() {
        run_encrypt(n_iters_);
    }
    void run_decrypt(uint64_t n_iters) {
        out_file_ << "---DECRYPT---" << std::endl;
        uint8_t max_n_bit = 32;
        for (uint8_t n_bit = 3; n_bit <= max_n_bit; n_bit++) {
            msg_generator<uint64_t> msg_gen{text_len_, msg_n_bit_};
            rsa::RSA rsa(n_bit);
            auto start = std::chrono::high_resolution_clock::now();
            for (size_t i = 0; i < n_iters; i++) {
                for (const auto &m : msg_gen) {
                    rsa.decrypt(m);
                }
            }
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
            out_file_ << duration / n_iters << " " << static_cast<uint64_t>(n_bit) << std::endl;
        }
    }
    void run_decrypt() {
        run_decrypt(n_iters_);
    }
    void run_keygen(uint64_t n_iters) {
        out_file_ << "---KEYGEN---" << std::endl;
        uint8_t max_n_bit = 32;
        for (uint8_t n_bit = 3; n_bit <= max_n_bit; n_bit++) {
            auto start = std::chrono::high_resolution_clock::now();
            for (size_t i = 0; i < n_iters; i++) {
                rsa::RSA rsa(n_bit);
            }
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
            out_file_ << duration / n_iters << " " << static_cast<uint64_t>(n_bit) << std::endl;
        }
    }
    void run_keygen() {
        run_keygen(n_iters_);
    }

private:
    size_t n_iters_;
    size_t text_len_;
    uint8_t msg_n_bit_;
    std::ofstream out_file_;
};

}
