#include <algorithm>
#include <charconv>
#include <format>
#include <fstream>
#include <iostream>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

auto parse_file(const std::string& file_name) -> std::vector<std::vector<int64_t>>
{
    auto istream = std::fstream(file_name);
    auto res = std::vector<std::vector<int64_t>>(1);
    std::string line;
    auto current = 0;
    while (istream.good())
    {
        std::getline(istream, line);
        if (line.empty())
        {
            res.emplace_back();
            current++;
        }
        else
        {
            int64_t val{};
            std::from_chars(line.data(), line.data() + line.size(), val);
            res.at(current).emplace_back(val);
        }
    }
    return res;
}

auto print(const std::vector<std::vector<int64_t>>& input) -> void
{
    for (const auto& elf : input)
    {
        std::cout << "[";
        for (const auto& food : elf)
        {
            std::cout << food << ", ";
        }
        std::cout << "]" << std::endl;
    }
}

auto find_max_inventory(const std::vector<std::vector<int64_t>>& input) -> int64_t
{
    return std::ranges::max(input | std::ranges::views::transform(
                                        [](const std::vector<int64_t>& list)
                                        { return std::accumulate(list.begin(), list.end(), 0LL); }));
}

auto solve(const std::string& file) -> void
{
    std::cout << file << std::endl;
    auto input = parse_file(file);
    print(input);
    std::cout << find_max_inventory(input) << std::endl << std::endl;
}

int main()
{
    solve("example.txt");
    solve("input.txt");
    return 0;
}