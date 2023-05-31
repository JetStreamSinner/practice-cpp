/*
Task:
1) print elements of different containers in ascending order. You may change them by calling `sort` if needed.

plus: change to descending order
*/
#include <deque>
#include <list>
#include <map>
#include <unordered_map>
#include <vector>
#include "gtest/gtest.h"

template <typename ForwardIterator, typename OutputStream>
void printLinearContainer(ForwardIterator first, ForwardIterator last, OutputStream& os) {
    while (first != last) {
        os << *first << " ";
        first++;
    }
}

template <typename ForwardIterator, typename OutputStream>
void printAssociativeContainer(ForwardIterator first, ForwardIterator last, OutputStream& os) {
    while (first != last) {
        os << "{ " << first->first << ", " << first->second << " }" << std::endl;
        first++;
    }
}

template <typename Container>
struct is_associative_container : std::false_type {};

template <typename Key, typename Value>
struct is_associative_container<std::unordered_map<Key, Value>> : std::true_type {};

template <typename Key, typename Value>
struct is_associative_container<std::map<Key, Value>> : std::true_type {};

template <typename Container, typename OutputStream = std::ostream>
void printContainer(const Container& container, OutputStream& os = std::cout) {
    if constexpr (is_associative_container<Container>()) {
        printAssociativeContainer(std::begin(container), std::end(container), os);
    } else {
        printLinearContainer(std::begin(container), std::end(container), os);
    }
}

TEST(AscendingOrder, Vector) {
    // Note: this task is already done
    std::vector<int> arr = {6, 5, 4, 1, 3, 2};

    std::sort(std::begin(arr), std::end(arr));

    testing::internal::CaptureStdout();

    printContainer(arr);

    EXPECT_EQ(testing::internal::GetCapturedStdout(),
              "1 2 3 4 5 6 ");  // Note: the last whitespace is just for convenience
}

TEST(AscendingOrder, CArray) {
    const int32_t itemsCount = 6;
    int arr[itemsCount] = {6, 5, 4, 1, 3, 2};

    std::sort(arr, arr + itemsCount);

    testing::internal::CaptureStdout();

    printContainer(arr);

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "1 2 3 4 5 6 ");
}

TEST(AscendingOrder, Deque) {
    std::deque<int> arr = {6, 5, 4, 1, 3, 2};

    std::sort(arr.begin(), arr.end());

    testing::internal::CaptureStdout();

    printContainer(arr);

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "1 2 3 4 5 6 ");
}

TEST(AscendingOrder, List) {
    std::list<int> arr = {6, 5, 4, 1, 3, 2};

    arr.sort();

    testing::internal::CaptureStdout();

    printContainer(arr);

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "1 2 3 4 5 6 ");
}

TEST(AscendingOrder, Map) {
    std::map<int, int> arr = {{6, 600}, {5, 500}, {4, 400}, {1, 100}, {3, 300}, {2, 200}};

    std::vector<int32_t> keys;

    for (auto& val : arr) {
        keys.push_back(val.first);
    }
    std::sort(std::begin(keys), std::end(keys));

    testing::internal::CaptureStdout();

    printContainer(keys);

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "1 2 3 4 5 6 ");
}

TEST(AscendingOrder, UnorderedMap) {
    std::unordered_map<int, int> arr = {{6, 600}, {5, 500}, {4, 400}, {1, 100}, {3, 300}, {2, 200}};

    std::vector<int32_t> keys;

    for (auto& val : arr) {
        keys.push_back(val.first);
    }

    std::sort(std::begin(keys), std::end(keys));

    testing::internal::CaptureStdout();

    printContainer(keys);

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "1 2 3 4 5 6 ");
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
