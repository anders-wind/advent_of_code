"""
day 11
"""
from copy import deepcopy
from typing import List
from part_1 import floor, empty, occupied, read_input, print_data


def sign(val):
    if val < 0:
        return -1
    if val > 0:
        return 1
    return 0


def solve(data: List[List[bool]]):

    y_limit = len(data)
    x_limit = len(data[0])

    def calc_new_state(state, pos_y, pos_x, curr_data):
        if state > floor:
            steps = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1),
                     (1, 0), (1, 1)]

            occupied_cnt = 0
            for step_y, step_x in steps:
                adj_y = pos_y + step_y
                adj_x = pos_x + step_x
                while adj_y < y_limit and adj_x < x_limit and adj_y >= 0 and adj_x >= 0:
                    if curr_data[adj_y][adj_x] > floor:
                        occupied_cnt += curr_data[adj_y][adj_x] == occupied
                        break

                    adj_y += step_y
                    adj_x += step_x

            if state == empty:
                if occupied_cnt == 0:
                    return occupied

            if state == occupied:
                if occupied_cnt >= 5:
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