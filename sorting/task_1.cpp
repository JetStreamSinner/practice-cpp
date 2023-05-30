/*
Task:
- write a function that returns true if the given sequence is sorted.
- pass all tests.

plus: add your own tests.
plus: you have a STL-based implementation and a manual variant.
plus: support for a reverse-sorted sequences too.
plus: write a template based variant that may work with vector of different types
plus: write a function that accepts two input iterators (begin, end)
*/
#include <iostream>
#include <limits>
#include <vector>
#include "gtest/gtest.h"

namespace custom {

template <typename It>
bool is_sorted_impl(It first, It last) {
    if (first >= last) {
        return true;
    }

    auto prev_item = first;
    auto next_item = std::next(prev_item);

    while (next_item < last) {
        if (*prev_item > *next_item) {
            return false;
        }
        prev_item = std::next(prev_item);
        next_item = std::next(next_item);
    }
    return true;
}

template <typename T>
bool is_sorted(const std::vector<T>& arr) {
    return is_sorted_impl(arr.begin(), arr.end());
}

template <typename T>
bool is_sorted(const std::initializer_list<T>& arr) {
    return is_sorted_impl(arr.begin(), arr.end());
}

template <typename It>
bool is_sorted(It first, It last) {
    return is_sorted_impl(first, last);
}
}  // namespace custom


TEST(is_sorted, all) {
    using namespace custom;

    EXPECT_TRUE(is_sorted<int>({}));
    EXPECT_TRUE(is_sorted({1, 2, 3, 4, 5}));
    EXPECT_TRUE(is_sorted({1}));
    EXPECT_TRUE(is_sorted({2, 2, 2}));
    EXPECT_TRUE(is_sorted({-5, -4, -3, -2, -1}));
    EXPECT_FALSE(is_sorted({5, 4, 3, 2, 1}));
    EXPECT_TRUE(is_sorted({-5, -5, 5, 5}));
    EXPECT_TRUE(is_sorted({-5, -4}));
    EXPECT_TRUE(is_sorted({std::numeric_limits<int>::min(), 1, 1, 2, 10, 15, std::numeric_limits<int>::max()}));
    EXPECT_FALSE(is_sorted({1, 2, 1, 3, 4, 5}));
    EXPECT_FALSE(is_sorted({1, 2, 3, 2}));
    EXPECT_FALSE(is_sorted({3, 2, 3, 4}));
}

TEST(is_sorted_reverse, all) {
    using namespace custom;

    std::vector vec1 = {5, 4, 3, 2, 1};
    std::vector vec2 = {1};
    std::vector vec3 = {2, 2, 2};
    std::vector vec4 = {-1, -2, -3, -4, -5};
    std::vector vec5 = {1, 2, 3, 4, 5};
    std::vector vec6 = {5, 5, -5, -5};
    std::vector vec7 = {-4, -5};
    std::vector vec8 = {1, 2, 1, 3, 4, 5};
    std::vector vec9 = {2, 3, 2, 1};
    std::vector vec10 = {4, 3, 2, 3};

    EXPECT_TRUE(custom::is_sorted(vec1.rbegin(), vec1.rend()));
    EXPECT_TRUE(custom::is_sorted(vec2.rbegin(), vec2.rend()));
    EXPECT_TRUE(custom::is_sorted(vec3.rbegin(), vec3.rend()));
    EXPECT_TRUE(custom::is_sorted(vec4.rbegin(), vec4.rend()));
    EXPECT_FALSE(custom::is_sorted(vec5.rbegin(), vec5.rend()));
    EXPECT_TRUE(custom::is_sorted(vec6.rbegin(), vec6.rend()));
    EXPECT_TRUE(custom::is_sorted(vec7.rbegin(), vec7.rend()));
    EXPECT_FALSE(custom::is_sorted(vec8.rbegin(), vec8.rend()));
    EXPECT_FALSE(custom::is_sorted(vec9.rbegin(), vec9.rend()));
    EXPECT_FALSE(custom::is_sorted(vec10.rbegin(), vec10.rend()));
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
