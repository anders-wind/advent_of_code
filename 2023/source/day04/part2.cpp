#include <algorithm>
#include <cctype>
#include <ranges>
#include <string>
#include <unordered_set>
#include <variant>
#include <vector>

#include <doctest/doctest.h>
#include <range/v3/algorithm/find_if.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/reverse.hpp>
#include <range/v3/view/split.hpp>
#include <range/v3/view/split_when.hpp>
#include <wind/helpers.hpp>

namespace wind::day04::part2
{

struct game
{
    int32_t number_of_cards {0};
    std::unordered_set<int32_t> winning;
    std::unordered_set<int32_t> yours;

    auto score() const
    {
        auto val = 0;
        for (auto number : this->yours) {
            if (this->winning.contains(number)) {
                val++;
            }
        }
        return val;
    }
};

static auto parse(std::string_view file) -> std::vector<game>
{
    auto parser = [](std::string_view line)
    {
        auto g = game {};
        line = line.substr(line.find(':') + 1);
        auto winning_numbers_line = line.substr(0, line.find('|'));
        auto winning_numbers =
            winning_numbers_line | string_view_split(' ')                                                    //
            | std::ranges::views::transform(trim)                                                            //
            | std::ranges::views::filter([](auto number_str) { return !number_str.empty(); })                //
            | std::ranges::views::transform([](auto number_str) { return to_number<int32_t>(number_str); })  //
            | ranges::to<std::unordered_set>;                                                                //
        auto your_numbers_line = line.substr(line.find("|") + 1);
        auto your_numbers =
            your_numbers_line | string_view_split(' ')                                                       //
            | std::ranges::views::transform(trim)                                                            //
            | std::ranges::views::filter([](auto number_str) { return !number_str.empty(); })                //
            | std::ranges::views::transform([](auto number_str) { return to_number<int32_t>(number_str); })  //
            | ranges::to<std::unordered_set>;                                                                //
        return game {.number_of_cards = 1, .winning = std::move(winning_numbers), .yours = std::move(your_numbers)};
    };
    return wind::read_input(file, parser);
}

static auto solve(std::vector<game> input)
{
    for (auto i = 0ULL; i < input.size(); i++) {
        auto g = input.at(i);
        auto score = g.score();
        for (auto j = i + 1; j <= i + score && j < input.size(); j++) {
            input.at(j).number_of_cards += g.number_of_cards;
        }
    }

    return ranges::accumulate(input, 0LL, [](auto acc, auto g) { return acc + g.number_of_cards; });
}

TEST_SUITE("part2")
{
    TEST_CASE("sample")
    {
        auto input = parse("./data/day04/sample2.txt");
        CHECK_EQ(solve(input), 30);
    }

    TEST_CASE("input")
    {
        auto input = parse("./data/day04/input2.txt");
        CHECK_EQ(solve(input), 7258152);
    }
}

}  // namespace wind::day04::part2
