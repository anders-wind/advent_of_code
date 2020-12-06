"""
day 6
"""
from typing import List, Set
from part_1 import read_input


def solve(data: List[List[bool]]):
    res = 0
    for group in data:
        answer_count = dict()
        for answers in group:
            for answer in answers:
                if answer not in answer_count:
                    answer_count[answer] = 0
                answer_count[answer] += 1
        for count in answer_count.values():
            if count == len(group):
                res += 1
    return res


def main():
    print(solve(read_input("sample.txt")))
    print(solve(read_input("input.txt")))


if __name__ == "__main__":
    main()