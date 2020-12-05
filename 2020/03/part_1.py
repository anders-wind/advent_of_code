"""
day 3
"""
from typing import List


def read_input(file_path) -> List[List[bool]]:
    res = []
    with open(file_path, 'r') as file_handle:
        for line in file_handle:
            res.append([True if x == '#' else False for x in line])
    return res


def solve(data: List[List[bool]]):
    move_hori = 3
    move_vert = 1
    pos_hori = 0
    pos_vert = 0

    # print(f"{len(data)},{len(data[0])}")

    hori_max = len(data[0])
    tree_count = 0
    while pos_vert < len(data):
        if data[pos_vert][pos_hori]:
            tree_count += 1
            # print(f"tree: {pos_vert},{pos_hori}")

        pos_hori = (pos_hori + move_hori) % (hori_max - 1)
        pos_vert += move_vert

        # print(f"{pos_vert},{pos_hori}")
    return tree_count


def main():
    print(solve(read_input("sample.txt")))
    print(solve(read_input("input.txt")))


if __name__ == "__main__":
    main()