"""
Day 15
"""
from typing import List, Dict, Tuple


def read_input(file_path) -> List[int]:
    with open(file_path, 'r') as file_handle:
        for line in file_handle:
            return [int(x) for x in line.strip().split(",")]


def solve(data: List[int], rounds) -> int:
    # print(f"{data}")
    numbers_to_count_lastseen: Dict[int, int] = dict()
    this_number = data[0]
    for i, x in enumerate(data[1:]): 
        # print(this_number)
        numbers_to_count_lastseen[this_number] = i+1
        this_number = x
        
    for i in range(len(data), rounds):
        # print(this_number)
        if this_number not in numbers_to_count_lastseen:
            numbers_to_count_lastseen[this_number] = i
            this_number = 0
        else:
            last_time = numbers_to_count_lastseen[this_number]
            numbers_to_count_lastseen[this_number] = i
            # print(f"  {i}, {last_time}")
            this_number = i-last_time

    return this_number


def main():
    print(solve(read_input("sample_1.txt"), 10))
    print(solve(read_input("sample_1.txt"), 2020))
    print(solve(read_input("sample_2.txt"), 2020))
    print(solve(read_input("sample_3.txt"), 2020))
    print(solve(read_input("sample_4.txt"), 2020))
    print(solve(read_input("sample_5.txt"), 2020))
    print(solve(read_input("sample_6.txt"), 2020))
    print(solve(read_input("sample_7.txt"), 2020))
    print(solve(read_input("input.txt"), 2020))


if __name__ == "__main__":
    main()