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

namespace wind::day06::part1
{

static auto parse(std::string_view file)
{
    auto parser = [](std::string_view line) { return 0; };
    return wind::read_input(file, parser);
}

static auto solve(const auto& input)
{
    return 0;
}

TEST_SUITE("part1")
{
    TEST_CASE("sample")
    {
        auto input = parse("./data/day06/sample1.txt");
        CHECK_EQ(solve(input), 13);
    }

    TEST_CASE("input")
    {
        auto input = parse("./data/day06/input1.txt");
        CHECK_EQ(solve(input), 24848);
    }
}

}  // namespace wind::day06::part1
