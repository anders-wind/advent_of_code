#include <algorithm>
#include <cctype>
#include <string>

#include <doctest/doctest.h>
#include <range/v3/algorithm/find_if.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/reverse.hpp>
#include <range/v3/view/zip.hpp>
#include <wind/helpers.hpp>

namespace wind::day01::part1
{

template<typename T>
struct value_and_index
{
    size_t index;
    T value;
};

static auto parse(std::string_view file)
{
    auto parser = [](std::string_view) {};
    return wind::read_input(file, parser);
}

static auto solve(const std::vector<int32_t>& input)
{
    return ranges::accumulate(input, 0, [](auto acc, auto v) { return acc + v; });
}

TEST_SUITE("part2")
{
    TEST_CASE("sample")
    {
        auto input = parse("./data/day01/sample2.txt");
        CHECK_EQ(solve(input), 281);
    }

    TEST_CASE("input")
    {
        auto input = parse("./data/day01/input2.txt");
        CHECK_EQ(solve(input), 54265);
    }
}

}  // namespace wind::day01::part1
