#pragma once
#include <fstream>
#include <ranges>
#include <stdexcept>
#include <string_view>
#include <vector>

#include <fmt/core.h>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/getlines.hpp>
#include <range/v3/view/transform.hpp>

#include <experimental/generator>

namespace wind
{

constexpr static auto is_digit = [](char v) -> bool { return std::isdigit(v); };
constexpr static auto to_digit = [](char v) -> int32_t { return v - '0'; };
constexpr static auto to_number = [](std::string_view sv) -> int32_t
{
    int32_t val {};
    auto result = std::from_chars(sv.data(), sv.data() + sv.size(), val);
    if (result.ec == std::errc::invalid_argument) {
        throw std::runtime_error(fmt::format("Could not convert to number: '{}'\n", sv));
    }
    return val;
};

constexpr static auto trim = [](std::string_view sv)
{
    if (sv.empty()) {
        return sv;
    }
    auto first = sv.find_first_not_of(" ");
    auto last = sv.find_last_not_of(" ");
    return sv.substr(first, last - first + 1);
};

constexpr static auto string_view_split = [](auto delimiter)
{
    return std::views::split(delimiter)                                            //
         | std::views::transform([](auto rng) { return std::string_view(rng); });  //
};

template<typename ParserT>
static auto read_input(std::string_view filename, ParserT parser)
{
    using T = std::invoke_result_t<ParserT, std::string_view>;
    auto fs = std::ifstream(std::string {filename});

    if (!fs.is_open()) {
        throw std::runtime_error(fmt::format("Could not read file: {}\n", filename));
    }

    return ranges::getlines(fs)                                                        //
         | ranges::views::filter([](std::string_view line) { return !line.empty(); })  //
         | ranges::views::transform(parser)                                            //
         | ranges::to<std::vector>;
}

}  // namespace wind
