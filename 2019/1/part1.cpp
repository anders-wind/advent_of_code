#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <numeric>

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

int main() {
    auto masses = read_input();
    std::transform(masses.begin(), masses.end(), masses.begin(), [](const int& elem) {
        return elem/3-2;
    });
    auto result = std::accumulate(masses.begin(), masses.end(), 0);
    std::cout << result << std::endl;
}