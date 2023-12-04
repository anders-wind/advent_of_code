#include <algorithm>
#include <cctype>
#include <string>

#include <doctest/doctest.h>
#include <range/v3/algorithm/find_if.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/reverse.hpp>
#include <wind/helpers.hpp>

namespace wind::day01::part1
{

static auto parse(std::string_view file)
{
    auto parser = [](std::string_view line)
    {
        char first = *ranges::find_if(line, is_digit);
        char last = *ranges::find_if(line | ranges::views::reverse, is_digit);
        return 10 * to_digit(first) + to_digit(last);
    };
    return wind::read_input(file, parser);
}

static auto solve(const auto& input)
{
    return ranges::accumulate(input, 0, [](auto acc, auto v) { return acc + v; });
}

TEST_SUITE("part1")
{
    TEST_CASE("sample")
    {
        auto input = parse("./data/day01/sample1.txt");
        CHECK_EQ(solve(input), 142);
    }

    TEST_CASE("input")
    {
        auto input = parse("./data/day01/input1.txt");
        CHECK_EQ(solve(input), 54450);
    }
}

}  // namespace wind::day01::part1
