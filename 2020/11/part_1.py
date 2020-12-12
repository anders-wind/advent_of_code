"""
day 11
"""
from copy import deepcopy
from typing import List

floor = 0  # '.' floor            0
empty = 1  # 'L' empty seat       1
occupied = 2  # '#' occupied seat 2

state_to_char = [".", "L", "#"]


def read_input(file_path) -> List[List[bool]]:
    res = []
    with open(file_path, 'r') as file_handle:
        for line in file_handle:
            res.append([0 if x == '.' else 1 for x in line.strip()])
    return res


def row_to_str(row):
    return "".join([state_to_char[x] for x in row])


def print_data(to_print):
    for i, row in enumerate(to_print):
        print(row_to_str(row))
    print()


def solve(data: List[List[bool]]):
    def get_lower(pos, distance=1):
        return max(pos - distance, 0)

    def get_upper_x(pos, distance=1):
        return min(pos + distance + 1, len(data[0]))

    def get_upper_y(pos, distance=1):
        return min(pos + distance + 1, len(data))

    def print_local(pos_y, pos_x, curr_data, distance=1):
        for adj_y in range(get_lower(pos_y, distance),
                           get_upper_y(pos_y, distance)):
            row = [
                curr_data[adj_y][x] for x in range(
                    get_lower(pos_x, distance), get_upper_x(pos_x, distance))
            ]
            print(row_to_str(row))

    def calc_new_state(state, pos_y, pos_x, curr_data):
        if state > floor:
            occupied_cnt = 0
            # print(f"({pos_y},{pos_x}) {state} \t occ: {occupied_cnt}")
            for adj_y in range(get_lower(pos_y), get_upper_y(pos_y)):
                for adj_x in range(get_lower(pos_x), get_upper_x(pos_x)):
                    if adj_y == pos_y and adj_x == pos_x:
                        continue
                    # print(f"({adj_y},{adj_x})")
                    occupied_cnt += curr_data[adj_y][adj_x] == occupied

            if state == empty:
                if occupied_cnt == 0:
                    return occupied

            if state == occupied:
                if occupied_cnt >= 4:
                    return empty

        return state

    has_changed = True
    while has_changed:
        has_changed = False
        input_data = deepcopy(data)
        for y, row in enumerate(input_data):
            for x, curr_state in enumerate(row):
                new_state = calc_new_state(curr_state, y, x, input_data)
                if new_state != curr_state:
                    has_changed = True
                    data[y][x] = new_state

    count = 0
    for row in data:
        for state in row:
            count += state == occupied
    return count


def main():
    print(solve(read_input("sample.txt")))
    print(solve(read_input("input.txt")))


if __name__ == "__main__":
    main()