#include <algorithm>
#include <cctype>
#include <ranges>
#include <string>

#include <doctest/doctest.h>
#include <range/v3/algorithm/find_if.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/reverse.hpp>
#include <range/v3/view/split.hpp>
#include <range/v3/view/split_when.hpp>
#include <wind/helpers.hpp>

namespace wind::day02::part2
{

struct game
{
    int32_t max_red {0};
    int32_t max_green {0};
    int32_t max_blue {0};

    auto power() const
    {
        return static_cast<int64_t>(this->max_red) * static_cast<int64_t>(this->max_green)
             * static_cast<int64_t>(this->max_blue);
    }
};

static auto parse(std::string_view file)
{
    auto parser = [](std::string_view line)
    {
        auto game_stop = line.find(':');
        auto g = game {};
        auto rounds = line.substr(game_stop + 1) | std::views::split(';')
                    | std::views::transform([](auto rng) { return std::string_view(rng); });
        for (auto round : rounds) {
            auto values =
                round | std::views::split(',') | std::views::transform([](auto rng) { return std::string_view(rng); });

            for (auto value : values) {
                if (auto it_red = value.find("red"); it_red != std::string_view::npos) {
                    g.max_red = std::max(g.max_red, to_number(trim(value.substr(0, it_red))));
                } else if (auto it_blue = value.find("blue"); it_blue != std::string_view::npos) {
                    g.max_blue = std::max(g.max_blue, to_number(trim(value.substr(0, it_blue))));
                } else if (auto it_green = value.find("green"); it_green != std::string_view::npos) {
                    g.max_green = std::max(g.max_green, to_number(trim(value.substr(0, it_green))));
                }
            }
        }
        return g;
    };
    return wind::read_input(file, parser);
}

static auto solve(const auto& input)
{
    return ranges::accumulate(input, 0LL, [](auto acc, auto g) { return acc + g.power(); });
}

TEST_SUITE("part2")
{
    TEST_CASE("sample")
    {
        auto input = parse("./data/day02/sample2.txt");
        CHECK_EQ(solve(input), 2286);
    }

    TEST_CASE("input")
    {
        auto input = parse("./data/day02/input2.txt");
        CHECK_EQ(solve(input), 62241);
    }
}

}  // namespace wind::day02::part2
