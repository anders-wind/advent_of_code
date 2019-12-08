#include <array>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>


template <int Width, int Height>
std::vector<std::array<int, Width * Height>> read_input(const std::string& file_name)
{
    constexpr auto size = Width * Height;
    auto result = std::vector<std::array<int, size>>();
    std::ifstream infile(file_name);
    if (!infile.is_open())
    {
        throw "cannot open file";
    }
    int digit_counter = 0;
    auto layer = std::array<int, size>();
    char elem;

    while (infile >> elem)
    {
        layer[digit_counter] = elem - '0';
        digit_counter++;

        if (digit_counter == size)
        {
            result.push_back(layer);
            digit_counter = 0;
        }
    }
    return result;
}

template <int Width> int index(int row, int col)
{
    return row * Width + col;
}

template <int Width, int Height> void print_layer(const std::array<int, Width * Height>& layer)
{
    std::cout << "Layer {" << std::endl;
    for (auto i = 0; i < Height; i++)
    {
        for (auto j = 0; j < Width; j++)
        {
            std::cout << " " << layer[index<Width>(i, j)];
        }
        std::cout << std::endl;
    }
    std::cout << "}" << std::endl;
}

template <int Width, int Height>
void print(const std::vector<std::array<int, Width * Height>>& image)
{
    for (const auto& layer : image)
    {
        print_layer<Width, Height>(layer);
    }
}

template <int Width, int Height>
std::array<int, Width * Height>
layer_with_least_zeroes(const std::vector<std::array<int, Width * Height>>& image)
{
    constexpr auto size = Width * Height;

    auto result_idx = -1;
    auto least_zeroes = std::numeric_limits<int>::max();
    for (auto idx = 0; idx < image.size(); idx++)
    {
        auto zeroes = 0;
        for (auto i = 0; i < size; i++)
        {
            zeroes += image[idx][i] == 0;
        }
        if (zeroes < least_zeroes)
        {
            least_zeroes = zeroes;
            result_idx = idx;
        }
    }
    return image[result_idx];
}

template <int Width, int Height> int checksum(const std::array<int, Width * Height>& layer)
{
    int ones = 0;
    int twos = 0;
    for (auto i = 0; i < layer.size(); i++)
    {
        ones += layer[i] == 1;
        twos += layer[i] == 2;
    }
    return ones * twos;
}


template <int Width, int Height>
std::array<int, Width * Height> combined_layers(const std::vector<std::array<int, Width * Height>>& image)
{
    constexpr auto size = Width * Height;

    auto result = std::array<int, size>();
    result.fill(2);
    for (auto idx = 0; idx < image.size(); idx++)
    {
        for (auto i = 0; i < size; i++)
        {
            if (result[i] == 2)
            {
                result[i] = image[idx][i];
            }
        }
    }
    return result;
}

int main()
{
    constexpr auto width = 25;
    constexpr auto height = 6;
    auto image = read_input<width, height>("input.txt");
    // print<width, height>(image);
    auto layer = combined_layers<width, height>(image);
    print_layer<width, height>(layer); // Look at the image and see the message
    return 0;
}