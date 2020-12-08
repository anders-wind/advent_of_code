"""
day 7
"""
from part_1 import read_input


def solve(data):
    cache = {}

    def opt(node):
        if node in cache:
            return cache[node]
        value = 1

        for amt, connection in data[node]:
            value += opt(connection) * amt

        cache[node] = value
        return value

    return opt('shiny gold') - 1


def main():
    print(solve(read_input("sample.txt")))
    print(solve(read_input("input.txt")))


if __name__ == "__main__":
    main()