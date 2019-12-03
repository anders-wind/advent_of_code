#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <numeric>
#include <functional>

std::vector<int> read_input() {
    auto result = std::vector<int>();
    std::ifstream infile("input.txt");
    int elem;
    while (infile >> elem)
    {
        result.push_back(elem);
    }
    return result;
}

// 5194854
int main() {
    auto masses = read_input();
    std::function<int(int)> fuel_calculator;
    fuel_calculator = [&](const int& elem) {
        const auto result = elem/3-2;
        if(result <= 0) {
            return 0;
        }
        return result + fuel_calculator(result);
    };
    std::transform(masses.begin(), masses.end(), masses.begin(), fuel_calculator);
    auto result = std::accumulate(masses.begin(), masses.end(), 0);
    std::cout << result << std::endl;
}