"""
day 6
"""
from typing import List, Set


def read_input(file_path) -> List[List[str]]:
    res = []
    with open(file_path, 'r') as file_handle:
        group_answers = []
        for line in file_handle:
            clean_line = line.strip()
            if len(clean_line) == 0:
                res.append(group_answers)
                group_answers = []
            else:
                group_answers.append([x for x in clean_line])
    res.append(group_answers)
    return res


def solve(data: List[List[bool]]):
    res = 0
    for group in data:
        set_answers = set()
        for answers in group:
            set_answers = set_answers.union(answers)
        res += len(set(set_answers))
    return res


def main():
    print(solve(read_input("sample.txt")))
    print(solve(read_input("input.txt")))


if __name__ == "__main__":
    main()