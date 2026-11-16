#include <gtest/gtest.h>
#include "vector.hpp"

TEST(is_const_iter, const_iter)
{
    Vector<unsigned int> vec(5);
    auto it = vec.cbegin();
    EXPECT_TRUE(std::is_const_v<std::remove_reference_t<decltype(*it)>>);
}

TEST(is_const_iter, nonconst_iter)
{
    Vector<unsigned int> vec(5);
    auto it = vec.begin();
    EXPECT_FALSE(std::is_const_v<std::remove_reference_t<decltype(*it)>>);
}

TEST(method_at, out_of_range)
{
    Vector<unsigned int> vec(5);
    EXPECT_THROW(vec.at(10), std::out_of_range);
}