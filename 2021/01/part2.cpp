#include <deque>
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
    int res = 0;
    std::deque<int> window;
    auto sum = 0;
    for (const auto& depth : input)
    {
        if (window.size() < 3)
        {
            window.push_back(depth);
            sum += depth;
            continue;
        }

        auto to_remove = window.front();


        auto new_sum = sum - to_remove + depth;
        if (new_sum > sum)
        {
            res++;
        }
        window.pop_front();
        window.push_back(depth);

        sum = new_sum;
    }
    return res;
}

int main()
{
    auto file = std::fstream("input.txt");
    auto input = parse_input(file);
    std::cout << solve(input) << std::endl;
}
