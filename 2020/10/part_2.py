"""
Day 10
"""
from typing import List
from part_1 import read_input


def solve(numbers: List[int]) -> int:
    sorted_numbers = sorted(numbers)

    dense_indicator = [True]
    current_value = 1
    for x in sorted_numbers:
        while current_value < x:
            dense_indicator.append(False)
            current_value += 1

        dense_indicator.append(True)
        current_value += 1

    cache = {}
    cache[0] = 1

    def opt(idx):
        if idx in cache:
            return cache[idx]

        value = 0
        if dense_indicator[idx]:
            for child in range(max(idx - 3, 0), idx):
                value += opt(child)

        cache[idx] = value
        return value

    res = opt(sorted_numbers[-1])
    return res


def main():
    print(solve(read_input("small.txt")))
    print(solve(read_input("sample.txt")))
    print(solve(read_input("input.txt")))


if __name__ == "__main__":
    main()