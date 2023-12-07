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

namespace wind::day04::part1
{

struct game
{
    std::unordered_set<int32_t> winning;
    std::unordered_set<int32_t> yours;

    auto score() const
    {
        auto multiplier = 1;
        for (auto number : this->yours) {
            if (this->winning.contains(number)) {
                multiplier *= 2;
            }
        }
        return multiplier / 2;
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
        return game {.winning = std::move(winning_numbers), .yours = std::move(your_numbers)};
    };
    return wind::read_input(file, parser);
}

static auto solve(const std::vector<game>& input)
{
    return ranges::accumulate(input, 0LL, [](auto acc, auto g) { return acc + g.score(); });
}

TEST_SUITE("part1")
{
    TEST_CASE("sample")
    {
        auto input = parse("./data/day04/sample1.txt");
        CHECK_EQ(solve(input), 13);
    }

    TEST_CASE("input")
    {
        auto input = parse("./data/day04/input1.txt");
        CHECK_EQ(solve(input), 24848);
    }
}

}  // namespace wind::day04::part1
