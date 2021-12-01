#include <fstream>
#include <iostream>
#include <vector>

std::vector<int> parse_input(std::istream& input_stream)
{
    auto res = std::vector<int>();
    while (input_stream.good())
    {
        int x;
        input_stream >> x;
        res.push_back(x);
    }
    return res;
}


int solve(const std::vector<int>& input)
{
    int res = -1;
    int curr = 0;
    for (const auto& depth : input)
    {
        if (depth > curr)
        {
            res++;
        }
        curr = depth;
    }
    return res;
}

int main()
{
    auto file = std::fstream("input.txt");
    auto input = parse_input(file);
    std::cout << solve(input) << std::endl;
}
