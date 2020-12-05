"""
day 5
"""
from typing import List
from part_1 import read_input, solve_one


def solve(data: List[str]):

    seat_ids = sorted([solve_one(bording_pass) for bording_pass in data])
    for idx in range(len(seat_ids))[1:-1]:
        prev = seat_ids[idx - 1]
        if prev + 2 == seat_ids[idx]:
            return prev + 1


def main():
    print(solve(read_input("sample.txt")))
    print(solve(read_input("input.txt")))


if __name__ == "__main__":
    main()