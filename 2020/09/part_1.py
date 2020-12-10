"""
Day 9
"""
from typing import List


def read_input(file_path) -> List[int]:
    res = []
    with open(file_path, 'r') as file_handle:
        for line in file_handle:
            res.append(int(line))
    return res


def solve(numbers: List[int], preamble_size) -> int:
    def has_opposite(i, number):
        for idx_1 in range(max(i - preamble_size, 0), i):
            for idx_2 in range(idx_1 + 1, i):
                sum = numbers[idx_1] + numbers[idx_2]
                if number == sum:
                    return True

        return False

    for i, number in enumerate(numbers[preamble_size:]):
        if not has_opposite(i + preamble_size, number):
            return number

    print("Failed at finding the right number")
    return 0


def main():
    print(solve(read_input("sample.txt"), preamble_size=5))
    print(solve(read_input("input.txt"), preamble_size=25))


if __name__ == "__main__":
    main()