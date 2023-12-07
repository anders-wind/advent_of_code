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

namespace wind::day02::part1
{

struct game
{
    int32_t id = {0};
    int32_t max_red {0};
    int32_t max_green {0};
    int32_t max_blue {0};
};

static auto parse(std::string_view file)
{
    auto parser = [](std::string_view line)
    {
        auto game_stop = line.find(':');
        auto game_id_start = line.find(' ');
        auto g = game {.id = to_number<int32_t>(trim(line.substr(game_id_start, game_stop - game_id_start)))};
        auto rounds = line.substr(game_stop + 1) | std::views::split(';')
                    | std::views::transform([](auto rng) { return std::string_view(rng); });
        for (auto round : rounds) {
            auto values =
                round | std::views::split(',') | std::views::transform([](auto rng) { return std::string_view(rng); });

            for (auto value : values) {
                if (auto it_red = value.find("red"); it_red != std::string_view::npos) {
                    g.max_red = std::max(g.max_red, to_number<int32_t>(trim(value.substr(0, it_red))));
                } else if (auto it_blue = value.find("blue"); it_blue != std::string_view::npos) {
                    g.max_blue = std::max(g.max_blue, to_number<int32_t>(trim(value.substr(0, it_blue))));
                } else if (auto it_green = value.find("green"); it_green != std::string_view::npos) {
                    g.max_green = std::max(g.max_green, to_number<int32_t>(trim(value.substr(0, it_green))));
                }
            }
        }
        return g;
    };
    return wind::read_input(file, parser);
}

static auto solve(const auto& input)
{
    // only 12 red cubes, 13 green cubes, and 14 blue cubes
    return ranges::accumulate(input,
                              0,
                              [](auto acc, auto g)
                              {
                                  auto was_possible = g.max_red <= 12 && g.max_green <= 13 && g.max_blue <= 14;
                                  return acc + (was_possible ? g.id : 0);
                              });
}

TEST_SUITE("part1")
{
    TEST_CASE("sample")
    {
        auto input = parse("./data/day02/sample1.txt");
        CHECK_EQ(solve(input), 8);
    }

    TEST_CASE("input")
    {
        auto input = parse("./data/day02/input1.txt");
        CHECK_EQ(solve(input), 2207);
    }
}

}  // namespace wind::day02::part1
