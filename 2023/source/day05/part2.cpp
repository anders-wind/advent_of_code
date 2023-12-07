#include <algorithm>
#include <cctype>
#include <map>
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

namespace wind::day05::part2
{

using namespace std::literals;

constexpr auto seeds_key = "seeds: "sv;
constexpr auto seed_to_soil_key = "seed-to-soil map:"sv;
constexpr auto soil_to_fertilizer_key = "soil-to-fertilizer map:"sv;
constexpr auto fertilizer_to_water_key = "fertilizer-to-water map:"sv;
constexpr auto water_to_light_key = "water-to-light map:"sv;
constexpr auto light_to_temperature_key = "light-to-temperature map:"sv;
constexpr auto temperature_to_humidity_key = "temperature-to-humidity map:"sv;
constexpr auto humidity_to_location_key = "humidity-to-location map:"sv;

enum struct ParsingMode
{
    seeds,
    seed_to_soil,
    soil_to_fertilizer,
    fertilizer_to_water,
    water_to_light,
    light_to_temperature,
    temperature_to_humidity,
    humidity_to_location,
};

// key_to_mode_map
static const auto key_to_mode_map = std::unordered_map<std::string_view, ParsingMode> {
    {seeds_key, ParsingMode::seeds},
    {seed_to_soil_key, ParsingMode::seed_to_soil},
    {soil_to_fertilizer_key, ParsingMode::soil_to_fertilizer},
    {fertilizer_to_water_key, ParsingMode::fertilizer_to_water},
    {water_to_light_key, ParsingMode::water_to_light},
    {light_to_temperature_key, ParsingMode::light_to_temperature},
    {temperature_to_humidity_key, ParsingMode::temperature_to_humidity},
    {humidity_to_location_key, ParsingMode::humidity_to_location},
};

struct Element
{
    int64_t source_start;
    int64_t destination_start;
    int64_t range;
};

constexpr static auto none_element = Element {-1, -1, -1};

struct Almanac
{
    std::vector<int64_t> seeds;
    std::map<int64_t, Element> seed_to_soil {
        {std::numeric_limits<int64_t>::min(), none_element},
        {std::numeric_limits<int64_t>::max(), none_element},
    };
    std::map<int64_t, Element> soil_to_fertilizer {
        {std::numeric_limits<int64_t>::min(), none_element},
        {std::numeric_limits<int64_t>::max(), none_element},
    };
    std::map<int64_t, Element> fertilizer_to_water {
        {std::numeric_limits<int64_t>::min(), none_element},
        {std::numeric_limits<int64_t>::max(), none_element},
    };
    std::map<int64_t, Element> water_to_light {
        {std::numeric_limits<int64_t>::min(), none_element},
        {std::numeric_limits<int64_t>::max(), none_element},
    };
    std::map<int64_t, Element> light_to_temperature {
        {std::numeric_limits<int64_t>::min(), none_element},
        {std::numeric_limits<int64_t>::max(), none_element},
    };
    std::map<int64_t, Element> temperature_to_humidity {
        {std::numeric_limits<int64_t>::min(), none_element},
        {std::numeric_limits<int64_t>::max(), none_element},
    };
    std::map<int64_t, Element> humidity_to_location {
        {std::numeric_limits<int64_t>::min(), none_element},
        {std::numeric_limits<int64_t>::max(), none_element},
    };
};

static auto parse(std::string_view file)
{
    auto almanac = Almanac {};
    auto mode = ParsingMode::seeds;
    for (auto line : wind::get_lines(file)) {
        if (key_to_mode_map.contains(line)) {
            mode = key_to_mode_map.at(line);
            if (mode != ParsingMode::seeds) {
                continue;
            }
        }

        if (mode == ParsingMode::seeds) {
            almanac.seeds = line.substr(seeds_key.size()) | wind::string_view_split(' ')
                          | std::views::transform(&wind::to_number<int64_t>) | ranges::to<std::vector>;
            continue;
        }

        auto numbers = line | wind::string_view_split(' ') | std::views::transform(&wind::to_number<int64_t>)
                     | ranges::to<std::vector>;
        auto destination_range_start = numbers.at(0);
        auto source_range_start = numbers.at(1);
        auto range_length = numbers.at(2);
        if (mode == ParsingMode::seed_to_soil) {
            almanac.seed_to_soil.insert_or_assign(source_range_start + range_length - 1,
                                                  Element {
                                                      .source_start = source_range_start,
                                                      .destination_start = destination_range_start,
                                                      .range = range_length,
                                                  });
        } else if (mode == ParsingMode::soil_to_fertilizer) {
            almanac.soil_to_fertilizer.insert_or_assign(source_range_start + range_length - 1,
                                                        Element {
                                                            .source_start = source_range_start,
                                                            .destination_start = destination_range_start,
                                                            .range = range_length,
                                                        });
        } else if (mode == ParsingMode::fertilizer_to_water) {
            almanac.fertilizer_to_water.insert_or_assign(source_range_start + range_length - 1,
                                                         Element {
                                                             .source_start = source_range_start,
                                                             .destination_start = destination_range_start,
                                                             .range = range_length,
                                                         });
        } else if (mode == ParsingMode::water_to_light) {
            almanac.water_to_light.insert_or_assign(source_range_start + range_length - 1,
                                                    Element {
                                                        .source_start = source_range_start,
                                                        .destination_start = destination_range_start,
                                                        .range = range_length,
                                                    });
        } else if (mode == ParsingMode::light_to_temperature) {
            almanac.light_to_temperature.insert_or_assign(source_range_start + range_length - 1,
                                                          Element {
                                                              .source_start = source_range_start,
                                                              .destination_start = destination_range_start,
                                                              .range = range_length,
                                                          });
        } else if (mode == ParsingMode::temperature_to_humidity) {
            almanac.temperature_to_humidity.insert_or_assign(source_range_start + range_length - 1,
                                                             Element {
                                                                 .source_start = source_range_start,
                                                                 .destination_start = destination_range_start,
                                                                 .range = range_length,
                                                             });
        } else if (mode == ParsingMode::humidity_to_location) {
            almanac.humidity_to_location.insert_or_assign(source_range_start + range_length - 1,
                                                          Element {
                                                              .source_start = source_range_start,
                                                              .destination_start = destination_range_start,
                                                              .range = range_length,
                                                          });
        }
    }
    return almanac;
}

static int64_t get_next_level(const std::map<int64_t, Element>& collection, int64_t value)
{
    auto it = collection.lower_bound(value);
    auto [source_start, destination_start, range] = it->second;
    if (value >= source_start && value < source_start + range) {
        return destination_start + (value - source_start);
    } else {
        return value;
    }
}

static auto solve(const auto& input)
{
    auto min_location = std::numeric_limits<int64_t>::max();
    for (auto i = 0ULL; i < input.seeds.size(); i += 2) {
        auto seed_start = input.seeds.at(i);
        auto seed_end = seed_start + input.seeds.at(i + 1);
        for (auto seed = seed_start; seed < seed_end; seed++) {
            fmt::print("{}\n", seed);
            // fmt::print("seed: {}\n", seed);
            auto soil = get_next_level(input.seed_to_soil, seed);
            // fmt::print("> soil: {}\n", soil);

            auto fertilizer = get_next_level(input.soil_to_fertilizer, soil);
            // fmt::print(">> fertilizer: {}\n", fertilizer);

            auto water = get_next_level(input.fertilizer_to_water, fertilizer);
            // fmt::print(">>> water: {}\n", water);

            auto light = get_next_level(input.water_to_light, water);
            // fmt::print(">>>> light: {}\n", light);

            auto temperature = get_next_level(input.light_to_temperature, light);
            // fmt::print(">>>>> temperature: {}\n", temperature);

            auto humidity = get_next_level(input.temperature_to_humidity, temperature);
            // fmt::print(">>>>>> humidity: {}\n", humidity);

            auto location = get_next_level(input.humidity_to_location, humidity);
            // fmt::print(">>>>>>> location: {}\n", location);

            min_location = std::min(min_location, location);
        }
    }
    return min_location;
}

TEST_SUITE("part2")
{
    TEST_CASE("sample")
    {
        auto input = parse("./data/day05/sample2.txt");
        CHECK_EQ(solve(input), 46);
    }

    TEST_CASE("input")
    {
        auto input = parse("./data/day05/input2.txt");
        CHECK_EQ(solve(input), 0);
    }
}

}  // namespace wind::day05::part2
