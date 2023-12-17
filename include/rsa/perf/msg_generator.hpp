#pragma once

#include <cstdint>
#include "math/math.hpp"

namespace rsa::perf {

template <typename T>
class msg_generator {
public:
    msg_generator(size_t text_len, uint8_t msg_n_bit) :
        text_len_(text_len), msg_n_bit_(msg_n_bit), msg_vec_(text_len_) {
        for (auto &e : msg_vec_) {
            e = math::n_bit_random(msg_n_bit_);
        }
    }

    using ConstIt = std::vector<T>::const_iterator;
    ConstIt begin() const { return msg_vec_.cbegin(); }
    ConstIt end() const { return msg_vec_.cend(); }

    const T& operator[](int i) const { return msg_vec_[i]; }

private:
    size_t text_len_;
    uint8_t msg_n_bit_;
    std::vector<T> msg_vec_;
};

}
