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
        auto path = std::vector<int>();
        std::queue<int> q;
        q.push(from);

        while (!q.empty())
        {
            auto active = q.front();
            path.push_back(active);
            if (active == to)
            {
                return path;
            }
            visited[active] = true;
            q.pop();
            for (auto i = 0; i < number_of_vertices_; i++)
            {
                if (i != active && !visited[i] && has_edge(active, i))
                {
                    q.push(i);
                }
            }
        }
        return {};
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

std::unordered_map<std::string, int> get_id_map(const std::vector<std::tuple<std::string, std::string>>& map)
{
    auto planet_to_id_map = std::unordered_map<std::string, int>();
    int current_id = 0;
    for (const auto& [first, second] : map)
    {
        if (planet_to_id_map.find(first) == planet_to_id_map.end())
        {
            planet_to_id_map.insert({ first, current_id++ });
        }
        if (planet_to_id_map.find(second) == planet_to_id_map.end())
        {
            planet_to_id_map.insert({ second, current_id++ });
        }
    }
    return planet_to_id_map;
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

int id_of_com(const std::unordered_map<std::string, int>& id_map)
{
    return id_map.find("COM")->second;
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
    }
    return graph;
}

int main()
{
    auto map = read_input("input.txt");
    auto id_map = get_id_map(map);
    auto com_id = id_of_com(id_map);
    // print_map_and_ids(map, id_map);

    auto graph = build_graph(map, id_map);
    // std::cout << graph.to_string() << std::endl;
    // std::cout << graph.is_connected() << std::endl;
    // std::cout << com_id << std::endl;

    auto total = 0;
    for (auto i = 0; i < graph.number_of_vertices_; i++)
    {
        if (i != com_id)
        {
            auto path = graph.bfs(i, com_id);
            // std::cout << path.size() << std::endl;
            if (!path.empty())
            {
                total += path.size() - 1; // path includes self
            }
        }
    }
    std::cout << total << std::endl;
    return 0;
}