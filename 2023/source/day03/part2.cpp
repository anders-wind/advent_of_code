#include <algorithm>
#include <cctype>
#include <ranges>
#include <string>
#include <variant>
#include <vector>

#include <doctest/doctest.h>
#include <range/v3/algorithm/find_if.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/reverse.hpp>
#include <range/v3/view/split.hpp>
#include <range/v3/view/split_when.hpp>
#include <wind/helpers.hpp>

namespace wind::day03::part2
{

struct gear
{
};
struct disregard
{
};
using part = std::variant<disregard, gear, int32_t>;

static auto parse(std::string_view file) -> std::vector<std::vector<part>>
{
    auto parser = [](std::string_view line)
    {
        auto vec = line
                 | ranges::views::transform(
                       [](char v) -> part
                       {
                           if (v == '*') {
                               return gear {};
                           } else if (isdigit(v)) {
                               return to_digit(v);
                           } else {
                               return disregard {};
                           }
                       })
                 | ranges::to<std::vector>;
        return vec;
    };
    return wind::read_input(file, parser);
}

static auto solve(const std::vector<std::vector<part>>& input)
{
    auto num_rows = static_cast<int64_t>(input.size());
    auto num_cols = static_cast<int64_t>(input.at(0).size());

    auto get_full_number = [&](int64_t row, int64_t col)
    {
        // find beginning of number in row
        auto start_col = col;
        for (auto i = col - 1; i >= 0LL; i--) {
            if (!std::holds_alternative<int32_t>(input.at(static_cast<size_t>(row)).at(static_cast<size_t>(i)))) {
                break;
            }
            start_col = i;
        }
        // find the end of the number in row
        auto end_col = col;
        for (auto i = col + 1; i < num_cols; i++) {
            if (!std::holds_alternative<int32_t>(input.at(static_cast<size_t>(row)).at(static_cast<size_t>(i)))) {
                break;
            }
            end_col = i;
        }
        // convert to full number
        auto number = 0;
        for (auto i = start_col; i <= end_col; i++) {
            number *= 10;
            number += std::get<int32_t>(input.at(static_cast<size_t>(row)).at(static_cast<size_t>(i)));
        }
        return std::make_pair(number, start_col);
    };

    auto iterate_neighbours = [&](auto i, auto j)
    {
        auto taken_start_positions = std::vector<std::vector<bool>>(
            static_cast<size_t>(num_rows), std::vector<bool>(static_cast<size_t>(num_cols), false));
        // check neighbouring cells including diagonals
        auto numbers = std::vector<int32_t> {};
        for (auto k = i - 1; k <= i + 1; k++) {
            for (auto l = j - 1; l <= j + 1; l++) {
                if (k >= 0LL && k < num_rows && l >= 0LL && l < num_cols) {
                    if (std::holds_alternative<int32_t>(input.at(static_cast<size_t>(k)).at(static_cast<size_t>(l)))) {
                        auto [number, start_col] = get_full_number(k, l);
                        if (!taken_start_positions.at(static_cast<size_t>(k)).at(static_cast<size_t>(start_col))) {
                            numbers.emplace_back(number);
                            taken_start_positions.at(static_cast<size_t>(k)).at(static_cast<size_t>(start_col)) = true;
                        }
                    }
                }
            }
        }
        if (numbers.size() == 2) {
            return numbers.at(0) * numbers.at(1);
        }
        return 0;
    };

    auto value = 0;
    for (auto i = 0LL; i < num_rows; i++) {
        const auto& row = input.at(static_cast<size_t>(i));
        for (auto j = 0LL; j < num_cols; j++) {
            if (std::holds_alternative<gear>(row.at(static_cast<size_t>(j)))) {
                // check neighbouring cells including diagonals
                value += iterate_neighbours(i, j);
            }
        }
    }
    return value;
}

TEST_SUITE("part2")
{
    TEST_CASE("sample")
    {
        auto input = parse("./data/day03/sample2.txt");
        CHECK_EQ(solve(input), 467835);
    }

    TEST_CASE("input")
    {
        auto input = parse("./data/day03/input2.txt");
        CHECK_EQ(solve(input), 87287096);
    }
}

}  // namespace wind::day03::part2
