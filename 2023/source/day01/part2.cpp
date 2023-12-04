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
    constexpr auto valid_substrings = std::array {
        "1",
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine",
    };
    constexpr auto values =
        std::array<int32_t, valid_substrings.size()> {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto parser = [](std::string_view line) -> int32_t
    {
        auto first = value_and_index<int32_t> {line.size() + 1, -1};
        for (auto [valid_substring, val] : ranges::views::zip(valid_substrings, values)) {
            auto str_index = line.find(valid_substring);
            if (str_index != std::string_view::npos && str_index < first.index) {
                first = value_and_index<int32_t> {str_index, val};
            }
        }
        auto last = value_and_index<int32_t> {0ULL, -1};
        for (auto [valid_substring, val] : ranges::views::zip(valid_substrings, values)) {
            auto str_index = line.rfind(valid_substring);
            if (str_index != std::string_view::npos && str_index >= last.index) {
                last = value_and_index<int32_t> {str_index, val};
            }
        }
        return 10 * first.value + last.value;
    };
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
