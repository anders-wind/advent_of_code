from typing import List


def read_input(file_path) -> List[int]:
    res = set({})
    with open(file_path, 'r') as file_handle:
        for line in file_handle:
            res.add(int(line))
    return res


def calculate_result(numbers: List[int]) -> int:
    for number in numbers:
        opposite = 2020 - number
        if opposite in numbers:
            return number * opposite

    raise Exception("Could not find combi")


def main():
    print(calculate_result(read_input("sample.txt")))
    print(calculate_result(read_input("input.txt")))


if __name__ == "__main__":
    main()