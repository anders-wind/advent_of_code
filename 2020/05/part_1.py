"""
day 5
"""
from typing import List


def read_input(file_path):
    with open(file_path, 'r') as file_handle:
        return [line.strip() for line in file_handle.readlines()]


def solve_one(boarding_pass: str):
    num_rows = 128
    num_cols = 8

    def get_row(row_codes: str) -> int:
        min_row = 0
        max_row = num_rows
        for row_code in row_codes:
            diff = max_row - min_row
            if row_code == 'F':
                max_row = max_row - diff // 2
            else:
                min_row = min_row + diff // 2
            # print(f"({min_row}, {max_row})")
        return min_row

    def get_col(col_codes: str) -> int:
        min_col = 0
        max_col = num_cols
        for col_code in col_codes:
            diff = max_col - min_col
            if col_code == 'L':
                max_col = max_col - diff // 2
            else:
                min_col = min_col + diff // 2
            # print(f"({min_col}, {max_col})")
        return min_col

    return get_row(boarding_pass[:7]) * 8 + get_col(boarding_pass[7:])


def solve(data: List[str]):

    highest_seat = 0
    for bording_pass in data:
        highest_seat = max(solve_one(bording_pass), highest_seat)
    return highest_seat


def main():
    print(solve(read_input("sample.txt")))
    print(solve(read_input("input.txt")))


if __name__ == "__main__":
    main()