/*
This program prints companies on a stock market.
Task:
- sort companies with three criterias: `dividends` first, then `rating`, then `capitalization`.
  This means that companies are compared by `dividends`, but if these fields are equal then the next field is used for comparison.

For example, these companies:
{DailyMarket              created Jan 1975, dividends, rating: Hold        , cap $15568997}
{SecuriWine Consulting    created May 1987, dividends, rating: Outperform  , cap $8729992}
{TeleBank Tech            created Aug 2003           , rating: Buy         , cap $17549087}
{FrontTravel              created Dec 1978, dividends, rating: Hold        , cap $631681}
{HiddenJets               created May 1980, dividends, rating: Outperform  , cap $12008927}

Would be sorted as such:
{HiddenJets               created May 1980, dividends, rating: Outperform  , cap $12008927}
{SecuriWine Consulting    created May 1987, dividends, rating: Outperform  , cap $8729992}
{DailyMarket              created Jan 1975, dividends, rating: Hold        , cap $15568997}
{FrontTravel              created Dec 1978, dividends, rating: Hold        , cap $631681}
{TeleBank Tech            created Aug 2003           , rating: Buy         , cap $17549087}

plus: check by using std::is_sorted
plus: sort in reverse direction
plus: add one more order criteria
plus: try `stable_sort` and examine its guarantees
*/
#include "internal/task_4.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include "gtest/gtest.h"

/*
enum class Rating {
  Sell,
  Underperform,
  Hold,
  Outperform,
  Buy
};

struct Company {
  std::string name;
  time_point creation_date;
  bool dividends;
  Rating rating;
  uint64_t capitalization;
};*/

bool compareImplementation(const Company& first, const Company& second, bool reverse)
{
    if (first.dividends != second.dividends) {
        return reverse ? first.dividends < second.dividends : first.dividends > second.dividends;
    }

    if (first.rating != second.rating) {
        return reverse ? first.rating < second.rating : first.rating > second.rating;
    }

    if (first.capitalization != second.capitalization) {
        return reverse ? first.capitalization < second.capitalization : first.capitalization > second.capitalization;
    }

    return true;
}

struct Ascending {
    bool operator()(const Company& first, const Company& second)
    {
        return compareImplementation(first, second, false);
    }
};

struct Descending {
    bool operator()(const Company& first, const Company& second)
    {
        return compareImplementation(first, second, true);
    }
};

TEST(CompaniesSort, Ascending) {
    std::vector<Company> input = {{"DailyMarket", {}, true, Rating::Hold, 15568997},
                                  {"SecurityWine", {}, true, Rating::Outperform, 8729992},
                                  {"TeleBank", {}, false, Rating::Buy, 17549087},
                                  {"FrontTravel", {}, true, Rating::Hold, 631681},
                                  {"HiddenJets", {}, true, Rating::Outperform, 12008927}};

    std::sort(input.begin(), input.end(), Ascending());

    std::vector<Company> expected = {
        {"HiddenJets", {}, true, Rating::Outperform, 12008927},
        {"SecurityWine", {}, true, Rating::Outperform, 8729992},
        {"DailyMarket", {}, true, Rating::Hold, 15568997},
        {"FrontTravel", {}, true, Rating::Hold, 631681},
        {"TeleBank", {}, false, Rating::Buy, 17549087},
    };

    EXPECT_EQ(input, expected);
    EXPECT_TRUE(std::is_sorted(expected.begin(), expected.end(), Ascending()));
}

TEST(CompaniesSort, Descending) {
    std::vector<Company> input = {{"DailyMarket", {}, true, Rating::Hold, 15568997},
                                  {"SecurityWine", {}, true, Rating::Outperform, 8729992},
                                  {"TeleBank", {}, false, Rating::Buy, 17549087},
                                  {"FrontTravel", {}, true, Rating::Hold, 631681},
                                  {"HiddenJets", {}, true, Rating::Outperform, 12008927}};

    std::sort(input.begin(), input.end(), Descending());

    std::vector<Company> expected = {
        {"TeleBank", {}, false, Rating::Buy, 17549087},
        {"FrontTravel", {}, true, Rating::Hold, 631681},
        {"DailyMarket", {}, true, Rating::Hold, 15568997},
        {"SecurityWine", {}, true, Rating::Outperform, 8729992},
        {"HiddenJets", {}, true, Rating::Outperform, 12008927},
    };

    EXPECT_EQ(input, expected);
    EXPECT_TRUE(std::is_sorted(expected.begin(), expected.end(), Descending()));
}

TEST(CompaniesStableSort, Ascending)
{
    std::vector<Company> input = {{"DailyMarket", {}, true, Rating::Hold, 15568997},
                                  {"SecurityWine", {}, true, Rating::Outperform, 8729992},
                                  {"TeleBank", {}, false, Rating::Buy, 17549087},
                                  {"FrontTravel", {}, true, Rating::Hold, 631681},
                                  {"HiddenJets", {}, true, Rating::Outperform, 12008927}};

    std::stable_sort(input.begin(), input.end(), Ascending());

    std::vector<Company> expected = {
        {"HiddenJets", {}, true, Rating::Outperform, 12008927},
        {"SecurityWine", {}, true, Rating::Outperform, 8729992},
        {"DailyMarket", {}, true, Rating::Hold, 15568997},
        {"FrontTravel", {}, true, Rating::Hold, 631681},
        {"TeleBank", {}, false, Rating::Buy, 17549087},
    };

    EXPECT_EQ(input, expected);
    EXPECT_TRUE(std::is_sorted(expected.begin(), expected.end(), Ascending()));
}

TEST(CompaniesStableSort, Descending)
{
    std::vector<Company> input = {{"DailyMarket", {}, true, Rating::Hold, 15568997},
                                  {"SecurityWine", {}, true, Rating::Outperform, 8729992},
                                  {"TeleBank", {}, false, Rating::Buy, 17549087},
                                  {"FrontTravel", {}, true, Rating::Hold, 631681},
                                  {"HiddenJets", {}, true, Rating::Outperform, 12008927}};

    std::stable_sort(input.begin(), input.end(), Descending());

    std::vector<Company> expected = {
        {"TeleBank", {}, false, Rating::Buy, 17549087},
        {"FrontTravel", {}, true, Rating::Hold, 631681},
        {"DailyMarket", {}, true, Rating::Hold, 15568997},
        {"SecurityWine", {}, true, Rating::Outperform, 8729992},
        {"HiddenJets", {}, true, Rating::Outperform, 12008927},
    };

    EXPECT_EQ(input, expected);
    EXPECT_TRUE(std::is_sorted(expected.begin(), expected.end(), Descending()));
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
