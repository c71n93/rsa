#include "dummy/dummy.hpp"
#include <gtest/gtest.h>

TEST(dummy, dummy_test_success) {
    std::cout << "Watermelon!" << std::endl;
    dummy_function();
    EXPECT_TRUE(true);
}
