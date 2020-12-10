"""
Day 10
"""
from typing import List


def read_input(file_path) -> List[int]:
    res = []
    with open(file_path, 'r') as file_handle:
        for line in file_handle:
            res.append(int(line))
    return res


def solve(numbers: List[int]) -> int:
    sorted_numbers = sorted(numbers)
    target = sorted_numbers[-1] + 3
    sorted_numbers.append(target)

    accus = [0, 0, 0, 0]
    prev = 0
    for number in sorted_numbers:
        accus[number - prev] += 1
        prev = number

    # print(accus)
    return accus[1] * accus[3]


def main():
    print(solve(read_input("sample.txt")))
    print(solve(read_input("input.txt")))


if __name__ == "__main__":
    main()