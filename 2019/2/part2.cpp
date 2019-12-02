#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <numeric>

std::vector<int> read_input()
{
    auto result = std::vector<int>();
    std::ifstream infile("input.txt");
    int elem;
    char seperator;
    while (infile >> elem)
    {
        result.push_back(elem);
        infile >> seperator;
    }
    return result;
}

void print(std::vector<int> arr)
{
    std::cout << "Array: " << std::endl;
    for (const auto elem : arr)
    {
        std::cout << "  " << elem << std::endl;
    }
}

int execute_codes(std::vector<int> codes, int noun, int verb) {
    codes[1] = noun;
    codes[2] = verb;
    auto i = 0;
    while(i < codes.size())
    {
        const auto code = codes[i];
        if (code == 99)
        {
            break;
        }
        else if (code == 1)
        {
            auto first = codes.at(i + 1);
            auto second = codes.at(i + 2);
            auto to = codes.at(i + 3);
            codes.at(to) = codes.at(first) + codes.at(second);
            i += 4;
        }
        else if (code == 2)
        {
            auto first = codes.at(i + 1);
            auto second = codes.at(i + 2);
            auto to = codes.at(i + 3);
            codes.at(to) = codes.at(first) * codes.at(second);
            i += 4;
        }
        else {
            i = -1;
            break;
        }
    }
    return codes[0];
}
// 490668 too high
int main()
{
    auto codes = read_input();
    for (auto noun = 0; noun < 100; noun++)
    {
        for (auto verb = 0; verb < 100; verb++)
        {
            auto result = execute_codes(codes, noun, verb);
            if (result == 19690720)
            {
                std::cout << 100 * noun + verb << std::endl;
                return 0;
            }
        }
    }
}
