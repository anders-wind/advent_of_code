"""
day 3
"""
from functools import reduce
from typing import List

from part_1 import read_input


def solve(data: List[List[bool]]):
    # print(f"{len(data)},{len(data[0])}")
    def check_for_move(move_vert: int, move_hori: int):
        pos_hori = 0
        pos_vert = 0
        hori_max = len(data[0])
        tree_count = 0
        while pos_vert < len(data):
            if data[pos_vert][pos_hori]:
                tree_count += 1
                # print(f"tree: {pos_vert},{pos_hori}")

            pos_hori = (pos_hori + move_hori) % (hori_max - 1)
            pos_vert += move_vert
        return tree_count

    results = [
        check_for_move(1, 1),
        check_for_move(1, 3),
        check_for_move(1, 5),
        check_for_move(1, 7),
        check_for_move(2, 1),
    ]
    return reduce((lambda x, y: x * y), results)


def main():
    print(solve(read_input("sample.txt")))
    print(solve(read_input("input.txt")))


if __name__ == "__main__":
    main()
