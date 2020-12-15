"""
Day 15
"""
from part_1 import read_input, solve


def main():
    print(solve(read_input("sample_1.txt"), 30000000))
    # print(solve(read_input("sample_2.txt"), 30000000))
    # print(solve(read_input("sample_3.txt"), 30000000))
    # print(solve(read_input("sample_4.txt"), 30000000))
    # print(solve(read_input("sample_5.txt"), 30000000))
    # print(solve(read_input("sample_6.txt"), 30000000))
    # print(solve(read_input("sample_7.txt"), 30000000))
    print(solve(read_input("input.txt"), 30000000))


if __name__ == "__main__":
    main()