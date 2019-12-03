#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <numeric>
#include <array>
#include <sstream>
#include <string>
#include <tuple>
#include <optional>


struct Move {
    char direction;
    int length;
};

struct Coord {
    int x;
    int y;
    bool operator ==(const Coord & obj) const {
        return x==obj.x && y == obj.y;
    }
};

struct LineX {
    int y;
    int x1;
    int x2;
    int x_low;
    int x_high;
    int dist_before;

    LineX(int x1, int x2, int y, int dist_before): y(y), x1(x1), x2(x2), dist_before(dist_before) {
        x_low = std::min(x1, x2);
        x_high = std::max(x1, x2);
    }

    int length() {
        return x_high-x_low;
    }
};

struct LineY {
    int x;
    int y1;
    int y2;
    int y_low;
    int y_high;
    int dist_before;
    
    LineY(int y1, int y2, int x, int dist_before): x(x), y1(y1), y2(y2), dist_before(dist_before) {
        y_low = std::min(y1, y2);
        y_high = std::max(y1, y2);
    }

    int length() {
        return y_high-y_low;
    }
};

std::optional<Coord> intersects(const LineX& line_x, const LineY& line_y) {
    auto between_x = line_y.x >= line_x.x_low && line_y.x <= line_x.x_high;
    auto between_y = line_x.y >= line_y.y_low && line_x.y <= line_y.y_high;
    if(between_x && between_y) {
        return Coord{line_y.x, line_x.y};
    } else {
        return std::nullopt;
    }
}

std::array<std::vector<Move>, 2> read_input(const std::string& file_name)
{
    auto result = std::array<std::vector<Move>, 2>();
    std::ifstream infile(file_name);
    char direction;
    int length;
    char seperator;

    std::string line;
    for(auto i = 0; i< result.size();i++) {
        std::getline(infile, line);
        auto ss = std::stringstream(line);
        while (ss >> direction >> length)
        {
            result[i].push_back({direction, length});
            ss >> seperator;
        }
    }
    return result;
}

void print(const std::vector<Move>& arr)
{
    std::cout << "Array: " << std::endl;
    for (const auto& elem : arr)
    {
        std::cout << "  " << elem.direction << elem.length << std::endl;
    }
}


void print(const std::vector<Coord>& arr)
{
    std::cout << "Array: " << std::endl;
    for (const auto& elem : arr)
    {
        std::cout << "  " << elem.x << " " << elem.y << std::endl;
    }
}

void print(const std::vector<LineX>& arr) {
    std::cout << "Array: " << std::endl;
    for (const auto& elem : arr)
    {
        std::cout << "  xh:" << elem.x_high << " xl:" << elem.x_low << " y:" << elem.y << std::endl;
    }
}

void print(const std::vector<LineY>& arr) {
    std::cout << "Array: " << std::endl;
    for (const auto& elem : arr)
    {
        std::cout << "  yh:" << elem.y_high << " yl:" << elem.y_low << " x:" << elem.x << std::endl;
    }
}



int manhatten_distance(const Coord& point1, const Coord& point2) {
    return std::abs(point1.x-point2.x) + std::abs(point1.y-point2.y);
}


std::tuple<std::vector<LineX>, std::vector<LineY>> play_moves(const std::vector<Move>& moves, const Coord& start) {
    auto line_xs = std::vector<LineX>();
    auto line_ys = std::vector<LineY>();

    auto current_position = start;
    auto distance = 0;
    for(const auto& move : moves) {
        if(move.direction == 'U') {
            auto new_y = current_position.y + move.length;
            line_ys.push_back(LineY{current_position.y, new_y, current_position.x, distance});
            current_position.y = new_y;
        } 
        else if(move.direction == 'D') {
            auto new_y = current_position.y - move.length;
            line_ys.push_back(LineY{current_position.y, new_y, current_position.x, distance});
            current_position.y = new_y;
        } 
        else if(move.direction == 'L') {
            auto new_x = current_position.x - move.length;
            line_xs.push_back(LineX{current_position.x, new_x, current_position.y, distance});
            current_position.x = new_x;
        } 
        else if(move.direction == 'R') {
            auto new_x = current_position.x + move.length;
            line_xs.push_back(LineX{current_position.x, new_x, current_position.y, distance});
            current_position.x = new_x;
        } else {
            throw "what";
        }
        distance += move.length;
    }

    return { line_xs, line_ys};
}


int main()
{
    auto moves = read_input("input.txt");
    // print(moves[0]);
    // print(moves[1]);

    Coord start = {0,0};
    auto [line1_xs, line1_ys] = play_moves(moves[0], start);
    auto [line2_xs, line2_ys] = play_moves(moves[1], start);

    // print(line1_xs);
    // print(line1_ys);

    // print(line2_xs);
    // print(line2_ys);

    auto best_distance = std::numeric_limits<int>::max();
    for(auto& line_x : line1_xs) {
        for(auto& line_y: line2_ys) {
            auto intersect = intersects(line_x, line_y);
            if(intersect) {
                auto distance = line_x.dist_before + line_y.dist_before;
                distance += manhatten_distance(Coord{line_x.x1, line_y.y1}, intersect.value());
                // std::cout << distance << std::endl;
                // std::cout << "  " << intersect->x << " " << intersect->y << std::endl;
                if(distance < best_distance && distance > 0) {
                    best_distance = distance;
                }
            }
        }
    }
    for(auto& line_x : line2_xs) {
        for(auto& line_y: line1_ys) {
            auto intersect = intersects(line_x, line_y);
            if(intersect) {
                auto distance = line_x.dist_before + line_y.dist_before;
                distance += manhatten_distance(Coord{line_x.x1, line_y.y1}, intersect.value());
                // std::cout << distance << std::endl;
                // std::cout << "  " << intersect->x << " " << intersect->y << std::endl;
                if(distance < best_distance && distance > 0) {
                    best_distance = distance;
                }
            }
        }
    }

//     print(positions1);
//     print(positions2);

    std::cout << best_distance << std::endl;
}