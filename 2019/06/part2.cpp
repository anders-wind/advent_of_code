#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

struct Graph
{
    int number_of_vertices_;
    std::vector<int8_t> edges_;

    Graph(int number_of_vertices)
      : number_of_vertices_(number_of_vertices)
      , edges_(std::vector<int8_t>(number_of_vertices * number_of_vertices))
    {
    }

    void add_edge(int from, int to)
    {
        edges_[index(from, to)] = true;
    }

    int index(int from, int to) const
    {
        return from * number_of_vertices_ + to;
    }

    int8_t has_edge(int from, int to) const
    {
        return edges_[index(from, to)];
    }

    std::string to_string() const
    {
        std::stringstream ss;
        ss << "Graph {" << std::endl;
        for (auto i = 0; i < number_of_vertices_; i++)
        {
            for (auto j = 0; j < number_of_vertices_; j++)
            {
                ss << " " << bool(edges_[index(i, j)]);
            }
            ss << std::endl;
        }
        ss << "}";
        return ss.str();
    }

    std::vector<int> bfs(int from, int to) const
    {
        auto visited = std::vector<int8_t>(number_of_vertices_);
        auto prev = std::vector<int>(number_of_vertices_);
        std::queue<int> q;
        q.push(from);
        auto found = false;

        while (!q.empty())
        {
            auto active = q.front();
            if (active == to)
            {
                found = true;
                break;
            }
            visited[active] = true;
            q.pop();
            for (auto i = 0; i < number_of_vertices_; i++)
            {
                if (i != active && !visited[i] && has_edge(active, i))
                {
                    prev[i] = active;
                    q.push(i);
                }
            }
        }

        auto path = std::vector<int>();
        if (!found)
        {
            return path;
        }

        int next = to;
        while (next != from)
        {
            path.push_back(next);
            next = prev[next];
        }
        path.push_back(from);
        return path;
    }

    bool is_connected() const
    {
        auto visited = std::vector<int8_t>(number_of_vertices_);
        std::queue<int> q;
        q.push(0);

        auto total = 0;
        while (!q.empty() && total != number_of_vertices_)
        {
            auto active = q.front();
            visited[active] = true;
            q.pop();
            total++;
            for (auto i = 0; i < number_of_vertices_; i++)
            {
                if (i != active && !visited[i] && has_edge(active, i))
                {
                    q.push(i);
                }
            }
        }
        return total == number_of_vertices_;
    }
};

std::vector<std::tuple<std::string, std::string>> read_input(const std::string& file_name)
{
    std::ifstream infile(file_name);
    if (!infile.is_open())
    {
        throw "file could not be opened";
    }
    char elem;

    auto result = std::vector<std::tuple<std::string, std::string>>();
    std::string line;
    while (std::getline(infile, line))
    {
        auto ss = std::stringstream(line);
        auto ss_out = std::stringstream();
        std::string first;
        while (ss >> elem)
        {
            if (elem == ')')
            {
                first = ss_out.str();
                ss_out.str("");
            }
            else
            {
                ss_out << elem;
            }
        }
        std::string second = ss_out.str();
        result.push_back({ first, second });
    }

    return result;
}

std::tuple<std::unordered_map<std::string, int>, std::unordered_map<int, std::string>>
get_id_map(const std::vector<std::tuple<std::string, std::string>>& map)
{
    auto planet_to_id_map = std::unordered_map<std::string, int>();
    auto id_to_planet_map = std::unordered_map<int, std::string>();
    int current_id = 0;
    for (const auto& [first, second] : map)
    {
        if (planet_to_id_map.find(first) == planet_to_id_map.end())
        {
            planet_to_id_map.insert({ first, current_id });
            id_to_planet_map.insert({ current_id, first });
            current_id++;
        }
        if (planet_to_id_map.find(second) == planet_to_id_map.end())
        {
            planet_to_id_map.insert({ second, current_id });
            id_to_planet_map.insert({ current_id, second });
            current_id++;
        }
    }
    return { planet_to_id_map, id_to_planet_map };
}

void print_map_and_ids(const std::vector<std::tuple<std::string, std::string>>& map,
                       const std::unordered_map<std::string, int>& id_map)
{
    for (const auto& [first, second] : map)
    {
        int first_id = id_map.find(first)->second;
        int second_id = id_map.find(second)->second;
        std::cout << first << ")" << second << "\t" << first_id << ")" << second_id << std::endl;
    }
}

int id_of(const std::unordered_map<std::string, int>& id_map, const std::string& name)
{
    return id_map.find(name)->second;
}

Graph build_graph(const std::vector<std::tuple<std::string, std::string>>& map,
                  const std::unordered_map<std::string, int>& id_map)
{
    auto graph = Graph(id_map.size());
    for (const auto& [first, second] : map)
    {
        auto first_id = id_map.find(first)->second;
        auto second_id = id_map.find(second)->second;
        graph.add_edge(second_id, first_id);
        graph.add_edge(first_id, second_id);
    }
    return graph;
}

void print_path(const std::vector<int>& path, const std::unordered_map<int, std::string>& planet_map)
{
    for (const auto& elem : path)
    {
        std::cout << planet_map.find(elem)->second << ", ";
    }
    std::cout << std::endl;
}

int main()
{
    auto map = read_input("input.txt");
    auto [id_map, planet_map] = get_id_map(map);
    auto san_id = id_of(id_map, "YOU");
    auto you_id = id_of(id_map, "SAN");
    // print_map_and_ids(map, id_map);

    auto graph = build_graph(map, id_map);
    // std::cout << graph.to_string() << std::endl;
    // std::cout << graph.is_connected() << std::endl;
    // std::cout << com_id << std::endl;

    auto path = graph.bfs(you_id, san_id);
    // print_path(path, planet_map);
    std::cout << (path.size() - 3) << std::endl;
    return 0;
}