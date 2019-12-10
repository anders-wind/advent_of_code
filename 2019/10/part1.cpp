#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

struct Coord
{
    int x;
    int y;

    bool operator==(const Coord& other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Coord& other) const
    {
        return !(*this == other);
    }
};

struct CoordTuple
{
    Coord coordinate;
    Coord lowest_fraction;
};

int manhattten(const Coord& coord1, const Coord& coord2)
{
    return std::abs(coord2.x - coord1.x) + std::abs(coord2.x - coord1.y);
}

struct CoordStack
{
    std::map<int, std::map<int, std::list<CoordTuple>>> coordinate_system;

    CoordStack(const std::vector<CoordTuple>& relative_coords)
    {
        for (const auto& coord_tuple : relative_coords)
        {
            auto low_x = coord_tuple.lowest_fraction.x;
            auto low_y = coord_tuple.lowest_fraction.y;
            coordinate_system[low_x][low_y].push_back(coord_tuple);
        }
        for (const auto& [key_x, val_x] : coordinate_system)
        {
            for (const auto& [key_y, val_y] : val_x)
            {
                std::sort(val_y.begin(), val_y.end(), [](const CoordTuple& coord1, const CoordTuple& coord2) {
                    return std::abs(coord1.coordinate.x) + std::abs(coord1.coordinate.y) >
                           std::abs(coord2.coordinate.x) + std::abs(coord2.coordinate.y);
                });
            }
        }
    }

    CoordTuple pop()
    {
        // given some current x and y values for rotation.
        // mutate the x or y in a proper way based the rotation by looking at the coordinate system values.
        // now when you have a std::list of elements with similar gradient pick the closest and remove it
        return { 0, 0 };
    }
};


namespace std
{
template <> struct hash<Coord>
{
    std::size_t operator()(const Coord& tuple) const
    {
        std::size_t res = tuple.x * 10000 + tuple.y;
        return res;
    }
};
} // namespace std

int calc_gcd(int a, int b)
{
    if (b == 0)
        return a;
    return calc_gcd(b, a % b);
}

Coord calc_lowest_fraction(const Coord& coord)
{
    Coord result;
    if (coord.x == 0 && coord.y == 0)
    {
        result = Coord{ 0, 0 };
    }
    else if (coord.x == 0)
    {
        auto y = coord.y > 0 ? 1 : -1;
        result = Coord{ 0, y };
    }
    else if (coord.y == 0)
    {
        auto x = coord.x > 0 ? 1 : -1;
        result = Coord{ x, 0 };
    }
    else
    {
        auto gcd = std::max(calc_gcd(std::abs(coord.x), std::abs(coord.y)), 1);
        auto result = Coord{ int(coord.x / gcd), int(coord.y / gcd) };
    }
    return result;
}

std::vector<Coord> read_input(const std::string& file_name)
{
    auto result = std::vector<Coord>();
    std::ifstream infile(file_name);
    if (!infile.is_open())
    {
        std::cerr << "could not open file" << std::endl;
        throw "error";
    }
    char sign;

    std::string line;
    int y = 0;
    while (std::getline(infile, line))
    {
        auto ss = std::stringstream(line);
        int x = 0;
        while (ss >> sign)
        {
            if (sign == '#')
            {
                result.push_back({ x, y });
            }
            x++;
        }
        y++;
    }
    return result;
}

void print(const std::vector<Coord>& coordinates)
{
    std::cout << "Coordinates {" << std::endl;
    for (const auto& elem : coordinates)
    {
        std::cout << "  (" << elem.x << ", " << elem.y << ")" << std::endl;
    }
    std::cout << "}" << std::endl;
}

int calc_number_of_observable_astroids(const std::vector<Coord>& astroids, Coord center)
{
    auto relative_coordinates = std::vector<CoordTuple>(astroids.size());
    std::transform(astroids.begin(), astroids.end(), relative_coordinates.begin(), [&center](const Coord& astroid) {
        auto relative_coord = Coord{ astroid.x - center.x, astroid.y - center.y };
        auto lowest_fraction = calc_lowest_fraction(relative_coord);
        return CoordTuple{ relative_coord, lowest_fraction };
    });

    auto observables = std::unordered_set<Coord>(); // the hash of a CoordTuple is its lowest fraction. So we only add if the lowest fraction has not been seen
    // std::cout << "CENTER " << center.x << " " << center.y << std::endl;

    for (const auto& coord_tuple : relative_coordinates)
    {
        auto is_center = coord_tuple.coordinate.x == 0 && coord_tuple.coordinate.y == 0;
        if (!is_center && observables.find(coord_tuple.lowest_fraction) == observables.end())
        {
            // std::cout << "  c" << coord_tuple.coordinate.x << " " << coord_tuple.coordinate.y <<
            // std::endl; std::cout << "  " << coord_tuple.lowest_fraction.x << " "
            //           << coord_tuple.lowest_fraction.y << std::endl;
            observables.insert(coord_tuple.lowest_fraction);
        }
    }
    // std::cout << "size " << observables.size() << std::endl;

    return static_cast<int>(observables.size());
}

int highest_number_of_observable_astroids(const std::vector<Coord>& astroids)
{
    auto best = 0;
    Coord best_coord;
    for (const auto& astroid : astroids)
    {
        auto number_of_observable_astroids = calc_number_of_observable_astroids(astroids, astroid);
        if (number_of_observable_astroids > best)
        {
            best = number_of_observable_astroids;
            best_coord = astroid;
        }
    }
    std::cout << "best_coord " << best_coord.x << " " << best_coord.y << std::endl;
    return best;
}


void test(const std::string& file_name, int expected)
{
    auto astroids = read_input(file_name);
    auto result = highest_number_of_observable_astroids(astroids);
    std::cout << result << " should be " << expected << std::endl;
}

int main()
{
    test("test0.txt", 8);
    test("test1.txt", 33);
    test("test2.txt", 35);
    test("test3.txt", 41);
    test("test4.txt", 210);

    std::cout << "Tests done" << std::endl << std::endl;

    std::cout << "Part 1: " << std::endl;
    // The real run:
    auto astroids = read_input("input.txt");
    // print(astroids);

    auto result = highest_number_of_observable_astroids(astroids);
    std::cout << "Result: " << result << std::endl;
}