#include <algorithm>
#include <cctype>
#include <ranges>
#include <string>
#include <vector>

#include <doctest/doctest.h>
#include <range/v3/algorithm/sort.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/zip.hpp>
#include <wind/helpers.hpp>

namespace wind::day01::part1
{

static auto parse(std::string_view file)
{
    auto list1 = std::vector<int64_t> {};
    auto list2 = std::vector<int64_t> {};
    auto parser = [&list1, &list2](std::string_view line)
    {
        auto splitted = line | wind::string_view_split("   ") | ranges::views::transform(&to_number<int64_t>)
                      | ranges::to<std::vector>();
        assert(splitted.size() == 2);
        list1.push_back(splitted[0]);
        list2.push_back(splitted[1]);
    };
    wind::read_input(file, parser);

    return std::make_pair(list1, list2);
}

static auto solve(const auto& input)
{
    auto [list1, list2] = input;
    ranges::sort(list1);
    ranges::sort(list2);

    return ranges::accumulate(ranges::views::zip(list1, list2),
                              0,
                              [](auto acc, auto v) { return acc + std::abs(std::get<0>(v) - std::get<1>(v)); });
}

TEST_SUITE("part1")
{
    TEST_CASE("sample")
    {
        auto input = parse("./data/day01/sample1.txt");
        CHECK_EQ(solve(input), 11);
    }

    TEST_CASE("input")
    {
        auto input = parse("./data/day01/input1.txt");
        CHECK_EQ(solve(input), 0);
    }
}

}  // namespace wind::day01::part1
