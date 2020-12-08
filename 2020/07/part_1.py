"""
day 7
"""


def read_input(file_path):
    res = {}
    with open(file_path, 'r') as file_handle:
        for line in file_handle:
            color = line[:line.find("bags") - 1]
            res[color] = []
            for containing in line[line.find("contain") + 7:].split(","):
                clean_containing = containing.strip()
                if clean_containing != "no other bags.":
                    amt = int(clean_containing[:clean_containing.find(" ")])
                    other_color = clean_containing[clean_containing.find(" ") +
                                                   1:clean_containing.
                                                   find(" bag")]
                    res[color].append((amt, other_color))

    return res


def solve(data):
    def build_reverse_graph():
        reverse_map = {}
        for type, amt_connections in data.items():
            if type not in reverse_map:
                reverse_map[type] = []

            for amt, connection in amt_connections:
                if connection not in reverse_map:
                    reverse_map[connection] = []
                reverse_map[connection].append(type)
        return reverse_map

    rev_map = build_reverse_graph()

    res = set({})
    next = ['shiny gold']
    while next:
        node = next.pop()
        for other_bag in rev_map[node]:
            res.add(other_bag)
            next.append(other_bag)

    return len(res)


def main():
    print(solve(read_input("sample.txt")))
    print(solve(read_input("input.txt")))


if __name__ == "__main__":
    main()