"""
Day 9
"""
from typing import List
from part_1 import read_input, solve


def solve_2(numbers: List[int], preamble_size) -> int:
    invalid_number = solve(numbers, preamble_size)

    for i, number in enumerate(numbers):
        sum = number
        idx = i + 1
        while sum < invalid_number:
            sum += numbers[idx]
            idx += 1
        if sum == invalid_number:
            return max(numbers[i:idx - 1]) + min(numbers[i:idx - 1])

    print("Failed at finding the right number")
    return 0


def main():
    print(solve_2(read_input("sample.txt"), preamble_size=5))
    print(solve_2(read_input("input.txt"), preamble_size=25))


if __name__ == "__main__":
    main()