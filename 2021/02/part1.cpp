#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

enum struct Direction
{
    Forward,
    Down,
    Up,
};

struct Move
{
    Direction direction;
    int amt;
};

std::vector<Move> read_input(std::ifstream& istream)
{
    auto result = std::vector<Move>();

    std::string line;
    while (istream.good())
    {
        std::getline(istream, line);
        auto tokens = line.substr(0, line.find(" "));
        Direction direction;
        if (tokens == "forward")
        {
            direction = Direction::Forward;
        }
        else if (tokens == "down")
        {
            direction = Direction::Down;
        }
        else
        {
            direction = Direction::Up;
        }

        auto amt = std::stoi(line.substr(line.find(" "), line.size()));

        result.push_back({ direction, amt });
    }
    return result;
}

int solve(const std::vector<Move>& instance)
{
    auto hori = 0;
    auto depth = 0;

    for (const auto& move : instance)
    {
        switch (move.direction)
        {
        case Direction::Up:
        {
            depth -= move.amt;
        }
        break;
        case Direction::Down:
        {
            depth += move.amt;
        }
        break;
        case Direction::Forward:
        {
            hori += move.amt;
        }
        break;
        }
    }
    return hori * depth;
}

int main()
{
    std::ifstream infile("input.txt");
    auto input = read_input(infile);
    std::cout << solve(input) << std::endl;
}